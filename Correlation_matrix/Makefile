CPPFLAGS=-Wall -Werror -std=c++17 -pedantic -ggdb3
SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, %.o, $(SRCS))
PROGRAM=correl_matrix

$(PROGRAM): $(OBJS)
	g++ $(CPPFLAGS) -o $@ $(OBJS)

%.o: %.cpp asset.hpp
	g++ -c $(CPPFLAGS) $<

.PHONY: clean
clean:
	rm -f $(OBJS) $(PROGRAM) *~