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
#include "JogoDaVelha.hpp"
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
    } else if(candidato_a_comando == "?") {
        return Comando::Ajuda;
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
std::vector<Jogador>::iterator Sistema::acharJogador(std::string apelido) {
    auto acharJogador = [apelido](Jogador const& j) { return j.getApelido() == apelido; };
    auto jogador = std::find_if(this->jogadores.begin(), this->jogadores.end(), acharJogador);
    
    return jogador;
}

/**
 * \brief Cadastra um novo jogador no sistema
 *
 * Essa funcao recebe duas strings: o apelido e o nome do jogador.
 * Como o apelido deve ser unico entre todos os jogadores,
 * a funcao joga uma excessao caso exista um jogador ja cadastrado
 * com o mesmo apelido.
 * Caso contrario, a funcao cria o novo jogador dinamicamente e
 * acrescenta-o na vetor de jogadores do sistema.
 * 
 * \param apelido O apelido do possivel novo jogador.
 * \param nome O nome do possivel novo jogador.
*/
void Sistema::cadastrarJogador(std::string apelido, std::string nome) {
    auto jogador = this->acharJogador(apelido);
    bool jogador_repetido = jogador != this->jogadores.end();
    
    if(jogador_repetido) throw Excecao("jogador repetido");
    
    this->jogadores.push_back(Jogador(apelido, nome));
}

/**
 * \brief Remove um jogador existente no sistema
 *
 * Essa funcao recebe uma string representado
 * o apelido do jogador a ser removido do sistema.
 * A funcao joga uma excessao caso nao exista,
 * no sistema, um jogador cadastrado com o apelido recebido.
 * Caso contrario, a funcao limpa a area de memoria ocupada
 * pelo jogador e deleta-o do vetor do sistema.
 * 
 * \param apelido O apelido do jogador a ser removido.
*/
void Sistema::removerJogador(std::string apelido) {
    auto jogador = this->acharJogador(apelido);
    bool jogador_inexistente = jogador == this->jogadores.end();

    if(jogador_inexistente) throw Excecao("jogador inexistente");

    this->jogadores.erase(jogador);
}

/**
 * \brief Lista em ordem alfabetica os jogadores cadastrados no sistema
 *
 * Essa funcao recebe uma string, que representa o base na qual sera realizada a
 * ordenacao: A (apelido) ou N (nome); e a referencia de um std::ostream,
 * que indica onde o resultado da funcao deve ser impresso (em um arquivo,
 * para testes ou na tela, para interacao com o ususario).
 * Caso a base de ordenacao recebido seja invalido, a funcao joga uma excecao.
 * Caso contrario, a funcao ordena o vetor de jogadores do sistema e imprime as informacoes
 * de cada jogador cadastrado.
 * 
 * \param base A base de ordenacao :`A` ou `N` (apelido ou nome).
 * \param out A stream na qual as informacoes do jogador serao impressas.
 * 
*/
void Sistema::listarJogadores(std::string base, std::ostream& out) {
    auto ordenacaoPorNome = [](Jogador const& j1, Jogador const& j2) { return j1.getNome() < j2.getNome(); };
    auto ordenacaoPorApelido = [](Jogador const& j1, Jogador const& j2) { return j1.getApelido() < j2.getApelido(); };

    if(base == "A")
        std::sort(this->jogadores.begin(), this->jogadores.end(), ordenacaoPorApelido);
    else if(base == "N")
        std::sort(this->jogadores.begin(), this->jogadores.end(), ordenacaoPorNome);
    else throw Excecao("criterio de ordenacao de jogadores invalido");

    if(this->jogadores.size() == 0) {
        out << "Nao existe jogadores cadastrados no sistema." << std::endl;
        return;
    }

    for(Jogador const& jogador : this->jogadores)
        jogador.imprimirInformacoes(out);
}

/**
 * \brief Executa uma partida entre dois jogadores cadastrados no sistema
 *
 * Essa funcao recebe tres strings e referencia a duas streams.
 * As strings representam, respectivamente, o nome do jogo e o apelido (identificador
 * unico) dos dois jogadores, que participarao da partida.
 * As streams indicam de onde a entrada deve ser lida, e aonde ela deve ser impressa
 * (em arquivos, para testes, ou na tela, para usufruto do usuario).
 * Primeiro, a funcao checa se os jogadores existem e joga uma excecao caso nao existam.
 * Entao, a funcao da inicio no event-loop do jogo: obtem a entrada a partir do `std::istream&`
 * recebido por parametro; e imprime o tabuleiro e as outras informacoes do fluxo da partida.
 * Os jogadores, entao, disputam a partida e, no final, a funcao imprime o resultado do jogo.
 * 
 * \param nome_do_jogo O nome de um jogo implementado no sistema.
 * \param apelido1 O apelido do primeiro jogador.
 * \param apelido2 O apelido do segundo jogador.
 * \param in Onde pegar a entrada para o jogo.
 * \param out Onde imprimir a saida do jogo.
 * 
*/
void Sistema::executarPartida(std::string nome_do_jogo, std::string apelido1, std::string apelido2, std::istream& in, std::ostream& out) {
    auto jogador1 = this->acharJogador(apelido1);
    auto jogador2 = this->acharJogador(apelido2);

    bool jogador1_existe = jogador1 != this->jogadores.end();
    bool jogador2_existe = jogador2 != this->jogadores.end();

    if(!jogador1_existe || !jogador2_existe) throw Excecao("jogador nao existe");

    std::unique_ptr<Jogo> jogo;
    if (nome_do_jogo == "Lig4") {
        jogo.reset(new Lig4(6, 7, *jogador1, *jogador2));
    } else if (nome_do_jogo == "Reversi") {
        jogo.reset(new Reversi(8, 8, *jogador1, *jogador2));
    } else if (nome_do_jogo == "JogoDaVelha") {
        jogo.reset(new JogoDaVelha(*jogador1, *jogador2));
    } else if (nome_do_jogo == "Xadrez") {
        jogo.reset(new Xadrez(*jogador1, *jogador2));
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

    if (Jogador const *vencedor = jogo->getVencedor()) {
        out << "Jogador " << vencedor->getApelido() << " foi o vencedor!\n";
    } else {
        out << "Empate!\n";
    }
}

/**
 * \brief Le e carrega, para o sistema, os dados salvos no disco
 *
 * Essa funcao carrega os dados salvos em disco para o sistema.
 * Esses dados consistem em uma lista de jogadores, com apelido, nome,
 * e informacoes de vitorias, derrotas e empates daquele jogador em cada jogo.
 * Caso o arquivo de banco de dados nao exista, a funcao joga uma excecao.
*/
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

        Jogador jogador(apelido, nome);

        int numjogos;
        arquivo >> numjogos;
        for(int j = 0; j < numjogos; j++) {
            std::string jogo;
            int vitorias, derrotas, empates;

            arquivo >> jogo >> vitorias >> derrotas >> empates;
            jogador.setResultados(jogo, Resultados(vitorias, derrotas, empates));
        }

        this->jogadores.push_back(jogador);
    }

    arquivo.close();
}

