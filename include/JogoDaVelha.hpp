#ifndef JOGODAVELHA_HPP
#define JOGODAVELHA_HPP

#include <vector>
#include <string>

#include "Jogada.hpp"
#include "Jogo.hpp"
#include "Jogador.hpp"

/**
 * \class JogoDaVelha
 * 
 * \brief Classe que representa o jogo da velha
 * 
 * Jogo da velha é um jogo de tabuleiro (3 x 3) jogado por dois jogadores.
 * O objetivo do jogo é que um jogador coloque no tabuleiro três peças
 * consecutivas de seu símbolo, seja em uma linha, coluna ou diagonal.
 * O primeiro jogador que completar esse objetivo vence o jogo. Caso todo 
 * o tabuleiro seja preenchido e nenhum jogador tenha conseguido colocar 
 * três peças consecutivas, os dois jogadores empataram.
 * Para jogar, o jogador da vez terá que digitar o número de uma linha e de
 * uma coluna do tabuleiro que deseja colocar sua peça. Caso as coordenadas
 * não estejam dentro dos limites do tabuleiro ou a posição esteja ocupada, 
 * o jogador deverá digitar outra linha e outra coluna que sejam válidas.
 * Essa classe é responsável por realizar uma partida do jogo da velha. Ela 
 * tem métodos que imprime o tabuleiro do jogo, que lê uma jogada de um jogador, 
 * que verifica se a jogada está no formato correto e é válida, que adiciona
 * a nova peça no tabuleiro e que verifica se houve empate ou vitória.
 */
class JogoDaVelha : public Jogo {
private:
    bool tabuleiro_cheio() const;
    bool jogada_valida(const Jogada &jogada) const;
    void realizar_jogada(const Jogada &jogada);

public:
    JogoDaVelha(Jogador &jogador1, Jogador &jogador2);
    ~JogoDaVelha();

    virtual std::string getNome() const override;
    virtual void imprimirTabuleiro(std::ostream& out) const override;
    virtual bool formatoCorreto(std::string possivel_jogada) const override;
    virtual bool jogadaValida(std::string possivel_jogada) const override;
    virtual void realizarJogada(std::string possivel_jogada) override;
    virtual bool verificarVitoria(Jogador const&) const override;
    virtual bool verificarEmpate() const override;
};

#endif
