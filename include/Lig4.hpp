#ifndef LIG4_HPP
#define LIG4_HPP

#include <vector>
#include <string>
#include <iostream>

#include "Jogada.hpp"
#include "Jogador.hpp"
#include "Jogo.hpp"

/**
 * \class Lig4
 * 
 * \brief Classe que representa o jogo Lig4
 * 
 * Lig4 é um jogo de tabuleiro jogado por dois jogadores.
 * O objetivo do jogo é que um jogador coloque no tabuleiro quatro peças
 * consecutivas de seu simbolo, seja em uma linha, coluna ou diagonal.
 * O primeiro jogador que completar esse objetivo vence o jogo. Caso todo 
 * o tabuleiro seja preenchido e nenhum jogador tenha conseguido colocar 
 * quatro peças consecutivas, os dois jogadores irao empatar e a partida 
 * termina.
 * Para jogar,o jogador da vez tera que digitar o numero de uma coluna do 
 * tabuleiro que deseja colocar sua peca. Caso a coluna nao exista ou esteja 
 * cheia, o jogador devera digitar outra coluna que seja valida.
 * Essa classe é responsavel por realizar uma partida do jogo Lig4. Ela tem
 * metodos que imprime o tabuleiro do jogo, que le uma jogada de um jogador, 
 * que verifica se a jogada esta no formato correto e é valida, que adiociona
 * a nova peça no tabuleiro e que verifica se houve empate ou vitoria.
 */
class Lig4 : public Jogo {
private:
    int get_linha_tabuleiro(int coluna) const;
    bool linha_vazia(int linha) const;
    bool coluna_vazia(int coluna) const;
    bool tabuleiro_cheio() const;
    bool jogada_valida(Jogada &jogada) const;
    void realizar_jogada(const Jogada &jogada);

public:
    Lig4(int linhas, int colunas, Jogador &jogador1, Jogador &jogador2);
    Lig4(int linhas, int colunas, Jogador &jogador1, Jogador &jogador2, std::vector<std::vector<char>> tabuleiro);
    ~Lig4();

    virtual std::string getNome() const override;
    virtual void imprimirTabuleiro(std::ostream& out) const override;
    virtual bool formatoCorreto(std::string possivel_jogada) const override;
    virtual bool jogadaValida(std::string possivel_jogada) const override;
    virtual void realizarJogada(std::string possivel_jogada) override;
    virtual bool verificarVitoria(Jogador const&) const override;
    virtual bool verificarEmpate() const override;
};

#endif