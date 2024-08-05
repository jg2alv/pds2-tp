#include <vector>
#include <string>
#include <sstream>

#include "Lig4.hpp"
#include "Excecao.hpp"
#include "Jogada.hpp"
#include "Jogador.hpp"
#include "Jogo.hpp"

using namespace std;

/**
 * \brief Construtor da classe Lig4
 * 
 * Construtor da classe Lig4, que inicializa a quantidade de 
 * linhas e colunas do tabuleiro e os jogadores da partida,
 * chamando o construtor da classe Jogo.
 * 
 * \param linhas Quantidade de linhas.
 * \param colunas Quantidade de colunas.
 * \param jogador1 Primeiro jogador.
 * \param jogador2 Segundo jogador.
 */

Lig4::Lig4(int linhas, int colunas, Jogador &jogador1, Jogador &jogador2) :
    Jogo(linhas, colunas, jogador1, jogador2) {}

/**
 * \brief Construtor da classe Lig4
 * 
 * Construtor da classe Lig4, que inicializa a quantidade de 
 * linhas e colunas do tabuleiro, os jogadores da partida e
 * o tabuleiro, chamando o construtor da classe Jogo.
 * 
 * \param linhas Quantidade de linhas.
 * \param colunas Quantidade de colunas.
 * \param jogador1 Primeiro jogador.
 * \param jogador2 Segundo jogador.
 * \param tabuleiro O tabuleiro do jogo.
 */
Lig4::Lig4(int linhas, int colunas, Jogador &jogador1, Jogador &jogador2, vector<vector<char>> tabuleiro) :
    Jogo(linhas,colunas, jogador1, jogador2, tabuleiro) {}

/**
 * \brief Destrutor da classe Lig4
 * 
 * Destrutor da classe Lig4. Como nao tem nenhum atributo
 * alocado dinamicamente, nao é preciso desalocar nenhuma
 * memoria manualmente.
 */
Lig4::~Lig4() {}

/**
 * \brief Retorna uma string do nome do jogo
 *
 * Essa funcao retorna o nome do jogo, no caso "Lig4".
 * 
 * \return Uma string "Lig4".
 */
string Lig4::getNome() const {
    return "Lig4";
}

/**
 * \brief Imprime o tabuleiro do jogo
 *
 * Essa funcao recebe um stream de saida e imprime, nesse
 * stream, o tabuleiro do jogo, com uma cabeçalho escrito
 * "Lig4" e indicando os indices de cada coluna.
 * 
 * \param out Um stream de saida.
 */
void Lig4::imprimirTabuleiro(ostream& out) const {
    out << "---------Lig4--------\n";
    
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            cout << "|" << get_char(i, j) << "|";
        }
        out << endl;
    }

    for (int i = 1; i <= colunas; i++) {
        out << " " << i << " ";
    }

    out << endl;
}

/**
 * \brief Analisa o formato da entrada recebida
 *
 * Essa funcao recebe como parametro uma string da entrada lida 
 * e analisa se existe exatamente um numero na entrada.
 * Se isso for atendido, a funcao retorna verdadeiro.
 * Caso contrario, retorna falso.
 * 
 * \param possivel_jogada A string da entrada.
 * \return true ou false
 */
bool Lig4::formatoCorreto(string possivel_jogada) const {
    stringstream jogada_stream(possivel_jogada);
    int coluna;
    string extra;

    if (!(jogada_stream >> coluna)) {
        return false;
    }

    return !(jogada_stream >> extra);
}

/**
 * \brief Encontra a primeira linha vazia de uma coluna
 *
 * Essa funcao recebe como parametro o numero de uma coluna,
 * percorre as posições dessa coluna do tabuleiro e retorna
 * o indice da linha da primeira posiçao vazia. Caso nenhuma
 * linha esteja vazia, a funcao retorna -1.
 * 
 * \param coluna Uma coluna do tabuleiro.
 * \return O indice da primeira linha vazia.
 */
int Lig4::get_linha_tabuleiro(int coluna) const {
    int i = linhas - 1;
    for (; i >= 0; i--) {
        if (get_char(i, coluna) == ' ') 
            break;
    }
    return i;
}

