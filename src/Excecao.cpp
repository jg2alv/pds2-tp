#include <iostream>
#include <string>

#include "Excecao.hpp"

Excecao::Excecao(std::string mensagem) : _mensagem(mensagem) {};
const char* Excecao::what() const throw() {
    return this->_mensagem.c_str();
}