#ifndef REVERSI_INCLUDED
#define REVERSI_INCLUDED

#include <iostream>
#include <Jogador.hpp>

class Reversi : public Jogo
{
    private:
    Jogador _jogador1;
    Jogador _jogador2;

    public:

    Reversi(){}
    void setJogadores (Jogador jogador1, Jogador jogador2) {}
    ~Reversi(){}
};












#endif

