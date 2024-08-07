#include "Jogada.hpp"

/**
 * \brief Construtor de jogada
 * 
 * Construtor que inicializa Jogada com uma determinada coluna, e a linha 0.
 * 
 * \param coluna coluna da jogada
 */
Jogada::Jogada(int coluna) : Jogada(0, coluna) {}

/**
 * \brief Construtor de jogada
 * 
 * Construtor que inicializa Jogada com uma determinada linha e coluna.
 * 
 * \param linha linha da jogada
 * \param coluna coluna da jogada
 */
Jogada::Jogada(int linha, int coluna) : _linha(linha), _coluna(coluna) {}

/**
 * \brief Retorna a linha da jogada
 * 
 * Função que retorna a linha da Jogada.
 * 
 * \return linha da jogada
 */
int Jogada::get_linha()const
{
    return _linha;
}

/**
 * \brief Retorna a coluna da jogada
 * 
 * Função que retorna a coluna da Jogada.
 * 
 * \return coluna da jogada
 */
int Jogada::get_coluna()const
{
    return _coluna;
}

/**
 * \brief Define a linha da jogada
 * 
 * Função que redefine a linha da Jogada.
 * 
 * \param linha linha da jogada
 */
void Jogada::set_linha(int linha)
{
    _linha = linha;
}
