#ifndef REVERSI_HPP
#define REVERSI_HPP

#include <vector>
#include <iostream>

#include "Jogador.hpp"
#include "Jogo.hpp"

/**
 * \class Reversi
 * 
 * \brief Classe que representa o jogo Reversi
 * 
 * Reversi é um jogo de tabuleiro jogado por dois jogadores. O objetivo do jogo é 
 * obter o maior número possível de peças do seu símbolo no tabuleiro ao final da 
 * partida. Os jogadores alternam turnos colocando peças em células vazias, com a 
 * condição de que a peça colocada deve "capturar" peças adversárias que estejam 
 * alinhadas entre a nova peça e outras peças do mesmo símbolo. A captura é feita 
 * virando as peças adversárias para o símbolo do jogador que fez a jogada. O jogo 
 * termina quando o tabuleiro está completamente preenchido ou quando nenhum dos 
 * jogadores pode fazer uma jogada válida. O jogador com o maior número de peças 
 * de seu símbolo no tabuleiro no final da partida é o vencedor.
 * A classe Reversi é responsável por gerenciar uma partida do jogo Reversi. Ela 
 * possui métodos para imprimir o tabuleiro do jogo, verificar se uma jogada é 
 * válida, realizar uma jogada, verificar se houve vitória ou empate e analisar o formato de entrada.
 * 
 */
using namespace std;

class Reversi : public Jogo {
private:
    bool dentroDosLimites(const Jogada& jogada) const;
    void reiniciarTabuleiro();
    bool jogada_valida(const Jogada& jogada, char simbolo) const;
    void realizar_jogada(const Jogada& jogada);
    int indicador_de_pontos() const;

public:
    Reversi(int linhas, int colunas, Jogador& jogador1, Jogador& jogador2);
    Reversi(int linhas, int colunas, Jogador& jogador1, Jogador& jogador2, vector<vector<char>> tabuleiro);
    ~Reversi();

    bool podeJogar(const Jogador& jogador) const;
    virtual string getNome() const override;
    virtual void imprimirTabuleiro(ostream& out) const override;
    virtual bool formatoCorreto(string possivel_jogada) const override;
    virtual bool jogadaValida(string possivel_jogada) const override;
    virtual void realizarJogada(string possivel_jogada) override;
    virtual bool verificarVitoria(Jogador const&) const override;
    virtual bool verificarEmpate() const override;
};


#endif
