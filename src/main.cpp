#include <iostream>
#include <string>
#include <exception>

#include "Jogador.hpp"
#include "Sistema.hpp"
#include "Jogo.hpp"

int main() {
    Sistema* sistema = new Sistema();

    while (true) {
        std::string comando; std::cin >> comando;
        Comando comando_analisado = sistema->analisarComando(comando);
        try {
            std::string saida = sistema->executarComando(comando_analisado);
            std::cout << saida << std::endl;
        }
        catch(const std::exception& e) {
            std::cerr << "ERRO: " << e.what() << std::endl;
        }
    }

    delete sistema;

    return 0;
}
