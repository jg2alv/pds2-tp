#ifndef LIG4_HPP
#define LIG4_HPP

#include "Jogador.hpp"
#include "Jogo.hpp"

class Lig4 : public Jogo
{
private:
    Jogador *_jogador1;
    Jogador *_jogador2;

public:
    Lig4(int rows, int cols, Jogador *jogador1, Jogador *jogador2);

    void setJogadores(Jogador *jogador1, Jogador *jogador2);
    bool lerJogada(int player, int row, int col);
    bool jogadaValida(int row, int col) const;
    bool verificarVitoria(int player) const;
    bool verificarEmpate() const;
};

#endif
