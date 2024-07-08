.PHONY: all clean


GPP = g++ -Werror -Wall -Wextra -fsanitize=address -fsanitize=undefined -I./include
RM = rm -rf


all: ./bin/main ./bin/t_main
	doxygen ./Doxyfile
	./bin/t_main

clean:
	$(RM) ./obj/*.o ./bin/main

./bin/main: ./src/main.cpp ./obj/Jogador.o ./obj/Sistema.o
	$(GPP) ./src/main.cpp ./obj/Jogador.o ./obj/Sistema.o -o ./bin/main

./bin/t_main: ./tests/t_main.cpp
	$(GPP) ./tests/t_main.cpp -o ./bin/t_main

./obj/Jogador.o: ./src/Jogador.cpp ./include/Jogador.hpp
	$(GPP) -c ./src/Jogador.cpp -o ./obj/Jogador.o

./obj/Sistema.o: ./src/Sistema.cpp ./include/Sistema.hpp
	$(GPP) -c ./src/Sistema.cpp -o ./obj/Sistema.o

