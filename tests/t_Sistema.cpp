#include <string>
#include <sstream>

#include "doctest.h"
#include "Sistema.hpp"


using namespace std;


TEST_CASE("Teste para Sistema") {
    SUBCASE("Arquivo de teste 1") {
        stringstream entrada("teste");
        stringstream saida;
        Sistema sistema(entrada, saida, "./data/jogadores_teste1.txt", false);
    }
}


