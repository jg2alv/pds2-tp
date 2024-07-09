#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <string>
#include <vector>

#include "Jogador.hpp"

enum class Comando {
    CadastrarJogador,
    RemoverJogador,
    ListarJogadores,
    ExecutarPartida,
    FinalizarSistema
};

class Sistema {
    private:
        std::vector<Jogador*> __jogadores;

    public:
        Comando analisarComando(std::string comando);
        std::string executarComando(Comando comando_);
        void cadastrarJogador(std::string nome, std::string apelido);
        void removerJogador(std::string apelido);
        int listarJogadores();
        bool jogadorExiste(std::string apelido);
};

#endif