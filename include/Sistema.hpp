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
        std::istream& __in;
        std::ostream& __out;
        std::string __bancodedados;
        bool salvar_ao_sair;

    public:
        bool isSistemaFinalizado();
        Comando analisarComando(std::string comando);
        void executarComando(Comando comando_analisado);
        std::vector<Jogador *>::iterator acharJogador(std::string apelido);
        void cadastrarJogador(std::string nome, std::string apelido);
        void removerJogador(std::string apelido);
        void listarJogadores(std::string criterio);
        void executarPartida(std::string nome_do_jogo);
        void carregarArquivo();
        void salvarSistema();
        void limparSistema();
        Sistema(std::istream& in, std::ostream& out, std::string bancodedados, bool salvar_ao_sair = true);
        ~Sistema();
};

#endif
