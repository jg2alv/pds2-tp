#include <iostream>
#include <string>
#include <exception>

#include "Jogador.hpp"
#include "Sistema.hpp"
#include "Jogo.hpp"

int main() {
    Sistema sistema(std::cin, std::cout, "./data/jogadores.txt");

    while (!sistema.isSistemaFinalizado()) {
        std::string comando; std::cin >> comando;
        Comando comando_analisado = sistema.analisarComando(comando);
        try {
            sistema.executarComando(comando_analisado);
        }
        catch(const std::exception& e) {
            std::cerr << "ERRO: " << e.what() << std::endl;
        }
    }

    return 0;
}
