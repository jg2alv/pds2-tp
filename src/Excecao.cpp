#include <iostream>
#include <string>

#include "Excecao.hpp"

using namespace std;

Excecao::Excecao(string mensagem) : mensagem(mensagem) {};
const char* Excecao::what() const throw() {
    return mensagem.c_str();
}