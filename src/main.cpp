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

            string linha_entrada;
            getline(cin, linha_entrada);
            stringstream linha_entrada_stream(linha_entrada);
            try {
                string candidato_a_comando;
                if (!(linha_entrada_stream >> candidato_a_comando)) {
                    continue;
                }

                switch (Sistema::identificar_comando(candidato_a_comando)) {
                    case Sistema::Comando::CadastrarJogador: {
                        string apelido, nome;
                        string string_de_teste;
                        if (linha_entrada_stream >> apelido && getline(linha_entrada_stream, nome) && stringstream(nome) >> string_de_teste) {
                            sistema.cadastrarJogador(apelido, nome.erase(0, 1));
                            cout << "Jogador " << apelido << " cadastrado com sucesso\n";
                            break;
                        } else {
                            throw Excecao("CJ aceita dois argumentos: CJ [apelido] [nome]");
                        }
                    }
                    case Sistema::Comando::RemoverJogador: {
                        string apelido;
                        string string_de_teste;
                        if (linha_entrada_stream >> apelido && !(linha_entrada_stream >> string_de_teste)) {
                            sistema.removerJogador(apelido);
                            cout << "Jogador " << apelido << " removido com sucesso\n";
                            break;
                        } else {
                            throw Excecao("RJ aceita apenas um argumento: RJ [apelido]");
                        }
                    }
                    case Sistema::Comando::ListarJogadores: {
                        string base;
                        string string_de_teste;
                        if (linha_entrada_stream >> base && !(linha_entrada_stream >> string_de_teste)) {
                            sistema.listarJogadores(base, cout);
                            break;
                        } else {
                            throw Excecao("LJ aceita apenas um argumento: LJ [A | N]");
                        }
                    }
                    case Sistema::Comando::ExecutarPartida: {
                        string nome_do_jogo, apelido1, apelido2;
                        if (linha_entrada_stream >> nome_do_jogo && linha_entrada_stream >> apelido1 && linha_entrada_stream >> apelido2) {
                            sistema.executarPartida(nome_do_jogo, apelido1, apelido2, linha_entrada_stream, cin, cout);
                            break;
                        } else {
                            throw Excecao("EP aceita pelo menos dois tres argumentos: EP [jogo] [apelido-1] [apelido-2] {extras}");
                        }
                    }
                    case Sistema::Comando::FinalizarSistema: {
                        string string_de_teste;
                        if (!(linha_entrada_stream >> string_de_teste)) {
                            sistema.finalizarSistema();
                            break;
                        } else {
                            throw Excecao("FS nao aceita argumentos");
                        }
                    }
                    case Sistema::Comando::Ajuda: {
                        cout << "CJ [apelido] [nome]                           Cadastra um jogador com um apelido unico." << endl;
                        cout << "RJ [apelido]                                  Remove o jogador com o apelido recebido." << endl;
                        cout << "LJ [A | N]                                    Lista os jogadores cadastrados em ordem de apelido/ nome." << endl;
                        cout << "EP [jogo] [apelido-1] [apelido-2] {extras}    Executa uma partida entre jogadores identificados por apelido (jogos: JogoDaVelha, Lig4, Reversi, Xadrez)." << endl;
                        cout << "FS                                            Encerra a execucao do sistema, salvando as modificacoes em disco." << endl;
                        cout << "?                                             Imprime essa mensagem de ajuda." << endl;
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

