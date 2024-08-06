#include <iostream>
#include <string>

#include "Excecao.hpp"

using namespace std;

Excecao::Excecao(string mensagem) : std::runtime_error(mensagem), _mensagem(mensagem) {};
const char* Excecao::what() const throw() {
    return _mensagem.c_str();
}