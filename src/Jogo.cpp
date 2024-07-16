#include "Jogo.hpp"


char Jogo::get_char(int i, int j) const {
    return board[i*cols + j];
}

void Jogo::set_char(int i, int j, char c) {
    board[i*cols + j] = c;
}

 
Jogo::Jogo(int rows, int cols) : rows(rows), cols(cols), board(rows * cols, ' ') {}

Jogo:: Jogo(){}


void Jogo::reiniciarTabuleiro() {
    fill(board.begin(), board.end(), ' ');
}

