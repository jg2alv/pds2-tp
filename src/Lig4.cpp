#include <iostream>
#include "Lig4.hpp"
#include "Jogada.hpp"
#include "Jogador.hpp"
#include "Jogo.hpp"

int Lig4::get_linha(int coluna) const
{
    if (get_char(0, coluna) != ' ')
        return -1;

    for (int i = (this->linhas - 1); i >= 0; i--)
    {
        if (get_char(i, coluna) == ' ')
            return i;
    }
}

bool Lig4::jogadaValida(Jogada &jogada) const
{
    int coluna = jogada.get_coluna();
    int linha = this->get_linha(coluna);

    if (coluna >= 1 && coluna <= this->colunas && linha != -1)
    {
        jogada.set_linha(linha);
        return true;
    }
    else
        return false;
}

bool Lig4::linhaVazia(int linha) const
{
    for (int j = 0; j < this->colunas; j++)
        if (get_char(linha, j) != ' ')
            return false;

    return true;
}

bool Lig4::colunaVazia(int coluna) const
{
    for (int i = 0; i < this->linhas; i++)
        if (get_char(i, colunas) != ' ')
            return false;

    return true;
}

bool Lig4::tabuleiroCheio() const
{
    for (int i = 0; i < this->linhas; i++)
        for (int j = 0; j < this->colunas; j++)
            if (get_char(i, j) == ' ')
                return false;

    return true;
}

void Lig4::imprimirVitoria() const
{
    if (this->jogador_atual == 1) std::cout << jogador1.getApelido();
    else if (this->jogador_atual == 2) std::cout << jogador2.getApelido();
    std::cout << " venceu a partida!" << std::endl;
}

void Lig4::imprimirEmpate() const
{
    std::cout << jogador1.getApelido() << " e ";
    std::cout << jogador2.getApelido() << " empataram!" << std::endl;
}

Lig4::Lig4(int linhas, int colunas, Jogador &jogador1, Jogador &jogador2)
    : Jogo(linhas, colunas, jogador1, jogador2)
{
    this->jogador_atual = 1;
}

void Lig4::imprimirTabuleiro() const
{
    for (int i = 0; i < this->linhas; i++)
    {
        for (int j = 0; j < this->colunas; j++)
        {
            std::cout << "|" << get_char(i, j) << "|";
        }
        std::cout << std::endl;
    }

    for (int i = 1; i <= this->colunas; i++)
    {
        std::cout << " " << i << " ";
    }
    std::cout << std::endl
              << std::endl;
}

Jogada Lig4::lerJogada(int jogador)
{
    std::cout << "Turno do jogador ";
    if (this->jogador_atual == 1) std::cout << this->jogador1.getApelido();
    else if (this->jogador_atual == 2) std::cout << this->jogador2.getApelido();
    std::cout << ": ";

    int coluna;
    std::cin >> coluna;
    Jogada jogada(coluna);

    return jogada;
}

void Lig4::realizarJogada(Jogada &jogada)
{
    if (jogadaValida(jogada) == true)
    {
        char simbolo;
        if (this->jogador_atual == 1) simbolo = this->simbolo_jogador1;
        else if (this->jogador_atual == 2) simbolo = this->simbolo_jogador2;

        set_char(jogada.get_linha(), jogada.get_coluna(), simbolo);
    }
    else
    {
        std::cout << "ERRO: jogada invalida" << std::endl;
        lerJogada(this->jogador_atual);
    }
}

bool Lig4::verificarVitoria() const
{
    char simbolo;
    if (this->jogador_atual == 1) simbolo = simbolo_jogador1;
    if (this->jogador_atual == 2) simbolo = simbolo_jogador2;

    for (int i = 0; i < this->linhas; i++) {
        if (linhaVazia(i) == true) continue;

        for (int j = 0; j < (this->colunas - 3); j++) {

            int qntd = 0;
            for (int k = j; k < j + 4; k++) {
                if (get_char(i, k) == ' ') continue;
                if (get_char(i, k) == simbolo) qntd++;
            }

            if (qntd == 4) return true;
        }
    }

    for (int i = 0; i < (this->linhas - 3); i++) {
        for (int j = 0; j < this->colunas; j++) {
            if(colunaVazia(j) == true) continue;

            int qntd = 0;
            for (int k = i; k < i + 4; k++) {
                if (get_char(k, j) == ' ') continue;
                if (get_char(k, j) == simbolo) qntd++;
            }

            if (qntd == 4) return true;
        }
    }

    for (int i = 0; i < (this->linhas - 3); i++) {
        for (int j = 0; j < (this->colunas - 3); j++) {

            int qntd = 0;
            for (int k = i, l = j; k < i + 4; k++, l++) {
                if (get_char(k, l) == ' ') continue;
                if (get_char(k, l) == simbolo) qntd++;
            }

            if (qntd == 4) return true;
        }
    }

    for (int i = 0; i < (this->linhas - 3); i++) {
        for (int j = (this->colunas - 1); (j - 3) >= 0; j--) {

            int qntd = 0;
            for (int k = i, l = j; k < i + 4; k++, l--) {
                if (get_char(k, l) == ' ') continue;
                if (get_char(k, l) == simbolo) qntd++;
            }

            if (qntd == 4) return true;
        }
    }

    return false;
}

bool Lig4::verificarEmpate() const
{
    if (tabuleiroCheio() == true)
    {
        imprimirEmpate();
        return true;
    }
    else
        return false;
}

void Lig4::reiniciarTabuleiro()
{
    for (int i = 0; i < this->linhas; i++)
        for (int j = 0; j < this->colunas; j++)
            set_char(i, j, ' ');
}

void Lig4::mudarTurno()
{
    if (this->jogador_atual == 1)
        this->jogador_atual = 2;
    else if (this->jogador_atual == 2)
        this->jogador_atual = 1;
}