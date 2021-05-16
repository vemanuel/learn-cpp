# Modules for this project:
# module load gcc/dev
# module load boost/dev

CXX=g++
CFLAGS=-std=c++20

pi: pi.cpp
	$(CXX) $(CFLAGS) pi.cpp -o pi.x

all: pi

.PHONY: clean

clean:
	rm -f *.x
