#ifndef XADREZ_HPP
#define XADREZ_HPP

#include <vector>
#include <string>
#include <iostream>
#include <map>

#include "Jogador.hpp"
#include "Jogo.hpp"
/**
 * \class Xadrez
 * 
 * \brief classe que implementa o jogo 'Xadrez'
 * 
 * Xadrez é um jogo de tabuleiro extremamente famoso, e muito antigo. Consiste em um jogo um contra um, 
 * em que o objetivo de cada jogador é tirar o Rei adversário de campo. 
 * O tabuleiro é dividido em 8 linhas e 8 colunas, coloridas alternadamente de preto e branco.
 * Para concluir o objetivo, cada jogador recebe um conjunto de peças, pretas ou brancas, que consiste de:
 * 
 * - 8 peões: peões podem se mover apenas uma casa para frente, com excessão da primeira vez que se movem, 
 * condição que permite avançarem duas casas a frente. Peões podem retirar peças oponentes presentes apenas nas diagonais
 * superiores esquerda e direita ao peão.
 * - 2 torres: torres podem se mover quantas casas quiserem para frente, trás, esquerda ou direita. Torres podem
 * retirar peças oponentes presentes em qualquer posição em seu caminho, caso não haja outra peça presente entre eles.
 * - 2 cavalos: cavalos podem se mover formato de 'L', 3 casas para uma direção, 2 para outra (3 para frente, 2 para a esqueda, por exemplo). 
 * Cavalos podem retirar peças oponentes caso estejam presentes na posição final do movimento.
 * - 2 bispos: bispos podem se mover quantas casas quiserem nas diagonais. Bispos podem retirar peças oponentes presentes em seu caminho, 
 * caso não haja nenhuma outra peça entre elas.
 * - 1 rainha: a rainha pode se mover quantas casas quiser, para qualquer direção. A rainha pode retirar uma peça oponente presente em seu
 * caminho, caso não haja nenhuma outra peça entre eles.
 * - 1 rei: o rei é a peça que deve ser protegida, ou retirada, caso seja do oponente. Ele pode se mover apenas 1 casa, em qualquer direção.
 * O rei pode retirar uma peça oponente caso ela esteja adjacente a ele.
 * 
 *
 */
class Xadrez : public Jogo {
public:
    Xadrez(Jogador &jogador1, Jogador &jogador2);
    ~Xadrez();

    virtual std::string getNome() const override;
    virtual void imprimirTabuleiro(std::ostream& out) const override;
    virtual bool formatoCorreto(std::string possivel_jogada) const override;
    virtual bool jogadaValida(std::string possivel_jogada) const override;
    virtual void realizarJogada(std::string possivel_jogada) override;
    virtual bool verificarVitoria(Jogador const&) const override;
    virtual bool verificarEmpate() const override;
};

#endif
