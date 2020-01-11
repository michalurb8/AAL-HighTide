#Michal Urbanski
#Zeglowanie w czasie przyplywu
CF = -Wall -pedantic -std=c++11 -O3

default: main.o Tide.o Solution.o Timer.o
	g++ main.o Tide.o Solution.o Timer.o -o exe

main.o: main.cpp 
	g++ $(CF) -c main.cpp -o main.o

Tide.o: Tide.cpp Tide.h
	g++ $(CF) -c Tide.cpp -o Tide.o

Solution.o: Solution.cpp Solution.h
	g++ $(CF) -c Solution.cpp -o Solution.o

Timer.o: Timer.cpp Timer.h
	g++ $(CF) -c Timer.cpp -o Timer.o

clean:
	rm -f *.o exe

run: default
	./exe