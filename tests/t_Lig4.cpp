#include <memory>

#include "doctest.h"
#include "Jogador.hpp"
#include "Jogada.hpp"
#include "Jogo.hpp"
#include "Lig4.hpp"


using namespace std;


TEST_CASE("Testando Lig4") {
    Jogador alice("A", "Alice");
    Jogador bruno("B", "Bruno");
    
    SUBCASE("Testando tabuleiro inicial Lig4") {
        unique_ptr<Lig4> lig4(new Lig4(6, 7, alice, bruno));

        CHECK_FALSE(lig4->verificarVitoria(alice));
        CHECK_FALSE(lig4->verificarVitoria(bruno));
        CHECK_FALSE(lig4->verificarEmpate());

        SUBCASE("Testando realizarJogada do Lig4") {
            REQUIRE_THROWS(lig4->realizarJogada("teste"));
            REQUIRE_THROWS(lig4->realizarJogada("1 1"));
            REQUIRE_THROWS(lig4->realizarJogada("\n"));
            REQUIRE_THROWS(lig4->realizarJogada("8"));
            REQUIRE_NOTHROW(lig4->realizarJogada("1"));
        };

        SUBCASE("Testando jogadaValida do Lig4") {
            CHECK_THROWS(lig4->jogadaValida("teste"));
            CHECK_THROWS(lig4->jogadaValida("1 1"));
            CHECK_THROWS(lig4->jogadaValida("\n"));
            CHECK_FALSE(lig4->jogadaValida("8"));

            for (int i = 1; i <= 7; i++) {
                CHECK_MESSAGE(lig4->jogadaValida(to_string(i)), "i: ", i);
            }
        }

        SUBCASE("Testando formatoCorreto do Lig4") {
            CHECK_FALSE(lig4->formatoCorreto("teste"));
            CHECK_FALSE(lig4->formatoCorreto("1 1"));
            CHECK_FALSE(lig4->formatoCorreto("\n"));
            CHECK(lig4->formatoCorreto("8"));
        }
    }
}

