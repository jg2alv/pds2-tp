#ifndef REVERSI_HPP
#define REVERSI_HPP

#include <iostream>
#include "Jogador.hpp"
#include "Jogo.hpp"

class Reversi : public Jogo {
private:
    char simbolo_jogador1;
    char simbolo_jogador2;
    bool dentroDosLimites(const Jogada& jogada) const;
    bool jogadaValida(const Jogada& jogada, char simbolo, char oponente) const;
    void realizarJogada(const Jogada& jogada, char simbolo, char oponente);
    bool verificarVitoria() const;
    bool verificarEmpate() const;
    bool podeJogar(char simbolo, char oponente) const;
    void reiniciarTabuleiro();
public:
   Reversi(int linhas, int colunas, Jogador& jogador1, Jogador& jogador2);
    void partida();
    void imprimirTabuleiro() const;
    ~Reversi();
};

#endif
