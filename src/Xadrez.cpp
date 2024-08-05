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
    out << "-----------Xadrez-----------\n";

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

    if(!linhasNoIntervaloCorreto || !colunasNoIntervaloCorreto) return false;
    return true;
}

bool Xadrez::jogadaValida(std::string possivel_jogada) const {
    if(this->fimDeJogo()) return false;
    if(!this->formatoCorreto(possivel_jogada)) throw Excecao("formato de linhas e/ou colunas incorreto (padrao: [a-h][1-8][a-h][1-8])");

    int tam = possivel_jogada.size();
    if(tam != 4) return false;

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

    char peca_selecionada = this->get_char(linha_origem, coluna_origem);
    bool peca_selecionada_eh_maiuscula = toupper(peca_selecionada) == peca_selecionada;
    bool peca_selecionada_eh_do_jogador = peca_selecionada_eh_maiuscula == maiuscula;
    bool posicao_nao_mudou = linha_origem == linha_dest && coluna_origem == coluna_dest;
 
    if(!peca_selecionada_eh_do_jogador || peca_selecionada == ' ' || posicao_nao_mudou) return false;
    return true;
}

void Xadrez::realizarJogada(std::string possivel_jogada) {
    if(this->fimDeJogo()) throw Excecao("fim de jogo");
    if(!this->jogadaValida(possivel_jogada)) throw Excecao("peca selecionada nao pertence ao jogador atual");

    std::stringstream stream(possivel_jogada);
    char linha_origem, linha_dest;
    int coluna_origem, coluna_dest;
    stream >> linha_origem >> coluna_origem >> linha_dest >> coluna_dest;

    linha_origem -= 97;
    coluna_origem -= 1;
    linha_dest -= 97;
    coluna_dest -= 1;

    char peca_selecionada = this->get_char(linha_origem, coluna_origem);
    char peca_no_destino = this->get_char(linha_dest, coluna_dest);

    int diff_no_x = std::abs(coluna_origem - coluna_dest);
    int diff_no_y = std::abs(linha_origem - linha_dest);

    auto ehPecaInimiga = [](char peca1, char peca2){
        if(peca1 == ' ' || peca2 == ' ') return false;
        bool peca1_eh_maiuscula = peca1 == toupper(peca1);
        bool peca2_eh_maiuscula = peca2 == toupper(peca2);
        return peca1_eh_maiuscula != peca2_eh_maiuscula;
    };

    auto movimentoValidoDoPeaoEDoRei = [peca_selecionada, linha_dest, linha_origem, diff_no_y, diff_no_x, ehPecaInimiga, peca_no_destino](std::string peca){
        bool andou_para_tras = (peca_selecionada == 'P' && linha_dest > linha_origem) || (peca_selecionada == 'p' && linha_origem > linha_dest);
        if(andou_para_tras) throw Excecao(peca + " nao anda para tras");

        bool andou_mais_de_uma_casa = diff_no_x > 1 || diff_no_y > 1;
        if(andou_mais_de_uma_casa) throw Excecao(peca + " anda apenas uma casa");

        bool andou_na_diagonal = diff_no_y == 1 && diff_no_x == 1;
        bool tem_peca_inimiga_na_diagonal = ehPecaInimiga(peca_selecionada, peca_no_destino);
        if(andou_na_diagonal && !tem_peca_inimiga_na_diagonal) throw Excecao(peca + " nao anda na diagonal");

        if(!andou_na_diagonal && peca_no_destino != ' ') throw Excecao(peca + " so captura na diagonal");
    };

    auto movimentoValidoDaTorre = [diff_no_x, diff_no_y, coluna_origem, coluna_dest, this, linha_origem, linha_dest](){
        bool andou_em_mais_de_uma_direcao = diff_no_x != 0 && diff_no_y != 0;
        if(andou_em_mais_de_uma_direcao) return "torre so anda em uma direcao";

        if(diff_no_x != 0) {
            for(int i = coluna_origem + 1; i < coluna_dest; i++) {
                char c = this->get_char(linha_origem, i);
                if(c != ' ') return "torre nao pula pecas";
            }
        } else {
            for(int i = linha_origem + 1; i < linha_dest; i++) {
                char c = this->get_char(i, coluna_origem);
                if(c != ' ') return "torre nao pula pecas";
            }
        }

        return "";
    };

    auto movimentoValidoDoBispo = [diff_no_x, diff_no_y, linha_dest, linha_origem, coluna_dest, coluna_origem, this](){
        if(diff_no_x != diff_no_y) return "bispo so anda na diagonal";

        if(linha_dest > linha_origem && coluna_dest > coluna_origem) {
            for(int i = linha_origem + 1, j = coluna_origem + 1; i < linha_dest && j < coluna_dest; i++, j++) {
                char c = this->get_char(i, j);
                if(c != ' ') return "bispo nao pula pecas";
            }
        } else if(linha_dest < linha_origem && coluna_dest > coluna_origem) {
            for(int i = linha_origem - 1, j = coluna_origem + 1; i > linha_dest && j < coluna_dest; i--, j++) {
                char c = this->get_char(i, j);
                if(c != ' ') return "bispo nao pula pecas";
            }
        } else if(linha_dest > linha_origem && coluna_dest < coluna_origem) {
            for(int i = linha_origem + 1, j = coluna_origem - 1; i < linha_dest && j > coluna_dest; i++, j--) {
                char c = this->get_char(i, j);
                if(c != ' ') return "bispo nao pula pecas";
            }
        } else if(linha_dest < linha_origem && coluna_dest < coluna_origem) {
            for(int i = linha_origem - 1, j = coluna_origem - 1; i > linha_dest && j > coluna_dest; i--, j--) {
                char c = this->get_char(i, j);
                if(c != ' ') return "bispo nao pula pecas";
            }
        }

        return "";
    };

    switch(peca_selecionada) {
        case 'P':
        case 'p': {
            movimentoValidoDoPeaoEDoRei("peao");
            break;
        }

        case 'R':
        case 'r': {
            std::string err = movimentoValidoDaTorre();
            if(err != "") throw Excecao(err);
            break;
        }

        case 'N':
        case 'n': {
            bool movimento_valido = (diff_no_x == 1 && diff_no_y == 2) || (diff_no_x == 2 && diff_no_y == 1);
            if(!movimento_valido) throw Excecao("movimento invalido para o cavalo");
            
            bool no_destino_tem_inimigo = ehPecaInimiga(peca_selecionada, peca_no_destino);
            if(!no_destino_tem_inimigo) throw Excecao("peca no destino nao eh inimigo");

            break;
        }

        case 'B':
        case 'b': {
            std::string err = movimentoValidoDoBispo();
            if(err != "") throw Excecao(err);
            break;
        }

        case 'Q':
        case 'q': {
            std::string err1 = movimentoValidoDaTorre();
            std::string err2 = movimentoValidoDoBispo();
            if(err1 != "" && err2 != "") throw Excecao("movimento invalido para a rainha");

            break;
        }

        case 'K':
        case 'k': {
            movimentoValidoDoPeaoEDoRei("rei");
            break;
        }
    }

    this->set_char(linha_origem, coluna_origem, ' ');
    this->set_char(linha_dest, coluna_dest, peca_selecionada);
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

