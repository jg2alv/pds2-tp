#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <string>
#include <set>

#include "Jogador.hpp"

enum class Comando
{
    CJ,
    RJ,
    LJ,
    EP,
    FS,
    IN
};

class Sistema
{
    private:
        std::set<Jogador*> __jogadores;

    public:
        Comando AnalisarComando(std::string comando);
        int CadastrarJogador(std::string nome, std::string apelido);
        int RemoverJogador(std::string apelido);
        int ListarJogadores();
        int JogadorExiste(std::string apelido);
};

#endif

