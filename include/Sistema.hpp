#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Jogador.hpp"

/**
 * \brief Classe que lida com a interface usuario-sistema
 *
 * Essa classe cuida da interação entre o jogador e o Sistema.
 * Com um método para cada comando do sistema, essa classe
 * representa o sistema como um todo e é a intermediária em
 * todas as interações entre o usuário e o sistema de jogos.
 * Ela é a responsável por criar, remover e listar jogadores;
 * além de carregar as informações do disco na memória, e salvar
 * as informações da memória de volta no disco.
*/
class Sistema {
    private:
        std::vector<Jogador> jogadores;
        bool sistema_finalizado = false;
        std::string banco_de_dados;
        bool salvar_ao_sair;

        std::vector<Jogador>::iterator achar_jogador(std::string apelido);

    public:
        enum class Comando {
            CadastrarJogador,
            RemoverJogador,
            ListarJogadores,
            ExecutarPartida,
            FinalizarSistema,
            Ajuda
        };
        static Sistema::Comando identificar_comando(std::string candidato_a_comando);
        bool isSistemaFinalizado();
        void cadastrarJogador(std::string nome, std::string apelido);
        void removerJogador(std::string apelido);
        void listarJogadores(std::string base, std::ostream& out);
        void finalizarSistema();
        void executarPartida(std::string nome_do_jogo, std::string apelido1, std::string apelido2, std::stringstream& extras, std::istream& in, std::ostream& out);
        void carregarArquivo();
        void salvarSistema();
        void limparSistema();
        Sistema(std::string banco_de_dados, bool salvar_ao_sair = true);
        ~Sistema();
};

#endif
