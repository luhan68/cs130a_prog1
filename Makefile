CXX = clang++

CXXFLAGS= -std=c++11 -Wall -g

all: prog1A prog1B

prog1A: mainA.o
	${CXX} mainA.o -o prog1A

prog1B: mainB.o
	${CXX} mainB.o -o prog1B

clean:
	/bin/rm -f *.o prog1A prog1B