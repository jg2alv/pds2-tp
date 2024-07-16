#ifndef REVERSI_HPP
#define REVERSI_HPP

#include <iostream>
#include "Jogador.hpp"
#include "Jogo.hpp"

class Reversi : public Jogo
{
    private:
    Jogador _jogador1;
    Jogador _jogador2;

    public:

    Reversi(int linhas, int colunas);
    void setJogadores (Jogador jogador1, Jogador jogador2);
    bool lerJogada (int jogador, int linha, int coluna) override; 
    bool jogadaValida (int linha, int coluna) const override;
    bool verificarVitoria (int jogador) const override;
    bool verificarEmpate() const override;
    
    ~Reversi();
};


#endif

