#include <iostream>
#include <string>

#include "Excecoes.hpp"

using namespace std;

Excecao::Excecao(string mensagem) : std::runtime_error(mensagem), _mensagem(mensagem) {};
const char* Excecao::what() const throw() {
    return _mensagem.c_str();
}

ExcecaoDoJogoDaVelha::ExcecaoDoJogoDaVelha(string mensagem) : Excecao(mensagem), _mensagem(mensagem) {};
const char* ExcecaoDoJogoDaVelha::what() const throw() {
    return _mensagem.c_str();
}

ExcecaoDoLig4::ExcecaoDoLig4(string mensagem) : Excecao(mensagem), _mensagem(mensagem) {};
const char* ExcecaoDoLig4::what() const throw() {
    return _mensagem.c_str();
}

ExcecaoDoReversi::ExcecaoDoReversi(string mensagem) : Excecao(mensagem), _mensagem(mensagem) {};
const char* ExcecaoDoReversi::what() const throw() {
    return _mensagem.c_str();
}

ExcecaoDoSistema::ExcecaoDoSistema(string mensagem) : Excecao(mensagem), _mensagem(mensagem) {};
const char* ExcecaoDoSistema::what() const throw() {
    return _mensagem.c_str();
}

ExcecaoDoXadrez::ExcecaoDoXadrez(string mensagem) : Excecao(mensagem), _mensagem(mensagem) {};
const char* ExcecaoDoXadrez::what() const throw() {
    return _mensagem.c_str();
}