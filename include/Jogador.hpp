#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <string>
#include <iostream>
#include <map>
#include <vector>

struct Resultados {
    int vitorias;
    int derrotas;
    int empates;

    Resultados(int vitorias, int derrotas, int empates);
    Resultados();
};

class Jogador {
private:
    std::string _apelido;
    std::string _nome;
    std::map<std::string, Resultados> __pontuacao;

public:
    Jogador(std::string apelido, std::string nome);
    std::string getApelido() const;
    std::string getNome();

    bool operator==(Jogador const& outro) const;
    bool operator!=(Jogador const& outro) const;

    Resultados getResultados(std::string jogo);
    void setResultados(std::string jogo, Resultados resultados);
    void incrementarVitorias(std::string jogo);
    void incrementarDerrotas(std::string jogo);
    void incrementarEmpates(std::string jogo);
    int getNumeroDeJogos();
    std::vector<std::string> getJogosCadastrados();
    void imprimirInformacoes(std::ostream& out);
};

#endif

