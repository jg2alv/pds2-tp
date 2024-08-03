#ifndef REVERSI_HPP
#define REVERSI_HPP

#include <vector>
#include <iostream>

#include "Jogador.hpp"
#include "Jogo.hpp"


class Reversi : public Jogo {
private:
    bool dentroDosLimites(const Jogada& jogada) const;
    void reiniciarTabuleiro();
    bool jogada_valida(const Jogada& jogada, char simbolo) const;
    void realizar_jogada(const Jogada& jogada);
    int indicador_de_pontos() const;

public:
    Reversi(int linhas, int colunas, Jogador& jogador1, Jogador& jogador2);
    Reversi(int linhas, int colunas, Jogador& jogador1, Jogador& jogador2, std::vector<char> tabuleiro);
    ~Reversi();

    bool podeJogar(const Jogador& jogador) const;
    virtual std::string getNome() const override;
    virtual void imprimirTabuleiro(std::ostream& out) const override;
    virtual bool formatoCorreto(std::string possivel_jogada) const override;
    virtual bool jogadaValida(std::string possivel_jogada) const override;
    virtual void realizarJogada(std::string possivel_jogada) override;
    virtual bool verificarVitoria(Jogador const&) const override;
    virtual bool verificarEmpate() const override;
};


#endif
