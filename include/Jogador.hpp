#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <string>

class Jogador {
private:
    std::string _apelido;
    std::string _nome;

public:
    Jogador(std::string apelido, std::string nome);
    std::string getApelido();
    std::string getNome();
};

#endif

