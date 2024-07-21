#include "Reversi.hpp"
#include "Jogador.hpp"
#include "Jogada.hpp"
#include <iostream>

Reversi::Reversi(int linhas, int colunas, Jogador &jogador1, Jogador &jogador2) : Jogo(8, 8, jogador1, jogador2) 
{
    this->simbolo_jogador1 = 'x';
    this->simbolo_jogador2 = 'o';
    reiniciarTabuleiro();
}

bool Reversi::dentroDosLimites(const Jogada& jogada) const {
    int linha = jogada.get_linha();
    int coluna = jogada.get_coluna();
    return linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas;
}

bool Reversi::jogadaValida(const Jogada& jogada, char simbolo, char oponente) const {
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




void Reversi::realizarJogada(const Jogada& jogada, char simbolo, char oponente) {
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
}


bool Reversi::verificarVitoria() const {
    int contador1 = 0;
    int contador2 = 0;

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (get_char(i, j) == simbolo_jogador1) {
                contador1++;
            } else if (get_char(i, j) == simbolo_jogador2) {
                contador2++;
            }
        }
    }

    if(contador2 == 0 && contador1 > 0){
            imprimirTabuleiro();
            std::cout << "Jogador 1 venceu" << std::endl;
            int pontuacaoJogador1 = jogador1.getPontuacao("Reversi", Resultado::Vitorias);
            jogador1.setPontuacao("Reversi", Resultado::Vitorias, pontuacaoJogador1 + 1);
            int pontuacaoJogador2 = jogador2.getPontuacao("Reversi", Resultado::Derrotas);
            jogador1.setPontuacao("Reversi", Resultado::Derrotas, pontuacaoJogador2 + 1);
            return true; 
        }else if (contador1 == 0 && contador2 > 0){
            imprimirTabuleiro();
            std::cout << "Jogador 2 venceu" << std::endl;
            int pontuacaoJogador2 = jogador2.getPontuacao("Reversi", Resultado::Vitorias);
            jogador2.setPontuacao("Reversi", Resultado::Vitorias, pontuacaoJogador2 + 1);
            int pontuacaoJogador1 = jogador1.getPontuacao("Reversi", Resultado::Derrotas);
            jogador1.setPontuacao("Reversi", Resultado::Derrotas, pontuacaoJogador1 + 1);
            return true;
           } 
        return false;
}

bool Reversi::verificarEmpate() const {
    int contador1 = 0;
    int contador2 = 0;

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (get_char(i, j) == simbolo_jogador1) {
                contador1++;
            } else if (get_char(i, j) == simbolo_jogador2) {
                contador2++;
            }
        }
    }

    if (contador1>contador2){
        imprimirTabuleiro();
        std::cout << "Jogador 1 venceu" << std::endl;
        int pontuacaoJogador1 = jogador1.getPontuacao("Reversi", Resultado::Vitorias);
        jogador1.setPontuacao("Reversi", Resultado::Vitorias, pontuacaoJogador1 + 1);
        int pontuacaoJogador2 = jogador2.getPontuacao("Reversi", Resultado::Derrotas);
        jogador2.setPontuacao("Reversi", Resultado::Derrotas, pontuacaoJogador2 + 1);
        return true;
    }else if(contador2 > contador1){
        imprimirTabuleiro();
        std::cout << "Jogador 2 venceu" << std::endl;
        int pontuacaoJogador2 = jogador2.getPontuacao("Reversi", Resultado::Vitorias);
        jogador2.setPontuacao("Reversi", Resultado::Vitorias, pontuacaoJogador2 + 1);
        int pontuacaoJogador1 = jogador1.getPontuacao("Reversi", Resultado::Derrotas);
        jogador1.setPontuacao("Reversi", Resultado::Derrotas, pontuacaoJogador1 + 1);
        return true;
    }else if(contador1==contador2){
        imprimirTabuleiro();
        std::cout << "Jogo empatado" << std::endl;
        int pontuacaoJogador1 = jogador1.getPontuacao("Reversi", Resultado::Empates);
        jogador1.setPontuacao("Reversi", Resultado::Empates, pontuacaoJogador1 + 1);
        int pontuacaoJogador2 = jogador2.getPontuacao("Reversi", Resultado::Empates);
        jogador2.setPontuacao("Reversi", Resultado::Empates, pontuacaoJogador2 + 1);
        return true;
    }
    return false;
}

bool Reversi::podeJogar(char simbolo, char oponente) const {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (jogadaValida(Jogada(i, j), simbolo, oponente)) {
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
        std::cout << " " << j << " ";
    }
        std::cout << "\n";
    for (int i = 0; i < linhas; i++) {
        std::cout << i << " "; 
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

    set_char(linhas / 2 - 1, colunas / 2 - 1, simbolo_jogador2);
    set_char(linhas / 2 - 1, colunas / 2, simbolo_jogador1);
    set_char(linhas / 2, colunas / 2 - 1, simbolo_jogador1);
    set_char(linhas / 2, colunas / 2, simbolo_jogador2);
}


void Reversi::partida() {
    bool passouUltimaJogada = false;
    int x, y;
    int jogadas = 0;
    const int MaxJogadas = linhas * colunas;

    while (jogadas < MaxJogadas) {
        imprimirTabuleiro();
        std::cout << "Jogador 1 (" << simbolo_jogador1 << "), escolha uma coordenada no seguinte formato: (x y): ";
        std::cin >> x >> y;

        while (!dentroDosLimites(Jogada(x, y)) || !jogadaValida(Jogada(x, y), simbolo_jogador1, simbolo_jogador2)) {
            std::cout << "Digite uma coordenada válida: \n";
            std::cin >> x >> y;
        }

        realizarJogada(Jogada(x, y), simbolo_jogador1, simbolo_jogador2);
        jogadas++;

        if (verificarVitoria()) {
            break;
        }

        if (!podeJogar(simbolo_jogador2, simbolo_jogador1)) {
            if (passouUltimaJogada) {
                break; 
            } else {
                passouUltimaJogada = true;
                std::cout << "Jogador 2 passou a vez" << std::endl;
                continue; 
            }
        } else {
            passouUltimaJogada = false;
        }

        imprimirTabuleiro();
        std::cout << "Jogador 2 (" << simbolo_jogador2 << "), escolha uma coordenada no seguinte formato: (x y): ";
        std::cin >> x >> y;

        while (!dentroDosLimites(Jogada(x, y)) || !jogadaValida(Jogada(x, y), simbolo_jogador2, simbolo_jogador1)) {
            std::cout << "Digite uma coordenada válida: \n";
            std::cin >> x >> y;
        }

        realizarJogada(Jogada(x, y), simbolo_jogador2, simbolo_jogador1);
        jogadas++;

        if (verificarVitoria()) {
            break;
        }

        if (jogadas == MaxJogadas) {
            if(verificarEmpate()){
                break;
            };
        }
    }
    std::cout << "Fim de jogo!!!" << std::endl;
}

Reversi::~Reversi() {}
