#include <memory>
#include <fstream>
#include <sstream>

#include "doctest.h"
#include "Jogador.hpp"
#include "Jogada.hpp"
#include "Jogo.hpp"
#include "Lig4.hpp"


using namespace std;


TEST_CASE("Testando Lig4") {
    Jogador alice("A", "Alice");
    Jogador bruno("B", "Bruno");
    
    unique_ptr<Lig4> lig4(new Lig4(6, 7, alice, bruno));

    SUBCASE("Testando tabuleiro inicial Lig4") {
        SUBCASE("Testando realizarJogada do Lig4") {
            REQUIRE_THROWS(lig4->realizarJogada("teste"));
            REQUIRE_THROWS(lig4->realizarJogada("1 1"));
            REQUIRE_THROWS(lig4->realizarJogada("\n"));
            REQUIRE_THROWS(lig4->realizarJogada("8"));
            REQUIRE_NOTHROW(lig4->realizarJogada("1"));
        }
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

    SUBCASE("Testando partida do Lig4") {
        REQUIRE(*lig4->getJogadorDaVez() == alice);
        REQUIRE(*lig4->getOutroJogador() == bruno);

        REQUIRE_FALSE(lig4->fimDeJogo());
        REQUIRE_FALSE(lig4->isJogoFinalizado());

        ifstream arquivo_de_jogadas("./test_data/jogadas_lig41.txt");
        stringstream jogadas_stream;
        jogadas_stream << arquivo_de_jogadas.rdbuf();
        for (string jogada; getline(jogadas_stream, jogada); ) {
            CHECK_FALSE(lig4->verificarEmpate());
            CHECK_FALSE(lig4->verificarVitoria(alice));
            CHECK_FALSE(lig4->verificarVitoria(bruno));

            REQUIRE_NOTHROW_MESSAGE(lig4->realizarJogada(jogada), "jogada: ", jogada);
        }

        stringstream tabuleiro_impresso;
        INFO("tabuleiro impresso: ", tabuleiro_impresso);
        CHECK_FALSE(lig4->verificarEmpate());
        CHECK_FALSE(lig4->verificarVitoria(alice));
        CHECK(lig4->verificarVitoria(bruno));

        REQUIRE(lig4->fimDeJogo());
        lig4->finalizarJogo();

        REQUIRE(lig4->isJogoFinalizado());

        CHECK(lig4->getVencedor() == &bruno);
        CHECK(lig4->getPerdedor() == &alice);

        CHECK(bruno.getResultados("Lig4").vitorias == 1);
        CHECK(bruno.getResultados("Lig4").empates == 0);

        CHECK(alice.getResultados("Lig4").derrotas == 1);
        CHECK(alice.getResultados("Lig4").empates == 0);

    }
}

