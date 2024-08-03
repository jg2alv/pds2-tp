#ifndef JOGO_HPP
#define JOGO_HPP

#include <vector>
#include <iostream>

#include "Jogada.hpp"
#include "Jogador.hpp"


class Jogo {
protected:
    int linhas; 
    int colunas; 
    std::vector<char> tabuleiro; 

    bool jogo_finalizado;

    Jogador& jogador1;
    Jogador& jogador2;

    Jogador *jogador_da_vez;
    Jogador *outro_jogador;

    Jogador *vencedor;
    Jogador *perdedor;

    std::map<std::string, char> simbolos;

    char get_simbolo(const Jogador& jogador) const;
    char get_char(int i, int j) const;
    void set_char(int i, int j, char c);

    void passar_a_vez();

public:
    Jogo(int linhas, int colunas, Jogador& jogador1, Jogador& jogador2);
    virtual ~Jogo();

    bool fimDeJogo() const;
    void finalizarJogo();
    void efetuarDesistencia();

    Jogador *getJogadorDaVez() const;
    Jogador *getOutroJogador() const;

    Jogador *getVencedor() const;
    Jogador *getPerdedor() const;

    virtual std::string getNome() const = 0;
    virtual void imprimirTabuleiro(std::ostream& out) const = 0;
    virtual bool formatoCorreto(std::string possivel_jogada) const = 0;
    virtual bool jogadaValida(std::string possivel_jogada) const = 0;
    virtual void realizarJogada(std::string possivel_jogada) = 0;
    virtual bool verificarVitoria(Jogador const&) const = 0;
    virtual bool verificarEmpate() const = 0;
};


#endif
