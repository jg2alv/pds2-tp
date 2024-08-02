#include <iostream>
#include <string>
#include <vector>

#include "Jogador.hpp"


Resultados::Resultados(int vitorias, int derrotas, int empates) :
    vitorias(vitorias), derrotas(derrotas), empates(empates) {}

Resultados::Resultados() : Resultados(0, 0, 0) {}


Jogador::Jogador(std::string apelido, std::string nome) : _apelido(apelido), _nome(nome) {}

std::string Jogador::getApelido() const {
    return this->_apelido;
}

std::string Jogador::getNome() {
    return this->_nome;
}


Resultados& Jogador::getResultados(std::string jogo) {
    return __pontuacao[jogo];
}

void Jogador::adicionarResultados(std::string jogo, Resultados resultados) {
    __pontuacao[jogo] = resultados;
}

void Jogador::incrementarVitorias(std::string jogo) {
    __pontuacao[jogo].vitorias++;
}

void Jogador::incrementarDerrotas(std::string jogo) {
    __pontuacao[jogo].derrotas++;
}

void Jogador::incrementarEmpates(std::string jogo) {
    __pontuacao[jogo].empates++;
}

int Jogador::getNumeroDeJogos() {
    return __pontuacao.size();
}

std::vector<std::string> Jogador::getJogosCadastrados()
{
    std::vector<std::string> jogos;
    for (auto it = __pontuacao.begin(); it != __pontuacao.end(); it++) {
        jogos.push_back(it->first);
    }

    return jogos;
}

void Jogador::imprimirInformacoes(std::ostream& out) {
    std::string apelido = this->getApelido();
    std::string nome = this->getNome();
    out << apelido << " " << nome << std::endl;
    std::vector<std::string> jogos = getJogosCadastrados();
    for (int i = 0; i < getNumeroDeJogos(); i++)
    {
        Resultados resultados = __pontuacao[jogos[i]];
        out << jogos[i] << " - " << "V: " << resultados.vitorias << " ";
        out << "D: " << resultados.derrotas << std::endl;
    }
}


