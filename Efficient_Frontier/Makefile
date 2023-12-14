efficient_frontier: main.cpp portfolio.o parse.o
	g++ -o efficient_frontier -pedantic -std=c++17 -Wall -Wextra -Werror -ggdb3 main.cpp portfolio.o parse.o

portfolio.o: portfolio.hpp portfolio.cpp
	g++ -c -o portfolio.o -pedantic -std=c++17 -Wall -Wextra -Werror -ggdb3 portfolio.cpp

parse.o: parse.cpp parse.hpp
	g++ -c -o parse.o -pedantic -std=c++17 -Wall -Wextra -Werror -ggdb3 parse.cpp

clean:
	rm -rf *.dSYM *.o efficient_frontier