#include <memory>

#include "doctest.h"
#include "Jogador.hpp"
#include "Jogada.hpp"
#include "Jogo.hpp"
#include "Lig4.hpp"


using namespace std;


TEST_CASE("Testes genericos para Lig4") {
    Jogador jogador1("A", "Alice");
    Jogador jogador2("B", "Bruno");
    
    unique_ptr<Jogo> lig4(new Lig4(6, 7, jogador1, jogador2));

    CHECK(lig4->jogadaValida(Jogada(1, 1)));
    CHECK(lig4->jogadaValida(Jogada(1, 2)));
    CHECK(lig4->jogadaValida(Jogada(1, 3)));
    CHECK(lig4->jogadaValida(Jogada(1, 4)));
    CHECK(lig4->jogadaValida(Jogada(1, 5)));
    CHECK(lig4->jogadaValida(Jogada(1, 6)));
    CHECK(lig4->jogadaValida(Jogada(1, 7)));
}


