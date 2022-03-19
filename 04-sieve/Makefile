# Modules for this project:
# module load gcc/dev
# module load boost/dev

CXX=g++
CFLAGS=-std=c++20

sieve: sieve.cpp
	$(CXX) $(CFLAGS) sieve.cpp -o sieve.x -lfmt

all: sieve

.PHONY: clean

clean:
	rm -f *.x
