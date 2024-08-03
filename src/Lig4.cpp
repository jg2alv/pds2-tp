#include <iostream>
#include <string>
#include <sstream>
#include "Lig4.hpp"
#include "Jogada.hpp"
#include "Jogador.hpp"
#include "Jogo.hpp"
#include "Excecao.hpp"


Lig4::Lig4(int linhas, int colunas, Jogador &jogador1, Jogador &jogador2) :
    Jogo(linhas, colunas, jogador1, jogador2) {}

Lig4::~Lig4() {}


std::string Lig4::getNome() const {
    return "Lig4";
}

void Lig4::imprimirTabuleiro(std::ostream& out) const {
    out << "----------Lig4----------\n";
    
    for (int i = 0; i < this->linhas; i++) {
        for (int j = 0; j < this->colunas; j++) {
            std::cout << "|" << get_char(i, j) << "|";
        }
        out << std::endl;
    }

    for (int i = 1; i <= this->colunas; i++) {
        out << " " << i << " ";
    }

    out << std::endl;
}

bool Lig4::formatoCorreto(std::string entrada) const {
    std::stringstream in;
    in.str(entrada);

    bool formato_correto = true;
    int qntd_numeros = 0;
    std::string aux;
    std::string coluna_str = "";

    while (in >> aux) {
        for (std::string::size_type i = 0; i < aux.length(); i++) {
            if (aux[i] < 48 || aux[i] > 57) 
                formato_correto = false;
        }

        if (formato_correto && (qntd_numeros == 0)) {
            coluna_str = aux;
            qntd_numeros++;

        } else return false;
    } 

    if(coluna_str == "") return false;
    else return true;
}

int Lig4::getLinhaTabuleiro(int coluna) const {
    int i = this->linhas - 1;
    for (; i >= 0; i--) {
        if (get_char(i, coluna) == ' ') 
            break;
    }
    return i;
}

bool Lig4::jogada_valida(const Jogada &jogada) const {
    int coluna = jogada.get_coluna();
    int linha = jogada.get_linha();

    if (coluna >= 0 && coluna < this->colunas && linha != -1) 
        return true;

    else return false;
}

bool Lig4::jogadaValida(std::string possivel_jogada) const {
    if (fimDeJogo()) {
        return false;
    }

    if (formatoCorreto(possivel_jogada)) {
        std::stringstream in;
        in.str(possivel_jogada);
        
        int coluna;
        in >> coluna;

        Jogada jogada(getLinhaTabuleiro(coluna), coluna);
        return jogada_valida(jogada);
    } else {
        return false;
    }
}

void Lig4::realizarJogada(std::string possivel_jogada) {
    if (fimDeJogo()) {
        throw Excecao("jogo ja acabou");
    }

    if (!formatoCorreto(possivel_jogada)) {
        throw Excecao("formato incorreto");
    }

    std::stringstream in;
    in.str(possivel_jogada);
    
    int coluna;
    in >> coluna;

    Jogada jogada(getLinhaTabuleiro(coluna), coluna);
    if (!jogada_valida(jogada)) {
        throw Excecao("jogada invalida");
    }

    realizar_jogada(jogada);
}

void Lig4::realizar_jogada(const Jogada &jogada) {
    std::string apelido = jogador_da_vez->getApelido();
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
        if (get_char(i, coluna) != ' ') 
            return false;
    }

    return true;
}

bool Lig4::verificarVitoria(const Jogador& jogador) const {
    std::string apelido = jogador.getApelido();
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

