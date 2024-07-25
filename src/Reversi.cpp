#include "Reversi.hpp"
#include "Jogador.hpp"
#include "Jogada.hpp"
#include <iostream>

Reversi::Reversi(int linhas, int colunas, Jogador &jogador1, Jogador &jogador2): Jogo(8, 8, jogador1, jogador2)
{
    reiniciarTabuleiro();
}

bool Reversi::dentroDosLimites(const Jogada& jogada) const {
    int linha = jogada.get_linha();
    int coluna = jogada.get_coluna();
    return linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas;
}

void Reversi::trocarJogador() {
    if (jogador_atual == &jogador1) {
        jogador_atual = &jogador2;
    } else {
        jogador_atual = &jogador1;
    }
}

bool Reversi::jogadaValida(const Jogada& jogada) const {
    std::string apelido = jogador_atual->getApelido();
    char simbolo = this->simbolos.at(apelido);
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

        while (dentroDosLimites(Jogada(nlinha +1, ncoluna +1)) && get_char(nlinha, ncoluna) == oponente) {
            encontrouOponente = true;
            nlinha += dlinha[i];
            ncoluna += dcoluna[i];
        }
        if (encontrouOponente && dentroDosLimites(Jogada(nlinha +1, ncoluna +1)) && get_char(nlinha, ncoluna) == simbolo) {
            return true;
        }
    }
    return false;
}

void Reversi::realizarJogada(const Jogada& jogada) {
    std::string apelido = jogador_atual->getApelido();
    char simbolo = this->simbolos.at(apelido);
    char oponente = (simbolo == 'X') ? 'O' : 'X';
    int linha = jogada.get_linha();
    int coluna = jogada.get_coluna();
    set_char(linha, coluna, simbolo);

    int dlinha[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dcoluna[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int i = 0; i < 8; i++) {
        int nlinha = linha + dlinha[i], ncoluna = coluna + dcoluna[i];
        bool encontrouOponente = false;

        while (dentroDosLimites(Jogada(nlinha +1, ncoluna +1)) && get_char(nlinha, ncoluna) == oponente) {
            encontrouOponente = true;
            nlinha += dlinha[i];
            ncoluna += dcoluna[i];
        }

        if (encontrouOponente && dentroDosLimites(Jogada(nlinha +1, ncoluna +1)) && get_char(nlinha, ncoluna) == simbolo) {
            nlinha -= dlinha[i];
            ncoluna -= dcoluna[i];

            while (nlinha != linha || ncoluna != coluna) {
                set_char(nlinha, ncoluna, simbolo);
                nlinha -= dlinha[i];
                ncoluna -= dcoluna[i];
            }
        }
    }
}

bool Reversi::verificarVitoria() const {
    int contador1 = 0;
    int contador2 = 0;

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (get_char(i, j) == 'X') {
                contador1++;
            } else if (get_char(i, j) == 'O') {
                contador2++;
            }
        }
    }

    if (contador1 == 0 || contador2 == 0) {
        if (contador1 > contador2) {
            imprimirTabuleiro();
            std::cout << jogador1.getApelido() << " venceu" << std::endl;
            jogador1.incrementarVitorias("Reversi");
            jogador2.incrementarDerrotas("Reversi");
        } else {
            imprimirTabuleiro();
            std::cout << jogador2.getApelido() << " venceu" << std::endl;
            jogador2.incrementarVitorias("Reversi");
            jogador1.incrementarDerrotas("Reversi");
        }
        return true;
    }

    return false;
}

bool Reversi::verificarEmpate() const {
    int contador1 = 0;
    int contador2 = 0;

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (get_char(i, j) == 'X') {
                contador1++;
            } else if (get_char(i, j) == 'O') {
                contador2++;
            }
        }
    }

    if (contador1 + contador2 == linhas * colunas) {
        if (contador1 > contador2) {
            imprimirTabuleiro();
            std::cout << jogador1.getApelido() << " venceu" << std::endl;
            jogador1.incrementarVitorias("Reversi");
            jogador2.incrementarDerrotas("Reversi");
        } else if (contador2 > contador1) {
            imprimirTabuleiro();
            std::cout << jogador2.getApelido() << " venceu" << std::endl;
            jogador2.incrementarVitorias("Reversi");
            jogador1.incrementarDerrotas("Reversi");
        } else {
            imprimirTabuleiro();
            std::cout << "Jogo empatado" << std::endl;
            jogador1.incrementarEmpates("Reversi");
            jogador2.incrementarEmpates("Reversi");
        }
        return true;
    }

    return false;
}

bool Reversi::podeJogar(const std::string& jogador) const {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (jogadaValida(Jogada(i +1, j +1))) {
                return true;
            }
        }
    }
    return false;
}

void Reversi::imprimirTabuleiro() const {
    std::cout << "---------Reversi---------" << std::endl;
    std::cout << "  ";
    for (int j = 0; j < colunas; j++) {
        std::cout << " " << j + 1 << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < linhas; i++) {
        std::cout << i + 1 << " "; 
        for (int j = 0; j < colunas; j++) {
            std::cout << "|" << get_char(i, j) << "|";
        }
        std::cout << "\n";
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

void Reversi::partida() {
    bool passouUltimaJogada = false;
    int jogadasSemMovimento = 0;
    const int MaxJogadas = linhas * colunas;

    while (jogadasSemMovimento < 2) { 
        imprimirTabuleiro();

        if (podeJogar(jogador_atual->getApelido())) {
            jogadasSemMovimento = 0; 
            std::cout << jogador1.getApelido() << "(" << 'X' << "), escolha uma coordenada no seguinte formato: (x y): ";
            int x, y;
            std::cin >> x >> y;

            while (!dentroDosLimites(Jogada(x, y)) || !jogadaValida(Jogada(x, y))) {
                std::cout << "Digite uma coordenada válida: ";
                std::cin >> x >> y;
            }

            realizarJogada(Jogada(x, y));
            if (verificarVitoria() || verificarEmpate()) {
                return;
            }
            trocarJogador();
        } else {
            jogadasSemMovimento++;
            std::cout << jogador1.getApelido() << " passou a vez" << std::endl;
             trocarJogador();
        }

        imprimirTabuleiro();

        if (podeJogar(jogador_atual->getApelido())) {
            jogadasSemMovimento = 0; 
            std::cout << jogador2.getApelido() << "(" << 'O' << "), escolha uma coordenada no seguinte formato: (x y): ";
            int x, y;
            std::cin >> x >> y;

            while (!dentroDosLimites(Jogada(x, y)) || !jogadaValida(Jogada(x, y))) {
                std::cout << "Digite uma coordenada válida: ";
                std::cin >> x >> y;
            }

            realizarJogada(Jogada(x, y));
            if (verificarVitoria() || verificarEmpate()) {
                return;
            }
            trocarJogador();
        } else {
            jogadasSemMovimento++;
            std::cout << jogador2.getApelido() << " passou a vez" << std::endl;
            trocarJogador();
        }
    }

    std::cout << "Nenhum jogador pode jogar." << std::endl;
    if (!verificarEmpate()) {
        verificarVitoria(); 
    }
    std::cout << "Fim de jogo!!!" << std::endl;
}

Reversi::~Reversi() {}
