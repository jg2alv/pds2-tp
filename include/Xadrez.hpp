#ifndef XADREZ_HPP
#define XADREZ_HPP

#include <vector>
#include <string>
#include <iostream>

#include "Jogador.hpp"
#include "Jogo.hpp"


class Xadrez : public Jogo {
private:
    bool jogada_valida(const Jogada &jogada) const;
    void realizar_jogada(const Jogada &jogada);

public:
    Xadrez(Jogador &jogador1, Jogador &jogador2);
    Xadrez(Jogador &jogador1, Jogador &jogador2, std::vector<std::vector<char>> tabuleiro);
    ~Xadrez();

    virtual std::string getNome() const override;
    virtual void imprimirTabuleiro(std::ostream& out) const override;
    virtual bool formatoCorreto(std::string possivel_jogada) const override;
    virtual bool jogadaValida(std::string possivel_jogada) const override;
    virtual void realizarJogada(std::string possivel_jogada) override;
    virtual bool verificarVitoria(Jogador const&) const override;
    virtual bool verificarEmpate() const override;
};


#endif
