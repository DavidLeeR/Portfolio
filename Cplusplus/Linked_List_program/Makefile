linkedlist: main.o inputVal.o menu.o List.o
	g++ -std=c++0x main.o inputVal.o menu.o List.o -o lab6

main.o: main.cpp
	g++ -std=c++0x -c main.cpp

inputVal.o: inputVal.cpp
	g++ -std=c++0x -c inputVal.cpp

menu.o: menu.cpp
	g++ -std=c++0x -c menu.cpp

listFunctions.o: List.cpp
	g++ -std=c++0x -c List.cpp 

clean:
	rm *.o lab6 
