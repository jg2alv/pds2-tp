#ifndef LIG4_HPP
#define LIG4_HPP

#include "Jogador.hpp"
#include "Jogo.hpp"

class Lig4 : public Jogo
{
private:
    int get_linha(int coluna);

public:
    Lig4(int linhas, int colunas, Jogador& jogador1, Jogador& jogador2);

    void imprimirTabuleiro() const;
    Jogada lerJogada(int jogador) override;
    bool jogadaValida(Jogada jogada) const override;
    bool verificarVitoria(int jogador) const override;
    bool verificarEmpate() const override;
};

#endif
