#include "Reversi.hpp"
#include "Jogador.hpp"
#include "Jogada.hpp"
#include "Excecao.hpp"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

/**
 * \brief Construtor da classe Reversi
 * 
 * Este construtor inicializa um jogo de Reversi com as dimensões
 * do tabuleiro especificadas e os jogadores fornecidos. Também chama
 * a função reiniciarTabuleiro() para configurar a disposição inicial
 * das peças.
 * 
 * \param linhas Número de linhas do tabuleiro.
 * \param colunas Número de colunas do tabuleiro.
 * \param jogador1 Referência ao primeiro jogador.
 * \param jogador2 Referência ao segundo jogador.
 */
using namespace std;

Reversi::Reversi(int linhas, int colunas, Jogador &jogador1, Jogador &jogador2) :
    Jogo(linhas, colunas, jogador1, jogador2) {
    reiniciarTabuleiro();
}
/**
 * \brief Construtor da classe Reversi com tabuleiro especificado
 * 
 * Este construtor inicializa um jogo de Reversi com as dimensões
 * do tabuleiro e os jogadores fornecidos, além de configurar o
 * tabuleiro com um estado inicial específico.
 * 
 * \param linhas Número de linhas do tabuleiro.
 * \param colunas Número de colunas do tabuleiro.
 * \param jogador1 Referência ao primeiro jogador.
 * \param jogador2 Referência ao segundo jogador.
 * \param tabuleiro Estado inicial do tabuleiro como uma matriz 2D.
 */

Reversi::Reversi(int linhas, int colunas, Jogador& jogador1, Jogador& jogador2, vector<vector<char>> tabuleiro) :
    Jogo(linhas, colunas, jogador1, jogador2, tabuleiro) {}

/**
 * \brief Destrutor da classe Reversi.
 * 
 * Limpa recursos alocados e realiza qualquer ação de limpeza que for necessária.
 */
Reversi::~Reversi() {}

/**
 * \brief Obtém o nome do jogo.
 * 
 * Esta função retorna o nome do jogo, que é "Reversi".
 * 
 * \return Uma string contendo o nome "Reversi".
 */

string Reversi::getNome() const {
    return "Reversi";
}

/**
 * \brief Verifica se uma jogada está dentro dos limites do tabuleiro.
 *
 * Esta função verifica se as coordenadas de uma jogada estão dentro
 * dos limites do tabuleiro, garantindo que a jogada é possível de ser
 * realizada no tabuleiro atual.
 * 
 * \param jogada A instância da classe Jogada representando a jogada a ser verificada.
 * \return true se a jogada estiver dentro dos limites do tabuleiro, false caso contrário.
 */
bool Reversi::dentroDosLimites(const Jogada& jogada) const {
    int linha = jogada.get_linha();
    int coluna = jogada.get_coluna();
    return linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas;
}

/**
 * \brief Verifica se uma jogada é válida para um determinado jogador.
 *
 * Esta função verifica se uma jogada específica é válida de acordo com
 * as regras do Reversi. A jogada é válida se colocar uma peça em uma 
 * posição que cercaria uma ou mais peças do oponente, permitindo que
 * sejam viradas para o símbolo do jogador que está jogando.
 * 
 * \param jogada A instância da classe Jogada representando a jogada a ser verificada.
 * \param simbolo O símbolo do jogador que está realizando a jogada ('X' ou 'O').
 * \return true se a jogada for válida, false caso contrário.
 */
