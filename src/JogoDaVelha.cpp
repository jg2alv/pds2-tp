#include <vector>
#include <string>
#include <sstream>

#include "JogoDaVelha.hpp"
#include "Excecao.hpp"
#include "Jogada.hpp"
#include "Jogador.hpp"
#include "Jogo.hpp"

/**
 * \brief Construtor da classe JogoDaVelha
 * 
 * Construtor da classe JogoDaVelha, que inicializa os jogadores 
 * da partida, a linha e a coluna com tamanho 3, chamando o
 * construtor da classe Jogo.
 * 
 * \param jogador1 Primeiro jogador.
 * \param jogador2 Segundo jogador.
 */
JogoDaVelha::JogoDaVelha(Jogador &jogador1, Jogador &jogador2) :
    Jogo(3, 3, jogador1, jogador2) {}

/**
 * \brief Construtor da classe JogoDaVelha
 * 
 * Construtor da classe JogoDaVelha, que inicializa os jogadores 
 * da partida, a linha e a coluna com tamanho 3, e o tabuleiro
 * chamando o construtor da classe Jogo.
 * 
 * \param jogador1 Primeiro jogador.
 * \param jogador2 Segundo jogador.
 * \param tabuleiro O tabuleiro do jogo.
 */
JogoDaVelha::JogoDaVelha(Jogador &jogador1, Jogador &jogador2, std::vector<std::vector<char>> tabuleiro) :
    Jogo(3, 3, jogador1, jogador2, tabuleiro) {}

/**
 * \brief Destrutor da classe JogoDaVelha
 * 
 * Destrutor da classe JogoDaVelha. Como nao tem nenhum atributo
 * alocado dinamicamente, nao é preciso desalocar nenhuma
 * memoria manualmente.
 */
JogoDaVelha::~JogoDaVelha() {}

/**
 * \brief Retorna uma string do nome do jogo
 *
 * Essa funcao retorna o nome do jogo, no caso 'JogoDaVelha'.
 * 
 * \return Uma string "JogoDaVelha".
 */
std::string JogoDaVelha::getNome() const {
    return "JogoDaVelha";
}

/**
 * \brief Imprime o tabuleiro do jogo
 *
 * Essa funcao recebe um stream de saida e imprime, nesse
 * stream, o tabuleiro do jogo, com uma cabeçalho escrito
 * 'Jogo da Velha' e indicando os indices de cada linha e
 * coluna.
 * 
 * \param out Um stream de saida.
 */
void JogoDaVelha::imprimirTabuleiro(std::ostream& out) const {
    out << "--Jogo da Velha--\n    ";

    for (int i = 1; i <= 3; i++) {
        out << " " << i << " ";
    }
    out << std::endl;
  
    for (int i = 0; i < 3; i++) {
        out << "  " << i + 1 << " ";
        for (int j = 0; j < 3; j++) {
            out << "|" << get_char(i, j) << "|";
    }
        out << std::endl;
  }
}

/**
 * \brief Analisa o formato da entrada recebida
 *
 * Essa funcao recebe como parametro uma string da entrada lida 
 * e analisa se existe exatamente dois numeros na entrada.
 * Se isso for atendido, a funcao retorna verdadeiro.
 * Caso contrario, retorna falso.
 * 
 * \param possivel_jogada A string da entrada.
 * \return True ou false.
 */
bool JogoDaVelha::formatoCorreto(std::string possivel_jogada) const {
    std::stringstream jogada_stream(possivel_jogada);
    int linha, coluna;
    std::string extra;

    if (!(jogada_stream >> linha)) {
        return false;
    }

    if (!(jogada_stream >> coluna)) {
        return false;
    }

    return !(jogada_stream >> extra);
}

/**
 * \brief Verifica se a jogada é valida
 *
 * Essa funcao recebe como parametro uma jogada e verifica se
 * a posicao dessa jogada está vazia no tabuleiro. Se não estiver
 * vazia, é retornado falso. Caso contrario, é verificado se a 
 * coluna e a linha dessa jogada estao dentro dos limites do 
 * tabuleiro. Se isso for atendido, retorna verdadeiro. Caso
 * contrário, retorna falso.
 * 
 * \param jogada Uma jogada lida.
 * \return True ou false.
 */
bool JogoDaVelha::jogada_valida(const Jogada &jogada) const {
    int linha = jogada.get_linha();
    int coluna = jogada.get_coluna();

    if (get_char(linha, coluna) != ' ') return false;
    else return ((linha >= 0 && linha < this->linhas) && (coluna >= 0 && coluna < this->colunas));
}

/**
 * \brief Verifica se a jogada é valida
 *
 * Essa funcao recebe como parametro uma string de uma possivel
 * jogada. A funcao verifica se é fim de jogo e retorna falso se
 * for fim de jogo, pois nao tem mais jogadas. Tambem verifica se 
 * o formato da possivel jogada esta correto e lanca uma excecao 
 * caso nao tenha formato correto. Por fim, é criada uma jogada 
 * com a linha e coluna lida da entrada e chamada a funcao 
 * 'jogada_valida', retornando verdadeiro se a jogada for valida 
 * ou falso, caso contrario.
 * 
 * \param possivel_jogada Uma string com a entrada lida.
 * \return True ou false.
 */
