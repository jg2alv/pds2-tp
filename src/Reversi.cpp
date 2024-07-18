#include "Reversi.hpp"
#include "Jogador.hpp"
#include <iostream>


Reversi::Reversi(int linhas, int colunas, Jogador& jogador1, Jogador& jogador2)
    : Jogo(linhas, colunas, jogador1, jogador2) {}


bool Reversi::dentroDosLimites(int linha, int coluna) const {
    return linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas;
}

bool Reversi::jogadaValida(int linha, int coluna, char simbolo, char oponente) const {
    if (get_char(linha, coluna) != ' ') {
        return false;
    }

    int dlinha[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dcoluna[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int i = 0; i < 8; i++) {
        int nlinha = linha + dlinha[i], ncoluna = coluna + dcoluna[i];
        bool encontrouOponente = false;

        while (dentroDosLimites(nlinha, ncoluna) && get_char(nlinha, ncoluna) == oponente) {
            encontrouOponente = true;
            nlinha += dlinha[i];
            ncoluna += dcoluna[i];
        }

        if (encontrouOponente && dentroDosLimites(nlinha, ncoluna) && get_char(nlinha, ncoluna) == simbolo) {
            return true;
        }
    }

    return false;
}

void Reversi::realizarJogada(int linha, int coluna, char simbolo, char oponente) {
    set_char(linha, coluna, simbolo);

    int dlinha[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dcoluna[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int i = 0; i < 8; i++) {
        int nlinha = linha + dlinha[i], ncoluna = coluna + dcoluna[i];
        bool encontrouOponente = false;

        while (dentroDosLimites(nlinha, ncoluna) && get_char(nlinha, ncoluna) == oponente) {
            encontrouOponente = true;
            nlinha += dlinha[i];
            ncoluna += dcoluna[i];
        }

        if (encontrouOponente && dentroDosLimites(nlinha, ncoluna) && get_char(nlinha, ncoluna) == simbolo) {
            nlinha -= dlinha[i];
            ncoluna -= dcoluna[i];

            while (nlinha != linha || ncoluna != coluna) {
                set_char(nlinha, ncoluna, simbolo);
                nlinha -= dlinha[i];
                ncoluna -= dcoluna[i];
            }
        }
    }
}

bool Reversi::verificarVitoria() const {
    char apelido1 = jogador1.getApelido()[0];
    char apelido2 = jogador2.getApelido()[0];
    int contador1 = 0;
    int contador2 = 0;

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (get_char(i, j) == apelido1) {
                contador1++;
            } else if (get_char(i, j) == apelido2) {
                contador2++;
            }
        }
    }

    return (contador1 > contador2 && contador2 == 0) || (contador2 > contador1 && contador1 == 0);
}

bool Reversi::verificarEmpate() const {
    char apelido1 = jogador1.getApelido()[0];
    char apelido2 = jogador2.getApelido()[0];
    int contador1 = 0;
    int contador2 = 0;

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (get_char(i, j) == apelido1) {
                contador1++;
            } else if (get_char(i, j) == apelido2) {
                contador2++;
            }
        }
    }

    return contador1 == contador2;
}

bool Reversi::podeJogar(char simbolo, char oponente) const {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (jogadaValida(i, j, simbolo, oponente)) {
                return true;
            }
        }
    }
    return false;
}

void Reversi::imprimirTabuleiro()const {
    for (int i = 0; i < linhas; i++) {
        std::cout << i << " ";
        for (int j = 0; j < colunas; j++) {
            std::cout << "|" << get_char(i, j) << "|";
        }
        std::cout << "\n";
    }
    std::cout << "  ";
    for (int j = 0; j < colunas; j++) {
        std::cout << " " << j << " ";
    }
    std::cout << "\n";
}

void Reversi::reiniciarTabuleiro() {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            set_char(i, j, ' ');
        }
    }

    set_char(linhas / 2 - 1, colunas / 2 - 1, jogador2.getApelido()[0]);
    set_char(linhas / 2 - 1, colunas / 2, jogador1.getApelido()[0]);
    set_char(linhas / 2, colunas / 2 - 1, jogador1.getApelido()[0]);
    set_char(linhas / 2, colunas / 2, jogador2.getApelido()[0]);
}

Reversi::~Reversi() {}
