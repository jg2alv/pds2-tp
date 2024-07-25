#include <iostream>
#include <string>
#include <sstream>
#include "Lig4.hpp"
#include "Jogada.hpp"
#include "Jogador.hpp"
#include "Jogo.hpp"

Lig4::Lig4(int linhas, int colunas, Jogador &jogador1, Jogador &jogador2)
    : Jogo(linhas, colunas, jogador1, jogador2) {}

void Lig4::imprimirTabuleiro() const {
    std::cout << "----------Lig4----------" << std::endl;
    
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

    int formato_correto = 1;
    int qntd_numeros = 0;
    std::string aux;
    std::string coluna_str;

    while (in >> aux) {
        for (int i = 0; i < aux.length(); i++) {
            if (aux[i] < 48 || aux[i] > 57) 
                formato_correto = 0;
        }

        if (formato_correto && (qntd_numeros == 0)) {
            coluna_str = aux;
            qntd_numeros++;

        } else return -1;
    } 

    int coluna = stoi(coluna_str);
    return coluna;
}

int Lig4::getLinhaTabuleiro(int coluna) const {
    if (get_char(0, coluna) != ' ') 
        return 0;

    for (int i = (this->linhas - 1); i >= 0; i--) {
        if (get_char(i, coluna) == ' ') 
            return (i + 1);
    }
}

Jogada Lig4::lerJogada() {
    std::string entrada;
    int coluna;

    while (1) {
        std::cout << "Turno do jogador ";
        std::cout << this->jogador_atual->getApelido();
        std::cout << ": ";

        getline(std::cin, entrada);
        coluna = formatoCorreto(entrada);

        if (coluna == -1) 
            std::cout << "ERRO: formato incorreto" << std::endl;

        else break;
    }

    Jogada jogada(getLinhaTabuleiro(coluna), coluna);
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
    std::string apelido = jogador_atual->getApelido();
    char simbolo = this->simbolos.at(apelido);
    set_char(jogada.get_linha(), jogada.get_coluna(), simbolo);
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
    std::string apelido = jogador_atual->getApelido();
    char simbolo = this->simbolos.at(apelido);

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
    std::cout << jogador_atual->getApelido();
    std::cout << " venceu a partida!" << std::endl;
}

void Lig4::imprimirEmpate() const {
    std::cout << jogador1.getApelido() << " e ";
    std::cout << jogador2.getApelido() << " empataram!" << std::endl;
}

void Lig4::mudarTurno() {
    if (jogador_atual->getApelido() == jogador1.getApelido()) 
        this->jogador_atual = &jogador2;

    else if (jogador_atual->getApelido() == jogador2.getApelido()) 
        this->jogador_atual = &jogador1;
}

Jogador* Lig4::getJogadorOponente() {
    if (jogador_atual->getApelido() == jogador1.getApelido()) 
        return &jogador2;
    else
        return &jogador1;
}

void Lig4::partida() {
    Jogada jogada(0, 0);
    while(1) {
        imprimirTabuleiro();
    
        while(1) {
            jogada = lerJogada();
            if (jogadaValida(jogada)) break;
            else 
                std::cout << "ERRO: jogada invalida" << std::endl;
        }

        realizarJogada(jogada);

        if (verificarVitoria()) {
            imprimirVitoria();

            jogador_atual->incrementarVitorias("Lig4");
            getJogadorOponente()->incrementarDerrotas("Lig4");

            break;

        } else if (verificarEmpate()) {
            imprimirEmpate();

            jogador1.incrementarEmpates("Lig4");
            jogador2.incrementarEmpates("Lig4");

            break;

        } else mudarTurno();
    }
}