bool Reversi::jogada_valida(const Jogada& jogada, char simbolo) const {
    char oponente = (simbolo == 'X') ? 'O' : 'X';
    int linha = jogada.get_linha();
    int coluna = jogada.get_coluna();
    
    if (!dentroDosLimites(jogada)) {
        return false;
    }

    if (get_char(linha, coluna) != ' ') { 
        return false;
    }

    int dlinha[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dcoluna[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int i = 0; i < 8; i++) {
        int nlinha = linha + dlinha[i];
        int ncoluna = coluna + dcoluna[i];
        bool encontrouOponente = false;

        while (dentroDosLimites(Jogada(nlinha, ncoluna)) && get_char(nlinha, ncoluna) == oponente) {
            encontrouOponente = true;
            nlinha += dlinha[i];
            ncoluna += dcoluna[i];
        }
        if (encontrouOponente && dentroDosLimites(Jogada(nlinha, ncoluna)) && get_char(nlinha, ncoluna) == simbolo) {
            return true;
        }
    }
    return false;
}

/**
 * \brief Analisa se o formato da entrada para uma jogada está correto.
 *
 * Esta função verifica se uma string de entrada contém exatamente dois números,
 * correspondendo às coordenadas de uma jogada. Isso é necessário para validar
 * a entrada antes de tentar realizar uma jogada.
 * 
 * \param possivel_jogada A string contendo a entrada para a jogada.
 * \return true se o formato estiver correto, false caso contrário.
 */

bool Reversi::formatoCorreto(string possivel_jogada) const {
    stringstream jogada_stream(possivel_jogada);
    int linha, coluna;
    string extra;

    if (!(jogada_stream >> linha)) {
        return false;
    }

    if (!(jogada_stream >> coluna)) {
        return false;
    }

    return !(jogada_stream >> extra);
}

/**
 * \brief Verifica se uma jogada é válida, considerando o formato e regras do jogo.
 *
 * Esta função analisa a string de entrada, verificando o formato correto e,
 * posteriormente, se a jogada é válida de acordo com as regras do Reversi.
 * Se o formato estiver incorreto, lança uma exceção. Caso a jogada seja válida,
 * retorna true, caso contrário, retorna false.
 * 
 * \param possivel_jogada Uma string representando a jogada.
 * \return true se a jogada for válida, false caso contrário.
 * \throw Excecao se o formato da jogada estiver incorreto.
 */

bool Reversi::jogadaValida(string possivel_jogada) const {
    if (fimDeJogo()) {
        return false; 
    }

    if (!formatoCorreto(possivel_jogada)) {
        throw Excecao("formato incorreto (formato correto: apenas [linha] [coluna])");
    }

    stringstream jogada_stream(possivel_jogada);
    int linha, coluna;
    jogada_stream >> linha >> coluna;
    linha--;
    coluna--;

    return jogada_valida(Jogada(linha, coluna), get_simbolo(*jogador_da_vez));
}

/**
 * \brief Realiza uma jogada no tabuleiro, atualizando o estado do jogo.
 *
 * Esta função executa uma jogada válida no tabuleiro, verificando primeiro
 * se o formato está correto e se a jogada é possível. Se o formato estiver
 * incorreto ou se a jogada não for válida, lança uma exceção. Caso contrário,
 * atualiza o tabuleiro com a nova jogada e altera o estado do jogo.
 * 
 * \param possivel_jogada Uma string representando a jogada.
 * \throw Excecao se o jogo já tiver terminado, se o formato da jogada estiver incorreto, ou se a jogada não for válida.
 */

void Reversi::realizarJogada(string possivel_jogada) {
    if (fimDeJogo()) {
        throw Excecao("jogo ja acabou");
    }

    if (!formatoCorreto(possivel_jogada)) {
        throw Excecao("formato incorreto (formato correto: apenas [linha] [coluna])");
    }

    stringstream jogada_stream(possivel_jogada);
    int linha, coluna;
    jogada_stream >> linha >> coluna;
    linha--;
    coluna--;

    if (!jogada_valida(Jogada(linha, coluna), get_simbolo(*jogador_da_vez))) {
        throw Excecao("jogada invalida (coordenada recebida esta fora dos limites do tabuleiro ou ja esta ocupada)");
    }

    realizar_jogada(Jogada(linha, coluna));
};

/**
 * \brief Realiza uma jogada no tabuleiro e atualiza o estado do jogo.
 *
 * Esta função executa uma jogada válida no tabuleiro. A jogada é aplicada
 * no tabuleiro e as peças do oponente são viradas para o símbolo do jogador,
 * de acordo com as regras do Reversi. Após a jogada, a vez do outro jogador é
 * verificada e, se ele puder jogar, a vez é passada para ele.
 * 
 * \param jogada A instância da classe Jogada representando a jogada a ser realizada.
 */
void Reversi::realizar_jogada(const Jogada& jogada) {
    char simbolo = get_simbolo(*jogador_da_vez);
    char oponente = get_simbolo(*outro_jogador);
    int linha = jogada.get_linha();
    int coluna = jogada.get_coluna();
    set_char(linha, coluna, simbolo);

    int dlinha[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dcoluna[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int i = 0; i < 8; i++) {
        int nlinha = linha + dlinha[i], ncoluna = coluna + dcoluna[i];
        bool encontrouOponente = false;

        while (dentroDosLimites(Jogada(nlinha, ncoluna)) && get_char(nlinha, ncoluna) == oponente) {
            encontrouOponente = true;
            nlinha += dlinha[i];
            ncoluna += dcoluna[i];
        }

        if (encontrouOponente && dentroDosLimites(Jogada(nlinha, ncoluna)) && get_char(nlinha, ncoluna) == simbolo) {
            nlinha -= dlinha[i];
            ncoluna -= dcoluna[i];

            while (nlinha != linha || ncoluna != coluna) {
                set_char(nlinha, ncoluna, simbolo);
                nlinha -= dlinha[i];
                ncoluna -= dcoluna[i];
            }
        }
    }

    if (podeJogar(*outro_jogador)) {
        passar_a_vez();
    }
}

/**
 * \brief Calcula o indicador de pontos no tabuleiro.
 * 
 * Esta função conta o número de peças de cada jogador no tabuleiro e retorna
 * um indicador com base na contagem. Retorna 1 se o número de peças do jogador
 * 'X' for maior, -1 se o número de peças do jogador 'O' for maior, e 0 se
 * houver um empate.
 * 
 * \return 1 se o jogador 'X' tiver mais peças, -1 se o jogador 'O' tiver mais
 * peças, e 0 se houver um empate.
 */
int Reversi::indicador_de_pontos() const {
    int contadorX = 0;
    int contadorO = 0;

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (get_char(i, j) == 'X') {
                contadorX++;
            } else if (get_char(i, j) == 'O') {
                contadorO++;
            }
        }
    }
    
    if (contadorX > contadorO) {
        return 1;
    } else if (contadorX < contadorO) {
        return -1;
    } else {
        return 0;
    }
}

