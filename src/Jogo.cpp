#include "Jogo.hpp"


char Jogo::get_char(int linhas, int colunas) const {
    return tabuleiro[linhas * colunas + colunas];
}

void Jogo::set_char(int linhas, int colunas, char c) {
    tabuleiro[linhas * colunas + colunas] = c;
}

Jogo::Jogo(int linhas, int colunas) : linhas(linhas), colunas(colunas), tabuleiro(linhas*colunas, ' ') {}

