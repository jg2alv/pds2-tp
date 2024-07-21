#ifndef LIG4_HPP
#define LIG4_HPP

#include "Jogador.hpp"
#include "Jogo.hpp"

class Lig4 : public Jogo
{
private:
    int jogador_atual;

    int get_linha(int coluna) const;
    bool jogadaValida(Jogada &jogada) const;
    bool linhaVazia(int linha) const;
    bool colunaVazia(int coluna) const;
    bool tabuleiroCheio() const;
    void imprimirVitoria() const;
    void imprimirEmpate() const;

public:
    Lig4(int linhas, int colunas, Jogador &jogador1, Jogador &jogador2);
    void partida();
    void imprimirTabuleiro() const;
    Jogada lerJogada() override;
    void realizarJogada(Jogada &jogada);
    bool verificarVitoria() const override;
    bool verificarEmpate() const override;
    void reiniciarTabuleiro() override;
    void mudarTurno();

};

#endif