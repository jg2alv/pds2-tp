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
        bool __sistema_finalizado = false;

    public:
        bool isSistemaFinalizado();
        Comando analisarComando(std::string comando);
        std::string executarComando(Comando comando_);
        std::vector<Jogador *>::iterator acharJogador(std::string apelido);
        std::string cadastrarJogador(std::string nome, std::string apelido);
        std::string removerJogador(std::string apelido);
        std::string listarJogadores(std::string criterio);
        ~Sistema();
};

#endif