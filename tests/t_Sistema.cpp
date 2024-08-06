#include <string>
#include <sstream>

#include "doctest.h"
#include "Sistema.hpp"


using namespace std;


TEST_CASE("Teste para Sistema") {

    SUBCASE("Primeiro arquivo de testes para Sistema") {
        REQUIRE_NOTHROW(Sistema("./test_data/jogadores1.txt", false));
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

        stringstream().swap(saida);
        stringstream extras("4 4");
        stringstream entrada("cancela");
        REQUIRE_NOTHROW(sistema.executarPartida("Lig4", "A", "B", extras, entrada, saida));

        saida_esperada = "A Alice\n"
                         "Lig4 - V: 0 D: 1 E: 3\n"
                         "Reversi - V: 2 D: 1 E: 0\n"
                         "B Bruno\n"
                         "Lig4 - V: 5 D: 0 E: 1\n"
                         "C Carol\n"
                         "JogoDaVelha - V: 0 D: 4 E: 2\n"
                         "Lig4 - V: 0 D: 0 E: 3\n"
                         "Reversi - V: 0 D: 1 E: 0\n"
                         "D Diogo\n";

        stringstream().swap(saida);
        sistema.listarJogadores("A", saida);
        CHECK(saida.str() == saida_esperada);

        sistema.finalizarSistema();
        CHECK(sistema.isSistemaFinalizado());
    }
    SUBCASE("Segundo arquivo de testes para Sistema") {
        REQUIRE_NOTHROW(Sistema("./test_data/jogadores2.txt", false));
        Sistema sistema("./test_data/jogadores2.txt", false);

        stringstream saida;
        sistema.listarJogadores("A", saida);
        CHECK(saida.str() == "davi Elias\njosue Abraao\n");

        stringstream().swap(saida);
        sistema.listarJogadores("N", saida);
        CHECK(saida.str() == "josue Abraao\ndavi Elias\n");

        stringstream().swap(saida);
        stringstream extras("4");
        stringstream entrada("desisto");
        REQUIRE_NOTHROW(sistema.executarPartida("Reversi", "josue", "davi", extras, entrada, saida));

        string saida_esperada = "josue Abraao\n"
                                "Reversi - V: 0 D: 1 E: 0\n"
                                "davi Elias\n"
                                "Reversi - V: 1 D: 0 E: 0\n";

        stringstream().swap(saida);
        sistema.listarJogadores("N", saida);
        CHECK(saida.str() == saida_esperada);

        REQUIRE_THROWS(sistema.removerJogador("paulo"));
        REQUIRE_NOTHROW(sistema.removerJogador("josue"));
        REQUIRE_NOTHROW(sistema.removerJogador("davi"));
        REQUIRE_THROWS(sistema.removerJogador("davi"));

        stringstream().swap(saida);
        sistema.listarJogadores("A", saida);
        CHECK(saida.str() == "Nao existe jogadores cadastrados no sistema.\n");

        sistema.finalizarSistema();
        REQUIRE(sistema.isSistemaFinalizado());
    }
    SUBCASE("Terceiro arquivo de teste para o Sistema") {
        REQUIRE_NOTHROW(Sistema("./test_data/jogadores3.txt", false));
        Sistema sistema("./test_data/jogadores3.txt", false);
        
        stringstream saida;
        sistema.listarJogadores("A", saida);
        CHECK(saida.str() == "Nao existe jogadores cadastrados no sistema.\n");

        stringstream().swap(saida);
        sistema.listarJogadores("N", saida);
        CHECK(saida.str() == "Nao existe jogadores cadastrados no sistema.\n");
        
        REQUIRE_NOTHROW(sistema.cadastrarJogador("apelido", "nome"));
        REQUIRE_THROWS(sistema.cadastrarJogador("apelido", "outro nome"));
        REQUIRE_NOTHROW(sistema.cadastrarJogador("outro_apelido", "nome"));

        stringstream().swap(saida);
        stringstream extras("4 4");
        stringstream entrada("1 1\n2 1\n1 2\n2 2\n1 3\n");
        REQUIRE_THROWS(sistema.executarPartida("JogoDaVelha", "apelido", "outro_apelido", extras, entrada, saida));

        stringstream().swap(saida);
        sistema.listarJogadores("A", saida);
        CHECK(saida.str() == "apelido nome\noutro_apelido nome\n");

        stringstream().swap(saida);
        sistema.listarJogadores("N", saida);
        CHECK(saida.str() == "apelido nome\noutro_apelido nome\n");

        sistema.finalizarSistema();
        REQUIRE(sistema.isSistemaFinalizado());
    }

    REQUIRE_THROWS(Sistema("./test_data/jogadores4.txt", false));
}


