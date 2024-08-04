#ifndef XADREZ_HPP
#define XADREZ_HPP

#include <vector>
#include <string>
#include <iostream>
#include <map>

#include "Jogador.hpp"
#include "Jogo.hpp"

enum class Pecas {
    PeaoBranco,
    PeaoPreto,
    TorreBranca,
    TorrePreta,
    CavaloBranco,
    CavaloPreto,
    BispoBranco,
    BispoPreto,
    ReiBranco,
    ReiPreto,
    RainhaBranca,
    RainhaPreta
};

class Posicao {
private:
    int linha;
    int coluna;

public:
    Posicao(int linha, int coluna);
    int x();
    int y();
};

class Peca {
private:
    Pecas tipo;
    Posicao pos;

public:
    Peca(Pecas tipo, Posicao pos);
    Pecas getTipo();
    Posicao getPosicao();
    char getChar();
};

class Xadrez : public Jogo {
private:
    std::map<std::string, std::vector<Peca*>> pecas;

public:
    Xadrez(Jogador &jogador1, Jogador &jogador2);
    Xadrez(Jogador &jogador1, Jogador &jogador2, std::vector<std::vector<char>> tabuleiro);
    void preencherTabuleiro();
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
