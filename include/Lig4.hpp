#ifndef LIG4_HPP
#define LIG4_HPP

#include <string>
#include "Jogador.hpp"
#include "Jogo.hpp"

class Lig4 : public Jogo
{
private:
    void imprimirTabuleiro() const;
    int formatoCorreto(std::string entrada);
    int getLinhaTabuleiro(int coluna) const;
    Jogada lerJogada();
    bool jogadaValida(const Jogada &jogada) const;
    void realizarJogada(const Jogada &jogada);
    bool linhaVazia(int linha) const;
    bool colunaVazia(int coluna) const;
    bool verificarVitoria() const override;
    bool tabuleiroCheio() const;
    bool verificarEmpate() const override;
    void imprimirVitoria() const;
    void imprimirEmpate() const;
    void mudarTurno();
    Jogador* getJogadorOponente();

public:
    Lig4(int linhas, int colunas, Jogador &jogador1, Jogador &jogador2);
    void partida() override;

};

#endif