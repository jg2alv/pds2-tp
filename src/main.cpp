#include <iostream>
#include <string>
#include <exception>
#include <sstream>

#include "Jogador.hpp"
#include "Sistema.hpp"
#include "Jogo.hpp"
#include "Excecao.hpp"

using namespace std;

int main() {
    try {
        Sistema sistema("./data/jogadores.txt");

        while (!sistema.isSistemaFinalizado()) {
            cout << "Entre um comando ou digite ? para ajuda: ";

            string candidato_a_comando_string, candidato_a_comando;
            getline(cin, candidato_a_comando_string);
            stringstream candidato_a_comando_stream(candidato_a_comando_string);
            candidato_a_comando_stream >> candidato_a_comando;
            try {
                switch (Sistema::identificar_comando(candidato_a_comando)) {
                    case Sistema::Comando::CadastrarJogador: {
                        std::string apelido, nome;
                        candidato_a_comando_stream >> apelido;
                        getline(candidato_a_comando_stream, nome);
                        sistema.cadastrarJogador(apelido, nome.erase(0, 1));
                        cout << "Jogador " << apelido << " cadastrado com sucesso\n";
                        break;
                    }
                    case Sistema::Comando::RemoverJogador: {
                        string apelido;
                        candidato_a_comando_stream >> apelido;
                        bool stream_terminou = candidato_a_comando_stream.eof();
                        if(!stream_terminou) throw Excecao("RJ aceita apenas um argumento: RJ [apelido]");
                        sistema.removerJogador(apelido);
                        cout << "Jogador " << apelido << " removido com sucesso\n";
                        break;
                    }
                    case Sistema::Comando::ListarJogadores: {
                        string base;
                        candidato_a_comando_stream >> base;
                        bool stream_terminou = candidato_a_comando_stream.eof();
                        if(!stream_terminou) throw Excecao("LJ aceita apenas um argumento: LJ [A | N]");
                        sistema.listarJogadores(base, cout);
                        break;
                    }
                    case Sistema::Comando::ExecutarPartida: {
                        string nome_do_jogo, apelido1, apelido2;
                        candidato_a_comando_stream >> nome_do_jogo >> apelido1 >> apelido2;
                        bool stream_terminou = candidato_a_comando_stream.eof();
                        if(!stream_terminou) throw Excecao("EP aceita apenas 3 argumentos: EP [jogo] [apelido-1] [apelido-2]");
                        sistema.executarPartida(nome_do_jogo, apelido1, apelido2, cin, cout);
                        break;
                    }
                    case Sistema::Comando::FinalizarSistema: {
                        bool stream_terminou = candidato_a_comando_stream.eof();
                        if(!stream_terminou) throw Excecao("FS nao aceita argumentos");
                        sistema.finalizarSistema();
                        break;
                    }
                    case Sistema::Comando::Ajuda: {
                        cout << "CJ [apelido] [nome]                   Cadastra um jogador com um apelido unico." << endl;
                        cout << "RJ [apelido]                          Remove o jogador com o apelido recebido." << endl;
                        cout << "LJ [A | N]                            Lista os jogadores cadastrados em ordem de apelido/ nome." << endl;
                        cout << "EP [jogo] [apelido-1] [apelido-2]     Executa uma partida entre jogadores identificados por apelido (jogos: JogoDaVelha, Lig4, Reversi, Xadrez)." << endl;
                        cout << "FS                                    Encerra a execucao do sistema, salvando as modificacoes em disco." << endl;
                        cout << "?                                     Imprime essa mensagem de ajuda." << endl;
                    }
                }
            } catch (const std::runtime_error& e) {
                cout << "ERRO: " << e.what() << endl;
            }
        }
    } catch(std::runtime_error& e) {
        cout << "ERRO: " << e.what() << endl;
    }

    return 0;
}