bool JogoDaVelha::jogadaValida(std::string possivel_jogada) const {
    if (fimDeJogo()) {
        return false;
    }

    if (!formatoCorreto(possivel_jogada)) {
        throw Excecao("formato incorreto");
    }

    std::stringstream in;
    in.str(possivel_jogada);
    
    int linha, coluna;
    in >> linha >> coluna;
    linha--, coluna--;

    Jogada jogada(linha, coluna);
    return jogada_valida(jogada);
}

/**
 * \brief Coloca um simbolo no tabuleiro
 *
 * Essa funcao recebe como parametro uma jogada e coloca no tabuleiro, 
 * na posiçao da linha e da coluna dessa jogada, o simbolo do jogador 
 * da vez.
 * 
 * \param jogada Uma jogada lida.
 */
void JogoDaVelha::realizar_jogada(const Jogada &jogada) {
    set_char(jogada.get_linha(), jogada.get_coluna(), get_simbolo(*jogador_da_vez));
}

/**
 * \brief Realiza uma jogada
 *
 * Essa funcao recebe como parametro uma string de uma possivel
 * jogada. A funcao verifica se é fim de jogo e lanca uma excecao
 * se for fim de jogo. Tambem verifica se o formato da possivel 
 * jogada esta correto e lanca uma excecao caso nao tenha formato
 * correto. É criada uma jogada com a linha e coluna lida da entrada 
 * e verificado se a jogada é valida e, caso não seja, é lançada uma
 * exceçao. Se nao for fim de jogo, o formato for correto e a jogada
 * for valida, entao é realizada a jogada e é trocado o jogador da vez.
 * 
 * \param possivel_jogada Uma string com a entrada lida.
 */
void JogoDaVelha::realizarJogada(std::string possivel_jogada) {
    if (fimDeJogo()) {
        throw Excecao("jogo ja acabou");
    }

    if (!formatoCorreto(possivel_jogada)) {
        throw Excecao("formato incorreto");
    }

    std::stringstream in;
    in.str(possivel_jogada);
    
    int linha, coluna;
    in >> linha >> coluna;
    linha --, coluna--;

    Jogada jogada(linha, coluna);
    if (!jogada_valida(jogada)) {
        throw Excecao("jogada invalida");
    }

    realizar_jogada(jogada);
    passar_a_vez();
}

/**
 * \brief Verifica a vitoria de um jogador
 *
 * Essa funcao recebe como parametro um jogador e verifica se
 * esse jogador tem tres pecas adjacentes no tabuleiro. É 
 * verificada cada linha, cada coluna e cada diagonal (nos dois
 * sentidos). Caso encontre tres simbolos do jogador em algum
 * desses casos, retorna verdadeiro. Caso contrario, retorna falso.
 * 
 * \param jogador Um jogador da partida.
 * \return True ou false.
 */
bool JogoDaVelha::verificarVitoria(Jogador const& jogador) const {
    char simbolo = get_simbolo(jogador);
    int qntd = 0;

    for (int i = 0; i < this->linhas; i++) {
        qntd = 0;

        for (int j = 0; j < this->colunas; j++) {
            if (get_char(i, j) == ' ') break;
            if (get_char(i, j) == simbolo) qntd++;
        }

        if (qntd == 3) return true;
    }

    for (int j = 0; j < this->colunas; j++) {
        qntd = 0;
        
        for (int i = 0; i < this->linhas; i++) {
            if (get_char(i, j) == ' ') break;
            if (get_char(i, j) == simbolo) qntd++;
        }

        if (qntd == 3) return true;
    }

    qntd = 0;
    for (int i = 0; i < this->linhas; i++) {
        if (get_char(i, i) == ' ') break;
        if (get_char(i, i) == simbolo) qntd++;
    }
    if (qntd == 3) return true;

    qntd = 0;
    for (int i = 0; i < this->linhas; i++) {
        int j = 2 - i;
        if (get_char(i, j) == ' ') break;
        if (get_char(i, j) == simbolo) qntd++;
    }
    if (qntd == 3) return true;

    return false;
}

/**
 * \brief Verifica se o tabuleiro esta cheio
 *
 * Essa funcao verifica se todas as posicoes do tabuleiro
 * estao cheias. Caso isso seja atendido, é retornado 
 * verdadeiro e, caso contrario, é retornado falso.
 * 
 * \return True ou false.
 */
bool JogoDaVelha::tabuleiroCheio() const {
    for (int i = 0; i < this->linhas; i++) {
        for (int j = 0; j < this->colunas; j++) {
            if (get_char(i, j) == ' ') 
                return false;
        }
    }

    return true;
}

/**
 * \brief Verifica o empate do jogo
 *
 * Essa funcao verifica se houve um empate retornando
 * a funcao 'tabuleiroCheio'. Caso o tabuleiro esteja 
 * cheio, houve empate e retorna verdadeiro. Caso 
 * contrario, nao houve empate e retorna falso.
 * 
 * \return True ou false.
 */
bool JogoDaVelha::verificarEmpate() const {
    return tabuleiroCheio();
}