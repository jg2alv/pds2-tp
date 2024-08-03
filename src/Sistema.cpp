#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <memory>

#include "Sistema.hpp"
#include "Excecao.hpp"
#include "Lig4.hpp"
#include "Reversi.hpp"
#include "Xadrez.hpp"

/**
 * \brief Analisa um comando da entrada
 *
 * Essa funcao recebe uma string da entrada, representando um comando,
 * analisa-o e retorna o campo de um Enum que simboliza o comando recebido.
 * Caso o comando seja invalido, joga uma Excecao de comando invalido.
 * 
 * \param candidato_a_comando A string da entrada.
 * \return O campo do enum Comando.
 */
Comando identificar_comando(std::string candidato_a_comando) {
    if (candidato_a_comando == "CJ") {
        return Comando::CadastrarJogador;
    } else if (candidato_a_comando == "RJ") {
        return Comando::RemoverJogador;
    } else if (candidato_a_comando == "LJ") {
        return Comando::ListarJogadores;
    } else if (candidato_a_comando == "EP") {
        return Comando::ExecutarPartida;
    } else if (candidato_a_comando == "FS") {
        return Comando::FinalizarSistema;
    } else {
        throw Excecao("comando invalido");
    }
}

/**
 * \brief Checa se o sistema finalizou
 *
 * Essa funcao retorna uma flag interna do sistema,
 * que indica se o sistema foi encerrado.
 * 
 * \return O booleano que representa se o sistema foi ou nao encerrado.
*/
bool Sistema::isSistemaFinalizado() {
    return this->sistema_finalizado;
}

/**
 * \brief Procura e retorna um jogador com base em seu apelido
 *
 * Essa funcao recebe o apelido de um jogador e retorna um iterador
 * do vetor interno do sistema que armazena os jogadores cadastrados.
 * Caso o jogador nao seja encontrado, retorna vector<Jogador*>::end().
 * 
 * \param apelido O apelido do jogador a ser encontrado.
 * \return O iterador que aponta para o jogador.
*/
std::vector<Jogador *>::iterator Sistema::acharJogador(std::string apelido) {
    auto acharJogador = [apelido](Jogador* j) { return j->getApelido() == apelido; };
    auto jogador = std::find_if(this->jogadores.begin(), this->jogadores.end(), acharJogador);
    
    return jogador;
}

void Sistema::cadastrarJogador(std::string apelido, std::string nome) {
    auto jogador = this->acharJogador(apelido);
    bool jogador_repetido = jogador != this->jogadores.end();
    
    if(jogador_repetido) throw Excecao("jogador repetido");
    
    Jogador* novo_jogador = new Jogador(apelido, nome);
    this->jogadores.push_back(novo_jogador);
}

void Sistema::removerJogador(std::string apelido) {
    auto jogador = this->acharJogador(apelido);
    bool jogador_inexistente = jogador == this->jogadores.end();

    if(jogador_inexistente) throw Excecao("jogador inexistente");

    delete *jogador;
    this->jogadores.erase(jogador);
}

void Sistema::listarJogadores(std::string base, std::ostream& out) {
    auto ordenacaoPorNome = [](Jogador* j1, Jogador* j2) { return j1->getNome() < j2->getNome(); };
    auto ordenacaoPorApelido = [](Jogador* j1, Jogador* j2) { return j1->getApelido() < j2->getApelido(); };

    if(base == "A")
        std::sort(this->jogadores.begin(), this->jogadores.end(), ordenacaoPorApelido);
    else if(base == "N")
        std::sort(this->jogadores.begin(), this->jogadores.end(), ordenacaoPorNome);
    else throw Excecao("criterio de ordenacao de jogadores invalido");

    for(Jogador* jogador : this->jogadores)
        jogador->imprimirInformacoes(out);
}

