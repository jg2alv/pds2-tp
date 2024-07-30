#include <memory>

#include "doctest.h"
#include "Jogador.hpp"
#include "Jogada.hpp"
#include "Jogo.hpp"
#include "Reversi.hpp"



using namespace std;


TEST_CASE("Testes genericos para Lig4") {
    Jogador jogador1("A", "Alice");
    Jogador jogador2("B", "Bruno");
    
    Jogo *reversi(new Reversi(8, 8, jogador1, jogador2));

    CHECK(reversi->jogadaValida(Jogada(5, 3)));

    delete reversi;
}


