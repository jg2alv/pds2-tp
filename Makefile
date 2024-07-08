.PHONY: all clean


GPP = g++ -Werror -Wall -Wextra -fsanitize=address -fsanitize=undefined -I./include
RM = rm -rf


all: ./bin/main ./bin/t_main
	doxygen ./Doxyfile
	./bin/t_main

clean:
	$(RM) ./obj/*.o ./bin/main

./bin/main: ./src/main.cpp ./src/Jogador.cpp ./src/Sistema.cpp
	$(GPP) ./src/main.cpp ./src/Jogador.cpp ./src/Sistema.cpp -o ./bin/main


./bin/t_main: ./tests/t_main.cpp
	$(GPP) ./tests/t_main.cpp -o ./bin/t_main

