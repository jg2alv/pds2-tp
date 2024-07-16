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
    
    virtual void imprimirTabuleiro() const=0;

     
    virtual void realizarJogada(int jogador, int linha, int coluna) = 0;

     
    virtual bool jogadaValida(int linha, int coluna, char simbolo, char oponente) const = 0;

     
    virtual bool verificarVitoria() const = 0;

     
    virtual bool verificarEmpate() const = 0;

    
    virtual void reiniciarTabuleiro() = 0;
};


#endif

