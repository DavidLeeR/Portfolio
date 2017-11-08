/****************************************************************************
 * File Name: Person.hpp
 * Author: David Ramirez
 * Date: 4/30/17
 * Description: This is the header file for the Person class. 
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

#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>



//The Person class represents any person on the university campus (can be 
//either a student or an instructor)
class Person
{
	protected:
		std::string nameP;
		int age;
		double cred;
		unsigned seed;
	public:
		Person();
		Person(std::string, int);
		std::string getNameP();
		double getCred();
		int getAge();
		int doWork(int);
		int returnType();
		void setCred(double);
};
#endif
