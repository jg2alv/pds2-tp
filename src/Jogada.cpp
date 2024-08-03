#include "Jogada.hpp"

Jogada::Jogada(int coluna) : Jogada(0, coluna) {}

Jogada::Jogada(int linha, int coluna) : _linha(linha), _coluna(coluna) {}

int Jogada::get_linha()const
{
    return this->_linha;
}

int Jogada::get_coluna()const
{
    return this->_coluna;
}

void Jogada::set_linha(int linha)
{
    this->_linha = linha;
}
