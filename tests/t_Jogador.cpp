#include <vector>
#include <string>
#include <sstream>

#include "doctest.h"
#include "Jogador.hpp"


using namespace std;


TEST_CASE("Testes para o Jogador") {
    Jogador alice("A", "Alice");
    CHECK(alice.getApelido() == "A");
    CHECK(alice.getNome() == "Alice");

    alice.adicionarResultados("Reversi", Resultados(0, 2, 1));
    CHECK(alice.getResultados("Reversi").vitorias == 0);
    CHECK(alice.getResultados("Reversi").derrotas == 2);
    CHECK(alice.getResultados("Reversi").empates == 1);

    alice.adicionarResultados("Lig4", Resultados(1, 1, 0));
    CHECK(alice.getResultados("Lig4").vitorias == 1);
    CHECK(alice.getResultados("Lig4").derrotas == 1);
    CHECK(alice.getResultados("Lig4").empates == 0);

    alice.incrementarVitorias("Reversi");
    CHECK(alice.getResultados("Reversi").vitorias == 1);
    alice.incrementarDerrotas("Reversi");
    CHECK(alice.getResultados("Reversi").derrotas == 3);

    alice.incrementarEmpates("Lig4");
    CHECK(alice.getResultados("Lig4").empates == 1);
    alice.incrementarEmpates("Lig4");
    CHECK(alice.getResultados("Lig4").empates == 2);

    CHECK(alice.getNumeroDeJogos() == 2);
    CHECK(alice.getJogosCadastrados() == vector<string>{"Lig4", "Reversi"}); 

    stringstream saida;
    alice.imprimirInformacoes(saida);
    char const *saida_esperada = "A Alice\n"
                                 "Lig4 - V: 1 D: 1\n"
                                 "Reversi - V: 1 D: 3\n";
    CHECK(saida.str() == saida_esperada);
}


