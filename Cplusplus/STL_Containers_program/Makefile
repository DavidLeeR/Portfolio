stlcontainer: main.o inputVal.o menu.o 
	g++ -std=c++0x main.o inputVal.o menu.o -o lab9

main.o: main.cpp
	g++ -std=c++0x -c main.cpp

inputVal.o: inputVal.cpp
	g++ -std=c++0x -c inputVal.cpp

menu.o: menu.cpp
	g++ -std=c++0x -c menu.cpp

clean:
	rm *.o lab9
