# Projeto Final

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

### Funcionalidade
Ao iniciar o programa, o arquivo `data/jogadores.txt` e lido, ou criado caso não exista, e o usuário pode digitar uma série comandos para interagir com o sistema. <br>
Digite `?` para uma explicação sobre os comandos disponíveis. <br>
Após serem cadastrados pelo menos dois jogadores, pode ser realizada uma partida entre eles. Os jogos `Lig4` e `Reversi` podem ser customizados adicionando logo após o conteúdo normal de um comando `EP`: um número de linhas e colunas do tabuleiro, e o tamanho do lado de um tabuleiro quadrado, repectivamente. <br>
 Cada um dos jogos disponíveis tem um formato de jogada único: <br>
- O `JogoDaVelha` e o `Reversi` recebem dois números, uma linha e uma coluna, respectivamente. <br>
- O `Lig4` recebe só um número, o da coluna. <br>
- O `Xadrez` recebe uma string na forma `[a-h][1-8][a-h][1-8]`, onde o primeiro par de letra e número representa a coluna e a linha de origem de uma peça, e o segundo, seu destino. <br>
Qualquer erro na entrada produzir uma mensagem de erro útil sobre a última ação. <br>
Quando o programa é fechado ou finaliza normalmente, os dados adquiridos durante a execução são escritos no arquivo `data/jogadores.txt`. <br>

### Formato do arquivo de jogadores
```
{número de jogadores}
[
{apelido do jogador}
{nome do jogador}
{número de jogos diferentes que o jogador já jogou}
[{nome do jogo} {número de vitórias} {número de derrotas} {número de empates}]
]
```

### Problema
Foi proposta a implementação de um sistema para cadastro de jogadores e realização de partidas em dois jogos, Reversi e Lig4, de forma que seus resultados sejam contabilizados entre execuções do programa. Foi definida como obrigatória a utilização da programção orientada a objetos em C++, em especial dos mecanismos de polimorfismo universal de inclusão fornecidos pela linguagem. <br>

### Solução
Em função de solucionar o problema proposto, foram criadas 9 classes, 1 delas abstrata com 5 herdeiras. <br>
A classe `Jogo`, com seus métodos pure virtual para a realização de jogadas e verificação de vitória, além de seu métodos para gerenciamento dos jogadores e do tabuleiro, serviu de base a para as classes dos jogos específicos, `Reversi`, `Lig4`, `JogoDaVelha` e `Xadrez`. <br>
A classe `Jogada` serviu de auxilio para a implementação dos jogos em particular. <br>
A classe `Jogador` serviu como receptáculo para as informações cadastradas e resultados de partidas. <br>
A classe `Sistema` acabou responsabilizada por construir e guardar `Jogador`es a partir do arquivo e reescrevê-lo com dados atualizados após o uso, além de realizar as partidas dos diferentes jogos de fato, com auxílio dos métodos disponibilizados pela classe `Jogo`. <br>
Também criamos uma classe `Excecao`, herdeira de `std::exception` para gerenciamento de erros de excução. <br>
O desenvolvimento e implementação de cada uma dessas classes foi dividido entre os membros do grupo. <br>
As maiores dificuldades encontradas foram relacionadas a definir qual seria a interface das classes `Jogo`, na medida em que precisavam interagir de forma adequada com o `Sistema` e pudessem ser testadas facilmente independente dele. <br>

### Extras
Como funcionalidade extras decidimos incluir: <br>
- Mensagens de erros explicativas e comandos de ajuda para os usuários. <br>
- Customização para os jogos `Lig4` e `Reversi`, permitindo tamanhos de tabuleiro diferentes. <br>
- Dois jogos novos sem opções de customização, `JogoDaVelha` e `Xadrez`*. <br>
- Possibilidade de desistência e cancelamento de uma partida. <br>
\*Basicamente um protótipo: não inclui xeque nem xeque-mate, roque, *en passant*, promoção para cavalo, bispo ou torre, afogamento ou outras possibilidades de empate. <br>

### Integrantes
Davi Oliveira Sad (DaviOSad) <br>
Giordano Henrique Liporati (Spwner) <br>
João Gabriel Guimarães Alves Vaz (jg2alv) <br>
Maria Eduarda Nunes e Carvalho de Vasconcelos Costa (MEduardaNunes) <br>
Thiago Esmerio Fernandes (HSThzz) <br>

