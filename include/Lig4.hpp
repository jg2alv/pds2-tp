#ifndef LIG4_HPP
#define LIG4_HPP

#include <string>
#include <iostream>

#include "Jogador.hpp"
#include "Jogo.hpp"


class Lig4 : public Jogo {
private:
    int formatoCorreto(std::string entrada);
    int getLinhaTabuleiro(int coluna) const;
    Jogada lerJogada();
    bool linhaVazia(int linha) const;
    bool colunaVazia(int coluna) const;
    bool tabuleiroCheio() const;
    void imprimirVitoria() const;
    void imprimirEmpate() const;
    Jogador* getJogadorOponente();

public:
    Lig4(int linhas, int colunas, Jogador &jogador1, Jogador &jogador2);
    ~Lig4();

    virtual std::string getNome() const override;
    virtual void imprimirTabuleiro(std::ostream& out) const override;
    virtual bool jogadaValida(std::string possivel_jogada) const override;
    virtual void realizarJogada(std::string possivel_jogada) override;
    virtual bool verificarVitoria(Jogador const&) const override;
    virtual bool verificarEmpate() const override;
};


#endif
