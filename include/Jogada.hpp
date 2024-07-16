#ifndef JOGADA_HPP
#define JOGADA_HPP

class Jogada
{
private:
    int _linha;
    int _coluna;

public:
    Jogada(int coluna);
    Jogada(int linha, int coluna);
    int get_linha();
    int get_coluna();
};

#endif