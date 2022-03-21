# Modules for this project:
# module load gcc/dev

CXX=g++
CFLAGS=-std=c++20

puzzle: puzzle.cpp
	$(CXX) $(CFLAGS) puzzle.cpp -o puzzle.x -lfmt

all: sieve

.PHONY: clean

clean:
	rm -f *.x
