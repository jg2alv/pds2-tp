#include "Jogada.hpp"

Jogada::Jogada(int coluna) : Jogada(-1, coluna) {}

Jogada::Jogada(int linha, int coluna)
{
    this->_linha = (linha - 1);
    this->_coluna = (coluna - 1);
}

int Jogada::get_linha()
{
    return this->_linha;
}

int Jogada::get_coluna()
{
    return this->_coluna;
}