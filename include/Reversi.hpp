#ifndef REVERSI_HPP
#define REVERSI_HPP

#include <iostream>
#include "Jogador.hpp"
#include "Jogo.hpp"

class Reversi : public Jogo {
private:
    bool dentroDosLimites(const Jogada& jogada) const;
    bool jogadaValida(const Jogada& jogada) const;
    void realizarJogada(const Jogada& jogada);
    bool verificarVitoria() const;
    bool verificarEmpate() const;
    bool podeJogar(const std::string& jogador) const;
    void reiniciarTabuleiro();
    void trocarJogador();

public:
    Reversi(int linhas, int colunas, Jogador& jogador1, Jogador& jogador2);
    void partida();
    void imprimirTabuleiro() const;
    ~Reversi();
};

#endif