/**
 * \brief Verifica se a jogada é valida
 *
 * Essa funcao recebe como parametro uma jogada e verifica
 * se a coluna esta dentro dos limites do tabuleiro. Se isso 
 * for atendido, é mudada a linha da jogada com a funcao 
 * 'get_linha_tabuleiro' e entao e verificado o valor da linha.
 * Se for diferente de -1, ou seja, a coluna nao esta cheia,
 * retorna verdadeiro e, caso contrario, retorna falso.
 * 
 * \param jogada Uma jogada lida.
 * \return true ou false
 */
bool Lig4::jogada_valida(Jogada &jogada) const {
    int coluna = jogada.get_coluna();

    if (!(coluna >= 0 && coluna < colunas))
        return false;

    else {
        int linha = get_linha_tabuleiro(coluna);
        jogada.set_linha(linha);
        return (linha != -1);
    }
}

/**
 * \brief Verifica se a jogada é valida
 *
 * Essa funcao recebe como parametro uma string de uma possivel
 * jogada. A funcao verifica se é fim de jogo e retorna falso se
 * for fim de jogo, pois nao tem mais jogadas. Tambem verifica se 
 * o formato da possivel jogada esta correto e lanca uma excecao 
 * caso nao tenha formato correto. Por fim, é criada uma jogada 
 * com a coluna lida da entrada e chamada a funcao 'jogada_valida', 
 * retornando verdadeiro se a jogada for valida ou falso, caso 
 * contrario.
 * 
 * \param possivel_jogada Uma string com a entrada lida.
 * \return true ou false
 */
