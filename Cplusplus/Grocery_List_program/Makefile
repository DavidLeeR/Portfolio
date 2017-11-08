grocery: main.o Item.o List.o inputVal.o menu.o
	g++ -std=c++0x main.o Item.o List.o inputVal.o menu.o -o project2

main.o: main.cpp
	g++ -std=c++0x -c main.cpp

Item.o: Item.cpp
	g++ -std=c++0x -c Item.cpp 

List.o: List.cpp
	g++ -std=c++0x -c List.cpp

inputVal.o: inputVal.cpp
	g++ -std=c++0x -c inputVal.cpp 

menu.o: menu.cpp
	g++ -std=c++0x -c menu.cpp

clean:
	rm *.o project2
