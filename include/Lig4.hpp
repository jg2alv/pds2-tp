#ifndef LIG4_HPP
#define LIG4_HPP

#include <string>

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

    void imprimirTabuleiro() const override;
    void realizarJogada(const Jogada &jogada) override;
    bool jogadaValida(const Jogada &jogada) const override;
    bool verificarVitoria() const override;
    bool verificarEmpate() const override;
    void trocarJogador() override;
    void partida() override;
};


#endif
