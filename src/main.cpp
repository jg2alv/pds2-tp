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
        string candidato_a_comando;
        cin >> candidato_a_comando;
        try {
            switch (identificar_comando(candidato_a_comando)) {
                case Comando::CadastrarJogador: {
                    std::string apelido, nome;
                    cin >> apelido;
                    getline(cin, nome);
                    sistema.cadastrarJogador(apelido, nome.erase(0, 1));
                    cout << "Jogador " << apelido << " cadastrado com sucesso\n";
                    break;
                }
                case Comando::RemoverJogador: {
                    string apelido;
                    cin >> apelido;
                    sistema.removerJogador(apelido);
                    cout << "Jogador " << apelido << " removido com sucesso\n";
                    break;
                }
                case Comando::ListarJogadores: {
                    string criterio;
                    cin >> criterio;
                    sistema.listarJogadores(criterio, cout);
                    break;
                }
                case Comando::ExecutarPartida: {
                    string nome_do_jogo, apelido1, apelido2;
                    cin >> nome_do_jogo >> apelido1 >> apelido2;
                    cin.ignore();
                    sistema.executarPartida(nome_do_jogo, apelido1, apelido2, cin, cout);
                    break;
                }
                case Comando::FinalizarSistema: {
                    sistema.finalizarSistema();
                    break;
                }
            }
        } catch (const std::exception& e) {
            cout << "ERRO: " << e.what() << endl;
        }
    }

    return 0;
}

