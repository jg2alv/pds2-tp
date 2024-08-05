#include <memory>
#include <string>

#include "doctest.h"
#include "Jogador.hpp"
#include "Jogo.hpp"
#include "JogoDaVelha.hpp"


using namespace std;


TEST_CASE("Testando JogoDaVelha") {
    Jogador alice("A", "Alice");
    Jogador bruno("B", "Bruno");
    
    SUBCASE("Testando tabuleiro inicial JogoDaVelha") {
        unique_ptr<JogoDaVelha> jogo_da_velha(new JogoDaVelha(alice, bruno));

        CHECK_FALSE(jogo_da_velha->verificarVitoria(alice));
        CHECK_FALSE(jogo_da_velha->verificarVitoria(bruno));
        CHECK_FALSE(jogo_da_velha->verificarEmpate());

        SUBCASE("Testando realizarJogada do JogoDaVelha") {
            REQUIRE_THROWS(jogo_da_velha->realizarJogada("teste"));
            REQUIRE_THROWS(jogo_da_velha->realizarJogada("1 1 1"));
            REQUIRE_THROWS(jogo_da_velha->realizarJogada("1"));
            REQUIRE_THROWS(jogo_da_velha->realizarJogada("4 4"));
            REQUIRE_NOTHROW(jogo_da_velha->realizarJogada("1 1"));
        };

        SUBCASE("Testando jogadaValida do JogoDaVelha") {
            CHECK_THROWS(jogo_da_velha->jogadaValida("teste"));
            CHECK_THROWS(jogo_da_velha->jogadaValida("1 1 1"));
            CHECK_THROWS(jogo_da_velha->jogadaValida("1"));
            CHECK_THROWS(jogo_da_velha->jogadaValida("4 4"));

            for (int i = 1; i <= 3; i++) {
                for (int j = 1; j <= 3; j++) {
                    string jogada_de_teste = to_string(i) + " " + to_string(j);
                    CHECK_MESSAGE(jogo_da_velha->jogadaValida(jogada_de_teste), "jogada_de_teste: ", jogada_de_teste);
                }
            }
        }

        SUBCASE("Testando formatoCorreto do JogoDaVelha") {
            CHECK_FALSE(jogo_da_velha->formatoCorreto("teste"));
            CHECK_FALSE(jogo_da_velha->formatoCorreto("1 1 1"));
            CHECK_FALSE(jogo_da_velha->formatoCorreto("1"));
            CHECK(jogo_da_velha->formatoCorreto("4 4"));
        }
    }
}


