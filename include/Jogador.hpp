#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <string>

class Jogador {
private:
    std::string _nome;
    std::string _apelido;

public:
    Jogador(std::string apelido, std::string nome);
    std::string getApelido();
    std::string getNome();
};

#endif

