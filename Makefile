.PHONY: all clean


GPP = g++ -Werror -Wall -Wextra -fsanitize=address -fsanitize=undefined -I./include
RM = rm -rf


all: ./bin/main ./bin/t_main
	doxygen ./Doxyfile
	./bin/t_main

clean:
	$(RM) ./obj/*.o ./bin/main ./bin/t_main


# ./bin/main: ./src/main.cpp ./obj/Jogador.o ./obj/Sistema.o ./obj/Jogo.o ./obj/Reversi.o ./obj/Lig4.o ./obj/Excecao.o
# 	$(GPP) ./src/main.cpp ./obj/Excecao.o ./obj/Jogador.o ./obj/Sistema.o ./obj/Jogo.o ./obj/Reversi.o ./obj/Lig4.o -o ./bin/main

./bin/main: ./src/main.cpp ./obj/Jogador.o ./obj/Sistema.o ./obj/Jogo.o ./obj/Excecao.o
	$(GPP) ./src/main.cpp ./obj/Excecao.o ./obj/Jogador.o ./obj/Sistema.o ./obj/Jogo.o -o ./bin/main

./obj/Jogador.o: ./src/Jogador.cpp ./include/Jogador.hpp
	$(GPP) -c ./src/Jogador.cpp -o ./obj/Jogador.o

./obj/Sistema.o: ./src/Sistema.cpp ./include/Sistema.hpp ./include/Jogador.hpp
	$(GPP) -c ./src/Sistema.cpp -o ./obj/Sistema.o

./obj/Jogo.o: ./src/Jogo.cpp ./include/Jogo.hpp
	$(GPP) -c ./src/Jogo.cpp -o ./obj/Jogo.o

./obj/Reversi.o: ./src/Reversi.cpp ./include/Reversi.hpp ./include/Jogador.hpp ./include/Jogo.hpp ./include/Jogada.hpp
	$(GPP) -c ./src/Reversi.cpp -o ./obj/Reversi.o

./obj/Lig4.o: ./src/Lig4.cpp ./include/Lig4.hpp ./include/Jogador.hpp ./include/Jogo.hpp ./include/Jogada.hpp
	$(GPP) -c ./src/Lig4.cpp -o ./obj/Lig4.o

./obj/Excecao.o: ./src/Excecao.cpp ./include/Excecao.hpp
	$(GPP) -c ./src/Excecao.cpp -o ./obj/Excecao.o

./obj/Jogada.o: ./src/Jogada.cpp ./include/Jogada.hpp
	$(GPP) -c ./src/Jogada.cpp -o ./obj/Jogada.o


./bin/t_main: ./tests/t_main.cpp ./obj/t_Lig4.o ./obj/t_Reversi.o ./obj/Jogador.o ./obj/Jogada.o ./obj/Jogo.o ./obj/Lig4.o ./obj/Reversi.o
	$(GPP) ./tests/t_main.cpp ./obj/t_Lig4.o ./obj/t_Reversi.o ./obj/Jogador.o ./obj/Jogada.o ./obj/Jogo.o ./obj/Lig4.o ./obj/Reversi.o -o ./bin/t_main

./obj/t_Lig4.o: ./tests/t_Lig4.cpp ./include/Jogador.hpp ./include/Jogada.hpp ./include/Jogo.hpp ./include/Lig4.hpp
	$(GPP) -c ./tests/t_Lig4.cpp -o ./obj/t_Lig4.o

./obj/t_Reversi.o: ./tests/t_Reversi.cpp ./include/Jogador.hpp ./include/Jogada.hpp ./include/Jogo.hpp ./include/Reversi.hpp
	$(GPP) -c ./tests/t_Reversi.cpp -o ./obj/t_Reversi.o


