#include <iostream>
#include <string>
#include <sstream>
#include "Lig4.hpp"
#include "Jogada.hpp"
#include "Jogador.hpp"
#include "Jogo.hpp"

Lig4::Lig4(int linhas, int colunas, Jogador &jogador1, Jogador &jogador2)
    : Jogo(linhas, colunas, jogador1, jogador2) {
    this->jogador_atual = 1;
}

void Lig4::imprimirTabuleiro() const {
    for (int i = 0; i < this->linhas; i++) {
        for (int j = 0; j < this->colunas; j++) {
            std::cout << "|" << get_char(i, j) << "|";
        }
        std::cout << std::endl;
    }

    for (int i = 1; i <= this->colunas; i++) {
        std::cout << " " << i << " ";
    }

    std::cout << std::endl << std::endl;
}

int Lig4::formatoCorreto(std::string entrada) {
    std::stringstream in;
    in.str(entrada);

    int formatoCorreto = 1;
    int qntdNumeros = 0;
    std::string aux;
    std::string colunaStr;

    while (in >> aux) {
        for (int i = 0; i < aux.length(); i++) {
            if (aux[i] < 48 || aux[i] > 57) 
                formatoCorreto = 0;
        }

        if (formatoCorreto && (qntdNumeros == 0)) {
            colunaStr = aux;
            qntdNumeros++;

        } else return -1;
    } 

    int coluna = 0;
    for (int i = (colunaStr.length() - 1), d = 1; i >= 0; i--, d *= 10) {
        int inteiro;
        
        if (colunaStr[i] == '0') inteiro = 0;
        else if (colunaStr[i] == '1') 
            inteiro = 1;
        else if (colunaStr[i] == '2') 
            inteiro = 2;
        else if (colunaStr[i] == '3') 
            inteiro = 3;
        else if (colunaStr[i] == '4') 
            inteiro = 4;
        else if (colunaStr[i] == '5') 
            inteiro = 5;
        else if (colunaStr[i] == '6') 
            inteiro = 6;
        else if (colunaStr[i] == '7') 
            inteiro = 7;
        else if (colunaStr[i] == '8') 
            inteiro = 8;
        else if (colunaStr[i] == '9') 
            inteiro = 9;

        coluna += inteiro * d;
    }

    return coluna;
}

int Lig4::get_linha(int coluna) const {
    if (get_char(0, coluna) != ' ') 
        return -1;

    for (int i = (this->linhas - 1); i >= 0; i--) {
        if (get_char(i, coluna) == ' ') 
            return i;
    }
}

Jogada Lig4::lerJogada() {
    std::string entrada;
    int coluna;

    while (1) {
        std::cout << "Turno do jogador ";
        if (this->jogador_atual == 1) 
            std::cout << this->jogador1.getApelido();
        
        else if (this->jogador_atual == 2) 
            std::cout << this->jogador2.getApelido();
        std::cout << ": ";

        getline(std::cin, entrada);
        coluna = formatoCorreto(entrada);

        if (coluna == -1) 
            std::cout << "ERRO: formato incorreto" << std::endl;

        else break;
    }

    Jogada jogada(get_linha(coluna), coluna);
    return jogada;
}

bool Lig4::jogadaValida(Jogada &jogada) const {
    int coluna = jogada.get_coluna();
    int linha = jogada.get_linha();

    if (coluna >= 1 && coluna <= this->colunas && linha != -1) 
        return true;

    else return false;
}

void Lig4::realizarJogada(Jogada &jogada) {
    if (jogadaValida(jogada)) {
        char simbolo;
        if (this->jogador_atual == 1) 
            simbolo = this->simbolo_jogador1;

        else if (this->jogador_atual == 2) 
            simbolo = this->simbolo_jogador2;

        set_char(jogada.get_linha(), jogada.get_coluna(), simbolo);

    } else std::cout << "ERRO: jogada invalida" << std::endl;
}

bool Lig4::linhaVazia(int linha) const {
    for (int j = 0; j < this->colunas; j++) {
        if (get_char(linha, j) != ' ') 
            return false;
    }

    return true;
}

bool Lig4::colunaVazia(int coluna) const {
    for (int i = 0; i < this->linhas; i++) {
        if (get_char(i, colunas) != ' ') 
            return false;
    }

    return true;
}

