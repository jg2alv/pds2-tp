#include <string>
#include <set>
#include <iostream>

#include "Sistema.h"

int Sistema::CadastrarJogador(std::string nome, std::string apelido) {
    std:: cout << apelido << nome;
    return 0;
}

int Sistema::RemoverJogador(std::string apelido) {
    std::cout << apelido;
    return 0;
}

int Sistema::ListarJogadores() {
    return 0;
}

int Sistema::JogadorExiste(std::string apelido) {
    // set.count()
    std::cout << apelido;
    return 0;
}

Comando Sistema::AnalisarComando(std::string comando)
{
    if (comando == "CJ") return Comando::CJ;
    else if (comando == "RJ") return Comando::RJ;
    else if (comando == "LJ") return Comando::LJ;
    else if (comando == "EP") return Comando::EP;
    else if (comando == "FS") return Comando::FS;
    else return Comando::IN;
}