/**
 * \brief Verifica se o jogador especificado venceu o jogo.
 * 
 * Esta função verifica se o jogador passado como argumento venceu o jogo
 * com base no estado atual do tabuleiro e nas regras de vitória. O jogador
 * vence se não houver mais jogadas válidas para o outro jogador e o número
 * de peças dele no tabuleiro for maior.
 * 
 * \param jogador A referência ao jogador a ser verificado.
 * \return true se o jogador venceu, false caso contrário.
 */
bool Reversi::verificarVitoria(const Jogador& jogador) const {
    if (podeJogar(*jogador_da_vez)) {
        return false;
    }

    int indicador = indicador_de_pontos();
    if (indicador == 1 && jogador == jogador1) {
        return true;
    } else if (indicador == -1 && jogador == jogador2) {
        return true;
    } else {
        return false;
    }
}

/**
 * \brief Verifica se o jogo terminou em empate.
 * 
 * Esta função verifica se o jogo terminou em empate, o que ocorre quando
 * não há mais jogadas válidas para nenhum dos jogadores e o número de peças
 * dos dois jogadores é igual.
 * 
 * \return true se o jogo terminou em empate, false caso contrário.
 */
bool Reversi::verificarEmpate() const {
    if (podeJogar(*jogador_da_vez)) {
        return false;
    }

    return indicador_de_pontos() == 0;
}

/**
 * \brief Verifica se um jogador pode realizar uma jogada.
 * 
 * Esta função verifica se o jogador especificado tem alguma jogada válida
 * no tabuleiro. Se o jogador puder realizar uma jogada, retorna true, caso
 * contrário, retorna false.
 * 
 * \param jogador A referência ao jogador a ser verificado.
 * \return true se o jogador puder jogar, false caso contrário.
 */
bool Reversi::podeJogar(const Jogador& jogador) const {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (jogada_valida(Jogada(i, j), get_simbolo(jogador))) {
                return true;
            }
        }
    }
    return false;
}

/**
 * \brief Imprime o estado atual do tabuleiro.
 * 
 * Esta função imprime o estado atual do tabuleiro em um fluxo de saída
 * especificado. O tabuleiro é exibido com as coordenadas das linhas e
 * colunas para facilitar a visualização.
 * 
 * \param out O fluxo de saída onde o tabuleiro será impresso.
 */

void Reversi::imprimirTabuleiro(ostream& out) const {
    out << "---------Reversi---------\n";
    out << "  ";
    for (int j = 0; j < colunas; j++) {
        cout << " " << j + 1 << " ";
    }
    out << "\n";
    for (int i = 0; i < linhas; i++) {
        cout << i + 1 << " "; 
        for (int j = 0; j < colunas; j++) {
            cout << "|" << get_char(i, j) << "|";
        }
        out << "\n";
    }
}

/**
 * \brief Reinicia o tabuleiro para o estado inicial.
 * 
 * Esta função configura o tabuleiro para o estado inicial do jogo de Reversi,
 * com as peças dos jogadores dispostas nas posições centrais.
 */
void Reversi::reiniciarTabuleiro() {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            set_char(i, j, ' '); 
        }
    }

    set_char(linhas / 2 - 1, colunas / 2 - 1, 'O');
    set_char(linhas / 2 - 1, colunas / 2, 'X');
    set_char(linhas / 2, colunas / 2 - 1, 'X');
    set_char(linhas / 2, colunas / 2, 'O');
}

