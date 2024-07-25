#include "Jogo.hpp"

char Jogo::get_char(int linhas, int colunas) const {
    return tabuleiro[linhas * colunas + colunas];
}

void Jogo::set_char(int linhas, int colunas, char c) {
    tabuleiro[linhas * colunas + colunas] = c;
}

Jogo::Jogo(int linhas, int colunas, Jogador& jogador1, Jogador& jogador2)
    : linhas(linhas),
      colunas(colunas),
      tabuleiro(linhas*colunas, ' '),
      jogador1(jogador1), 
      jogador2(jogador2 ),
      jogador_atual(&jogador1),
      simbolos {{jogador1.getApelido(), 'X'}, 
      {jogador2.getApelido(), 'O'}} {}
