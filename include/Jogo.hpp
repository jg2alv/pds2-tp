#ifndef JOGO_HPP
#define JOGO_HPP

#include <vector>
#include <iostream>

#include "Jogada.hpp"
#include "Jogador.hpp"


/**
 * \brief Classe base abstrata para jogos de trabuleiro entre dois jogadores.
 *
 * Objetos instânciados de classes derivadas dessa representam partidas entre dois jogadores em um
 * jogo específico. Jogadas são realizadas até que um seja possível identificar um empate ou vitória;
 * nessa cirscuntância, o jogo pode ser finalizado para que os jogadores tenham seus dados atualizados.
 *
 * Essa classe armazena um tabuleiro de caracteres, onde as jogadas são registradas,
 * duas referências, uma para cada jogador, ponteiros para os jogadores de acordo com seu papel em certo
 * instante da partida, e um mapa entre apelidos dos jogadores e caracteres no tabuleiro.
 *
 * \see Reversi
 * \see Lig4
 * \see JogoDaVelha
 * \see Xadrez
 */
class Jogo {
protected:
    int linhas; 
    int colunas; 
    std::vector<std::vector<char>> tabuleiro; 

    bool jogo_finalizado;

    Jogador& jogador1;
    Jogador& jogador2;

    Jogador *jogador_da_vez;
    Jogador *outro_jogador;

    Jogador *vencedor;
    Jogador *perdedor;

    std::map<std::string, char> simbolos;

    char get_simbolo(const Jogador& jogador) const;
    char get_char(int i, int j) const;
    void set_char(int i, int j, char c);

    void passar_a_vez();

public:
    Jogo(int linhas, int colunas, Jogador& jogador1, Jogador& jogador2);
    virtual ~Jogo();

    bool fimDeJogo() const;
    void finalizarJogo();
    void efetuarDesistencia();
    bool isJogoFinalizado() const;

    Jogador *getJogadorDaVez() const;
    Jogador *getOutroJogador() const;

    Jogador *getVencedor() const;
    Jogador *getPerdedor() const;

    virtual std::string getNome() const = 0;
    virtual void imprimirTabuleiro(std::ostream& out) const = 0;
    virtual bool formatoCorreto(std::string possivel_jogada) const = 0;
    virtual bool jogadaValida(std::string possivel_jogada) const = 0;
    virtual void realizarJogada(std::string possivel_jogada) = 0;
    virtual bool verificarVitoria(Jogador const&) const = 0;
    virtual bool verificarEmpate() const = 0;
};


#endif
