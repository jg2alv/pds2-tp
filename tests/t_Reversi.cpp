#include <memory>

#include "doctest.h"
#include "Reversi.hpp"
#include "Jogador.hpp"
#include "Jogada.hpp"
#include "Jogo.hpp"


using namespace std;


TEST_CASE("Testando Reversi") {
    Jogador alice("A", "Alice");
    Jogador bruno("B", "Bruno");
    
    SUBCASE("Testando tabuleiro inicial Reversi") {
        unique_ptr<Reversi> reversi(new Reversi(8, 8, alice, bruno));

        CHECK_FALSE(reversi->verificarVitoria(alice));
        CHECK_FALSE(reversi->verificarVitoria(bruno));
        CHECK_FALSE(reversi->verificarEmpate());

        SUBCASE("Testando realizarJogada do Reversi") {
            REQUIRE_THROWS(reversi->realizarJogada("teste"));
            REQUIRE_THROWS(reversi->realizarJogada("3 4 4"));
            REQUIRE_THROWS(reversi->realizarJogada("4"));
            REQUIRE_THROWS(reversi->realizarJogada("3 3"));
            REQUIRE_NOTHROW(reversi->realizarJogada("3 4"));
        };

        SUBCASE("Testando jogadaValida do Reversi") {
            CHECK_THROWS(reversi->jogadaValida("teste"));
            CHECK_THROWS(reversi->jogadaValida("3 4 4"));
            CHECK_THROWS(reversi->jogadaValida("4"));
            CHECK_THROWS(reversi->realizarJogada("3 3"));

            CHECK(reversi->jogadaValida("3 4"));
            CHECK_FALSE(reversi->jogadaValida("3 5"));
            CHECK_FALSE(reversi->jogadaValida("4 6"));
            CHECK(reversi->jogadaValida("5 6"));
            CHECK(reversi->jogadaValida("6 5"));
            CHECK_FALSE(reversi->jogadaValida("6 4"));
            CHECK_FALSE(reversi->jogadaValida("5 3"));
            CHECK(reversi->jogadaValida("4 3"));
        }

        SUBCASE("Testando formatoCorreto do Reversi") {
            CHECK_FALSE(reversi->formatoCorreto("teste"));
            CHECK_FALSE(reversi->formatoCorreto("3 4 4"));
            CHECK_FALSE(reversi->formatoCorreto("4"));
            CHECK(reversi->formatoCorreto("3 3"));
        }
    }
}

