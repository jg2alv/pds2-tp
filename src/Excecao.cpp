#include <iostream>
#include <string>

#include "Excecao.hpp"

using namespace std;

/**
 * \brief Esse costrutor recebe a mensagem assiciada a Excecao.
 *
 * A mensagem recebida por esse método é a mesma retornada por `Excecao::what()`.
 * \see what()
 * \param mensagem Mensagem associada à Excecao.
 */
Excecao::Excecao(string mensagem) : std::runtime_error(mensagem), _mensagem(mensagem) {};


/**
 * \brief Essa função retorna a mensagem associada à Excecao.
 *
 * O ponteiro retornado por essa função é para o caratere inicial uma C-style string igual à mensagem introduzida no construtor.
 * \see Excecao()
 * \return Mensagem associada à Excecao como uma C-style string.
 */
const char* Excecao::what() const throw() {
    return _mensagem.c_str();
}
