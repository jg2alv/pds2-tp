#include "Jogada.hpp"

/**
 * \brief Construtor de jogada
 * 
 * Construtor que inicializa Jogada com uma determinada coluna, e a linha 0
 * 
 * \param coluna coluna da jogada
 */
Jogada::Jogada(int coluna) : Jogada(0, coluna) {}

/**
 * \brief Construtor de jogada
 * 
 * Construtor que inicializa Jogada com uma determinada linha e coluna
 * 
 * \param linha linha da jogada
 * \param coluna coluna da jogada
 */
Jogada::Jogada(int linha, int coluna) : _linha(linha), _coluna(coluna) {}

/**
 * \brief Retorna a linha da jogada
 * 
 * Função get_linha que retorna a linha de uma determinada jogada
 * 
 * \return linha da jogada
 */
int Jogada::get_linha()const
{
    return this->_linha;
}

/**
 * \brief Retorna a coluna da jogada
 * 
 * Função get_coluna que retorna a coluna de uma determinada jogada
 * 
 * \return coluna da jogada
 */
int Jogada::get_coluna()const
{
    return this->_coluna;
}

/**
 * \brief Define a linha da jogada
 * 
 * Função set_linha que define a linha de uma determinada jogada
 * 
 * \param linha linha da jogada
 */
void Jogada::set_linha(int linha)
{
    this->_linha = linha;
}
