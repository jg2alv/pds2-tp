#ifndef REVERSI_INCLUDED
#define REVERSI_INCLUDED

#include <iostream>
#include "Jogador.hpp"
#include "ClassePai.hpp"

class Reversi : public Jogo
{
    private:
    Jogador _jogador1;
    Jogador _jogador2;

    public:

    Reversi(int rows, int cols);
    void setJogadores (Jogador jogador1, Jogador jogador2);
    bool lerJogada (int player, int row, int col) override; 
    bool jogadaValida (int row, int col) const override;
    bool verificarVitoria (int player) const override;
    bool verificarEmpate() const override;
    
    ~Reversi();
};












#endif

