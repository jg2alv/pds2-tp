#include "Jogo.hpp"


char Jogo::get_char(int i, int j) const {
    return tabuleiro[i*colunas + j];
}

void Jogo::set_char(int i, int j, char c) {
    tabuleiro[i*colunas + j] = c;
}

 
Jogo::Jogo(int linhas, int colunas) : linhas(linhas), colunas(colunas), tabuleiro(linhas*colunas, ' ') {}

Jogo:: Jogo(){}


void Jogo::reiniciarTabuleiro() {
    fill(tabuleiro.begin(), tabuleiro.end(), ' ');
}

