#include <iostream>
#include "Jogo.hpp"
#include "Lig4.hpp"

Lig4::Lig4(int rows, int cols, Jogador *jogador1, Jogador *jogador2) : Jogo(rows, cols)
{
    this->_jogador1 = jogador1;
    this->_jogador2 = jogador2;
}

void Lig4::setJogadores(Jogador *jogador1, Jogador *jogador2)
{
}

bool Lig4::lerJogada(int player, int row, int col)
{
}

bool Lig4::jogadaValida(int row, int col) const
{
}

bool Lig4::verificarVitoria(int player) const
{
}

bool Lig4::verificarEmpate() const
{
}