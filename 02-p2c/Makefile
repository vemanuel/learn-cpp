# Modules for this project:
# module load gcc/dev
# module load boost/dev

CXX=g++
CFLAGS=-std=c++20

p2c: p2c.cpp
	$(CXX) $(CFLAGS) p2c.cpp -o p2c.x

all: p2c

.PHONY: clean

clean:
	rm -f *.x
