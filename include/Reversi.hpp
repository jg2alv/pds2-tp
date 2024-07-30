#ifndef REVERSI_HPP
#define REVERSI_HPP

#include <iostream>

#include "Jogador.hpp"
#include "Jogo.hpp"


class Reversi : public Jogo {
private:
    bool dentroDosLimites(const Jogada& jogada) const;
    bool podeJogar(const std::string& jogador) const;
    void reiniciarTabuleiro();

public:
    Reversi(int linhas, int colunas, Jogador& jogador1, Jogador& jogador2);
    ~Reversi();

    void imprimirTabuleiro() const override;
    void realizarJogada(const Jogada &jogada) override;
    bool jogadaValida(const Jogada &jogada) const override;
    bool verificarVitoria() const override;
    bool verificarEmpate() const override;
    void trocarJogador() override;
    void partida() override;
};


#endif
