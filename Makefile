.PHONY: all clean


GPP = g++ -Werror -Wall -Wextra -fsanitize=address -fsanitize=undefined -I./include
RM = rm -rf


all: ./bin/main
	doxygen Doxyfile

clean:
	$(RM) ./obj/*.o ./bin/main

./bin/main: ./src/main.cpp
	$(GPP) ./src/main.cpp -o ./bin/main

