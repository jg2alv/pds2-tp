#ifndef REVERSI_HPP
#define REVERSI_HPP

#include <iostream>
#include "Jogador.hpp"
#include "Jogo.hpp"

class Reversi : public Jogo {
protected:
    bool dentroDosLimites(int linha, int coluna) const;
    bool podeJogar(char simbolo, char oponente) const;

public:
    Reversi(int linhas, int colunas, Jogador& jogador1, Jogador& jogador2);

    void setJogadores(Jogador jogador1, Jogador jogador2);
    void realizarJogada(int linha, int coluna, char simbolo, char oponente); 
    bool jogadaValida(int linha, int coluna, char simbolo, char oponente) const override;
    bool verificarVitoria() const override;
    Jogada lerJogada (int jogador) override;
    bool verificarEmpate() const override;
    void imprimirTabuleiro() const override;
    void reiniciarTabuleiro()override;

    ~Reversi();
};

#endif
