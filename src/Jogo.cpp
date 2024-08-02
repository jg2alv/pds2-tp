#include <algorithm>

#include "Jogo.hpp"


char Jogo::get_char(int i, int j) const {
    return tabuleiro[i * colunas + j];
}

void Jogo::set_char(int i, int j, char c) {
    tabuleiro[i * colunas + j] = c;
}

void Jogo::passar_a_vez() {
    std::swap(jogador_da_vez, outro_jogador);
}


Jogo::Jogo(int linhas, int colunas, Jogador& jogador1, Jogador& jogador2) :
    linhas(linhas),
    colunas(colunas),
    tabuleiro(linhas*colunas, ' '),
    jogo_finalizado(false),
    jogador1(jogador1),
    jogador2(jogador2 ),
    jogador_da_vez(&jogador1),
    outro_jogador(&jogador2),
    simbolos{{jogador1.getApelido(), 'X'}, {jogador2.getApelido(), 'O'}} {}

Jogo::~Jogo() {
    finalizarJogo();
}

bool Jogo::fimDeJogo() const {
    if (jogo_finalizado) {
        return true;
    } else {
        return verificarEmpate() || verificarVitoria(jogador1) || verificarVitoria(jogador2);
    }
}

void Jogo::finalizarJogo() {
    if (jogo_finalizado) {
        return;
    }

    if (!fimDeJogo() || verificarEmpate()) {
        jogador1.incrementarEmpates(getNome());
        jogador2.incrementarEmpates(getNome());
    } else {
        Jogador *vencedor = verificarVitoria(jogador1) ? &jogador1 : &jogador2;
        if (jogador_da_vez == vencedor) {
            passar_a_vez();
        }

        jogador_da_vez->incrementarDerrotas(getNome());
        outro_jogador->incrementarVitorias(getNome());
    }

    jogo_finalizado = true;
}

Jogador *Jogo::getJogadorDaVez() const {
    return jogador_da_vez;
}

Jogador *Jogo::getOutroJogador() const {
    return outro_jogador;
}

