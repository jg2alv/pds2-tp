#ifndef JOGO_HPP
#define JOGO_HPP

#include <iostream>
#include <vector>
#include "Jogada.hpp"

using namespace std;

class Jogo {
protected:
    int linhas; 
    int colunas; 
    vector<char> tabuleiro; 

    char get_char(int i, int j) const;
    void set_char(int i, int j, char c);

public:
     
    Jogo(int linhas, int colunas);
    Jogo();
    
    virtual void imprimirTabuleiro() const;
    virtual Jogada lerJogada(int jogador) = 0;
    virtual bool jogadaValida(Jogada jogada) const = 0;
    virtual bool verificarVitoria(int jogador) const = 0;
    virtual bool verificarEmpate() const = 0;
    virtual void reiniciarTabuleiro();
};


#endif

