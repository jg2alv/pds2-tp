#ifndef LIG4_INCLUDED
#define LIG4_INCLUDED

#include "Jogador.hpp"
#include "ClassePai.hpp"

class Lig4 : public Jogo
{
private:
    Jogador _jogador1;
    Jogador _jogador2;

public:
    Lig4();
    void setJogadores(Jogador jogador1, Jogador jogador2);
    ~Lig4();
};

#endif