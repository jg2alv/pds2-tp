#include <string>
#include <sstream>

#include "doctest.h"
#include "Sistema.hpp"


using namespace std;


TEST_CASE("Teste para Sistema") {
    SUBCASE("Arquivo de teste 1") {
        Sistema sistema("./test_data/jogadores1.txt", false);

        string saida_esperada = "A Alice\n"
                                 "Lig4 - V: 0 D: 1 E: 2\n"
                                 "Reversi - V: 2 D: 1 E: 0\n"
                                 "B Bruno\n"
                                 "Lig4 - V: 5 D: 0 E: 0\n"
                                 "C Carol\n"
                                 "JogoDaVelha - V: 0 D: 4 E: 2\n"
                                 "Lig4 - V: 0 D: 0 E: 3\n"
                                 "Reversi - V: 0 D: 1 E: 0\n"
                                 "D Diogo\n";
        
        stringstream saida;

        sistema.listarJogadores("A", saida);
        CHECK(saida.str() == saida_esperada);

        stringstream().swap(saida);

        sistema.listarJogadores("N", saida);
        CHECK(saida.str() == saida_esperada);
    }
    SUBCASE("Arquivo de teste 2") {
        Sistema sistema("./test_data/jogadores2.txt", false);

        stringstream saida;

        sistema.listarJogadores("A", saida);
        CHECK(saida.str() == "davi Elias\njosue Abraao\n");

        stringstream().swap(saida);

        sistema.listarJogadores("N", saida);
        CHECK(saida.str() == "josue Abraao\ndavi Elias\n");
    }
    SUBCASE("Arquivo de teste 3") {
        Sistema sistema("./test_data/jogadores3.txt", false);
        
        stringstream saida;

        sistema.listarJogadores("A", saida);
        CHECK(saida.str() == "Nao existe jogadores cadastrados no sistema.\n");

        stringstream().swap(saida);

        sistema.listarJogadores("N", saida);
        CHECK(saida.str() == "Nao existe jogadores cadastrados no sistema.\n");
    }
}


