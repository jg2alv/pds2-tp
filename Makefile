.PHONY: all run test clean


GPP = g++ -Werror -Wall -Wextra -fsanitize=address -fsanitize=undefined -I./include
RM = rm -rf

OBJs = ./obj/Xadrez.o ./obj/Jogo.o ./obj/Jogador.o ./obj/Jogada.o ./obj/Reversi.o ./obj/Lig4.o ./obj/Excecao.o ./obj/Sistema.o
T_OBJs = ./obj/t_Jogador.o ./obj/t_Reversi.o ./obj/t_Lig4.o ./obj/t_Sistema.o


all: ./bin/main ./bin/t_main
	doxygen ./Doxyfile

run: ./bin/main
	./bin/main

test: ./bin/t_main
	./bin/t_main

clean:
	$(RM) ./obj/*.o ./bin/main ./bin/t_main


./bin/main: ./src/main.cpp $(OBJs)
	$(GPP) ./src/main.cpp $(OBJs) -o ./bin/main

./obj/Jogador.o: ./src/Jogador.cpp ./include/Jogador.hpp
	$(GPP) -c ./src/Jogador.cpp -o ./obj/Jogador.o

./obj/Sistema.o: ./src/Sistema.cpp ./include/Jogo.hpp ./include/Jogador.hpp ./include/Jogada.hpp ./include/Reversi.hpp ./include/Lig4.hpp ./include/Excecao.hpp ./include/Sistema.hpp
	$(GPP) -c ./src/Sistema.cpp -o ./obj/Sistema.o

./obj/Jogo.o: ./src/Jogo.cpp ./include/Jogo.hpp ./include/Jogador.hpp ./include/Jogada.hpp
	$(GPP) -c ./src/Jogo.cpp -o ./obj/Jogo.o

./obj/Reversi.o: ./src/Reversi.cpp ./include/Jogo.hpp ./include/Jogador.hpp ./include/Jogada.hpp ./include/Reversi.hpp
	$(GPP) -c ./src/Reversi.cpp -o ./obj/Reversi.o

./obj/Lig4.o: ./src/Lig4.cpp ./include/Jogo.hpp ./include/Jogador.hpp ./include/Jogada.hpp ./include/Lig4.hpp
	$(GPP) -c ./src/Lig4.cpp -o ./obj/Lig4.o

./obj/Xadrez.o: ./src/Xadrez.cpp ./include/Jogo.hpp ./include/Jogador.hpp ./include/Jogada.hpp ./include/Xadrez.hpp
	$(GPP) -c ./src/Xadrez.cpp -o ./obj/Xadrez.o

./obj/Excecao.o: ./src/Excecao.cpp ./include/Excecao.hpp
	$(GPP) -c ./src/Excecao.cpp -o ./obj/Excecao.o

./obj/Jogada.o: ./src/Jogada.cpp ./include/Jogada.hpp
	$(GPP) -c ./src/Jogada.cpp -o ./obj/Jogada.o


./bin/t_main: ./tests/t_main.cpp $(OBJs) $(T_OBJs)
	$(GPP) ./tests/t_main.cpp $(OBJs) $(T_OBJs) -o ./bin/t_main

./obj/t_Lig4.o: ./tests/t_Lig4.cpp ./include/Jogo.hpp ./include/Jogador.hpp ./include/Jogada.hpp ./include/Lig4.hpp
	$(GPP) -c ./tests/t_Lig4.cpp -o ./obj/t_Lig4.o

./obj/t_Reversi.o: ./tests/t_Reversi.cpp ./include/Jogo.hpp ./include/Jogador.hpp ./include/Jogada.hpp ./include/Reversi.hpp
	$(GPP) -c ./tests/t_Reversi.cpp -o ./obj/t_Reversi.o

./obj/t_Jogador.o: ./tests/t_Jogador.cpp ./include/Jogador.hpp
	$(GPP) -c ./tests/t_Jogador.cpp -o ./obj/t_Jogador.o

./obj/t_Sistema.o: ./tests/t_Sistema.cpp ./include/Jogador.hpp ./include/Sistema.hpp
	$(GPP) -c ./tests/t_Sistema.cpp -o ./obj/t_Sistema.o