bool Lig4::verificarVitoria() const {
    char simbolo;
    if (this->jogador_atual == 1) 
        simbolo = simbolo_jogador1;

    else if (this->jogador_atual == 2) 
        simbolo = simbolo_jogador2;

    for (int i = 0; i < this->linhas; i++) {
        if (linhaVazia(i)) 
            continue;

        for (int j = 0; j < (this->colunas - 3); j++) {

            int qntd = 0;
            for (int k = j; k < j + 4; k++) {
                if (get_char(i, k) == ' ') 
                    continue;

                if (get_char(i, k) == simbolo) 
                    qntd++;
            }

            if (qntd == 4) 
                return true;
        }
    }

    for (int j = 0; j < this->colunas; j++) {
        if(colunaVazia(j)) 
            continue;

        for (int i = 0; i < (this->linhas - 3); i++) {

            int qntd = 0;
            for (int k = i; k < i + 4; k++) {
                if (get_char(k, j) == ' ') 
                    continue;

                if (get_char(k, j) == simbolo) 
                    qntd++;
            }

            if (qntd == 4) 
                return true;
        }
    }

    for (int i = 0; i < (this->linhas - 3); i++) {
        for (int j = 0; j < (this->colunas - 3); j++) {

            int qntd = 0;
            for (int k = i, l = j; k < i + 4; k++, l++) {
                if (get_char(k, l) == ' ') 
                    continue;

                if (get_char(k, l) == simbolo) 
                    qntd++;
            }

            if (qntd == 4) 
                return true;
        }
    }

    for (int i = 0; i < (this->linhas - 3); i++) {
        for (int j = (this->colunas - 1); (j - 3) >= 0; j--) {

            int qntd = 0;
            for (int k = i, l = j; k < i + 4; k++, l--) {
                if (get_char(k, l) == ' ') 
                    continue;

                if (get_char(k, l) == simbolo) 
                    qntd++;
            }

            if (qntd == 4) 
                return true;
        }
    }

    return false;
}

bool Lig4::tabuleiroCheio() const {
    for (int i = 0; i < this->linhas; i++) {
        for (int j = 0; j < this->colunas; j++) {
            if (get_char(i, j) == ' ') 
                return false;
        }
    }

    return true;
}

bool Lig4::verificarEmpate() const {
    return tabuleiroCheio();
}

void Lig4::imprimirVitoria() const {
    if (this->jogador_atual == 1) 
        std::cout << jogador1.getApelido();

    else if (this->jogador_atual == 2) 
        std::cout << jogador2.getApelido();

    std::cout << " venceu a partida!" << std::endl;
}

void Lig4::imprimirEmpate() const {
    std::cout << jogador1.getApelido() << " e ";
    std::cout << jogador2.getApelido() << " empataram!" << std::endl;
}

void Lig4::mudarTurno() {
    if (this->jogador_atual == 1) 
        this->jogador_atual = 2;

    else if (this->jogador_atual == 2) 
        this->jogador_atual = 1;
}

void Lig4::reiniciarTabuleiro() {
    for (int i = 0; i < this->linhas; i++) {
        for (int j = 0; j < this->colunas; j++) {
            set_char(i, j, ' ');
        }
    }
}

void Lig4::partida() {
    std::cout << "----------Lig4----------" << std::endl;

    Jogada jogada(0, 0);
    while(1) {
        imprimirTabuleiro();
    
        while(1) {
            jogada = lerJogada();
            if (jogadaValida(jogada)) break;
        }

        realizarJogada(jogada);

        if (verificarVitoria()) {
            imprimirVitoria();

            if (this->jogador_atual == 1) {
                jogador1.setPontuacao("Lig4", Resultado::Vitorias, 
                jogador1.getPontuacao("Lig4", Resultado::Vitorias) + 1);

                jogador2.setPontuacao("Lig4", Resultado::Derrotas, 
                jogador2.getPontuacao("Lig4", Resultado::Derrotas) + 1);

            } else {
                jogador1.setPontuacao("Lig4", Resultado::Derrotas, 
                jogador1.getPontuacao("Lig4", Resultado::Derrotas) + 1);

                jogador2.setPontuacao("Lig4", Resultado::Vitorias, 
                jogador2.getPontuacao("Lig4", Resultado::Vitorias) + 1);
            }

            break;

        } else if (verificarEmpate()) {
            imprimirEmpate();

            jogador1.setPontuacao("Lig4", Resultado::Empates, 
            jogador1.getPontuacao("Lig4", Resultado::Empates) + 1);

            jogador2.setPontuacao("Lig4", Resultado::Empates, 
            jogador2.getPontuacao("Lig4", Resultado::Empates) + 1);

            break;

        } else mudarTurno();
    }
}