#ifndef JOGO_HPP
#define JOGO_HPP

#include <iostream>
#include <vector>

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

     
    virtual bool lerJogada(int jogador, int linha, int coluna) = 0;

     
    virtual bool jogadaValida(int linha, int coluna) const = 0;

     
    virtual bool verificarVitoria(int jogador) const = 0;

     
    virtual bool verificarEmpate() const = 0;

    
    virtual void reiniciarTabuleiro();
};


#endif

