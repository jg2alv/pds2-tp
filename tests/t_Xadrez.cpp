#include <memory>
#include <fstream>
#include <sstream>

#include "doctest.h"
#include "Xadrez.hpp"
#include "Jogador.hpp"
#include "Jogada.hpp"
#include "Jogo.hpp"


using namespace std;


TEST_CASE("Testando Xadrez") {
    Jogador alice("A", "Alice");
    Jogador bruno("B", "Bruno");

    unique_ptr<Xadrez> xadrez(new Xadrez(alice, bruno));

    SUBCASE("Testando tabuleiro inicial Xadrez") {
        SUBCASE("Testando realizarJogada do Xadrez") {
            REQUIRE_THROWS(xadrez->realizarJogada("teste"));
            REQUIRE_THROWS(xadrez->realizarJogada("a2a3 a3a4"));
            REQUIRE_THROWS(xadrez->realizarJogada("a2"));
            REQUIRE_THROWS(xadrez->realizarJogada("f1d3"));
            REQUIRE_NOTHROW(xadrez->realizarJogada("g1f3"));
        }
        SUBCASE("Testando jogadaValida do Xadrez") {
            CHECK_THROWS(xadrez->jogadaValida("teste"));
            CHECK_THROWS(xadrez->jogadaValida("a2a3 a3a4"));
            CHECK_THROWS(xadrez->jogadaValida("a2"));
            CHECK_FALSE(xadrez->jogadaValida("f1d3"));

            CHECK(xadrez->jogadaValida("g1f3"));
            CHECK(xadrez->jogadaValida("b1c3"));
            CHECK(xadrez->jogadaValida("a2a3"));
            CHECK(xadrez->jogadaValida("b2b3"));
            CHECK(xadrez->jogadaValida("c2c3"));
            CHECK(xadrez->jogadaValida("d2d3"));
            CHECK(xadrez->jogadaValida("e2e3"));
            CHECK(xadrez->jogadaValida("f2f3"));
            CHECK(xadrez->jogadaValida("g2g3"));
            CHECK(xadrez->jogadaValida("h2h3"));
        }
        SUBCASE("Testando formatoCorreto do Xadrez") {
            CHECK_FALSE(xadrez->formatoCorreto("teste"));
            CHECK_FALSE(xadrez->formatoCorreto("a2a3 a3a4"));
            CHECK_FALSE(xadrez->formatoCorreto("a2"));
            CHECK(xadrez->formatoCorreto("f1d3"));
        }
    }

    SUBCASE("Testando partida do Xadrez") {
        ifstream arquivo_de_jogadas("./test_data/jogadas_xadrez1.txt");
        stringstream jogadas_stream;
        jogadas_stream << arquivo_de_jogadas.rdbuf();
        for (string jogada; getline(jogadas_stream, jogada); ) {
            CHECK_FALSE(xadrez->verificarEmpate());
            CHECK_FALSE(xadrez->verificarVitoria(alice));
            CHECK_FALSE(xadrez->verificarVitoria(bruno));

            REQUIRE_NOTHROW_MESSAGE(xadrez->realizarJogada(jogada), "jogada: ", jogada);
        }

        stringstream tabuleiro_impresso;
        INFO("tabuleiro impresso: ", tabuleiro_impresso);
        CHECK_FALSE(xadrez->verificarEmpate());
        CHECK_FALSE(xadrez->verificarVitoria(alice));
        CHECK_FALSE(xadrez->verificarVitoria(bruno));
    }

}