/**
 * \brief Salva, no disco, os dados de jogadores do sistema
 *
 * Essa funcao salva, no disco, os dados dos jogadores no sistema.
 * A padronizacao do arquivo segue o mesmo padrao definido pela funcao
 * `Sistema::carregarArquivo()`. Caso o arquivo de banco de dados nao exista,
 * essa funcao tambem joga uma excecao.
*/
void Sistema::salvarSistema() {
    std::ofstream arquivo(this->banco_de_dados);
    arquivo << this->jogadores.size() << "\n";

    for(Jogador const& jogador : this->jogadores) {
        arquivo << jogador.getApelido() << "\n";
        arquivo << jogador.getNome() << "\n";

        int njogos = jogador.getNumeroDeJogos();
        arquivo << njogos << "\n";
        if(njogos == 0) continue;

        for(std::string jogo : jogador.getJogosCadastrados()) {
            auto resultados = jogador.getResultados(jogo);
            arquivo << jogo << " ";
            arquivo << resultados.vitorias << " ";
            arquivo << resultados.derrotas << " ";
            arquivo << resultados.empates << "\n";
        }
    }

    arquivo.close();
}

/**
 * \brief Finaliza o sistema, definindo correatamente a flag interna
 *
 * Essa funcao finaliza o sistema, definindo a flag de `sistema_finalizado`,
 * e chamando a funcao `Sistema::salvarSistema()` (caso necessario);
 * por fim, ela limpa os dados salvos em memoria do sistema.
*/
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

/**
 * \brief Limpa os dados do sistema salvos em memoria
 *
 * Essa funcao percorre o vetor de jogadores do sistema, deletando
 * cada objeto. Alem disso, ela limpa todos os slots do vetor,
 * zerando seu `vector<Jogador*>::size()`.
*/
void Sistema::limparSistema() {
    this->jogadores.clear();
}

/**
 * \brief Constroi o sistema
 *
 * Essa funcao pega, como parametro, uma string e um booleano.
 * A string indica o caminho (relativo ou absoluto) para o arquivo
 * de banco de dados do sistema. O booleano indica se deve-se ou
 * nao salvar as modificacoes do banco de dados ao finalizar o sistema.
 * A funcao checa pela existencia do arquivo de banco de dados.
 * A nao existencia dele implica tambem a nao existencia de jogadores cadastrados
 * previamente. Nesse caso, a funcao cria um novo arquivo e imprime o inteiro "0"
 * dentro dele - indicando que ha zero jogadores.
 * Caso contrario, a funcao carrega o arquivo para o sistema por meio de
 * `Sistema::carregarArquivo()`.
*/
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
