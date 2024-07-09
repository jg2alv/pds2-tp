#include "ClassePai.hpp"

 
Jogo::Jogo(int rows, int cols) : rows(rows), cols(cols), board(rows * cols, ' ') {}

Jogo:: Jogo(){}

void Jogo::reiniciarTabuleiro() {
    fill(board.begin(), board.end(), ' ');
}
