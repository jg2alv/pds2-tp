#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <string>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

/**
 * \brief struct que armazena os resultados
 * 
 */
struct Resultados {
    int vitorias;
    int derrotas;
    int empates;

    Resultados(int vitorias, int derrotas, int empates);
    Resultados();
};

/**
 * \class Jogador
 * \brief Classe Jogador que controla os participantes dos jogos
 * 
 * Classe que possui apelido, nome, e um mapa que relaciona os Jogos e seus Resultados
 * para determinado jogador. Também é usada para controlar jogadores dentro de uma partida
 * 
 */
class Jogador {
private:
    string _apelido;
    string _nome;
    map<string, Resultados> __pontuacao;

public:
    Jogador(string apelido, string nome);
    string getApelido() const;
    string getNome() const;

    bool operator==(Jogador const& outro) const;
    bool operator!=(Jogador const& outro) const;

    Resultados getResultados(string jogo) const;
    void setResultados(string jogo, Resultados resultados);
    void incrementarVitorias(string jogo);
    void incrementarDerrotas(string jogo);
    void incrementarEmpates(string jogo);
    int getNumeroDeJogos() const;
    vector<string> getJogosCadastrados() const;
    void imprimirInformacoes(ostream& out) const;
};

#endif

