#include <iostream>
#include <string>
#include <vector>

#include "Jogador.hpp"

using namespace std;

/**
 * \brief Construtor para Resultados com número de vitórias, derrotas e empates
 *
 * Recebe três números, o de vitórias, derrotas e empates, e constrói o Resultado de acordo.
 * \param vitorias Número de vitórias.
 * \param derrotas Número de derrotas.
 * \param empates Número de empates.
 */
Resultados::Resultados(int vitorias, int derrotas, int empates) :
    vitorias(vitorias), derrotas(derrotas), empates(empates) {}

/**
 * \brief Construtor para Resultados com todos seus valores zerados 
 *
 * Constrói os Resultados com seu número de vitórias, derrotas e empates zerados.
 */
Resultados::Resultados() : Resultados(0, 0, 0) {}

/**
 * \brief Construtor da classe Jogador
 * 
 * Construtor da classe Jogador, que inicializa o apelido e o nome do jogador.
 * 
 * \param apelido Apelido do jogador
 * \param nome Nome do jogador
 */
Jogador::Jogador(string apelido, string nome) : _apelido(apelido), _nome(nome) {}

/**
 * \brief Retorna o apelido do jogador
 * 
 * Função que retorna o apelido de um determinado jogador.
 * 
 * \return Apelido do jogador
 */
string Jogador::getApelido() const {
    return _apelido;
}

/**
 * \brief Retorna o nome do jogador
 * 
 * Função que retorna o nome de um determinado jogador.
 * 
 * \return Nome do jogador
 */
string Jogador::getNome() const {
    return _nome;
}


/**
 * \brief Sobrecarga do operador de igualdade
 * 
 * Sobrecarrega o operador == para a classe Jogador, para que compare
 * os apelidos de dois jogadores, que são únicos, e retorna true para 
 * apelidos iguais, ou falso para apelidos diferentes. 
 *
 * \param outro Jogador a ser comparado
 * \return true se o outro jogador tem o mesmo apelido desse, false caso contrário
 */
bool Jogador::operator==(Jogador const& outro) const {
    return _apelido == outro._apelido;
}

/**
 * \brief Sobrecarga do operador de diferença
 * 
 * Sobrecarrega o operador != para a classe Jogador, para que compare
 * os apelidos de dois jogadores, que são únicos, e retorna true para 
 * apelidos diferentes, ou falso para apelidos iguais. 
 *
 * \param outro Jogador a ser comparado
 * \return true se o outro jogador tem apelido diferente desse, false caso contrário
 */
bool Jogador::operator!=(Jogador const& outro) const {
    return _apelido != outro._apelido;
}


/**
 * \brief Retorna os resultados de um determinado jogo
 * 
 * Função que retorna os Resultados de um determinado jogo.
 * 
 * \param jogo Nome do jogo a ser consultado
 * \return Resultados do jogador no jogo
 */
Resultados Jogador::getResultados(string jogo) const {
    return __pontuacao.at(jogo);
}

/**
 * \brief Define os resultados de um determinado jogo
 * 
 * Função que define os Resultados de um determinado jogo.
 * 
 * \param jogo Nome do jogo a ser definido
 * \param resultados Resultados do jogador no jogo
 */
void Jogador::setResultados(string jogo, Resultados resultados) {
    __pontuacao[jogo] = resultados;
}

/**
 * \brief Incrementa o número de vitórias em um determinado jogo
 * 
 * Função que incrementa o número de vitórias em um determinado jogo.
 * 
 * \param jogo Nome do jogo a ser incrementado
 */
void Jogador::incrementarVitorias(string jogo) {
    __pontuacao[jogo].vitorias++;
}

/**
 * \brief Incrementa o número de derrotas em um determinado jogo
 * 
 * Função que incrementa o número de derrotas em um determinado jogo.
 * 
 * \param jogo Nome do jogo a ser incrementado
 */
void Jogador::incrementarDerrotas(string jogo) {
    __pontuacao[jogo].derrotas++;
}

/**
 * \brief Incrementa o número de empates em um determinado jogo
 * 
 * Função que incrementa o número de empates em um determinado jogo.
 * 
 * \param jogo Nome do jogo a ser incrementado
 */
void Jogador::incrementarEmpates(string jogo) {
    __pontuacao[jogo].empates++;
}

/**
 * \brief Retorna o número de jogos cadastrados
 * 
 * Função que retorna o número de jogos diferentes já jogados por esse jogador.
 * 
 * \return Número de jogos diferentes já jogados
 */
int Jogador::getNumeroDeJogos() const {
    return __pontuacao.size();
}

/**
 * \brief Retorna os jogos cadastrados
 * 
 * Função que retorna os jogos que o jogador já jogou.
 * 
 * \return Vetor de jogos já jogados
 */
vector<string> Jogador::getJogosCadastrados() const {
    vector<string> jogos;
    for (auto it = __pontuacao.begin(); it != __pontuacao.end(); it++) {
        jogos.push_back(it->first);
    }

    return jogos;
}

/**
 * \brief Imprime as informações do jogador
 * 
 * Função que imprime as informações do jogador.
 * 
 * \param out Stream de saída
 */
void Jogador::imprimirInformacoes(ostream& out) const {
    string apelido = getApelido();
    string nome = getNome();
    out << apelido << " " << nome << endl;
    vector<string> jogos = getJogosCadastrados();
    for (int i = 0; i < getNumeroDeJogos(); i++)
    {
        Resultados resultados = __pontuacao.at(jogos[i]);
        out << jogos[i] << " - ";
        out << "V: " << resultados.vitorias << " ";
        out << "D: " << resultados.derrotas << " ";
        out << "E: " << resultados.empates << endl;
    }
}


