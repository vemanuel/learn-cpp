# Modules for this project:
# module load gcc/dev

CXX=g++
CFLAGS=-std=c++20

puzzle: seven-eleven.cpp
	$(CXX) $(CFLAGS) seven-eleven.cpp -o seven-eleven.x -lfmt

all: sieve

.PHONY: clean

clean:
	rm -f *.x
