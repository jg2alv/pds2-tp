#include <iostream>
#include <string>
#include <exception>

#include "Jogador.hpp"
#include "Sistema.hpp"
#include "Jogo.hpp"

int main() {
    Sistema sistema;

    while (!sistema.isSistemaFinalizado()) {
        std::string comando; std::cin >> comando;
        Comando comando_analisado = sistema.analisarComando(comando);
        try {
            std::string saida = sistema.executarComando(comando_analisado);
            bool saida_vazia = (saida.length() == 0);

            if(!saida_vazia) std::cout << saida << std::endl;
        }
        catch(const std::exception& e) {
            std::cerr << "ERRO: " << e.what() << std::endl;
        }
    }

    return 0;
}
