#include "Xadrez.hpp"
#include "Jogada.hpp"
#include "Jogador.hpp"
#include "Jogo.hpp"
#include "Excecao.hpp"

#include <vector>
#include <string>
#include <algorithm>

Xadrez::Xadrez(Jogador &jogador1, Jogador &jogador2) : Jogo(8, 8, jogador1, jogador2) {
    std::string apelido1 = jogador1.getApelido();
    std::string apelido2 = jogador2.getApelido();

    Peca* torre11 = new Peca(Pecas::TorreBranca, Posicao{0, 0});
    Peca* torre12 = new Peca(Pecas::TorreBranca, Posicao{0, 7});
    Peca* torre21 = new Peca(Pecas::TorrePreta, Posicao{7, 0});
    Peca* torre22 = new Peca(Pecas::TorrePreta, Posicao{7, 7});
    this->pecas[apelido1].push_back(torre11);
    this->pecas[apelido1].push_back(torre12);
    this->pecas[apelido2].push_back(torre21);
    this->pecas[apelido2].push_back(torre22);

    Peca* cavalo11 = new Peca(Pecas::CavaloBranco, Posicao{0, 1});
    Peca* cavalo12 = new Peca(Pecas::CavaloBranco, Posicao{0, 6});
    Peca* cavalo21 = new Peca(Pecas::CavaloPreto, Posicao{7, 1});
    Peca* cavalo22 = new Peca(Pecas::CavaloPreto, Posicao{7, 6});
    this->pecas[apelido1].push_back(cavalo11);
    this->pecas[apelido1].push_back(cavalo12);
    this->pecas[apelido2].push_back(cavalo21);
    this->pecas[apelido2].push_back(cavalo22);

    Peca* bispo11 = new Peca(Pecas::BispoBranco, Posicao{0, 2});
    Peca* bispo12 = new Peca(Pecas::BispoBranco, Posicao{0, 5});
    Peca* bispo21 = new Peca(Pecas::BispoPreto, Posicao{7, 2});
    Peca* bispo22 = new Peca(Pecas::BispoPreto, Posicao{7, 5});
    this->pecas[apelido1].push_back(bispo11);
    this->pecas[apelido1].push_back(bispo12);
    this->pecas[apelido2].push_back(bispo21);
    this->pecas[apelido2].push_back(bispo22);

    Peca* rei1 = new Peca(Pecas::ReiBranco, Posicao{0, 3});
    Peca* rei2 = new Peca(Pecas::ReiPreto, Posicao{7, 3});
    this->pecas[apelido1].push_back(rei1);
    this->pecas[apelido2].push_back(rei2);

    Peca* rainha1 = new Peca(Pecas::RainhaBranca, Posicao{0, 4});
    Peca* rainha2 = new Peca(Pecas::RainhaPreta, Posicao{7, 4});
    this->pecas[apelido1].push_back(rainha1);
    this->pecas[apelido2].push_back(rainha2);

    for(int i = 0; i < 8; i++) {
        Peca* peao1 = new Peca(Pecas::PeaoBranco, Posicao{1, i});
        Peca* peao2 = new Peca(Pecas::PeaoPreto, Posicao{6, i});

        this->pecas[apelido1].push_back(peao1);
        this->pecas[apelido2].push_back(peao2);
    }

    this->preencherTabuleiro();
}

Xadrez::Xadrez(Jogador &jogador1, Jogador &jogador2, std::vector<std::vector<char>> tabuleiro) : Jogo(8, 8, jogador1, jogador2, tabuleiro) {}
Xadrez::~Xadrez() {
    std::string apelido1 = this->jogador1.getApelido();
    std::string apelido2 = this->jogador2.getApelido();

    auto pecas1 = this->pecas.at(apelido1);
    auto pecas2 = this->pecas.at(apelido2);

    for(Peca* peca : pecas1)
        delete peca;

    for(Peca* peca : pecas2)
        delete peca;

    pecas1.clear();
    pecas2.clear();
}

std::string Xadrez::getNome() const {
    return "Xadrez";
}

void Xadrez::preencherTabuleiro() {
    std::string apelido1 = this->jogador1.getApelido();
    std::string apelido2 = this->jogador2.getApelido();
    auto pecas1 = this->pecas.at(apelido1);
    auto pecas2 = this->pecas.at(apelido2);

    for(Peca* peca : pecas1) {
        Posicao pos = peca->getPosicao();
        char c = peca->getChar();
        int x = pos.x();
        int y = pos.y();

        this->set_char(x, y, c);
    }

    for(Peca* peca : pecas2) {
        Posicao pos = peca->getPosicao();
        char c = peca->getChar();
        int x = pos.x();
        int y = pos.y();

        this->set_char(x, y, c);
    }
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
    std::cout << possivel_jogada;
    return true;
}

void Xadrez::realizarJogada(std::string possivel_jogada) {
    std::cout << possivel_jogada;
}

bool Xadrez::verificarVitoria(Jogador const& jogador) const {
    auto acharRei = [](Peca* p) { return p->getTipo() == Pecas::ReiBranco || p->getTipo() == Pecas::ReiPreto; };
    std::string apelido = jogador.getApelido();
    auto pecas = this->pecas.at(apelido);
    auto rei = std::find_if(pecas.begin(), pecas.end(), acharRei);

    return rei == pecas.end();
}

bool Xadrez::verificarEmpate() const {
    return false;
}

Posicao::Posicao(int linha, int coluna) : linha(linha), coluna(coluna) {}
int Posicao::x() { return this->linha; }
int Posicao::y() { return this->coluna; }

Peca::Peca(Pecas tipo, Posicao pos) : tipo(tipo), pos(pos) {}
Pecas Peca::getTipo() { return this->tipo; }
Posicao Peca::getPosicao() { return this->pos; }
char Peca::getChar() {
    switch (this->tipo)
    {
    case Pecas::PeaoBranco:
        return 'P';
    
    case Pecas::PeaoPreto:
        return 'p';

    case Pecas::TorreBranca:
        return 'R';

    case Pecas::TorrePreta:
        return 'r';

    case Pecas::CavaloBranco:
        return 'K';

    case Pecas::CavaloPreto:
        return 'k';

    case Pecas::BispoBranco:
        return 'B';

    case Pecas::BispoPreto:
        return 'b';

    case Pecas::ReiBranco:
        return 'E';

    case Pecas::ReiPreto:
        return 'e';

    case Pecas::RainhaBranca:
        return 'A';

    case Pecas::RainhaPreta:
        return 'a';

    default:
        throw Excecao("erro");
    }
}