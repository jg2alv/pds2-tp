#include <vector>
#include <algorithm>

#include "Jogo.hpp"

using namespace std;

/**
 * \brief Obtém o símbolo associado a um jogador.
 * 
 * Esse método usa o apelido do jogador para recuperar o símbolo associado a ele 
 * a partir do mapa de símbolos.
 * 
 * \param jogador O jogador cujo símbolo é necessário.
 * \return O símbolo do jogador (caractere).
 */

char Jogo::get_simbolo(const Jogador& jogador) const {
    return simbolos.at(jogador.getApelido());
}

 /**
 * \brief Obtém o caractere presente em uma célula específica do tabuleiro.
 * 
 * Esse método acessa o tabuleiro e retorna o caractere armazenado na célula 
 * especificada pelos índices de linha e coluna.
 * 
 * \param i Índice da linha (0-based).
 * \param j Índice da coluna (0-based).
 * \return O caractere na posição (i, j) do tabuleiro.
 */
char Jogo::get_char(int i, int j) const {
    return tabuleiro[i][j];
}

/**
 * \brief Define o caractere em uma célula específica do tabuleiro.
 * 
 * Esse método atualiza o tabuleiro colocando o caractere especificado na célula 
 * identificada pelos índices de linha e coluna.
 * 
 * \param i Índice da linha (0-based).
 * \param j Índice da coluna (0-based).
 * \param c Caractere a ser colocado na posição (i, j).
 */
void Jogo::set_char(int i, int j, char c) {
    tabuleiro[i][j] = c;
}

/**
 * \brief Passa a vez para o outro jogador.
 * 
 * Esse método troca o jogador da vez e o outro jogador, alternando a responsabilidade 
 * pela próxima jogada.
 */
void Jogo::passar_a_vez() {
    swap(jogador_da_vez, outro_jogador);
}

/**
 * \brief Construtor da classe Jogo.
 * 
 * Esse construtor inicializa um jogo com o número de linhas e colunas do tabuleiro, 
 * e com dois jogadores, sendo o jogador 1 representado pelo símbolo 'X' e o jogador 2 sendo representado
 * pelo símbolo 'O'. O tabuleiro é inicializado com espaços vazios.
 * 
 * \param linhas Número de linhas do tabuleiro.
 * \param colunas Número de colunas do tabuleiro.
 * \param jogador1 Referência ao primeiro jogador.
 * \param jogador2 Referência ao segundo jogador.
 */
Jogo::Jogo(int linhas, int colunas, Jogador& jogador1, Jogador& jogador2) :
    linhas(linhas),
    colunas(colunas),
    tabuleiro(linhas, vector<char>(colunas, ' ')),
    jogo_finalizado(false),
    jogador1(jogador1),
    jogador2(jogador2 ),
    jogador_da_vez(&jogador1),
    outro_jogador(&jogador2),
    vencedor(nullptr),
    perdedor(nullptr),
    simbolos{{jogador1.getApelido(), 'X'}, {jogador2.getApelido(), 'O'}} {}

/**
 * \brief Destruidor da classe Jogo.
 * 
 * O destrutor da classe Jogo limpa e libera qualquer recurso alocado pela classe.
 * Necessariamente virtual para bom funcionamento do polimorfismo universal de inclusão.
 */
Jogo::~Jogo() {}

/**
 * \brief Verifica se o jogo terminou (vitória ou empate).
 * 
 * Esse método avalia se o jogo atingiu seu estado final, ou seja, se houve vitória 
 * de algum jogador ou empate. Se o jogo já foi finalizado, retorna `true`
 * 
 * \return True se o jogo estiver pronto para ser finalizado, false caso contrário.
 */
bool Jogo::fimDeJogo() const {
    if (jogo_finalizado) {
        return true;
    } else {
        return verificarEmpate() || verificarVitoria(jogador1) || verificarVitoria(jogador2);
    }
}

 /**
 * \brief Finaliza o jogo e atualiza os registros dos jogadores.
 * 
 * Esse método atualiza o status dos jogadores e define o estado do jogo como finalizado.
 * Caso ocorra empate ou o jogo seja finalizado prematuramente (`fimDeJogo()` é falso), os dois jogadores tem seu número de empates incrementado.
 * Caso contrário, o jogador vencedor tem seu número de vitórias incrementado e o outro, o número de derrotas.
 */
void Jogo::finalizarJogo() {
    if (jogo_finalizado) {
        return;
    }

    if (!fimDeJogo() || verificarEmpate()) {
        jogador1.incrementarEmpates(getNome());
        jogador2.incrementarEmpates(getNome());
    } else {
        if (verificarVitoria(jogador1)) {
            vencedor = &jogador1;
            perdedor = &jogador2;
        } else {
            vencedor = &jogador2;
            perdedor = &jogador1;
        }

        vencedor->incrementarVitorias(getNome());
        perdedor->incrementarDerrotas(getNome());
    }

    jogador_da_vez = outro_jogador = nullptr;
    jogo_finalizado = true;
}

/**
 * \brief Efetua a desistência do jogador da vez, finalizando o jogo.
 * 
 * Esse método lida com a situação em que o jogador da vez desiste do jogo, atribuindo 
 * a vitória ao outro jogador e a derrota ao jogador que desistiu. O jogo é marcado 
 * como finalizado.
 */
void Jogo::efetuarDesistencia() {
    if (jogo_finalizado) {
        return;
    }

    vencedor = outro_jogador;
    perdedor = jogador_da_vez;

    vencedor->incrementarVitorias(getNome());
    perdedor->incrementarDerrotas(getNome());

    jogador_da_vez = outro_jogador = nullptr;
    jogo_finalizado = true;
}

/**
 * \brief Indica se o jogo já foi finalizado.
 * 
 * Esse método retorna se o jogo já foi encerrado.
 *
 * \see finalizarJogo()
 * \see efetuarDesistencia()
 * \return True se o jogo estiver finalizado, false caso contrário.
 */
bool Jogo::isJogoFinalizado() const {
    return jogo_finalizado;
}

/**
 * \brief Obtém o jogador da vez.
 * 
 * Antes do jogo ser finalizado, esse método retorna um ponteiro para o jogador que irá realizar a próxima jogada.
 * 
 * \return Ponteiro para o jogador da vez.
 */
Jogador *Jogo::getJogadorDaVez() const {
    return jogador_da_vez;
}

/**
 * \brief Obtém o outro jogador.
 * 
 * Antes do jogo ser finalizado, esse método retorna um ponteiro para o jogador que não irá realizar a próxima jogada.
 * Retorna `nullptr` depois do jogo ser finalizado.
 * 
 * \return Ponteiro para o outro jogador.
 */
Jogador *Jogo::getOutroJogador() const {
    return outro_jogador;
}

/**
 * \brief Obtém o vencedor do jogo.
 * 
 * Após o jogo ser finalizado, esse método retorna um ponteiro para o jogador que venceu o jogo.
 * Retorna `nullptr` antes do jogo ser finalizado.
 *
 * \return Ponteiro para o jogador vencedor.
 */
Jogador *Jogo::getVencedor() const {
    return vencedor;
}

/**
 * \brief Obtém o perdedor do jogo.
 * 
 * Após o jogo ser finalizado, esse método retorna um ponteiro para o jogador que perdeu o jogo.
 * Retorna `nullptr` antes do jogo ser finalizado.
 * 
 * \return Ponteiro para o jogador perdedor.
 */
Jogador *Jogo::getPerdedor() const {
    return perdedor;
}

