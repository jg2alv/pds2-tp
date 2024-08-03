#include "Reversi.hpp"
#include "Jogador.hpp"
#include "Jogada.hpp"
#include "Excecao.hpp"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>


Reversi::Reversi(int linhas, int colunas, Jogador &jogador1, Jogador &jogador2) :
    Jogo(linhas, colunas, jogador1, jogador2) {
    reiniciarTabuleiro();
}

Reversi::Reversi(int linhas, int colunas, Jogador& jogador1, Jogador& jogador2, std::vector<char> tabuleiro) :
    Jogo(linhas, colunas, jogador1, jogador2, tabuleiro) {}

Reversi::~Reversi() {}

std::string Reversi::getNome() const {
    return "Reversi";
}

bool Reversi::dentroDosLimites(const Jogada& jogada) const {
    int linha = jogada.get_linha();
    int coluna = jogada.get_coluna();
    return linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas;
}

bool Reversi::jogada_valida(const Jogada& jogada, char simbolo) const {
    char oponente = (simbolo == 'X') ? 'O' : 'X';
    int linha = jogada.get_linha();
    int coluna = jogada.get_coluna();
    
    if (!dentroDosLimites(jogada)) {
        return false;
    }

    if (get_char(linha, coluna) != ' ') { 
        return false;
    }

    int dlinha[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dcoluna[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int i = 0; i < 8; i++) {
        int nlinha = linha + dlinha[i];
        int ncoluna = coluna + dcoluna[i];
        bool encontrouOponente = false;

        while (dentroDosLimites(Jogada(nlinha, ncoluna)) && get_char(nlinha, ncoluna) == oponente) {
            encontrouOponente = true;
            nlinha += dlinha[i];
            ncoluna += dcoluna[i];
        }
        if (encontrouOponente && dentroDosLimites(Jogada(nlinha, ncoluna)) && get_char(nlinha, ncoluna) == simbolo) {
            return true;
        }
    }
    return false;
}

bool Reversi::formatoCorreto(std::string possivel_jogada) const {
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

bool Reversi::jogadaValida(std::string possivel_jogada) const {
    if (fimDeJogo()) {
        return false; 
    }

    if (!formatoCorreto(possivel_jogada)) {
        throw Excecao("formato incorreto");
    }

    std::stringstream jogada_stream(possivel_jogada);
    int linha, coluna;
    jogada_stream >> linha >> coluna;
    linha--;
    coluna--;

    return jogada_valida(Jogada(linha, coluna), get_simbolo(*jogador_da_vez));
}

void Reversi::realizarJogada(std::string possivel_jogada) {
    if (fimDeJogo()) {
        throw Excecao("jogo ja acabou");
    }

    if (!formatoCorreto(possivel_jogada)) {
        throw Excecao("formato incorreto");
    }

    std::stringstream jogada_stream(possivel_jogada);
    int linha, coluna;
    jogada_stream >> linha >> coluna;
    linha--;
    coluna--;

    if (!jogada_valida(Jogada(linha, coluna), get_simbolo(*jogador_da_vez))) {
        throw Excecao("jogada invalida");
    }

    realizar_jogada(Jogada(linha, coluna));
};

void Reversi::realizar_jogada(const Jogada& jogada) {
    char simbolo = get_simbolo(*jogador_da_vez);
    char oponente = get_simbolo(*outro_jogador);
    int linha = jogada.get_linha();
    int coluna = jogada.get_coluna();
    set_char(linha, coluna, simbolo);

    int dlinha[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dcoluna[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int i = 0; i < 8; i++) {
        int nlinha = linha + dlinha[i], ncoluna = coluna + dcoluna[i];
        bool encontrouOponente = false;

        while (dentroDosLimites(Jogada(nlinha, ncoluna)) && get_char(nlinha, ncoluna) == oponente) {
            encontrouOponente = true;
            nlinha += dlinha[i];
            ncoluna += dcoluna[i];
        }

        if (encontrouOponente && dentroDosLimites(Jogada(nlinha, ncoluna)) && get_char(nlinha, ncoluna) == simbolo) {
            nlinha -= dlinha[i];
            ncoluna -= dcoluna[i];

            while (nlinha != linha || ncoluna != coluna) {
                set_char(nlinha, ncoluna, simbolo);
                nlinha -= dlinha[i];
                ncoluna -= dcoluna[i];
            }
        }
    }

    if (podeJogar(*outro_jogador)) {
        passar_a_vez();
    }
}

int Reversi::indicador_de_pontos() const {
    int contadorX = 0;
    int contadorO = 0;

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (get_char(i, j) == 'X') {
                contadorX++;
            } else if (get_char(i, j) == 'O') {
                contadorO++;
            }
        }
    }
    
    if (contadorX > contadorO) {
        return 1;
    } else if (contadorX < contadorO) {
        return -1;
    } else {
        return 0;
    }
}

bool Reversi::verificarVitoria(const Jogador& jogador) const {
    if (podeJogar(*jogador_da_vez)) {
        return false;
    }

    int indicador = indicador_de_pontos();
    if (indicador == 1 && jogador == jogador1) {
        return true;
    } else if (indicador == -1 && jogador == jogador2) {
        return true;
    } else {
        return false;
    }
}

bool Reversi::verificarEmpate() const {
    if (podeJogar(*jogador_da_vez)) {
        return false;
    }

    return indicador_de_pontos() == 0;
}

bool Reversi::podeJogar(const Jogador& jogador) const {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (jogada_valida(Jogada(i, j), get_simbolo(jogador))) {
                return true;
            }
        }
    }
    return false;
}

void Reversi::imprimirTabuleiro(std::ostream& out) const {
    out << "---------Reversi---------\n";
    out << "  ";
    for (int j = 0; j < colunas; j++) {
        std::cout << " " << j + 1 << " ";
    }
    out << "\n";
    for (int i = 0; i < linhas; i++) {
        std::cout << i + 1 << " "; 
        for (int j = 0; j < colunas; j++) {
            std::cout << "|" << get_char(i, j) << "|";
        }
        out << "\n";
    }
}

void Reversi::reiniciarTabuleiro() {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            set_char(i, j, ' '); 
        }
    }

    set_char(linhas / 2 - 1, colunas / 2 - 1, 'O');
    set_char(linhas / 2 - 1, colunas / 2, 'X');
    set_char(linhas / 2, colunas / 2 - 1, 'X');
    set_char(linhas / 2, colunas / 2, 'O');
}

