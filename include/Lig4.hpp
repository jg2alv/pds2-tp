#ifndef LIG4_HPP
#define LIG4_HPP

#include "Jogador.hpp"
#include "Jogo.hpp"

class Lig4 : public Jogo
{
private:
    int jogador_atual;
    char simbolo_jogador1;
    char simbolo_jogador2;

    int get_linha(int coluna) const;
    bool jogadaValida(Jogada &jogada) const;
    bool linhaVazia(int linha);

public:
    Lig4(int linhas, int colunas, Jogador &jogador1, Jogador &jogador2);

    void imprimirTabuleiro() const;
    Jogada lerJogada(int jogador) override;
    void realizarJogada(Jogada &jogada);
    bool verificarVitoria() const override;
    bool verificarEmpate() const override;
    void mudarTurno();
};

#endif