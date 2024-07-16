#ifndef JOGO_HPP
#define JOGO_HPP

#include <iostream>
#include <vector>

using namespace std;


class Jogo {
protected:
    int rows; 
    int cols; 
    vector<char> board; 

    char get_char(int i, int j);
    void set_char(int i, int j, char c);

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

