#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "Jogador.hpp"

using namespace std;

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
        vector<Jogador> jogadores;
        bool sistema_finalizado = false;
        string banco_de_dados;
        bool salvar_ao_sair;

    public:
        enum class Comando {
            CadastrarJogador,
            RemoverJogador,
            ListarJogadores,
            ExecutarPartida,
            FinalizarSistema,
            Ajuda
        };
        static Sistema::Comando identificar_comando(string candidato_a_comando);
        bool isSistemaFinalizado();
        vector<Jogador>::iterator acharJogador(string apelido);
        void cadastrarJogador(string nome, string apelido);
        void removerJogador(string apelido);
        void listarJogadores(string base, ostream& out);
        void finalizarSistema();
        void executarPartida(string nome_do_jogo, string apelido1, string apelido2, istream& in, ostream& out);
        void carregarArquivo();
        void salvarSistema();
        void limparSistema();
        Sistema(string banco_de_dados, bool salvar_ao_sair = true);
        ~Sistema();
};

#endif
