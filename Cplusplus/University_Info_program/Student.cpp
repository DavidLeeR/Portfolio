/****************************************************************************
 * File Name: Student.cpp
 * Author: David Ramirez
 * Date: 4/30/17
 * Description: This is the implementation file for the Student class. 
 * 		This class is a child class of the Person class, and uses
 * 		the constructors of the Person class. This class has the same 
 * 		data members as the Person class. It's member functions 
 * 		consist of 3 different constructors that are used depending
 * 		on the parameters passed, the printCred() function (overloaded
 * 		from the Person class) to return the student gpa, and 
 * 		the returnType() function that returns an integer used to keep
 * 		track of whether the person is a student or instructor. 
 * *************************************************************************/

#include <iostream>
#include <string>
#include "Student.hpp"
#include "inputVal.hpp"



//Function Name: default constructor
//Parameters: none
//Return Value: none
//Description: creates an 'empty' Student object using the Person class
//		default constructor
Student::Student():
Person()
{
}



//Function Name: constructor
//Parameters: nameSC (string holding name), ageSC (integer holding age)
//Return Value: none
//Description: creates a Student object using the Person class constructor and
//		using user input for the student gpa
Student::Student(std::string nameSC, int ageSC):
Person(nameSC, ageSC)
{
	std::string tempGpaC; //used to hold input for validation
	char* last8;

	//prompt and save student gpa
	std::cout << std::endl;
	std::cout << "Enter the gpa for the first student (max 4.0)";
	std::cout << std::endl;
	getline(std::cin, tempGpaC);

	//validate input to be a float value
	while ((inputValF(tempGpaC) == false ) || 
	       		(strtod(tempGpaC.c_str(), &last8) < 0.0 )||
	       		(strtod(tempGpaC.c_str(), &last8) > 4.0))
	{
			std::cout << std::endl;
			std::cout << "The input entered is invalid";
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << "Enter the gpa for the first student (max 4.0)";
			std::cout << std::endl;
			getline(std::cin, tempGpaC);
	}
	cred = strtod(tempGpaC.c_str(), &last8);
}



//Function Name:constructor
//Parameters: nameSC (string holding name), ageSC (integer holding age), 
//		credSC (double holding student gpa)
//Return Value: none
//Description: creates a Student object using only parameters passed and
//		 the Person class constructor
Student::Student(std::string nameSC, int ageSC, double credSC):
Person(nameSC, ageSC)
{
	cred = credSC;
}



//Function Name: printCred()
//Parameters: none
//Return Value: none
//Description: Displays the student gpa to the console window
void Student::printCred()
{
	std::cout << "The gpa for " << getNameP() << " is " ;
	std::cout << getCred() << std::endl;
}



//Function Name: returnType()
//Parameters: none
//Return Value: 1 (integer representing the student person type
//Description: Returns the integer '1', representing the student person type
int Student::returnType()
{
	return 1;
}
