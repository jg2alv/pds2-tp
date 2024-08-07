#ifndef XADREZ_HPP
#define XADREZ_HPP

#include <vector>
#include <string>
#include <iostream>
#include <map>

#include "Jogador.hpp"
#include "Jogo.hpp"

/**
 * \brief Classe que implementa o jogo Xadrez
 * 
 * Xadrez é um jogo de tabuleiro extremamente famoso, e muito antigo. Consiste em um jogo um contra um, 
 * em que o objetivo de cada jogador é tirar o Rei adversário de campo. 
 * O tabuleiro é dividido em 8 linhas e 8 colunas, coloridas alternadamente de preto e branco.
 * Para concluir o objetivo, cada jogador recebe um conjunto de peças, pretas ou brancas, que consiste de:
 * 
 * - 8 peões: peões podem se mover apenas uma casa para frente, com excessão da primeira vez que se movem, 
 * condição que permite avançarem duas casas a frente. Peões podem capturar peças oponentes presentes apenas nas diagonais
 * esquerda e direita imediatamente acima do peão.
 * - 2 torres: torres podem se mover quantas casas quiserem para frente, trás, esquerda ou direita. Torres só podem se mover ou
 * capturar peças oponentes caso não haja outra peça no caminho.
 * - 2 cavalos: cavalos podem se mover formato de 'L', 2 casas para uma direção, 1 para outra (2 para frente, 1 para a esqueda, por exemplo). 
 * Cavalos podem se mover ou capturar peças oponentes independente das peças no caminho.
 * - 2 bispos: bispos podem se mover quantas casas quiserem nas diagonais. Bispos só podem se mover ou capturar peças oponentes
 *   caso não haja outra peça no caminho.
 * - 1 rainha: a rainha pode se mover quantas casas quiser, para qualquer direção. Rainhas só podem se mover ou capturar peças oponentes
 *   caso não haja outra peça no caminho.
 * - 1 rei: o rei é a peça que deve ser protegida, ou retirada, caso seja do oponente. Ele pode se mover apenas 1 casa, em qualquer direção.
 * O rei pode se mover ou capturar uma peça oponente caso esteja adjacente a ela.
 */
class Xadrez : public Jogo {
public:
    Xadrez(Jogador &jogador1, Jogador &jogador2);
    ~Xadrez();

    static void converterInput(char* linha, int* coluna);

    virtual std::string getNome() const override;
    virtual void imprimirTabuleiro(std::ostream& out) const override;
    virtual bool formatoCorreto(std::string possivel_jogada) const override;
    virtual bool jogadaValida(std::string possivel_jogada) const override;
    virtual void realizarJogada(std::string possivel_jogada) override;
    virtual bool verificarVitoria(Jogador const&) const override;
    virtual bool verificarEmpate() const override;
};

#endif
