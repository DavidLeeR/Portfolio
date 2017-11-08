/****************************************************************************
 * File Name: Instructor.hpp
 * Author: David Ramirez
 * Date: 4/30/17
 * Description: This is the header file for the Instructor class. 
 * 		This class is a child class of the Person class, and uses
 * 		the constructors of the Person class. This class has the same 
 * 		data members as the Person class. It's member function 
 * 		consist of 3 different constructors that are used depending
 * 		on the parameters passed, the printCred() function (overloaded
 * 		from the Person class) to return the instructor rating, and 
 * 		the returnType() function that returns an integer used to keep
 * 		track of whether the person is a student or instructor. 
 * *************************************************************************/

#ifndef INSTRUCTOR_HPP
#define INSTRUCTOR_HPP

#include <string>
#include "Person.hpp"



//The Instructor class represents an instructor on the university campus
class Instructor: public Person
{
	public:
		Instructor();
		Instructor(std::string, int);
		Instructor(std::string, int, double);
		void printCred();
		int returnType();

};
#endif
