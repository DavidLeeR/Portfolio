university: main.o Building.o inputVal.o Instructor.o menu.o Person.o Student.o University.o 
	g++ -std=c++0x main.o Building.o inputVal.o Instructor.o menu.o Person.o Student.o University.o -o lab4

main.o: main.cpp
	g++ -std=c++0x -c main.cpp

Building.o: Building.cpp
	g++ -std=c++0x -c Building.cpp

inputVal.o: inputVal.cpp
	g++ -std=c++0x -c inputVal.cpp

Instructor.o: Instructor.cpp
	g++ -std=c++0x -c Instructor.cpp

menu.o: menu.cpp
	g++ -std=c++0x -c menu.cpp

Person.o: Person.cpp
	g++ -std=c++0x -c Person.cpp

Student.o: Student.cpp
	g++ -std=c++0x -c Student.cpp

University.o: University.cpp
	g++ -std=c++0x -c University.cpp

clean:
	rm *.o lab4
