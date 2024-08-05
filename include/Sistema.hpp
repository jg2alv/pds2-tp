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
    FinalizarSistema,
    Ajuda
};


Comando identificar_comando(std::string candidato_a_comando);

/**
 * \class Sistema
 * 
 * \brief Classe que lida com a interface usuario-sistema
 *
 * Essa classe cuida da interacao entre o jogador e o Sistema.
 * Com um metodo para cada comando do sistema, essa classe
 * representa o sistema como um todo e eh a intermediaria em
 * todas as interacoes entre o usuario e o sistema de jogos.
 * Ela eh a responsavel por criar, remover e listar jogadores;
 * alem de carregar as informacoes do disco na memoria, e salvar
 * as informacoes da memoria de volta no disco.
*/
class Sistema {
    private:
        std::vector<Jogador> jogadores;
        bool sistema_finalizado = false;
        std::string banco_de_dados;
        bool salvar_ao_sair;

    public:
        bool isSistemaFinalizado();
        std::vector<Jogador>::iterator acharJogador(std::string apelido);
        void cadastrarJogador(std::string nome, std::string apelido);
        void removerJogador(std::string apelido);
        void listarJogadores(std::string base, std::ostream& out);
        void finalizarSistema();
        void executarPartida(std::string nome_do_jogo, std::string apelido1, std::string apelido2, std::istream& in, std::ostream& out);
        void carregarArquivo();
        void salvarSistema();
        void limparSistema();
        Sistema(std::string banco_de_dados, bool salvar_ao_sair = true);
        ~Sistema();
};

#endif
