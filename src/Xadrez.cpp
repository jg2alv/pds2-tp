#include "Xadrez.hpp"
#include "Jogada.hpp"
#include "Jogador.hpp"
#include "Jogo.hpp"
#include "Excecao.hpp"

#include <string>

Xadrez::Xadrez(Jogador &jogador1, Jogador &jogador2) : Jogo(8, 8, jogador1, jogador2) {}
Xadrez::~Xadrez() {}

std::string Xadrez::getNome() const {
    return "Xadrez";
}

void Xadrez::imprimirTabuleiro(std::ostream& out) const {
    out << "---------Xadrez---------\n";

    out << "   a  b  c  d  e  f  g  h " << std::endl;
    for (int i = 0; i < this->linhas; i++) {
        out << i + 1 << " ";
        for (int j = 0; j < this->colunas; j++) {
            std::cout << "|" << get_char(i, j) << "|";
        }
        out << " " << i + 1 << std::endl;
    }
    out << "   a  b  c  d  e  f  g  h " << std::endl;
}

bool Xadrez::formatoCorreto(std::string possivel_jogada) const {
    std::cout << possivel_jogada;
    return true;
}

bool Xadrez::jogadaValida(std::string possivel_jogada) const {
    std::cout << possivel_jogada;
    return true;
}

void Xadrez::realizarJogada(std::string possivel_jogada) {
    std::cout << possivel_jogada;
}

bool Xadrez::verificarVitoria(Jogador const& jogador) const {
    std::cout << jogador.getApelido();
    return false;
}

bool Xadrez::verificarEmpate() const {
    return false;
}