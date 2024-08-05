#include "Xadrez.hpp"
#include "Jogada.hpp"
#include "Jogador.hpp"
#include "Jogo.hpp"
#include "Excecao.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

/**
 * \brief Construtor da classe Xadrez
 * 
 * Construtor da classe Xadrez, que inicializa os jogadores
 * da partida, a linha e a coluna do tabuleiro com tamanho
 * 8, chamando o construtor da classe Jogo, e coloca os peoes
 * de cada jogador na posicao inicial do jogo.
 * 
 * \param jogador1 Primeiro jogador.
 * \param jogador2 Segundo jogador.
 */
Xadrez::Xadrez(Jogador &jogador1, Jogador &jogador2) : Jogo(8, 8, jogador1, jogador2) {
    char pecas[] = { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' };

    for(int i = 0; i < this->colunas; i++) {
        char peca = pecas[i];
        this->set_char(0, i, peca);
        this->set_char(1, i, 'p');

        this->set_char(7, i, toupper(peca));
        this->set_char(6, i, 'P');
    }
}

/**
 * \brief Construtor da classe Xadrez
 * 
 * Construtor da classe Xadrez, que inicializa os jogadores 
 * da partida, a linha e a coluna com tamanho 8, e o tabuleiro,
 * chamando o construtor da classe Jogo.
 * 
 * \param jogador1 Primeiro jogador.
 * \param jogador2 Segundo jogador.
 * \param tabuleiro O tabuleiro do jogo.
 */
Xadrez::Xadrez(Jogador &jogador1, Jogador &jogador2, vector<vector<char>> tabuleiro) : Jogo(8, 8, jogador1, jogador2, tabuleiro) {}

/**
 * \brief Destrutor da classe Xadrez
 * 
 * Destrutor da classe Xadrez. Como nao tem nenhum atributo
 * alocado dinamicamente, nao é preciso desalocar nenhuma
 * memoria manualmente.
 */
Xadrez::~Xadrez() {}

/**
 * \brief Retorna uma string do nome do jogo
 *
 * Essa funcao retorna o nome do jogo, no caso "Xadrez".
 * 
 * \return Uma string "Xadrez".
 */
string Xadrez::getNome() const {
    return "Xadrez";
}

/**
 * \brief Imprime o tabuleiro do jogo
 *
 * Essa funcao recebe um stream de saida e imprime, nesse
 * stream, o tabuleiro do jogo, com uma cabeçalho escrito
 * "Xadrez" e indicando os indices de cada coluna e as 
 * letras de cada linha.
 * 
 * \param out Um stream de saida.
 */
void Xadrez::imprimirTabuleiro(ostream& out) const {
    out << "-----------Xadrez-----------\n";

    char alpha[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    out << "   1  2  3  4  5  6  7  8 " << endl;
    for (int i = 0; i < this->linhas; i++) {
        out << alpha[i] << " ";
        for (int j = 0; j < this->colunas; j++) {
            cout << "|" << get_char(i, j) << "|";
        }
        out << " " << alpha[i] << endl;
    }
    out << "   1  2  3  4  5  6  7  8 " << endl;
}

/**
 * \brief Analisa o formato da entrada recebida
 *
 * Essa funcao recebe como parametro uma string da entrada lida 
 * e analisa se existe exatamente uma letra e um numero para uma
 * posicao inicial da peca e para uma posicao final. É lido da 
 * entrada essas letra e numeros, transformado as letras em numeros
 * da linha do tabuleiro e, então, é verificado se as coordenadas
 * recebidas estao dentro do limite do tabuleiro. Se isso for atendido,
 * é retornado verdadeiro e, caso contrario, é retornado falso.
 * 
 * \param possivel_jogada A string da entrada.
 * \return true ou false
 */
bool Xadrez::formatoCorreto(string possivel_jogada) const {
    stringstream stream(possivel_jogada);
    char linha_origem, linha_dest;
    int coluna_origem, coluna_dest;
    stream >> linha_origem >> coluna_origem >> linha_dest >> coluna_dest;

    linha_origem -= 97;
    coluna_origem -= 1;
    linha_dest -= 97;
    coluna_dest -= 1;

    auto linhaValida = [](char linha) { return  linha >= 0 && linha <= 7; };
    auto colunaValida = [](int coluna) { return coluna >= 0 && coluna <= 7; };

    bool linhasNoIntervaloCorreto = linhaValida(linha_origem) && linhaValida(linha_dest);
    bool colunasNoIntervaloCorreto = colunaValida(coluna_origem) && colunaValida(coluna_dest);

    if(!linhasNoIntervaloCorreto || !colunasNoIntervaloCorreto) return false;
    return true;
}

/**
 * \brief Verifica se a jogada é valida
 *
 * Essa funcao recebe como parametro uma string de uma possivel
 * jogada. A funcao verifica se é fim de jogo e retorna falso se
 * for fim de jogo, pois nao tem mais jogadas. Tambem verifica se 
 * o formato da possivel jogada esta correto e lanca uma excecao 
 * caso nao tenha formato correto. É lido da possivel jogada as 
 * coordenadas da posicao inicial da peca e da posicao final.
 * 
 * \param possivel_jogada Uma string com a entrada lida.
 * \return true ou false
 */
bool Xadrez::jogadaValida(string possivel_jogada) const {
    if(this->fimDeJogo()) return false;
    if(!this->formatoCorreto(possivel_jogada)) throw Excecao("formato de linhas e/ou colunas incorreto (padrao: [a-h][1-8][a-h][1-8])");

    int tam = possivel_jogada.size();
    if(tam != 4) return false;

    stringstream stream(possivel_jogada);
    char linha_origem, linha_dest;
    int coluna_origem, coluna_dest;
    stream >> linha_origem >> coluna_origem >> linha_dest >> coluna_dest;

    linha_origem -= 97;
    coluna_origem -= 1;
    linha_dest -= 97;
    coluna_dest -= 1;

    bool maiuscula;
    string apelido1 = this->jogador1.getApelido();
    string apelido_da_vez = this->jogador_da_vez->getApelido();

    if(apelido_da_vez == apelido1) maiuscula = true;
    else maiuscula = false;

    char peca_selecionada = this->get_char(linha_origem, coluna_origem);
    bool peca_selecionada_eh_maiuscula = toupper(peca_selecionada) == peca_selecionada;
    bool peca_selecionada_eh_do_jogador = peca_selecionada_eh_maiuscula == maiuscula;
    bool posicao_nao_mudou = linha_origem == linha_dest && coluna_origem == coluna_dest;
 
    if(!peca_selecionada_eh_do_jogador || peca_selecionada == ' ' || posicao_nao_mudou) return false;
    return true;
}

/**
 * \brief Realiza uma jogada
 *
 * Essa funcao recebe como parametro uma string de uma possivel
 * jogada. A funcao verifica se é fim de jogo e lanca uma excecao
 * se for fim de jogo. Tambem verifica se a jogada é valida e 
 * lanca uma excecao se nao for valida. Se nao for fim de jogo e 
 * a jogada for valida, é lido da possivel jogada as coordenadas 
 * da posicao inicial da peca e da posicao final.
 * 
 * \param possivel_jogada Uma string com a entrada lida.
 */
void Xadrez::realizarJogada(string possivel_jogada) {
    if(this->fimDeJogo()) throw Excecao("jogo ja acabou");
    if(!this->jogadaValida(possivel_jogada)) throw Excecao("peca selecionada nao pertence ao jogador atual");

    stringstream stream(possivel_jogada);
    char linha_origem, linha_dest;
    int coluna_origem, coluna_dest;
    stream >> linha_origem >> coluna_origem >> linha_dest >> coluna_dest;

    linha_origem -= 97;
    coluna_origem -= 1;
    linha_dest -= 97;
    coluna_dest -= 1;

    char peca_selecionada = this->get_char(linha_origem, coluna_origem);
    char peca_no_destino = this->get_char(linha_dest, coluna_dest);

    int diff_no_x = abs(coluna_origem - coluna_dest);
    int diff_no_y = abs(linha_origem - linha_dest);

    auto ehPecaInimiga = [](char peca1, char peca2){
        if(peca1 == ' ' || peca2 == ' ') return false;
        bool peca1_eh_maiuscula = peca1 == toupper(peca1);
        bool peca2_eh_maiuscula = peca2 == toupper(peca2);
        return peca1_eh_maiuscula != peca2_eh_maiuscula;
    };

    auto movimentoValidoDaTorre = [diff_no_x, diff_no_y, coluna_origem, coluna_dest, this, linha_origem, linha_dest](){
        bool andou_em_mais_de_uma_direcao = diff_no_x != 0 && diff_no_y != 0;
        if(andou_em_mais_de_uma_direcao) return "torre so anda em uma direcao";

        if(diff_no_x != 0) {
            for(int i = coluna_origem + 1; i < coluna_dest; i++) {
                char c = this->get_char(linha_origem, i);
                if(c != ' ') return "torre nao pula pecas";
            }
        } else {
            for(int i = linha_origem + 1; i < linha_dest; i++) {
                char c = this->get_char(i, coluna_origem);
                if(c != ' ') return "torre nao pula pecas";
            }
        }

        return "";
    };

    auto movimentoValidoDoBispo = [diff_no_x, diff_no_y, linha_dest, linha_origem, coluna_dest, coluna_origem, this](){
        if(diff_no_x != diff_no_y) return "bispo so anda na diagonal";

        if(linha_dest > linha_origem && coluna_dest > coluna_origem) {
            for(int i = linha_origem + 1, j = coluna_origem + 1; i < linha_dest && j < coluna_dest; i++, j++) {
                char c = this->get_char(i, j);
                if(c != ' ') return "bispo nao pula pecas";
            }
        } else if(linha_dest < linha_origem && coluna_dest > coluna_origem) {
            for(int i = linha_origem - 1, j = coluna_origem + 1; i > linha_dest && j < coluna_dest; i--, j++) {
                char c = this->get_char(i, j);
                if(c != ' ') return "bispo nao pula pecas";
            }
        } else if(linha_dest > linha_origem && coluna_dest < coluna_origem) {
            for(int i = linha_origem + 1, j = coluna_origem - 1; i < linha_dest && j > coluna_dest; i++, j--) {
                char c = this->get_char(i, j);
                if(c != ' ') return "bispo nao pula pecas";
            }
        } else if(linha_dest < linha_origem && coluna_dest < coluna_origem) {
            for(int i = linha_origem - 1, j = coluna_origem - 1; i > linha_dest && j > coluna_dest; i--, j--) {
                char c = this->get_char(i, j);
                if(c != ' ') return "bispo nao pula pecas";
            }
        }

        return "";
    };

    switch(peca_selecionada) {
        case 'P':
        case 'p': {
            bool andou_para_tras = (peca_selecionada == 'P' && linha_dest > linha_origem) || (peca_selecionada == 'p' && linha_origem > linha_dest);
            if(andou_para_tras) throw Excecao("peao nao anda para tras");

            bool andou_mais_de_uma_casa = diff_no_x > 1 || diff_no_y > 1;
            if(andou_mais_de_uma_casa) throw Excecao("peao anda apenas uma casa");

            bool andou_na_diagonal = diff_no_y == 1 && diff_no_x == 1;
            bool tem_peca_inimiga_na_diagonal = ehPecaInimiga(peca_selecionada, peca_no_destino);
            if(andou_na_diagonal && !tem_peca_inimiga_na_diagonal) throw Excecao("peao nao anda na diagonal");

            if(!andou_na_diagonal && peca_no_destino != ' ') throw Excecao("peao so captura na diagonal");

            if(linha_origem > linha_dest && linha_dest == 0)
                peca_selecionada = 'Q';
            else if(linha_origem < linha_dest && linha_dest == 7)
                peca_selecionada = 'q';
            
            break;
        }

        case 'R':
        case 'r': {
            string err = movimentoValidoDaTorre();
            if(err != "") throw Excecao(err);
            break;
        }

        case 'N':
        case 'n': {
            bool movimento_valido = (diff_no_x == 1 && diff_no_y == 2) || (diff_no_x == 2 && diff_no_y == 1);
            if(!movimento_valido) throw Excecao("movimento invalido para o cavalo");
            
            bool no_destino_tem_inimigo = ehPecaInimiga(peca_selecionada, peca_no_destino);
            bool peca_no_destino_eh_espaco = peca_no_destino == ' ';
            if(!peca_no_destino_eh_espaco && !no_destino_tem_inimigo) throw Excecao("peca no destino nao eh inimigo");

            break;
        }

        case 'B':
        case 'b': {
            string err = movimentoValidoDoBispo();
            if(err != "") throw Excecao(err);
            break;
        }

        case 'Q':
        case 'q': {
            string err1 = movimentoValidoDaTorre();
            string err2 = movimentoValidoDoBispo();
            if(err1 != "" && err2 != "") throw Excecao("movimento invalido para a rainha");

            break;
        }

        case 'K':
        case 'k': {
            bool andou_mais_de_uma_casa = diff_no_x > 1 || diff_no_y > 1;
            if(andou_mais_de_uma_casa) throw Excecao("rei anda apenas uma casa");

            break;
        }
    }

    this->set_char(linha_origem, coluna_origem, ' ');
    this->set_char(linha_dest, coluna_dest, peca_selecionada);
    this->passar_a_vez();
}

/**
 * \brief Verifica a vitoria de um jogador
 *
 * Essa funcao recebe como parametro um jogador e verifica se
 * o jogador adversario ainda tem a peca do rei no tabuleiro.
 * Se isso for atendido, o jogador nao venceu a partida e é
 * retornado falso e, caso nao for encontrado o rei do outro
 * jogador, ele venceu a partida e é retornado verdadeiro.
 * 
 * \param jogador Um jogador da partida.
 * \return true ou false
 */
bool Xadrez::verificarVitoria(Jogador const& jogador) const {
    // jogador1 eh branco: rei eh K
    // jogador2 eh preto: rei eh k

    // se verifica vitoria de jogador1, tem que ver se existe k.
    // se nao existir, jogador1 venceu
    
    // se verifica vitoria de jogador2, tem que ver se existe K.
    // se no existir, jogador2 venceu
    char rei = jogador.getApelido() == jogador1.getApelido() ? 'k' : 'K';

    for(int i = 0; i < this->linhas; i++) {
        for(int j = 0; j < this->colunas; j++) {
            char c = this->get_char(i, j);
            if(c == rei) return false;
        }
    }

    return true;
}

/**
 * \brief Verifica o empate do jogo
 *
 * Essa funcao sempre retorna falso, pois, no Xadrez,
 * nao existe empate.
 * 
 * \return false
 */
bool Xadrez::verificarEmpate() const {
    return false;
}