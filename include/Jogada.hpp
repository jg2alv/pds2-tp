#ifndef JOGADA_HPP
#define JOGADA_HPP

/**
 * \class Jogada
 * 
 * \brief Classe que representa uma jogada em um jogo de tabuleiro.
 * 
 * Classe que armazena a linha e a coluna de uma jogada em um jogo de tabuleiro.
 * 
 */
class Jogada
{
private:
    int _linha;
    int _coluna;

public:
    Jogada(int coluna);
    Jogada(int linha, int coluna);
    int get_linha()const;
    int get_coluna()const;
    void set_linha(int linha);
};

#endif
