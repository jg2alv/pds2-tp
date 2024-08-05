#include <memory>
#include <string>
#include <fstream>
#include <sstream>

#include "doctest.h"
#include "Jogador.hpp"
#include "Jogo.hpp"
#include "JogoDaVelha.hpp"


using namespace std;


TEST_CASE("Testando JogoDaVelha") {
    Jogador alice("A", "Alice");
    Jogador bruno("B", "Bruno");
    
    unique_ptr<JogoDaVelha> jogo_da_velha(new JogoDaVelha(alice, bruno));

    SUBCASE("Testando jogadas no tabuleiro inicial do JogoDaVelha") {
        SUBCASE("Testando realizarJogada do JogoDaVelha") {
            REQUIRE_THROWS(jogo_da_velha->realizarJogada("teste"));
            REQUIRE_THROWS(jogo_da_velha->realizarJogada("1 1 1"));
            REQUIRE_THROWS(jogo_da_velha->realizarJogada("1"));
            REQUIRE_THROWS(jogo_da_velha->realizarJogada("4 4"));
            REQUIRE_NOTHROW(jogo_da_velha->realizarJogada("1 1"));
        }
        SUBCASE("Testando jogadaValida do JogoDaVelha") {
            CHECK_THROWS(jogo_da_velha->jogadaValida("teste"));
            CHECK_THROWS(jogo_da_velha->jogadaValida("1 1 1"));
            CHECK_THROWS(jogo_da_velha->jogadaValida("1"));
            CHECK_FALSE(jogo_da_velha->jogadaValida("4 4"));

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

    SUBCASE("Testando partida do JogoDaVelha") {
        ifstream arquivo_de_jogadas("./test_data/jogadas_jogo_da_velha1.txt");
        stringstream jogadas_stream;
        jogadas_stream << arquivo_de_jogadas.rdbuf();
        for (string jogada; getline(jogadas_stream, jogada); ) {
            CHECK_FALSE(jogo_da_velha->verificarEmpate());
            CHECK_FALSE(jogo_da_velha->verificarVitoria(alice));
            CHECK_FALSE(jogo_da_velha->verificarVitoria(bruno));

            REQUIRE_NOTHROW_MESSAGE(jogo_da_velha->realizarJogada(jogada), "jogada: ", jogada);
        }

        stringstream tabuleiro_impresso;
        INFO("tabuleiro impresso: ", tabuleiro_impresso);
        CHECK_FALSE(jogo_da_velha->verificarEmpate());
        CHECK(jogo_da_velha->verificarVitoria(alice));
        CHECK_FALSE(jogo_da_velha->verificarVitoria(bruno));

        REQUIRE(jogo_da_velha->fimDeJogo());
        jogo_da_velha->finalizarJogo();

        CHECK(jogo_da_velha->getVencedor() == &alice);
        CHECK(jogo_da_velha->getPerdedor() == &bruno);

        CHECK(alice.getResultados("JogoDaVelha").vitorias == 1);
        CHECK(alice.getResultados("JogoDaVelha").empates == 0);

        CHECK(bruno.getResultados("JogoDaVelha").derrotas == 1);
        CHECK(bruno.getResultados("JogoDaVelha").empates == 0);
    }
}


