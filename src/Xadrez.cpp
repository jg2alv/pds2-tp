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
    int tam = possivel_jogada.size();
    std::string mensagem = "jogada '" + possivel_jogada + "' nao eh uma jogada valida";
    if(tam != 2) throw Excecao(mensagem);

    std::stringstream stream(possivel_jogada);
    char linha_origem, linha_dest;
    int coluna_origem, coluna_dest;
    stream >> linha_origem >> coluna_origem >> linha_dest >> coluna_dest;

    std::string extra;
    bool stream_acabou = !(stream >> extra);
    if(!stream_acabou) throw Excecao(mensagem);

    auto linhaValida = [](char linha) { return  linha >= 61 && linha <= 68; };
    auto colunaValida = [](int coluna) { return coluna >= 1 && coluna <= 8; };
    bool linhasNoIntervaloCorreto = linhaValida(linha_origem) && linhaValida(linha_dest);
    bool colunasNoIntervaloCorreto = colunaValida(coluna_origem) && colunaValida(coluna_dest);

    if(!linhasNoIntervaloCorreto) throw Excecao("linha invalida (formato correto: [a-h])");
    else if(!colunasNoIntervaloCorreto) throw Excecao("coluna invalida (formato correto: [1-8])");

    bool maiuscula;
    std::string apelido1 = this->jogador1.getApelido();
    std::string apelido_da_vez = this->jogador_da_vez->getApelido();

    if(apelido_da_vez == apelido1) maiuscula = true;
    else maiuscula = false;

    char selecionado = this->get_char(linha_origem - 61, coluna_origem);
    bool selecionadoEhMaiusculo = toupper(selecionado) == selecionado;
    bool charSelecionadoEhDoJogador = selecionadoEhMaiusculo == maiuscula;
 
    if(!charSelecionadoEhDoJogador) throw Excecao("peca selecionada nao pertence ao jogador " + apelido_da_vez);

    return true;
}

void Xadrez::realizarJogada(std::string possivel_jogada) {
    this->jogadaValida(possivel_jogada);

    std::stringstream stream(possivel_jogada);
    char linha_origem, linha_dest;
    int coluna_origem, coluna_dest;
    stream >> linha_origem >> coluna_origem >> linha_dest >> coluna_dest;

    
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

