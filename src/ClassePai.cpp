#include "ClassePai.hpp"

 
Jogo::Jogo(int rows, int cols) : rows(rows), cols(cols), board(rows * cols, ' ') {}


void Jogo::reiniciarTabuleiro() {
    fill(board.begin(), board.end(), ' ');
}
