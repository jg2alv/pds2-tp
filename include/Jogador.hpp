#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <string>
#include <map>

enum class Resultado {
    Vitorias,
    Derrotas,
    Empates
};

class Jogador {
private:
    std::string _apelido;
    std::string _nome;
    std::map<std::string, std::map<Resultado, int>> __pontuacao;

public:
    Jogador(std::string apelido, std::string nome);
    std::string getApelido() const;
    std::string getNome();
    int getPontuacao(std::string jogo, Resultado resultado);
    void imprimirInformacoes();
};

#endif

