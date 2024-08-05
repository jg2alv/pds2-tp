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
 * O objetivo do jogo é que um jogador coloque no tabuleiro tres peças
 * consecutivas de seu simbolo, seja em uma linha, coluna ou diagonal.
 * O primeiro jogador que completar esse objetivo vence o jogo. Caso todo 
 * o tabuleiro seja preenchido e nenhum jogador tenha conseguido colocar 
 * tres peças consecutivas, os dois jogadores irao empatar e a partida 
 * termina.
 * Para jogar, o jogador da vez tera que digitar o numero de uma linha e de
 * uma coluna do tabuleiro que deseja colocar sua peca. Caso as coordenadas
 * nao estejam dentro dos limites do tabuleiro ou a posicao esteja ocupada, 
 * o jogador devera digitar outra linha e outra coluna que sejam validas.
 * Essa classe é responsavel por realizar uma partida do jogo da velha. Ela 
 * tem metodos que imprime o tabuleiro do jogo, que le uma jogada de um jogador, 
 * que verifica se a jogada esta no formato correto e é valida, que adiociona
 * a nova peça no tabuleiro e que verifica se houve empate ou vitoria.
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
