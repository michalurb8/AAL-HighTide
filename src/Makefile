CF = -g -Wall -pedantic -std=c++11

default: main.o Tide.o Shell.o
	g++ main.o Tide.o Shell.o -o exe

main.o: main.cpp
	g++ $(CF) -c main.cpp -o main.o

Tide.o: Tide.cpp Tide.h
	g++ $(CF) -c Tide.cpp -o Tide.o

Shell.o: Shell.cpp Shell.h
	g++ $(CF) -c Shell.cpp -o Shell.o

clean:
	rm -f *.o exe

run:
	./exe