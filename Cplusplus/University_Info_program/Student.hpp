/****************************************************************************
 * File Name: Student.hpp
 * Author: David Ramirez
 * Date: 4/30/17
 * Description: This is the header file for the Student class. 
 * 		This class is a child class of the Person class, and uses
 * 		the constructors of the Person class. This class has the same 
 * 		data members as the Person class. It's member functions 
 * 		consist of 3 different constructors that are used depending
 * 		on the parameters passed, the printCred() function (overloaded
 * 		from the Person class) to return the student gpa, and 
 * 		the returnType() function that returns an integer used to keep
 * 		track of whether the person is a student or instructor. 
 * *************************************************************************/



#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
#include "Person.hpp"


//The Student class represents a student on the university campus
class Student: public Person
{
	public:
		Student();
		Student(std::string, int);
		Student(std::string, int, double);
		void printCred();
		int returnType();
};
#endif
