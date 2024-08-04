#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "JogoDaVelha.hpp"
#include "Excecao.hpp"
#include "Jogada.hpp"
#include "Jogador.hpp"
#include "Jogo.hpp"

JogoDaVelha::JogoDaVelha(Jogador &jogador1, Jogador &jogador2) :
    Jogo(3, 3, jogador1, jogador2) {}

JogoDaVelha::JogoDaVelha(Jogador &jogador1, Jogador &jogador2, std::vector<std::vector<char>> tabuleiro) :
    Jogo(3, 3, jogador1, jogador2, tabuleiro) {}

JogoDaVelha::~JogoDaVelha() {}

std::string JogoDaVelha::getNome() const {
    return "JogoDaVelha";
}

void JogoDaVelha::imprimirTabuleiro(std::ostream& out) const {
    out << "--Jogo da Velha--\n    ";

    for (int i = 1; i <= 3; i++) {
        out << " " << i << " ";
    }
    out << std::endl;
  
    for (int i = 0; i < 3; i++) {
        out << "  " << i + 1 << " ";
        for (int j = 0; j < 3; j++) {
            out << "|" << get_char(i, j) << "|";
    }
        out << std::endl;
  }
}

bool JogoDaVelha::formatoCorreto(std::string possivel_jogada) const {
    std::stringstream jogada_stream(possivel_jogada);
    int linha, coluna;
    std::string extra;

    if (!(jogada_stream >> linha)) {
        return false;
    }

    if (!(jogada_stream >> coluna)) {
        return false;
    }

    return !(jogada_stream >> extra);
}

bool JogoDaVelha::jogada_valida(const Jogada &jogada) const {
    int linha = jogada.get_linha();
    int coluna = jogada.get_coluna();

    if (get_char(linha, coluna) != ' ') return false;
    else return ((linha >= 0 && linha < this->linhas) && (coluna >= 0 && coluna < this->colunas));
}

bool JogoDaVelha::jogadaValida(std::string possivel_jogada) const {
    if (fimDeJogo()) {
        return false;
    }

    if (!formatoCorreto(possivel_jogada)) {
        throw Excecao("formato incorreto");
    }

    std::stringstream in;
    in.str(possivel_jogada);
    
    int linha, coluna;
    in >> linha >> coluna;
    linha--, coluna--;

    Jogada jogada(linha, coluna);
    return jogada_valida(jogada);
}

void JogoDaVelha::realizar_jogada(const Jogada &jogada) {
    set_char(jogada.get_linha(), jogada.get_coluna(), get_simbolo(*jogador_da_vez));
}

void JogoDaVelha::realizarJogada(std::string possivel_jogada) {
    if (fimDeJogo()) {
        throw Excecao("jogo ja acabou");
    }

    if (!formatoCorreto(possivel_jogada)) {
        throw Excecao("formato incorreto");
    }

    std::stringstream in;
    in.str(possivel_jogada);
    
    int linha, coluna;
    in >> linha >> coluna;
    linha --, coluna--;

    Jogada jogada(linha, coluna);
    if (!jogada_valida(jogada)) {
        throw Excecao("jogada invalida");
    }

    realizar_jogada(jogada);
    passar_a_vez();
}

bool JogoDaVelha::verificarVitoria(Jogador const& jogador) const {
    char simbolo = get_simbolo(jogador);
    int qntd = 0;

    for (int i = 0; i < this->linhas; i++) {
        qntd = 0;

        for (int j = 0; j < this->colunas; j++) {
            if (get_char(i, j) == ' ') break;
            if (get_char(i, j) == simbolo) qntd++;
        }

        if (qntd == 3) return true;
    }

    for (int j = 0; j < this->colunas; j++) {
        qntd = 0;
        
        for (int i = 0; i < this->linhas; i++) {
            if (get_char(i, j) == ' ') break;
            if (get_char(i, j) == simbolo) qntd++;
        }

        if (qntd == 3) return true;
    }

    qntd = 0;
    for (int i = 0; i < this->linhas; i++) {
        if (get_char(i, i) == ' ') break;
        if (get_char(i, i) == simbolo) qntd++;
    }
    if (qntd == 3) return true;

    qntd = 0;
    for (int i = 0; i < this->linhas; i++) {
        int j = 2 - i;
        if (get_char(i, j) == ' ') break;
        if (get_char(i, j) == simbolo) qntd++;
    }
    if (qntd == 3) return true;

    return false;
}

bool JogoDaVelha::tabuleiroCheio() const {
    for (int i = 0; i < this->linhas; i++) {
        for (int j = 0; j < this->colunas; j++) {
            if (get_char(i, j) == ' ') 
                return false;
        }
    }

    return true;
}

bool JogoDaVelha::verificarEmpate() const {
    return tabuleiroCheio();
}
