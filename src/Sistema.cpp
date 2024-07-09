#include <string>
#include <iostream>

#include "Sistema.hpp"
#include "Excecao.hpp"

void Sistema::cadastrarJogador(std::string apelido, std::string nome) {
    bool jogador_existe = this->jogadorExiste(apelido);
    if(jogador_existe) throw Excecao("jogador repetido");
    
    Jogador* jogador = new Jogador(apelido, nome);
    this->__jogadores.push_back(jogador);
}

void Sistema::removerJogador(std::string apelido) {
    bool jogador_existe = this->jogadorExiste(apelido);
    if(!jogador_existe) throw Excecao("jogador inexistente");

    //remover jogador
}

int Sistema::listarJogadores() {
    return 0;
}

bool Sistema::jogadorExiste(std::string apelido) {
    int tam = this->__jogadores.size();
    for(int i = 0; i < tam; i++)
        if(this->__jogadores[i]->getApelido() == apelido) return true;
    
    return false;
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
            return "";
        }

        case Comando::ExecutarPartida: {
            return "";
        }

        case Comando::FinalizarSistema: {
            return "";
        }

        default: {
            throw Excecao("comando invalido");
        }
    }
}