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
    Jogador *jogador_atual;
    std::map<std::string, char> simbolos;

    char get_char(int i, int j) const;
    void set_char(int i, int j, char c);

public:
    Jogo(int linhas, int colunas, Jogador& jogador1, Jogador& jogador2);
    virtual void imprimirTabuleiro() const = 0;
    virtual void realizarJogada(const Jogada& jogada, const std::string& jogador) = 0;
    virtual bool jogadaValida(const Jogada& jogada, const std::string& jogador) const = 0;
    virtual bool verificarVitoria() = 0;
    virtual bool verificarEmpate() const = 0;
    virtual void reiniciarTabuleiro() = 0;
    virtual void partida()=0;
    virtual Jogada lerJogada() = 0;
};

#endif