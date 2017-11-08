/****************************************************************************
 * File Name: Person.cpp
 * Author: David Ramirez
 * Date: 4/30/17
 * Description: This is the implementation file for the Person class. 
 * 		This class is the base class of both the Student class and the 
 * 		Instructor class. The Person class holds as data members
 * 		nameP (a string holding the name), age (an integer holding
 * 		the age), cred (a double value holding either the gpa or 
 * 		rating of the person), and seed (an unsigned value used as a 
 * 		seed for generating a random number. The member functions
 * 		consist of 2 constructors used depending on the parameters
 * 		passed, the getCred() function to return person gpa or rating
 * 		, the getAge() function to return the age, the doWork()
 * 		function to calculate and return a random number representing
 * 		hours worked, the returnType() function that returns an 
 * 		integer that represents the general 'person' type, and the
 * 		setCred()function to set either the gpa or rating after
 * 		initialization. 
 * *************************************************************************/

#include <string>
#include <ctime>
#include <cstdlib>
#include "Person.hpp"



//Function Name: default constructor
//Parameters: none
//Return Value: none
//Description: creates an 'empty' Person object 
Person::Person()
{
	nameP = "none";
	age = 0;
	cred = 0.0;
	seed = 0;
}



//Function Name: default constructor
//Parameters: pName (string holding name), pAge (integer holding age)
//Return Value: none
//Description: Creates a Person object using the parameters passed and seeds
//		the srand function to generate a random number
Person::Person(std::string pName, int pAge)
{
	nameP = pName;
	age = pAge;
	seed = time(0);
	srand(seed);
}



//Function Name: getNameP()
//Parameters: none
//Return Value: nameP (string holding the name)
//Description: Returns nameP
std::string Person::getNameP()
{
	return nameP;
}



//Function Name: getCred()
//Parameters: none
//Return Value: cred (double holding gpa or rating)
//Description: Returns cred
double Person::getCred()
{
	return cred;
}



//Function Name: getAge()
//Parameters: none
//Return Value: age (integer holding the age)
//Description: Returns age
int Person::getAge()
{
	return age;
}



//Function Name: doWork()
//Parameters: maxHoursP (integer holding the maximum hours to work)
//Return Value: result (integer representing amount of hours worked)
//Description: Generates and returns a random number (result), with the max 
//		value given by the parameter, that represents the amount of 
//		hours worked
int Person::doWork(int maxHoursP)
{
	int result;	//holds random number generated

	//generates random number using already seeded srand
	result = rand() % maxHoursP + 1;	

	return result;
}
	


//Function Name: returnType()
//Parameters: none
//Return Value: 0 (integer representing the general person type
//Description: Returns the integer '0', representing the general person type
int Person::returnType()
{
	return 0;
}



//Function Name: setCred()
//Parameters: credSC (double holding the gpa or rating)
//Return Value: none
//Description: Sets the cred data member (holds either gpa or rating) using
//		parameter passed after initialization
void Person::setCred(double credSC)
{
	cred = credSC;
}	
