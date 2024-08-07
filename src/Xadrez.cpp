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
 * 8, chamando o construtor da classe Jogo, e coloca os peões
 * de cada jogador na posição inicial do jogo.
 * 
 * \param jogador1 Primeiro jogador.
 * \param jogador2 Segundo jogador.
 */
Xadrez::Xadrez(Jogador &jogador1, Jogador &jogador2) : Jogo(8, 8, jogador1, jogador2) {
    char pecas[] = { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' };

    for(int i = 0; i < colunas; i++) {
        char peca = pecas[i];
        set_char(0, i, peca);
        set_char(1, i, 'p');

        set_char(7, i, toupper(peca));
        set_char(6, i, 'P');
    }
}

/**
 * \brief Destrutor da classe Xadrez
 * 
 * Destrutor da classe Xadrez. Como não tem nenhum atributo
 * alocado dinamicamente, não é preciso desalocar nenhuma
 * memória manualmente.
 */
Xadrez::~Xadrez() {}

/**
 * \brief Retorna uma string do nome do jogo
 *
 * Essa função retorna o nome do jogo, no caso "Xadrez".
 * 
 * \return Uma string "Xadrez".
 */
string Xadrez::getNome() const {
    return "Xadrez";
}

/**
 * \brief Imprime o tabuleiro do jogo
 *
 * Essa função recebe um stream de saída e imprime, nesse
 * stream, o tabuleiro do jogo, com uma cabeçalho escrito
 * "Xadrez" e indicando os índices de cada coluna e as 
 * letras de cada linha.
 * 
 * \param out Um stream de saida.
 */
void Xadrez::imprimirTabuleiro(ostream& out) const {
    out << "-----------Xadrez-----------\n";

    out << "   a  b  c  d  e  f  g  h " << endl;
    for (int i = 0; i < linhas; i++) {
        out << 8 - i << " ";
        for (int j = 0; j < colunas; j++) {
            out << "|" << get_char(i, j) << "|";
        }
        out << " " << 8 - i << endl;
    }
    out << "   a  b  c  d  e  f  g  h " << endl;
}

/**
 * \brief Analisa o formato da entrada recebida
 *
 * Essa função recebe como parâmetro uma string da entrada lida 
 * e analisa se existe exatamente uma letra e um número para uma
 * posição inicial da peça e para uma posição final. É lido da 
 * entrada essas letras e números, transformado as letras em números
 * da linha do tabuleiro e, então, é verificado se as coordenadas
 * recebidas estão dentro do limite do tabuleiro. Se isso for 
 * atendido, é retornado verdadeiro e, caso contrário, é retornado 
 * falso.
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

    int tam = possivel_jogada.size();
    bool tamanho_da_entrada_eh_correto = tam == 4;

    if(!linhasNoIntervaloCorreto || !colunasNoIntervaloCorreto || !tamanho_da_entrada_eh_correto) return false;
    return true;
}

void Xadrez::converterInput(char* linha, int* coluna) {
    char linha_convertida = 7 - *coluna;
    int coluna_convertida = (int)(*linha);
    *linha = linha_convertida;
    *coluna = coluna_convertida; 
}

/**
 * \brief Verifica se a jogada é válida
 *
 * Essa função recebe como parâmetro uma string de uma possível
 * jogada. A função verifica se é fim de jogo e retorna falso se
 * for fim de jogo, pois não tem mais jogadas. Também verifica se 
 * o formato da possível jogada está correto e lança uma Excecao 
 * caso não tenha formato correto. É lido da possível jogada as 
 * coordenadas da posiçãoo inicial da peça e da posiçãoo final.
 * Então, o input do usuario é convertido, por meio da função 
 * estática `Xadrez::converterInput()`, e algumas verificações são 
 * feitas. Uma Excecao é lançada caso o jogador atual esteja 
 * selecionando uma peça que pertence ao inimigo; ou caso a peça 
 * selecionada seja uma casa vazia; ou caso a posição inicial e 
 * final sejam as mesmas. Se esses 3 testes passarem, a função 
 * retorna true. Caso contrário, retorna false, indicando que uma 
 * Excecao deve ser lançada.
 * 
 * \param possivel_jogada Uma string com a entrada lida.
 * \return true ou false
 */
bool Xadrez::jogadaValida(string possivel_jogada) const {
    if(fimDeJogo()) return false;
    if(!formatoCorreto(possivel_jogada)) throw Excecao("formato de linhas e/ou colunas incorreto (padrao: [a-h][1-8][a-h][1-8])");

    stringstream stream(possivel_jogada);
    char linha_origem, linha_dest;
    int coluna_origem, coluna_dest;
    stream >> linha_origem >> coluna_origem >> linha_dest >> coluna_dest;

    linha_origem -= 97;
    coluna_origem -= 1;
    linha_dest -= 97;
    coluna_dest -= 1;

    Xadrez::converterInput(&linha_origem, &coluna_origem);
    Xadrez::converterInput(&linha_dest, &coluna_dest);

    bool maiuscula;
    string apelido1 = jogador1.getApelido();
    string apelido_da_vez = jogador_da_vez->getApelido();

    if(apelido_da_vez == apelido1) maiuscula = true;
    else maiuscula = false;

    char peca_selecionada = get_char(linha_origem, coluna_origem);
    bool peca_selecionada_eh_maiuscula = toupper(peca_selecionada) == peca_selecionada;
    bool peca_selecionada_eh_do_jogador = peca_selecionada_eh_maiuscula == maiuscula;
    bool posicao_nao_mudou = linha_origem == linha_dest && coluna_origem == coluna_dest;
 
    if(!peca_selecionada_eh_do_jogador || peca_selecionada == ' ' || posicao_nao_mudou) return false;
    return true;
}

/**
 * \brief Realiza uma jogada
 *
 * Essa função recebe como parâmetro uma string de uma possível jogada. 
 * A função verifica se é fim de jogo e lança uma Excecao se for fim de
 * jogo. Também verifica se a jogada é válida e lança uma Excecao se não
 * for válida. Se não for fim de jogo e a jogada for válida, é lido da 
 * possível jogada as coordenadas da posição inicial da peça e da posição
 * final. Do mesmo modo como na função de verificar a validez da jogada, 
 * o input é convertido. Após isso, é verificada a validez do movimento; 
 * ou seja, se o movimento desejado para a peça selecionada é um movimento
 * permitido nas regras do jogo de xadrez. Eis, aqui, tais regras:
 * - Peão: pode se mover somente para frente uma ou duas casas (duas 
 *         apenas se for o primeiro movimento da peça no jogo). Captura 
 *         peças inimigas que estão na sua diagonal (esquerda ou
 *         direita).
 * - Torre: pode se mover nos eixos x e y - ou seja, horizontal e 
 *          verticalmente -, por quantas casas desejar (desde que não 
 *          haja peças entre sua posição final e inicial, pois a torre 
 *          não pula peças). Captura peças se movimentando horizontal ou
 *          verticalmente.
 * - Cavalo: faz um L no tabuleiro: anda duas casas em uma direção e uma 
 *           casa em outra. Pode pular peças, inimigas ou amigas, que 
 *           estejam entre sua posição final e inicial. Captura a peça 
 *           inimiga sobre a qual ele cai.
 * - Bispo: pode andar somente nas diagonais, qualquer uma das quatro. 
 *          Não pula peças.
 * - Rainha: regras de movimento são a união das habilidades do Bispo e 
 *           da Torre.
 * - Rei: pode se mover uma casa em qualquer uma das 8 direções (4 direções 
 *        principais e 4 diagonais).
 * Além disso, foi implementada a promoção de Peão para Rainha: se um peão 
 * chega no outro lado do tabuleiro, ele é promovido em Rainha.
 * A função joga exceções se os movimentos inseridos forem inválidos. Caso 
 * isso não ocorra, a função realiza a jogada e passa a vez para o próximo 
 * jogador.
 * 
 * \param possivel_jogada Uma string com a entrada lida.
 */
void Xadrez::realizarJogada(string possivel_jogada) {
    if(fimDeJogo()) throw Excecao("jogo ja acabou");
    if(!jogadaValida(possivel_jogada)) throw Excecao("peca selecionada nao pertence ao jogador atual");

    stringstream stream(possivel_jogada);
    char linha_origem, linha_dest;
    int coluna_origem, coluna_dest;
    stream >> linha_origem >> coluna_origem >> linha_dest >> coluna_dest;

    linha_origem -= 97;
    coluna_origem -= 1;
    linha_dest -= 97;
    coluna_dest -= 1;

    Xadrez::converterInput(&linha_origem, &coluna_origem);
    Xadrez::converterInput(&linha_dest, &coluna_dest);

    char peca_selecionada = get_char(linha_origem, coluna_origem);
    char peca_no_destino = get_char(linha_dest, coluna_dest);

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
                char c = get_char(linha_origem, i);
                if(c != ' ') return "torre nao pula pecas";
            }
        } else {
            for(int i = linha_origem + 1; i < linha_dest; i++) {
                char c = get_char(i, coluna_origem);
                if(c != ' ') return "torre nao pula pecas";
            }
        }

        return "";
    };

    auto movimentoValidoDoBispo = [diff_no_x, diff_no_y, linha_dest, linha_origem, coluna_dest, coluna_origem, this](){
        if(diff_no_x != diff_no_y) return "bispo so anda na diagonal";

        if(linha_dest > linha_origem && coluna_dest > coluna_origem) {
            for(int i = linha_origem + 1, j = coluna_origem + 1; i < linha_dest && j < coluna_dest; i++, j++) {
                char c = get_char(i, j);
                if(c != ' ') return "bispo nao pula pecas";
            }
        } else if(linha_dest < linha_origem && coluna_dest > coluna_origem) {
            for(int i = linha_origem - 1, j = coluna_origem + 1; i > linha_dest && j < coluna_dest; i--, j++) {
                char c = get_char(i, j);
                if(c != ' ') return "bispo nao pula pecas";
            }
        } else if(linha_dest > linha_origem && coluna_dest < coluna_origem) {
            for(int i = linha_origem + 1, j = coluna_origem - 1; i < linha_dest && j > coluna_dest; i++, j--) {
                char c = get_char(i, j);
                if(c != ' ') return "bispo nao pula pecas";
            }
        } else if(linha_dest < linha_origem && coluna_dest < coluna_origem) {
            for(int i = linha_origem - 1, j = coluna_origem - 1; i > linha_dest && j > coluna_dest; i--, j--) {
                char c = get_char(i, j);
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

            bool peao_eh_branco = linha_origem > linha_dest;
            bool andou_mais_de_uma_casa = diff_no_x > 1 || diff_no_y > 1;
            bool primeiro_movimento_do_peao = peao_eh_branco ? (linha_origem == 6) : (linha_origem == 1);

            if(andou_mais_de_uma_casa && !primeiro_movimento_do_peao) throw Excecao("peao anda apenas uma casa");

            bool andou_na_diagonal = diff_no_y == 1 && diff_no_x == 1;
            bool tem_peca_inimiga_na_diagonal = ehPecaInimiga(peca_selecionada, peca_no_destino);
            if(andou_na_diagonal && !tem_peca_inimiga_na_diagonal) throw Excecao("peao nao anda na diagonal");

            if(!andou_na_diagonal && peca_no_destino != ' ') throw Excecao("peao so captura na diagonal");

            bool peao_branco_vai_pro_final = peao_eh_branco && linha_dest == 0;
            bool peao_preto_vai_pro_final = !peao_eh_branco && linha_dest == 7;

            if(peao_branco_vai_pro_final)
                peca_selecionada = 'Q';
            else if(peao_preto_vai_pro_final)
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

    set_char(linha_origem, coluna_origem, ' ');
    set_char(linha_dest, coluna_dest, peca_selecionada);
    passar_a_vez();
}

/**
 * \brief Verifica a vitória de um jogador
 *
 * Essa função recebe como parâmetro um jogador e verifica se
 * o jogador adversário (j2) ainda tem a peca do rei no tabuleiro.
 * Se isso for atendido, o jogador atual (j1) não venceu a partida 
 * e é retornado falso. Caso não for encontrado o rei de j2 no 
 * tabuleiro, j1 venceu a partida e é retornado verdadeiro.
 * 
 * \param jogador Um jogador da partida.
 * \return true ou false
 */
bool Xadrez::verificarVitoria(Jogador const& jogador) const {
    // jogador1 é branco: rei é K
    // jogador2 é preto: rei é k

    // se verifica vitória de jogador1, tem que ver se existe k.
    // se não existir, jogador1 venceu
    
    // se verifica vitória de jogador2, tem que ver se existe K.
    // se não existir, jogador2 venceu
    char rei = jogador.getApelido() == jogador1.getApelido() ? 'k' : 'K';

    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            char c = get_char(i, j);
            if(c == rei) return false;
        }
    }

    return true;
}

/**
 * \brief Verifica o empate do jogo
 *
 * Essa função sempre retorna falso, pois, no Xadrez,
 * não existe empate.
 * 
 * \return false
 */
bool Xadrez::verificarEmpate() const {
    return false;
}
