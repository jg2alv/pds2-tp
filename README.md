# Projeto Final (PDS2)

### Dependências
É necessário `g++` para compilar os binários e `doxygen` para a documentação. <br>
O projeto foi criado exclusivamente com a plataforma Linux em mente. <br>

### Compilação
Use `make bin/main` para compilar o programa. <br>
Use `make bin/t_main` para compilar os testes. <br>
Use `doxygen Doxyfile` para compilar a documentação. <br>
Use `make` ou `make all` para compilar o programa, os testes e a documentação, nessa ordem. <br>
Use `make clean` para deletar todos os objetos compilados. <br>

### Execução
Use `bin/main` no directório raíz do projeto para jogar. <br>
Use `bin/t_main` para rodar os testes. <br>
Use `make run` para compilar e jogar de uma só vez. <br>
Use `make test` para compilar e testar de uma só vez. <br>

### Problema
Foi proposta a implementação de dois jogos, Reversi e Lig4, utilizando-se do conhecimento de C++ adquirido ao longo do semestre.Junto aos jogos, foi proposta a implementação de um sistema de cadastro de jogadores, que armazena os dados referente à um mesmo jogador, como suas vitórias e derrotas em determinado jogo. <br>

### Solução
Em visão de solucionar esse problema, iniciamos o desenvolvimento deste programa. Foram criadas, inicialmente 7 classes, sendo elas: <br>
- `Jogo`: classe abstrata de jogos de tabuleiro, servindo o propósito de ser classe pai para os diversos jogos <br>
- `Reversi`: classe que implementa o jogo Reversi, herdando as características da classe 'Jogo' <br>
- `Lig4`: classe que implementa o jogo Lig4, herdando as características da classe 'Jogo' <br> 
- `Jogador`: responsável por armazenar os dados de um jogador, como nome, apelido e pontuação. <br>
- `Jogada`: responsável por representar uma jogada de um determinado jogador em um determinado jogo. <br>
- `Sistema`: responsável por controlar todo o funcionamento do programa, como interpretar comandos, iniciar jogos, escrever resultados em arquivos ou encerrar o programa quando solicitado. <br>
- `Excecao`: responsável por lançar uma exceção personalizada em caso de erro no programa <br>

O desenvolvimento e implementação de cada uma dessas classes foi dividido entre os membros do grupo. <br>

Após a implementação de todos estes, e o programa funcionando corretamente, decidimos desenvolver outros dois jogos, como extras para o trabalho: <br>
- `Xadrez`: classe que implementa o jogo Xadrez, herdando características da classe 'Jogo' <br>
- `JogoDaVelha`: classe que implementa o jogo 'Jogo da Velha', herdando características da classe 'Jogo' <br>

### Dificuldades
Durante o desenvolvimento, nos deparamos com todas as dificuldades comuns, como relacionar todas as classes entre si, implementar a lógica de cada um dos jogos, e desenvolver um sistema com outros participantes.<br>
Porém, todos os integrantes se mostraram dispostos a solucionar todas as adversidades encontradas, e por meio de comunicação diária e reuniões periódicas, passamos por todas as dificuldades sem problemas, e o programa foi implementado com sucesso.<br>


### Integrantes
Davi Oliveira Sad (DaviOSad) <br>
Giordano Henrique Liporati (Spwner) <br>
João Gabriel Guimarães Alves Vaz (jg2alv) <br>
Maria Eduarda Nunes e Carvalho de Vasconcelos Costa (MEduardaNunes) <br>
Thiago Esmerio Fernandes (HSThzz) <br>

