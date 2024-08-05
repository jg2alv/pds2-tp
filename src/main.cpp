#include <iostream>
#include <string>
#include <exception>

#include "Jogador.hpp"
#include "Sistema.hpp"
#include "Jogo.hpp"


using namespace std;


int main() {
    Sistema sistema("./data/jogadores.txt");

    while (!sistema.isSistemaFinalizado()) {
        cout << "Entre um comando ou digite ? para ajuda: ";

        string candidato_a_comando;
        cin >> candidato_a_comando;
        try {
            switch (Sistema::identificar_comando(candidato_a_comando)) {
                case Sistema::Comando::CadastrarJogador: {
                    std::string apelido, nome;
                    cin >> apelido;
                    getline(cin, nome);
                    sistema.cadastrarJogador(apelido, nome.erase(0, 1));
                    cout << "Jogador " << apelido << " cadastrado com sucesso\n";
                    break;
                }
                case Sistema::Comando::RemoverJogador: {
                    string apelido;
                    cin >> apelido;
                    sistema.removerJogador(apelido);
                    cout << "Jogador " << apelido << " removido com sucesso\n";
                    break;
                }
                case Sistema::Comando::ListarJogadores: {
                    string criterio;
                    cin >> criterio;
                    sistema.listarJogadores(criterio, cout);
                    break;
                }
                case Sistema::Comando::ExecutarPartida: {
                    string nome_do_jogo, apelido1, apelido2;
                    cin >> nome_do_jogo >> apelido1 >> apelido2;
                    cin.ignore();
                    sistema.executarPartida(nome_do_jogo, apelido1, apelido2, cin, cout);
                    break;
                }
                case Sistema::Comando::FinalizarSistema: {
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
        } catch (const std::exception& e) {
            cout << "ERRO: " << e.what() << endl;
        }
    }

    return 0;
}

