#include <iostream>
#include "Jogo.hpp"
#include "Lig4.hpp"


int Lig4::get_linha(int coluna)
{
    if (get_char(0, coluna) != ' ')
        return -1;

    for (int i = (this->linhas - 1); i >= 0; i--)
    {
        if (get_char(i, coluna) == ' ')
            return i;
    }
}


Lig4::Lig4(int linhas, int colunas, Jogador& jogador1, Jogador& jogador2)
    : Jogo(linhas, colunas, jogador1, jogador2) {}


void Lig4::imprimirTabuleiro() const
{
    for (int i = 0; i < this->linhas; i++)
    {
        for (int j = 0; j < this->colunas; j++)
        {
            std::cout << "|" << get_char(i, j) << "|";
        }
        std::cout << std::endl;
    }

    for (int i = 1; i <= this->colunas; i++)
    {
        std::cout << " " << i << " ";
    }
    std::cout << std::endl;
}

Jogada Lig4::lerJogada(int jogador)
{
}

bool Lig4::jogadaValida(Jogada jogada) const
{
}

bool Lig4::verificarVitoria(int jogador) const
{
}

bool Lig4::verificarEmpate() const
{
}
