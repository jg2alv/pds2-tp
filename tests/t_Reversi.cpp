#include <memory>

#include "doctest.h"
#include "Reversi.hpp"
#include "Jogador.hpp"
#include "Jogada.hpp"
#include "Jogo.hpp"


using namespace std;


TEST_CASE("Testes genericos para Reversi") {
    Jogador jogador1("A", "Alice");
    Jogador jogador2("B", "Bruno");
    
    unique_ptr<Jogo> reversi(new Reversi(8, 8, jogador1, jogador2));

    CHECK(reversi->jogadaValida(Jogada(5, 3)));
}


