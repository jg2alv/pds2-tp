#ifndef CLASSEPAI_HPP
#define CLASSEPAI_HPP

#include <iostream>
#include <vector>
using namespace std;


class Jogo {
protected:
    int rows; 
    int cols; 
    vector<char> board; 

public:
     
    Jogo(int rows, int cols);
    Jogo();
    
    virtual void imprimirTabuleiro() const;

     
    virtual bool lerJogada(int player, int row, int col) = 0;

     
    virtual bool jogadaValida(int row, int col) const = 0;

     
    virtual bool verificarVitoria(int player) const = 0;

     
    virtual bool verificarEmpate() const = 0;

    
    virtual void reiniciarTabuleiro();
};

#endif 
