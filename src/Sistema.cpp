#include <string>
#include <iostream>
#include <algorithm>

#include "Sistema.hpp"
#include "Excecao.hpp"

void Sistema::cadastrarJogador(std::string apelido, std::string nome) {
    int indice_jogador = this->indiceDoJogador(apelido);
    if(indice_jogador != -1) throw Excecao("jogador repetido");
    
    Jogador* jogador = new Jogador(apelido, nome);
    this->__jogadores.push_back(jogador);
}

void Sistema::removerJogador(std::string apelido) {
    int indice_jogador = this->indiceDoJogador(apelido);
    if(indice_jogador == -1) throw Excecao("jogador inexistente");

    this->__jogadores.erase(this->__jogadores.begin() + indice_jogador);
}

bool ordenacaoPorNome(Jogador* j1, Jogador* j2) { return j1->getNome() < j2->getNome(); };
bool ordenacaoPorApelido(Jogador* j1, Jogador* j2) { return j1->getApelido() < j2->getApelido(); };

void Sistema::listarJogadores(std::string criterio) {    
    if(criterio == "A")
        std::sort(this->__jogadores.begin(), this->__jogadores.end(), ordenacaoPorApelido);
    else if(criterio == "N")
        std::sort(this->__jogadores.begin(), this->__jogadores.end(), ordenacaoPorNome);
    else throw Excecao("criterio de ordenacao de jogadores invalido");

    int tam = this->__jogadores.size();
    for(int i = 0; i < tam; i++) {
        std::string apelido = this->__jogadores[i]->getApelido();
        std::string nome = this->__jogadores[i]->getNome();

        std::cout << apelido << " " << nome << std::endl; 
        // vitorias e derrotas
    }
}

int Sistema::indiceDoJogador(std::string apelido) {
    int tam = this->__jogadores.size();
    for(int i = 0; i < tam; i++)
        if(this->__jogadores[i]->getApelido() == apelido) return i;
    
    return -1;
}

Comando Sistema::analisarComando(std::string comando) {
    if (comando == "CJ") return Comando::CadastrarJogador;
    else if (comando == "RJ") return Comando::RemoverJogador;
    else if (comando == "LJ") return Comando::ListarJogadores;
    else if (comando == "EP") return Comando::ExecutarPartida;
    else if (comando == "FS") return Comando::FinalizarSistema;
    else throw Excecao("comando invalido");
}

std::string Sistema::executarComando(Comando comando_analisado) {
    switch (comando_analisado) {
        case Comando::CadastrarJogador: {
            std::string apelido, nome;
            std::cin >> apelido >> nome;
            this->cadastrarJogador(apelido, nome);
            return "Jogador " + apelido + " cadastrado com sucesso";
        }
        
        case Comando::RemoverJogador: {
            std::string apelido;
            std::cin >> apelido;
            this->removerJogador(apelido);
            return "Jogador " + apelido + " removido com sucesso";
        }

        case Comando::ListarJogadores: {
            std::string criterio;
            std::cin >> criterio;
            this->listarJogadores(criterio);
            return "";
        }

        case Comando::ExecutarPartida: {
            return "";
        }

        case Comando::FinalizarSistema: {
            return "FS";
        }

        default: {
            throw Excecao("comando invalido");
        }
    }
}

Sistema::~Sistema() {
    int tam = this->__jogadores.size();
    for(int i = 0; i < tam; i++)
        delete this->__jogadores[i];
}