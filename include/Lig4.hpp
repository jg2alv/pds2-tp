#ifndef LIG4_HPP
#define LIG4_HPP

#include "Jogador.hpp"
#include "Jogo.hpp"

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

