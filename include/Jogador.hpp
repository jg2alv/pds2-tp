#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <string>
#include <iostream>
#include <map>
#include <vector>

/**
 * \brief Struct que armazena os resultados
 * 
 * Struct que armazena um número de vitórias, derrotas e empates.
 * Usado pelo Jogador e seus usuários.
 */
struct Resultados {
    int vitorias;
    int derrotas;
    int empates;

    Resultados(int vitorias, int derrotas, int empates);
    Resultados();
};

/**
 * \brief Classe Jogador que controla os participantes dos jogos
 * 
 * Classe que possui apelido, nome, e um mapa que relaciona os nomes dos Jogos e seus Resultados.
 * É usada tanto pelo Sistema quanto para controlar jogadores em um Jogo.
 */
class Jogador {
private:
    std::string _apelido;
    std::string _nome;
    std::map<std::string, Resultados> __pontuacao;

public:
    Jogador(std::string apelido, std::string nome);
    std::string getApelido() const;
    std::string getNome() const;

    bool operator==(Jogador const& outro) const;
    bool operator!=(Jogador const& outro) const;

    Resultados getResultados(std::string jogo) const;
    void setResultados(std::string jogo, Resultados resultados);
    void incrementarVitorias(std::string jogo);
    void incrementarDerrotas(std::string jogo);
    void incrementarEmpates(std::string jogo);
    int getNumeroDeJogos() const;
    std::vector<std::string> getJogosCadastrados() const;
    void imprimirInformacoes(std::ostream& out) const;
};

#endif

