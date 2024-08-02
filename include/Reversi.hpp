#ifndef REVERSI_HPP
#define REVERSI_HPP

#include <iostream>

#include "Jogador.hpp"
#include "Jogo.hpp"


class Reversi : public Jogo {
private:
    bool dentroDosLimites(const Jogada& jogada) const;
    bool podeJogar() const;
    void reiniciarTabuleiro();

public:
    Reversi(int linhas, int colunas, Jogador& jogador1, Jogador& jogador2);
    ~Reversi();

    virtual std::string getNome() const override;
    virtual void imprimirTabuleiro(std::ostream& out) const override;
    virtual bool jogadaValida(std::string possivel_jogada) const override;
    virtual void realizarJogada(std::string possivel_jogada) override;
    virtual bool verificarVitoria(Jogador const&) const override;
    virtual bool verificarEmpate() const override;

    bool determinarResultadoFinal() const;
};


#endif
