#include "Xadrez.hpp"
#include "Jogada.hpp"
#include "Jogador.hpp"
#include "Jogo.hpp"
#include "Excecao.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

Xadrez::Xadrez(Jogador &jogador1, Jogador &jogador2) : Jogo(8, 8, jogador1, jogador2) {
    char pecas[] = { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' };

    for(int i = 0; i < this->colunas; i++) {
        char peca = pecas[i];
        this->set_char(0, i, peca);
        this->set_char(1, i, 'p');

        this->set_char(7, i, toupper(peca));
        this->set_char(6, i, 'P');
    }
}

Xadrez::Xadrez(Jogador &jogador1, Jogador &jogador2, std::vector<std::vector<char>> tabuleiro) : Jogo(8, 8, jogador1, jogador2, tabuleiro) {}

Xadrez::~Xadrez() {}

std::string Xadrez::getNome() const {
    return "Xadrez";
}

void Xadrez::imprimirTabuleiro(std::ostream& out) const {
    out << "---------Xadrez---------\n";

    char alpha[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    out << "   1  2  3  4  5  6  7  8 " << std::endl;
    for (int i = 0; i < this->linhas; i++) {
        out << alpha[i] << " ";
        for (int j = 0; j < this->colunas; j++) {
            std::cout << "|" << get_char(i, j) << "|";
        }
        out << " " << alpha[i] << std::endl;
    }
    out << "   1  2  3  4  5  6  7  8 " << std::endl;
}

bool Xadrez::formatoCorreto(std::string possivel_jogada) const {
    std::stringstream stream(possivel_jogada);
    char linha_origem, linha_dest;
    int coluna_origem, coluna_dest;
    stream >> linha_origem >> coluna_origem >> linha_dest >> coluna_dest;

    linha_origem -= 97;
    coluna_origem -= 1;
    linha_dest -= 97;
    coluna_dest -= 1;

    auto linhaValida = [](char linha) { return  linha >= 0 && linha <= 7; };
    auto colunaValida = [](int coluna) { return coluna >= 0 && coluna <= 7; };

    bool linhasNoIntervaloCorreto = linhaValida(linha_origem) && linhaValida(linha_dest);
    bool colunasNoIntervaloCorreto = colunaValida(coluna_origem) && colunaValida(coluna_dest);

    if(!linhasNoIntervaloCorreto) throw Excecao("linha invalida (formato correto: [a-h])");
    else if(!colunasNoIntervaloCorreto) throw Excecao("coluna invalida (formato correto: [1-8])");

    return true;
}

bool Xadrez::jogadaValida(std::string possivel_jogada) const {
    int tam = possivel_jogada.size();
    std::string mensagem = "jogada '" + possivel_jogada + "' nao eh uma jogada valida";
    if(tam != 4) throw Excecao(mensagem);
    this->formatoCorreto(possivel_jogada);

    std::stringstream stream(possivel_jogada);
    char linha_origem, linha_dest;
    int coluna_origem, coluna_dest;
    stream >> linha_origem >> coluna_origem >> linha_dest >> coluna_dest;

    linha_origem -= 97;
    coluna_origem -= 1;
    linha_dest -= 97;
    coluna_dest -= 1;

    bool maiuscula;
    std::string apelido1 = this->jogador1.getApelido();
    std::string apelido_da_vez = this->jogador_da_vez->getApelido();

    if(apelido_da_vez == apelido1) maiuscula = true;
    else maiuscula = false;

    char selecionado = this->get_char(linha_origem, coluna_origem);
    bool selecionadoEhMaiusculo = toupper(selecionado) == selecionado;
    bool charSelecionadoEhDoJogador = selecionadoEhMaiusculo == maiuscula;
 
    if(!charSelecionadoEhDoJogador || selecionado == ' ') throw Excecao("peca selecionada nao pertence ao jogador " + apelido_da_vez);

    return true;
}

void Xadrez::realizarJogada(std::string possivel_jogada) {
    this->jogadaValida(possivel_jogada);

    std::stringstream stream(possivel_jogada);
    char linha_origem, linha_dest;
    int coluna_origem, coluna_dest;
    stream >> linha_origem >> coluna_origem >> linha_dest >> coluna_dest;

    linha_origem -= 97;
    coluna_origem -= 1;
    linha_dest -= 97;
    coluna_dest -= 1;

    char selecionado = this->get_char(linha_origem, coluna_origem);
    char peca_no_destino = this->get_char(linha_dest, coluna_dest);

    auto ehPecaInimiga = [](char peca1, char peca2){
        if(peca1 == ' ' || peca2 == ' ') return false;
        bool peca1_eh_maiuscula = peca1 == toupper(peca1);
        bool peca2_eh_maiuscula = peca2 == toupper(peca2);
        return peca1_eh_maiuscula != peca2_eh_maiuscula;
    }; 

    switch(selecionado) {
        case 'P':
        case 'p': {
            bool andou_para_tras = (selecionado == 'P' && linha_dest > linha_origem) || (selecionado == 'p' && linha_origem > linha_dest);
            if(andou_para_tras) throw Excecao("peao nao anda para tras");

            int diff_no_y = std::abs(linha_origem - linha_dest);
            int diff_no_x = std::abs(coluna_origem - coluna_dest);

            bool andou_mais_de_uma_casa = diff_no_y > 1;
            if(andou_mais_de_uma_casa) throw Excecao("peao anda apenas uma casa");

            bool andou_na_diagonal = diff_no_y == 1 && diff_no_x == 1;
            bool tem_peca_inimiga_na_diagonal = ehPecaInimiga(selecionado, peca_no_destino);
            if(andou_na_diagonal && !tem_peca_inimiga_na_diagonal) throw Excecao("peao nao pode andar na diagonal");

            this->set_char(linha_origem, coluna_origem, ' ');
            this->set_char(linha_dest, coluna_dest, selecionado);
            break;
        }

        case 'R':
        case 'r': {
            break;
        }

        case 'N':
        case 'n': {
            break;
        }

        case 'B':
        case 'b': {
            break;
        }

        case 'Q':
        case 'q': {
            break;
        }

        case 'K':
        case 'k': {
            break;
        }
    }
    this->passar_a_vez();
}

bool Xadrez::verificarVitoria(Jogador const& jogador) const {
    // jogador1 eh branco: rei eh K
    // jogador2 eh preto: rei eh k

    // se verifica vitoria de jogador1, tem que ver se existe k.
    // se nao existir, jogador1 venceu
    
    // se verifica vitoria de jogador2, tem que ver se existe K.
    // se no existir, jogador2 venceu
    char rei = jogador.getApelido() == jogador1.getApelido() ? 'k' : 'K';

    for(int i = 0; i < this->linhas; i++) {
        for(int j = 0; j < this->colunas; j++) {
            char c = this->get_char(i, j);
            if(c == rei) return false;
        }
    }

    return true;
}

bool Xadrez::verificarEmpate() const {
    return false;
}

