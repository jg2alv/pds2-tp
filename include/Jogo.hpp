#ifndef JOGO_HPP
#define JOGO_HPP

#include <vector>
#include "Jogada.hpp"
#include "Jogador.hpp"


class Jogo {
protected:
    int linhas; 
    int colunas; 
    std::vector<char> tabuleiro; 

    Jogador& jogador1;
    Jogador& jogador2;

    char get_char(int i, int j) const;
    void set_char(int i, int j, char c);

public:
    Jogo(int linhas, int colunas, Jogador& jogador1, Jogador& jogador2);

    virtual void imprimirTabuleiro() const = 0;
    virtual void realizarJogada(int jogador, int linha, int coluna) = 0;
    virtual bool jogadaValida(int linha, int coluna, char simbolo, char oponente) const = 0;
    virtual bool verificarVitoria() const = 0;
    virtual bool verificarEmpate() const = 0;
    virtual void reiniciarTabuleiro() = 0;
    virtual Jogada lerJogada(int jogador) = 0;
};


#endif

