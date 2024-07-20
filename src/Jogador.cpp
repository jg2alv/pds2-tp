#include <iostream>
#include <string>

#include "Jogador.hpp"

Jogador::Jogador(std::string apelido, std::string nome) : _apelido(apelido), _nome(nome) {
    this->__pontuacao["Reversi"][Resultado::Vitorias] = 0;
    this->__pontuacao["Reversi"][Resultado::Derrotas] = 0;
    this->__pontuacao["Reversi"][Resultado::Empates] = 0;
    this->__pontuacao["Lig4"][Resultado::Vitorias] = 0;
    this->__pontuacao["Lig4"][Resultado::Derrotas] = 0;
    this->__pontuacao["Lig4"][Resultado::Empates] = 0;
}

std::string Jogador::getApelido() const {
    return this->_apelido;
}

std::string Jogador::getNome() {
    return this->_nome;
}

int Jogador::getPontuacao(std::string jogo, Resultado resultado) {
    return this->__pontuacao[jogo][resultado];
}

void Jogador::imprimirInformacoes() {
    std::string apelido = this->getApelido();
    std::string nome = this->getNome();

    for(auto it = this->__pontuacao.begin(); it != this->__pontuacao.end(); it++) {
        std::cout << it->first << std::endl;
    }

    std::cout << apelido << " " << nome << std::endl; 
}