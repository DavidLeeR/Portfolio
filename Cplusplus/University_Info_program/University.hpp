/****************************************************************************
 * File Name: University.hpp
 * Author: David Ramirez
 * Date: 4/30/17
 * Description: This is the header file for the University class. 
 * 		This class holds as data members nameU (string holding name
 * 		of university), building1 (Building obect), building2 (Building
 * 		object), student1 (Student object), instructor1 (Instructor
 * 		object), studentList (array of pointers to Student objects),
 * 		instructorList (array of pointers to Instructor objects), 
 * 		listNumberI (integer holding number of objects in 
 * 		instructorList), and listNumberS (integer holding number of 
 * 		objects in studentList). The University class's member
 * 		functions include a default constructor, the save() function
 * 		for saving all university person data, the load() function 
 * 		for loading all saved university person data, the 
 * 		printBuilding() function for displaying all the information
 * 		for each Building object, the printPeople() function for
 * 		printing all the information for each Student and
 * 		Instructor object, the s1DoWork() function for making 
 * 		student 1 (pre-initialized) do work, the i1DoWork() function
 * 		for making instructor 1 (pre-initialized) do work, the 
 * 		getNameStu() function for returning the name of student 1,
 * 		the getNameInst() function for returning the name of
 * 		instructor 1, the addPerson() function that adds either a 
 * 		Student or an Instructor class object to be pointed to by an
 * 		array of pointers, the extendSList() function for creating
 * 		more space in the studentList array, the extendIList() 
 * 		function for creating more space in the instructorList array, 
 * 		and the deleteList() function for deleting the dynamically
 * 		allocated studentList and instructorList arrays.
 * *************************************************************************/

#ifndef UNIVERSITY_HPP
#define UNIVERSITY_HPP

#include <string>
#include "Building.hpp"
#include "Student.hpp"
#include "Instructor.hpp"
#include "Person.hpp"
#include "inputVal.hpp"



//The University class represents a university with buildings, students, 
//and instructors
class University
{
	private:
		std::string nameU;
		Building building1;
		Building building2;
		Student	student1;
		Instructor instructor1;
		Instructor* instructorList;
		Student* studentList;
		int listNumberI;
		int listNumberS;
	public:
		University();
		void save();
		void load();
		void printBuildings();
		void printPeople();
		void s1DoWork();
		void i1DoWork();
		void otherDoWork();
		std::string getNameStu();
		std::string getNameInst();
		void addPerson();
		void extendSList();
		void extendIList();
		void deleteList();
};
#endif