bool Lig4::jogadaValida(string possivel_jogada) const {
    if (fimDeJogo()) {
        return false;
    }

    if (!formatoCorreto(possivel_jogada)) {
        throw Excecao("formato incorreto (formato correto: [coluna])");
    }

    stringstream in;
    in.str(possivel_jogada);
    
    int coluna;
    in >> coluna;
    coluna--;

    Jogada jogada(coluna);
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
void Lig4::realizar_jogada(const Jogada &jogada) {
    set_char(jogada.get_linha(), jogada.get_coluna(), get_simbolo(*jogador_da_vez));
}

/**
 * \brief Realiza uma jogada
 *
 * Essa funcao recebe como parametro uma string de uma possivel
 * jogada. A funcao verifica se é fim de jogo e lanca uma excecao
 * se for fim de jogo. Tambem verifica se o formato da possivel 
 * jogada esta correto e lanca uma excecao caso nao tenha formato
 * correto. É criada uma jogada com a coluna lida da entrada e 
 * verificado se a jogada é valida e, caso não seja, é lançada uma
 * exceçao. Se nao for fim de jogo, o formato for correto e a jogada
 * for valida, entao é realizada a jogada e é trocado o jogador da vez.
 * 
 * \param possivel_jogada Uma string com a entrada lida.
 */
void Lig4::realizarJogada(string possivel_jogada) {
    if (fimDeJogo()) throw Excecao("jogo ja acabou");
    if (!formatoCorreto(possivel_jogada)) throw Excecao("formato incorreto (formato correto: [coluna])");
    

    stringstream in;
    in.str(possivel_jogada);
    
    int coluna;
    in >> coluna;
    coluna--;

    Jogada jogada(coluna);
    if (!jogada_valida(jogada)) throw Excecao("jogada invalida (coluna informada esta cheia ou esta fora dos limites do tabuleiro)");
    

    realizar_jogada(jogada);
    passar_a_vez();
}

/**
 * \brief Verifica se uma linha do tabuleiro esta vazia
 *
 * Essa funcao recebe como parametro uma linha e verifica se
 * todas as posicoes do tabuleiro que estao nessa linha estão 
 * vazias. Caso todas estejam vazias, retorna verdadeiro, se
 * nao, retorna falso.
 * 
 * \param linha Uma linha do tabuleiro.
 * \return true ou false
 */
bool Lig4::linha_vazia(int linha) const {
    for (int j = 0; j < colunas; j++) {
        if (get_char(linha, j) != ' ') 
            return false;
    }

    return true;
}

/**
 * \brief Verifica se uma coluna do tabuleiro esta vazia
 *
 * Essa funcao recebe como parametro uma coluna e verifica se
 * todas as posicoes do tabuleiro que estao nessa coluna estão 
 * vazias. Caso todas estejam vazias, retorna verdadeiro, se
 * nao, retorna falso.
 * 
 * \param coluna Uma coluna do tabuleiro.
 * \return true ou false
 */
bool Lig4::coluna_vazia(int coluna) const {
    for (int i = 0; i < linhas; i++) {
        if (get_char(i, coluna) != ' ') 
            return false;
    }

    return true;
}

/**
 * \brief Verifica a vitoria de um jogador
 *
 * Essa funcao recebe como parametro um jogador e verifica se
 * esse jogador tem quatro pecas adjacentes no tabuleiro. É 
 * verificada cada linha, cada coluna e cada diagonal (nos dois
 * sentidos). Caso encontre quatro simbolos do jogador em algum
 * desses casos, retorna verdadeiro. Caso contrario, retorna falso.
 * 
 * \param jogador Um jogador da partida.
 * \return true ou false
 */
bool Lig4::verificarVitoria(const Jogador& jogador) const {
    char simbolo = get_simbolo(jogador);

    for (int i = 0; i < linhas; i++) {
        if (linha_vazia(i)) 
            continue;

        for (int j = 0; j < (colunas - 3); j++) {

            int qntd = 0;
            for (int k = j; k < j + 4; k++) {
                if (get_char(i, k) == ' ') 
                    break;

                if (get_char(i, k) == simbolo) 
                    qntd++;
            }

            if (qntd == 4) 
                return true;
        }
    }

    for (int j = 0; j < colunas; j++) {
        if(coluna_vazia(j)) 
            continue;

        for (int i = 0; i < (linhas - 3); i++) {

            int qntd = 0;
            for (int k = i; k < i + 4; k++) {
                if (get_char(k, j) == ' ') 
                    break;

                if (get_char(k, j) == simbolo) 
                    qntd++;
            }

            if (qntd == 4) 
                return true;
        }
    }

    for (int i = 0; i < (linhas - 3); i++) {
        for (int j = 0; j < (colunas - 3); j++) {

            int qntd = 0;
            for (int k = i, l = j; k < i + 4; k++, l++) {
                if (get_char(k, l) == ' ') 
                    break;

                if (get_char(k, l) == simbolo) 
                    qntd++;
            }

            if (qntd == 4) 
                return true;
        }
    }

    for (int i = 0; i < (linhas - 3); i++) {
        for (int j = (colunas - 1); (j - 3) >= 0; j--) {

            int qntd = 0;
            for (int k = i, l = j; k < i + 4; k++, l--) {
                if (get_char(k, l) == ' ') 
                    break;

                if (get_char(k, l) == simbolo) 
                    qntd++;
            }

            if (qntd == 4) 
                return true;
        }
    }

    return false;
}

/**
 * \brief Verifica se o tabuleiro esta cheio
 *
 * Essa funcao verifica se todas as posicoes do tabuleiro
 * estao cheias. Caso isso seja atendido, é retornado 
 * verdadeiro e, caso contrario, é retornado falso.
 * 
 * \return true ou false
 */
bool Lig4::tabuleiro_cheio() const {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (get_char(i, j) == ' ') 
                return false;
        }
    }

    return true;
}

/**
 * \brief Verifica o empate do jogo
 *
 * Essa funcao verifica se houve a vitora de algum
 * jogador e, caso tenha, nao houve empate e é retornado
 * falso. Caso contrario, verifica se o tabuleiro esta
 * cheio. Se estiver, houve empate e é retornado 
 * verdadeiro e, se nao estiver, é retornado falso.
 * 
 * \return true ou false
 */
bool Lig4::verificarEmpate() const {
    if (verificarVitoria(jogador1) || verificarVitoria(jogador2)) {
        return false;
    } else {
        return tabuleiro_cheio();
    }
}