CXX=g++
CFLAGS=-std=c++20

wordle: wordle.cpp utils Dict Engine
	$(CXX) $(CFLAGS) wordle.cpp Dict.o Engine.o -o wordle.x -lfmt

utils: utils.cpp
	$(CXX) $(CFLAGS) -c utils.cpp -o utils.o

Dict: Dict.cpp
	$(CXX) $(CFLAGS) -c Dict.cpp -o Dict.o

Engine: Engine.cpp
	$(CXX) $(CFLAGS) -c Engine.cpp -o Engine.o

all: wordle

.PHONY: clean

clean:
	rm -f *.x *.o
