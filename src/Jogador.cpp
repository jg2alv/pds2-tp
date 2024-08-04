#include <iostream>
#include <string>
#include <vector>

#include "Jogador.hpp"

/**
 * \brief Struct que armazena os resultados do jogador durante a execução
 * 
 * Estrutura de dados para armazenar as vitórias, derrotas e empates de 
 * um jogador, para facilitar o controle e a escrita no arquivo
 * 
 */
Resultados::Resultados(int vitorias, int derrotas, int empates) :
    vitorias(vitorias), derrotas(derrotas), empates(empates) {}

Resultados::Resultados() : Resultados(0, 0, 0) {}

/**
 * \brief Construtor da classe Jogador
 * 
 * Construtor da classe Jogador, que inicializa o apelido e o nome do jogador
 * 
 * \param apelido Apelido do jogador
 * \param nome Nome do jogador
 */

Jogador::Jogador(std::string apelido, std::string nome) : _apelido(apelido), _nome(nome) {}

/**
 * \brief Retorna o apelido do jogador
 * 
 * Função getApelido que retorna o apelido de um determinado jogador
 * 
 * \return Apelido do jogador
 */
std::string Jogador::getApelido() const {
    return this->_apelido;
}

/**
 * \brief Retorna o nome do jogador
 * 
 * Função getNome que retorna o nome de um determinado jogador
 * 
 * \return Nome do jogador
 */
std::string Jogador::getNome() const {
    return this->_nome;
}


/**
 * \brief Sobrecarga do operador de igualdade
 * 
 * Sobrecarrega o operador == para a classe Jogador, para que compare
 * os apelidos de dois jogadores, que são únicos, e retorna true para 
 * apelidos iguais, ou falso para apelidos diferentes. Útil para 
 * saber se um jogador já existe ou não.
 * 
 * \param outro Jogador a ser comparado
 * \return true se os jogadores são iguais, false caso contrário
 */
bool Jogador::operator==(Jogador const& outro) const {
    return _apelido == outro._apelido;
}

/**
 * \brief Sobrecarga do operador de diferença
 * 
 * Sobrecarrega o operador != para a classe Jogador, para que compare
 * os apelidos de dois jogadores, que são únicos, e retorna true para 
 * apelidos diferentes, ou falso para apelidos iguais. Útil para 
 * saber se um jogador já existe ou não.
 * 
 * \param outro Jogador a ser comparado
 * \return true se os jogadores são diferentes, false caso contrário
 */
bool Jogador::operator!=(Jogador const& outro) const {
    return _apelido != outro._apelido;
}


/**
 * \brief Retorna os resultados de um determinado jogo
 * 
 * Função getResultados que retorna os resultados de um determinado jogo
 * 
 * \param jogo Nome do jogo a ser consultado
 * \return Resultados do jogador no jogo
 */
Resultados Jogador::getResultados(std::string jogo) const {
    return __pontuacao.at(jogo);
}

/**
 * \brief Define os resultados de um determinado jogo
 * 
 * Função setResultados que define os resultados de um determinado jogo
 * 
 * \param jogo Nome do jogo a ser definido
 * \param resultados Resultados do jogador no jogo
 */
void Jogador::setResultados(std::string jogo, Resultados resultados) {
    __pontuacao[jogo] = resultados;
}

/**
 * \brief Incrementa o número de vitórias em um determinado jogo
 * 
 * Função incrementarVitorias que incrementa o número de vitórias em um determinado jogo
 * 
 * \param jogo Nome do jogo a ser incrementado
 */
void Jogador::incrementarVitorias(std::string jogo) {
    __pontuacao[jogo].vitorias++;
}

/**
 * \brief Incrementa o número de derrotas em um determinado jogo
 * 
 * Função incrementarDerrotas que incrementa o número de derrotas em um determinado jogo
 * 
 * \param jogo Nome do jogo a ser incrementado
 */
void Jogador::incrementarDerrotas(std::string jogo) {
    __pontuacao[jogo].derrotas++;
}

/**
 * \brief Incrementa o número de empates em um determinado jogo
 * 
 * Função incrementarEmpates que incrementa o número de empates em um determinado jogo
 * 
 * \param jogo Nome do jogo a ser incrementado
 */
void Jogador::incrementarEmpates(std::string jogo) {
    __pontuacao[jogo].empates++;
}

/**
 * \brief Retorna o número de jogos cadastrados
 * 
 * Função getNumeroDeJogos que retorna o número de jogos cadastrados
 * 
 * \return Número de jogos cadastrados
 */
int Jogador::getNumeroDeJogos() const {
    return __pontuacao.size();
}

/**
 * \brief Retorna os jogos cadastrados
 * 
 * Função getJogosCadastrados que retorna os jogos que o jogador
 * já jogou
 * 
 * \return Vetor de jogos cadastrados
 */
std::vector<std::string> Jogador::getJogosCadastrados() const {
    std::vector<std::string> jogos;
    for (auto it = __pontuacao.begin(); it != __pontuacao.end(); it++) {
        jogos.push_back(it->first);
    }

    return jogos;
}

/**
 * \brief Imprime as informações do jogador
 * 
 * Função imprimirInformacoes que imprime as informações do jogador
 * 
 * \param out Stream de saída
 */
void Jogador::imprimirInformacoes(std::ostream& out) const {
    std::string apelido = this->getApelido();
    std::string nome = this->getNome();
    out << apelido << " " << nome << std::endl;
    std::vector<std::string> jogos = getJogosCadastrados();
    for (int i = 0; i < getNumeroDeJogos(); i++)
    {
        Resultados resultados = __pontuacao.at(jogos[i]);
        out << jogos[i] << " - " << "V: " << resultados.vitorias << " ";
        out << "D: " << resultados.derrotas << std::endl;
    }
}


