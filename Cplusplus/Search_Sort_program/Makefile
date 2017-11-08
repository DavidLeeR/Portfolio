all: program1 program2 program3

simplesearch: main1.o inputVal.o
	g++ -std=c++0x main1.o inputVal.o -o program1

sortprog: main2.o
	g++ -std=c++0x main2.o -o program2

binarysearch: main3.o inputVal.o
	g++ -std=c++0x main3.o inputVal.o -o program3 

main1.o: main1.cpp
	g++ -std=c++0x -c main1.cpp

main2.o: main2.cpp
	g++ -std=c++0x -c main2.cpp

main3.o: main3.cpp
	g++ -std=c++0x -c main3.cpp  

inputVal.o: inputVal.cpp
	g++ -std=c++0x -c inputVal.cpp 

clean:
	rm -f program1 program2 program3 *.o
