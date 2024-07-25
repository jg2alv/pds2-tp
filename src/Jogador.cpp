#include <iostream>
#include <string>

#include "Jogador.hpp"


Resultados::Resultados(int vitorias, int derrotas, int empates)
    : vitorias(vitorias), derrotas(derrotas), empates(empates) {}

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

int Jogador::getNumeroDeJogos() {
    return __pontuacao.size();
}

void Jogador::imprimirInformacoes() {
    std::string apelido = this->getApelido();
    std::string nome = this->getNome();
    Resultados resultadosReversi = this->getResultados("Reversi");
    Resultados resultadosLig4= this->getResultados("Lig4");
    
    std::cout << apelido << " " << nome << std::endl; 
    std::cout << "REVERSI - " << "V: " << resultadosReversi.vitorias;
    std::cout << "D: " << resultadosReversi.derrotas << std::endl;
    std::cout << "LIG4 - " << "V: " << resultadosLig4.vitorias;
    std::cout << "D: " << resultadosLig4.derrotas << std::endl;

}
