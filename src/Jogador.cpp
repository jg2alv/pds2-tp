#include <iostream>
#include <string>

#include "Jogador.hpp"

Jogador::Jogador(std::string apelido, std::string nome) : _apelido(apelido), _nome(nome) {}

std::string Jogador::getApelido() const {
    return this->_apelido;
}

std::string Jogador::getNome() {
    return this->_nome;
}

int Jogador::getPontuacao(std::string jogo, Resultado resultado) {
    return this->__pontuacao[jogo][resultado];
}

void Jogador::setPontuacao(std::string jogo, Resultado resultado, int pontuacao) {
    this->__pontuacao[jogo][resultado] = pontuacao;
}

void Jogador::imprimirInformacoes() {
    std::string apelido = this->getApelido();
    std::string nome = this->getNome();
    
    std::cout << apelido << " " << nome << std::endl; 
}