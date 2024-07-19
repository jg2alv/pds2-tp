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

    int get_linha(int coluna);

public:
    Lig4(int linhas, int colunas, Jogador& jogador1, Jogador& jogador2);

    void imprimirTabuleiro() const;
    Jogada lerJogada(int jogador) override;
    bool jogadaValida(int linha, int coluna, char simbolo, char oponente) const override;
    bool verificarVitoria() const override;
    bool verificarEmpate() const override;
};

#endif