#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <memory>

#include "Sistema.hpp"
#include "Excecao.hpp"
#include "Lig4.hpp"
#include "Reversi.hpp"

bool Sistema::isSistemaFinalizado() { return this->__sistema_finalizado; }

Comando Sistema::analisarComando(std::string comando) {
    if (comando == "CJ") return Comando::CadastrarJogador;
    else if (comando == "RJ") return Comando::RemoverJogador;
    else if (comando == "LJ") return Comando::ListarJogadores;
    else if (comando == "EP") return Comando::ExecutarPartida;
    else if (comando == "FS") return Comando::FinalizarSistema;
    else throw Excecao("comando invalido");
}

std::vector<Jogador *>::iterator Sistema::acharJogador(std::string apelido) {
    auto acharJogador = [apelido](Jogador* j) { return j->getApelido() == apelido; };
    auto jogador = std::find_if(this->__jogadores.begin(), this->__jogadores.end(), acharJogador);
    
    return jogador;
}

void Sistema::cadastrarJogador(std::string apelido, std::string nome) {
    auto jogador = this->acharJogador(apelido);
    bool jogador_repetido = jogador != this->__jogadores.end();
    
    if(jogador_repetido) throw Excecao("jogador repetido");
    
    Jogador* novo_jogador = new Jogador(apelido, nome);
    this->__jogadores.push_back(novo_jogador);

    this->__out << "Jogador " << apelido << " cadastrado com sucesso" << std::endl;
}

void Sistema::removerJogador(std::string apelido) {
    auto jogador = this->acharJogador(apelido);
    bool jogador_inexistente = jogador == this->__jogadores.end();

    if(jogador_inexistente) throw Excecao("jogador inexistente");

    delete *jogador;

    this->__jogadores.erase(jogador);

    this->__out << "Jogador " << apelido << " removido com sucesso" << std::endl;
}

void Sistema::listarJogadores(std::string criterio) {
    auto ordenacaoPorNome = [](Jogador* j1, Jogador* j2) { return j1->getNome() < j2->getNome(); };
    auto ordenacaoPorApelido = [](Jogador* j1, Jogador* j2) { return j1->getApelido() < j2->getApelido(); };

    if(criterio == "A")
        std::sort(this->__jogadores.begin(), this->__jogadores.end(), ordenacaoPorApelido);
    else if(criterio == "N")
        std::sort(this->__jogadores.begin(), this->__jogadores.end(), ordenacaoPorNome);
    else throw Excecao("criterio de ordenacao de jogadores invalido");

    int tam = this->__jogadores.size();
    for(int i = 0; i < tam; i++) {
        this->__jogadores[i]->imprimirInformacoes(this->__out);
    }
}

void Sistema::executarPartida(std::string nome_do_jogo) {
    std::string apelido1, apelido2;
    this->__in >> apelido1 >> apelido2;

    auto jogador1 = this->acharJogador(apelido1);
    auto jogador2 = this->acharJogador(apelido2);

    bool jogador1_existe = jogador1 != this->__jogadores.end();
    bool jogador2_existe = jogador2 != this->__jogadores.end();

    if(!jogador1_existe || !jogador2_existe) throw Excecao("jogador nao existe");

    std::unique_ptr<Jogo> jogo;
    if (nome_do_jogo == "Lig4") {
        jogo.reset(new Lig4(6, 7, **jogador1, **jogador2));
    } else if (nome_do_jogo == "Reversi") {
        jogo.reset(new Reversi(8, 8, **jogador1, **jogador2));
    } else {

    }
    this->__in.ignore();
    jogo->partida();
}

void Sistema::executarComando(Comando comando_analisado) {
    switch (comando_analisado) {
        case Comando::CadastrarJogador: {
            std::string apelido, nome, saida;
            this->__in >> apelido;
            std::getline(this->__in, nome);
            this->cadastrarJogador(apelido, nome.erase(0, 1));
            break;
        }
        
        case Comando::RemoverJogador: {
            std::string apelido, saida;
            this->__in >> apelido;
            this->removerJogador(apelido);
            break;
        }

        case Comando::ListarJogadores: {
            std::string criterio, saida;
            this->__in >> criterio;
            this->listarJogadores(criterio);
            break;
        }

        case Comando::ExecutarPartida: {
            std::string jogo, apelido1, apelido2;
            this->__in >> jogo;
            this->executarPartida(jogo);
            break;
        }

        case Comando::FinalizarSistema: {
            this->__sistema_finalizado = true;
            break;
        }

        default: {
            throw Excecao("comando invalido");
        }
    }
}

void Sistema::carregarArquivo() {
    std::ifstream arquivo(this->__bancodedados);
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
            jogador->adicionarResultados(jogo, Resultados(vitorias, derrotas, empates));
        }

        this->__jogadores.push_back(jogador);
    }

    arquivo.close();
}

void Sistema::salvarSistema() {
    std::ofstream arquivo(this->__bancodedados);
    int njogadores = this->__jogadores.size();
    arquivo << njogadores << "\n";

    for(int i = 0; i < njogadores; i++) {
        Jogador* jogador = this->__jogadores[i];
        arquivo << jogador->getApelido() << "\n";
        arquivo << jogador->getNome() << "\n";

        int njogos = jogador->getNumeroDeJogos();
        arquivo << njogos << "\n";

        if(njogos == 0) continue;

        std::vector<std::string> jogos = jogador->getJogosCadastrados();
        for(int j = 0; j < njogos; j++) {
            auto resultados = jogador->getResultados(jogos[j]);
            arquivo << jogos[j] << " ";
            arquivo << resultados.vitorias << " ";
            arquivo << resultados.derrotas << " ";
            arquivo << resultados.empates << "\n";
        }
    }

    arquivo.close();
}

void Sistema::limparSistema() {
    for (Jogador *jogador : __jogadores) {
        delete jogador;
    }

    this->__jogadores.clear();
}

Sistema::Sistema(std::istream& in, std::ostream& out, std::string bancodedados, bool salvar_ao_sair) :
    __in(in),
    __out(out),
    __bancodedados(bancodedados),
    salvar_ao_sair(salvar_ao_sair) {
    std::ifstream arquivo(this->__bancodedados);
    bool arquivo_existe = arquivo.good();
    arquivo.close();
    
    if(!arquivo_existe) {
        std::ofstream arquivo(this->__bancodedados);
        arquivo << "0";
        arquivo.close();
    }

    this->carregarArquivo();
}

Sistema::~Sistema() {
    if (salvar_ao_sair) {
        this->salvarSistema();
    }

    this->limparSistema();
}
