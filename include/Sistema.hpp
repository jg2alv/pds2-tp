#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

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
        void executarComando(Comando comando_analisado);
        std::vector<Jogador *>::iterator acharJogador(std::string apelido);
        void cadastrarJogador(std::string nome, std::string apelido);
        void removerJogador(std::string apelido);
        void listarJogadores(std::string criterio);
        void executarPartida(std::string jogo);
        void carregarArquivo();
        void salvarSistema();
        void limparSistema();
        Sistema();
        ~Sistema();
};

#endif