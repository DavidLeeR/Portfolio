/****************************************************************************
 * File Name: Instructor.cpp
 * Author: David Ramirez
 * Date: 4/30/17
 * Description: This is the implementation file for the Instructor class. 
 * 		This class is a child class of the Person class, and uses
 * 		the constructors of the Person class. This class has the same 
 * 		data members as the Person class. It's member function 
 * 		consist of 3 different constructors that are used depending
 * 		on the parameters passed, the printCred() function (overloaded
 * 		from the Person class) to return the instructor rating, and 
 * 		the returnType() function that returns an integer used to keep
 * 		track of whether the person is a student or instructor. 
 * *************************************************************************/

#include <iostream>
#include "Instructor.hpp"
#include "inputVal.hpp"



//Function Name: default constructor
//Parameters: none
//Return Value: none
//Description: creates an 'empty' Instructor object using the Person class
//		default constructor
Instructor::Instructor():
Person()
{
}



//Function Name: constructor
//Parameters: nameIC (string holding name), ageIC (integer holding age)
//Return Value: none
//Description: Creates an Instructor object using the Person class constructor
//		and using  user input for the instructor rating
Instructor::Instructor(std::string nameIC, int ageIC):
Person(nameIC, ageIC)
{
	std::string tempRatingC; //used to hold input for validation
	char* last9;
	
	//prompt and save instructor rating
	std::cout << std::endl;
	std::cout << "Enter the rating for the first instructor (max 5.0)";
	std::cout << std::endl;
	getline(std::cin, tempRatingC);

	//validate input to be a float value
	while ((inputValF(tempRatingC) == false ) || 
	       		(strtod(tempRatingC.c_str(), &last9) < 0.0 )||
	       		(strtod(tempRatingC.c_str(), &last9) > 5.0))
	{
			std::cout << std::endl;
			std::cout << "The input entered is invalid";
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << "Enter the rating for the first instructor (max 5.0)";
			std::cout << std::endl;
			getline(std::cin, tempRatingC);
	}
	cred = strtod(tempRatingC.c_str(), &last9);
}



//Function Name: constructor
//Parameters: nameIC (string holding name), ageIC (integer holding age), 
//		credIC (double holding instructor rating)
//Return Value: none
//Description: Creates an Instructor object using only parameters passed and
//		the Person class constructor
Instructor::Instructor(std::string nameIC, int ageIC, double credIC):
Person(nameIC, ageIC)
{
	cred = credIC;
}



//Function Name: printCred()
//Parameters: none
//Return Value: none
//Description: Displays the instructor rating to the console window
void Instructor::printCred()
{
	std::cout << "The instructor rating for " << getNameP() << " is " ;
	std::cout << getCred() << std::endl;
}



//Function Name: returnType()
//Parameters: none
//Return Value: 2 (integer representing the instructor person type)
//Description: Returns the integer '2', representing the instructor person 
//		type
int Instructor::returnType()
{
	return 2;
}
