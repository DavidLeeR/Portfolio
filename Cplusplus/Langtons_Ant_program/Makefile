ant: main.o Ant.o Board.o menu.o
	g++ -std=c++0x main.o Ant.o Board.o menu.o -o project1

main.o: main.cpp
	g++ -std=c++0x -c main.cpp

Ant.o: Ant.cpp
	g++ -std=c++0x -c Ant.cpp

Board.o: Board.cpp
	g++ -std=c++0x -c Board.cpp

menu.o: menu.cpp
	g++ -std=c++0x -c  menu.cpp

clean:
	rm *.o project1