void Sistema::executarPartida(std::string nome_do_jogo, std::string apelido1, std::string apelido2, std::istream& in, std::ostream& out) {
    auto jogador1 = this->acharJogador(apelido1);
    auto jogador2 = this->acharJogador(apelido2);

    bool jogador1_existe = jogador1 != this->jogadores.end();
    bool jogador2_existe = jogador2 != this->jogadores.end();

    if(!jogador1_existe || !jogador2_existe) throw Excecao("jogador nao existe");

    std::unique_ptr<Jogo> jogo;
    if (nome_do_jogo == "Lig4") {
        jogo.reset(new Lig4(6, 7, **jogador1, **jogador2));
    } else if (nome_do_jogo == "Reversi") {
        jogo.reset(new Reversi(8, 8, **jogador1, **jogador2));
    } else if (nome_do_jogo == "Xadrez") {
        jogo.reset(new Xadrez(**jogador1, **jogador2));
    } else {
        throw Excecao("jogo nao existe");
    }

    jogo->imprimirTabuleiro(out);
    while (!jogo->fimDeJogo()) {
        try {
            out << "Turno do jogador " << jogo->getJogadorDaVez()->getApelido() << ": ";

            std::string possivel_jogada;
            std::getline(in, possivel_jogada);

            std::stringstream jogada_stream(possivel_jogada);
            std::string comando;
            jogada_stream >> comando;
            if (comando == "desisto") {
                jogo->efetuarDesistencia();
                break;
            } else {
                jogo->realizarJogada(possivel_jogada);
            }

            jogo->imprimirTabuleiro(out);
        } catch (std::exception const& e) {
            out << "ERRO: " << e.what() << std::endl;
        }
    }

    jogo->finalizarJogo();

    if (Jogador *vencedor = jogo->getVencedor()) {
        out << "Jogador " << vencedor->getApelido() << " foi o vencedor!\n";
    } else {
        out << "Empate!\n";
    }
}

void Sistema::carregarArquivo() {
    std::ifstream arquivo(this->banco_de_dados);
    bool arquivo_existe = arquivo.good();
    if(!arquivo_existe) throw Excecao("falha na abertura do arquivo");

    int numjogadores;
    arquivo >> numjogadores;

    for(int i = 0; i < numjogadores; i++) {
        std::string apelido, nome;
        arquivo >> apelido;
        arquivo.ignore();
        std::getline(arquivo, nome);
        Jogador* jogador = new Jogador(apelido, nome);

        int numjogos;
        arquivo >> numjogos;
        for(int j = 0; j < numjogos; j++) {
            std::string jogo;
            int vitorias, derrotas, empates;

            arquivo >> jogo >> vitorias >> derrotas >> empates;
            jogador->setResultados(jogo, Resultados(vitorias, derrotas, empates));
        }

        this->jogadores.push_back(jogador);
    }

    arquivo.close();
}

void Sistema::salvarSistema() {
    std::ofstream arquivo(this->banco_de_dados);
    arquivo << this->jogadores.size() << "\n";

    for(Jogador* jogador: this->jogadores) {
        arquivo << jogador->getApelido() << "\n";
        arquivo << jogador->getNome() << "\n";

        int njogos = jogador->getNumeroDeJogos();
        arquivo << njogos << "\n";
        if(njogos == 0) continue;

        for(std::string jogo : jogador->getJogosCadastrados()) {
            auto resultados = jogador->getResultados(jogo);
            arquivo << jogo << " ";
            arquivo << resultados.vitorias << " ";
            arquivo << resultados.derrotas << " ";
            arquivo << resultados.empates << "\n";
        }
    }

    arquivo.close();
}

void Sistema::finalizarSistema() {
    if (this->sistema_finalizado) {
        return;
    }

    this->sistema_finalizado = true;

    if (salvar_ao_sair) {
        this->salvarSistema();
    }

    this->limparSistema();
}

void Sistema::limparSistema() {
    for (Jogador *jogador : this->jogadores) {
        delete jogador;
    }

    this->jogadores.clear();
}

Sistema::Sistema(std::string banco_de_dados, bool salvar_ao_sair) :
    banco_de_dados(banco_de_dados),
    salvar_ao_sair(salvar_ao_sair) {
    std::ifstream arquivo(this->banco_de_dados);
    bool arquivo_existe = arquivo.good();
    arquivo.close();
    
    if(!arquivo_existe) {
        std::ofstream arquivo(this->banco_de_dados);
        arquivo << "0";
        arquivo.close();
    }

    this->carregarArquivo();
}

Sistema::~Sistema() {
    this->finalizarSistema();
}
