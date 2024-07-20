#include <string>
#include <iostream>
#include <algorithm>

#include "Sistema.hpp"
#include "Excecao.hpp"

bool Sistema::isSistemaFinalizado() { return this->__sistema_finalizado; }

Comando Sistema::analisarComando(std::string comando) {
    if (comando == "CJ") return Comando::CadastrarJogador;
    else if (comando == "RJ") return Comando::RemoverJogador;
    else if (comando == "LJ") return Comando::ListarJogadores;
    else if (comando == "EP") return Comando::ExecutarPartida;
    else if (comando == "FS") return Comando::FinalizarSistema;
    else throw Excecao("comando invalido");
}

std::vector<Jogador *>::iterator Sistema::acharJogador(std::string apelido) {
    auto acharJogador = [apelido](Jogador* j) { return j->getApelido() == apelido; };
    auto jogador = std::find_if(this->__jogadores.begin(), this->__jogadores.end(), acharJogador);
    
    return jogador;
}

std::string Sistema::cadastrarJogador(std::string apelido, std::string nome) {
    auto jogador = this->acharJogador(apelido);
    bool jogador_repetido = jogador != this->__jogadores.end();
    
    if(jogador_repetido) throw Excecao("jogador repetido");
    
    Jogador* novo_jogador = new Jogador(apelido, nome);
    this->__jogadores.push_back(novo_jogador);

    return "Jogador " + apelido + " cadastrado com sucesso";
}

std::string Sistema::removerJogador(std::string apelido) {
    auto jogador = this->acharJogador(apelido);
    bool jogador_inexistente = jogador == this->__jogadores.end();

    if(jogador_inexistente) throw Excecao("jogador inexistente");
    this->__jogadores.erase(jogador);

    return "Jogador " + apelido + " removido com sucesso";
}

std::string Sistema::listarJogadores(std::string criterio) {
    auto ordenacaoPorNome = [](Jogador* j1, Jogador* j2) { return j1->getNome() < j2->getNome(); };
    auto ordenacaoPorApelido = [](Jogador* j1, Jogador* j2) { return j1->getApelido() < j2->getApelido(); };

    if(criterio == "A")
        std::sort(this->__jogadores.begin(), this->__jogadores.end(), ordenacaoPorApelido);
    else if(criterio == "N")
        std::sort(this->__jogadores.begin(), this->__jogadores.end(), ordenacaoPorNome);
    else throw Excecao("criterio de ordenacao de jogadores invalido");

    int tam = this->__jogadores.size();
    std::string saida = "";

    for(int i = 0; i < tam; i++) {
        std::string apelido = this->__jogadores[i]->getApelido();
        std::string nome = this->__jogadores[i]->getNome();

        saida += apelido + " " + nome + "\n"; 
        // vitorias e derrotas
    }

    return saida;
}

std::string Sistema::executarComando(Comando comando_analisado) {
    switch (comando_analisado) {
        case Comando::CadastrarJogador: {
            std::string apelido, nome, saida;
            std::cin >> apelido >> nome;
            saida = this->cadastrarJogador(apelido, nome);
            return saida;
        }
        
        case Comando::RemoverJogador: {
            std::string apelido, saida;
            std::cin >> apelido;
            saida = this->removerJogador(apelido);
            return saida;
        }

        case Comando::ListarJogadores: {
            std::string criterio, saida;
            std::cin >> criterio;
            saida = this->listarJogadores(criterio);
            return saida;
        }

        case Comando::ExecutarPartida: {
            return "";
        }

        case Comando::FinalizarSistema: {
            this->__sistema_finalizado = true;
            return "";
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