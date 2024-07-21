#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>

#include "Sistema.hpp"
#include "Excecao.hpp"
#include "Lig4.hpp"
#include "Reversi.hpp"

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

void Sistema::cadastrarJogador(std::string apelido, std::string nome) {
    auto jogador = this->acharJogador(apelido);
    bool jogador_repetido = jogador != this->__jogadores.end();
    
    if(jogador_repetido) throw Excecao("jogador repetido");
    
    Jogador* novo_jogador = new Jogador(apelido, nome);
    this->__jogadores.push_back(novo_jogador);

    std::cout << "Jogador " << apelido << " cadastrado com sucesso" << std::endl;
}

void Sistema::removerJogador(std::string apelido) {
    auto jogador = this->acharJogador(apelido);
    bool jogador_inexistente = jogador == this->__jogadores.end();

    if(jogador_inexistente) throw Excecao("jogador inexistente");
    this->__jogadores.erase(jogador);

    std::cout << "Jogador " << apelido << " removido com sucesso" << std::endl;
}

void Sistema::listarJogadores(std::string criterio) {
    auto ordenacaoPorNome = [](Jogador* j1, Jogador* j2) { return j1->getNome() < j2->getNome(); };
    auto ordenacaoPorApelido = [](Jogador* j1, Jogador* j2) { return j1->getApelido() < j2->getApelido(); };

    if(criterio == "A")
        std::sort(this->__jogadores.begin(), this->__jogadores.end(), ordenacaoPorApelido);
    else if(criterio == "N")
        std::sort(this->__jogadores.begin(), this->__jogadores.end(), ordenacaoPorNome);
    else throw Excecao("criterio de ordenacao de jogadores invalido");

    this->carregarArquivo();
    int tam = this->__jogadores.size();
    for(int i = 0; i < tam; i++) {
        this->__jogadores[i]->imprimirInformacoes();
    }
}

void Sistema::executarComando(Comando comando_analisado) {
    switch (comando_analisado) {
        case Comando::CadastrarJogador: {
            std::string apelido, nome, saida;
            std::cin >> apelido >> nome;
            this->cadastrarJogador(apelido, nome);
            break;
        }
        
        case Comando::RemoverJogador: {
            std::string apelido, saida;
            std::cin >> apelido;
            this->removerJogador(apelido);
            break;
        }

        case Comando::ListarJogadores: {
            std::string criterio, saida;
            std::cin >> criterio;
            this->listarJogadores(criterio);
            break;
        }

        case Comando::ExecutarPartida: {
            std::string jogo;
            std::cin >> jogo;
            if(jogo == "Lig4") {
                

            }
            else if(jogo == "Reversi") {

            }
            else {

            }
            break;
        }

        case Comando::FinalizarSistema: {
            this->__sistema_finalizado = true;
            break;
        }

        default: {
            throw Excecao("comando invalido");
        }
    }
}

void Sistema::limparSistema() {
    this->__jogadores.clear();
}

void Sistema::carregarArquivo() {
    if(!this->__arquivo) throw Excecao("falha na abertura do arquivo");
    this->limparSistema();

    int numjogadores; this->__arquivo >> numjogadores;
    for(int i = 0; i < numjogadores; i++) {
        std::string apelido, nome;
        this->__arquivo >> apelido >> nome;
        Jogador* jogador = new Jogador(apelido, nome);

        int numjogos; this->__arquivo >> numjogos;
        for(int j = 0; j < numjogos; j++) {
            std::string jogo; this->__arquivo >> jogo;
            int vit, derr, emp; this->__arquivo >> vit >> derr >> emp;
            jogador->adicionarResultados(jogo, Resultados(vit, derr, emp));
        }

        this->__jogadores.push_back(jogador);
    }
}

Sistema::Sistema() {
    std::ifstream arquivo("./data/jogadores.txt");
    bool arquivoexiste = arquivo.good();
    arquivo.close();
    this->__arquivo = std::fstream("./data/jogadores.txt", std::fstream::out);

    if(!arquivoexiste) {
        this->__arquivo << "0";
        this->__arquivo.flush();
    }

    this->carregarArquivo();
}

Sistema::~Sistema() {
    this->__arquivo.close();
    this->limparSistema();
}