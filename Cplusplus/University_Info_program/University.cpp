/****************************************************************************
 * File Name: University.cpp
 * Author: David Ramirez
 * Date: 4/30/17
 * Description: This is the implementation file for the University class. 
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

#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "University.hpp"



//Function Name: constructor
//Parameters: none
//Return Value: none
//Description: Sets data members building1 and building2 using pre-set
//		parameters. Sets data members student1 and instructor1 using
//		pre-set parameters and user input. Sets nameU data member
//		to pre-set parameter and creates both instructorList and 
//		studentList arrays (1 space)
University::University():
building1("Austin Hall", "2751 SW Jefferson Way, Corvallis, OR 97331", 93941),
building2("Crop Science Building", "3050 Campus Way, Corvallis,OR 97330", 57638),
student1("David Ramirez", 25),
instructor1("Thomas Hanks", 60)

{
	nameU = "Oregon State University";

	instructorList = new Instructor[1];
	listNumberI = 0;

	studentList = new Student[1];
	listNumberS = 0;

	
}



//Function Name: save()
//Parameters: none
//Return Value: none
//Description: Saves all person data held in University class object to 
//		file "saveFile.txt"
void University::save()
{
	std::ofstream outputFile;

	//The following 3 lines is modified code from a post on 
	//stackoverflow.com by author PureW. 
	//stackoverflow.com/questions/17032970/clear-data-inside-text-file-in-c	
	outputFile.open("saveFile.txt", std::ofstream::out | std::ofstream
			::trunc);
	outputFile.close();

	outputFile.open("saveFile.txt");
	
	//save credential info for student1 and instructor1
	outputFile << student1.getCred() << std::endl;
	outputFile << instructor1.getCred() << std::endl;

	//saves list numbers 
	outputFile << listNumberS << std::endl;
	outputFile << listNumberI << std::endl;
	
	//step through array of pointers to Student and save name, age, and 
	//gpa
	for (int q = 0; q < listNumberS; q++)
	{
		outputFile << studentList[q].getNameP() << std::endl;
		outputFile << studentList[q].getAge() << std::endl;
		outputFile << studentList[q].getCred() << std::endl;
	}

	//step through array of pointers to Instructor and save name, age, and
	//rating
	for (int r = 0; r < listNumberI; r++)
	{
		outputFile << instructorList[r].getNameP() << std::endl;
		outputFile << instructorList[r].getAge() << std::endl;
		outputFile << instructorList[r].getCred() << std::endl;
	}

	//close output file
	outputFile.close();

	std::cout << std::endl;
	std::cout << "Person data for Oregon State University has been saved";
	std::cout << std::endl;
}



//Function Name: load()
//Parameters: none
//Return Value: none
//Description: Loads all previously saved person data held in University class 
//		object from file "saveFile.txt"
void University::load()
{
	double loadCredS;
	double loadCredI;
	std::string test;	
	
	std::ifstream inputFile;
	
	//open input file
	inputFile.open("saveFile.txt");

	//if file has saved contents
	if (inputFile >> loadCredS)
	{
		//load instructor rating for instructor1
		inputFile >> loadCredI;

		//use setter function to set loaded credentials
		student1.setCred(loadCredS);
		instructor1.setCred(loadCredI); 

		//load both list numbers
		inputFile >> listNumberS;
		inputFile >> listNumberI;

		//delete both arrays of pointers
		delete [] studentList;
		delete [] instructorList;

		//create new arraysof pointers
		studentList = new Student[listNumberS];
		instructorList = new Instructor[listNumberI];

		//step through array of pointers to Student
		for (int s = 0; s < listNumberS; s++)
		{
			std::string nameL;
			int ageL;
			double credL;
			
			//load student name, age, and gpa for each saved 
			//Student object
			inputFile >> nameL;
			inputFile >> ageL;
			inputFile >> credL;
			
			//create Student object with loaded parameters
			studentList[s] = Student(nameL, ageL, credL);
		}

		//step through array of pointers to Instructor
		for (int t = 0; t < listNumberI; t++)
		{
			std::string nameLI;
			int ageLI;
			double credLI;

			//load instructor name, age, and rating for each saved
			//Instructor object
			inputFile >> nameLI;
			inputFile >> ageLI;
			inputFile >> credLI;
			
			//create Instructor object with loaded parameters
			instructorList[t] = Instructor(nameLI, ageLI, credLI);
		}

		std::cout << std::endl;
		std::cout << "Person data for Oregon State University has been loaded";
		std::cout << std::endl;
		}

	//if no previous saved data found in saveFile.txt
	else
	{
		std::cout << std::endl;
		std::cout << "No previous save data";
		std::cout << std::endl;
	}
}



//Function Name: printBuildings()
//Parameters: none
//Return Value: none
//Description: Displays all the information for each Building object held by 
//		the University class object to the console window

void University::printBuildings()
{
	std::cout << std::endl;
	std::cout << nameU << " building list:";
	std::cout << std::endl << std::endl;
	std::cout << "name of building 1: " << building1.getNameB();
	std::cout << std::endl;
	std::cout << "square feet of building 1: " << building1.getSqFeet();
	std::cout << " m^2" << std::endl;
	std::cout << "address of building 1: " << building1.getAddress();
	std::cout << std::endl << std::endl;

	std::cout << std::endl;
	std::cout << "name of building 2: " << building2.getNameB();
	std::cout << std::endl;
	std::cout << "square feet of building 2: " << building2.getSqFeet();
	std::cout << " m^2" << std::endl;
	std::cout << "address of building 2: " << building2.getAddress();
	std::cout << std::endl << std::endl;
}



//Function Name: printPeople()
//Parameters: none
//Return Value: none
//Description: Displays all information for each Student or Instructor
//		class object contained in the University class object, and 
//		also for each Student or Instructor class object pointed to
//		by the studentList array or the instructorList array
void University::printPeople()
{
	//print information for instructor1
	std::cout << std::endl;
	std::cout << nameU << " instructor and student list:";
	std::cout << std::endl << std::endl;
	std::cout << "name of instructor: " << instructor1.getNameP();
	std::cout << std::endl;
	std::cout << "age of instructor: " << instructor1.getAge();		
	std::cout << std::endl;
	std::cout << "instructor rating: "; 
	std::cout << instructor1.getCred();
	std::cout << std::endl;

	//steps through instructorList array and display all information
	//held by each Instructor class object
	for (int k = 0; k < listNumberI; k++)
	{
		//if location in array is not 'empty'
		if (instructorList[k].getNameP() != "none")
		{
			std::cout << std::endl;
			std::cout << "name of instructor: " << instructorList[k].getNameP();
			std::cout << std::endl;
			std::cout << "age of instructor: " << instructorList[k].getAge();		
			std::cout << std::endl;
			std::cout << "instructor rating: " << instructorList[k].getCred();
			std::cout << std::endl;
		}
	
	}
	
	//steps through studentList array and display all information
	//held by each Student class object	
	for (int m = 0; m < listNumberS; m++)
	{
		//if location in array is not 'empty'
		if (studentList[m].getNameP() != "none")
		{
			std::cout << std::endl;
			std::cout << "name of student: " << studentList[m].getNameP();
			std::cout << std::endl;
			std::cout << "age of student: " << studentList[m].getAge();
			std::cout << std::endl;
			std::cout << "gpa of student: " << studentList[m].getCred();
			std::cout << std::endl;
		}
	}
	
	//display information fro student1
	std::cout << std::endl;
	std::cout << "name of student: " << student1.getNameP();
	std::cout << std::endl;
	std::cout << "age of student: " << student1.getAge();		
	std::cout << std::endl;
	std::cout << "gpa of student: " << student1.getCred();
	std::cout << std::endl;
}



//Function Name: s1DoWork()
//Parameters: none
//Return Value: none
//Description: Makes student1 do random amount of hours of work less than 
//		user defined number
void University::s1DoWork()
{
	int maxHoursS;
	std::string tempHours1;
	char* last7;

	std::cout << "Enter the maximum amount of hours for this person ";
	std::cout << "to work. (max 10 hours)" << std::endl;
	
	getline(std::cin, tempHours1);
	
	//input validation for bounds and if integer
	while ((inputVal(tempHours1) == false ) || 
	       (strtol(tempHours1.c_str(), &last7, 10) < 1)||
	       (strtol(tempHours1.c_str(), &last7, 10) > 10))
	{
		std::cout << "Enter the maximum amount of hours for this person ";
		std::cout << "to work. (max 10 hours)" << std::endl;
	
		getline(std::cin, tempHours1);
	}
	maxHoursS = strtol(tempHours1.c_str(), &last7, 10);

	std::cin.clear();

	//displays statement of work done
	std::cout << std::endl;
	std::cout << getNameStu() << " did ";
	std::cout << student1.doWork(maxHoursS) << " hours of homework";

	std::cout << std::endl;
}



//Function Name: i1DoWork()
//Parameters: none
//Return Value: none
//Description: Makes instructor1 do random amount of hours of work less than 
//		user defined number
void University::i1DoWork()
{
	int maxHoursI;
	std::string tempHours2;
	char* last6;

	std::cout << "Enter the maximum amount of hour for this person ";
	std::cout << "to work. (max 10 hours)" << std::endl;
	
	getline(std::cin, tempHours2);	
	
	//input validation for bounds and if integer
	while ((inputVal(tempHours2) == false ) || 
	       (strtol(tempHours2.c_str(), &last6, 10) < 1)||
	       (strtol(tempHours2.c_str(), &last6, 10) > 10))
	{
		std::cout << "Enter the maximum amount of hour for this person ";
		std::cout << "to work. (max 10 hours)" << std::endl;
	
		getline(std::cin, tempHours2);
	}
	maxHoursI = strtol(tempHours2.c_str(), &last6, 10);
		
	std::cin.clear();

	//display statement of work done
	std::cout << std::endl;
	std::cout << "Instructor " << getNameInst() << " graded papers for ";
	std::cout << instructor1.doWork(maxHoursI) << " hours";

	std::cout << std::endl;
}



//Function Name: otherDoWork()
//Parameters: none
//Return Value: none
//Description: Searches for Student or Instructor to do random amount of 
//		hours of work less than user defined number

void University::otherDoWork()
{
	int chooseWork;	
	int matchTrack =0;	//stores 1  if name matched
	int matchTrack2 =0;
	int matchLoc;		//stores location in array of matched name
	int matchLoc2;
	int maxHoursS;		//stores maximum hours to work
	int maxHoursI;
	std::string tempWork;	//all temp strings for input validation
	std::string tempHoursS;
	std::string tempHoursI;
	char* last5;

	std::cout << "If you want a student to do work enter ";
	std::cout << "\'1\', if you want an instructor to do work enter ";
	std::cout << "\'2\'" << std::endl;
	getline(std::cin, tempWork);

	//input validation for bounds and if integer
	while ((inputVal(tempWork) == false ) || 
	       (strtol(tempWork.c_str(), &last5, 10) < 1)||
	       (strtol(tempWork.c_str(), &last5, 10) > 2))
	{
		std::cout << "If you want to find a student to do work enter ";
		std::cout << "\'1\', if you want an instructor to do work enter ";
		std::cout << "\'2\'" << std::endl;
		getline(std::cin, tempWork);
	}
	chooseWork = strtol(tempWork.c_str(), &last5, 10);

	//if user wants Student to do work
	if (chooseWork == 1)
	{
		std::string nameW;
	
		std::cout << "Enter the name of the student that you want to ";
		std::cout << "do work";
		std::cout << std::endl;
		//save name to be matched to do work
		getline(std::cin, nameW);

		//steps through studentList array
		for (int n = 0; n < listNumberS; n++)
		{
			//if user input name matches object name
			if (nameW == studentList[n].getNameP())
			{
				std::cout << std::endl;
				std::cout << "Enter how many hours you would ";
				std::cout << "like " << nameW << " to work ";
				std::cout << "(max 10 hours)" << std::endl;
				
				getline(std::cin, tempHoursS);
				
				//inout validation for bounds and if integer
				while ((inputVal(tempHoursS) == false ) || 
	       			(strtol(tempHoursS.c_str(), &last5, 10) < 1)||
	      			 (strtol(tempHoursS.c_str(), &last5, 10) > 10))
				{
					std::cout << "The input entered is ";
					std::cout << "invalid" << std::endl;
					std::cout << std::endl;
					std::cout << "Enter how many hours you would ";
					std::cout << "like " << nameW << " to work ";
					std::cout << "(max 10 hours)" << std::endl;
				
					getline(std::cin, tempHoursS);
				}
				maxHoursS = strtol(tempHoursS.c_str(), &last5, 10);
				matchTrack =1;
				matchLoc =n;
			} 
		}
		//if user input name does not match any object name
		if (matchTrack == 0)
		{
			std::cout << std::endl;
			std::cout << "The entered name could not be found";
			std::cout << std::endl;
		}

		//if user input name does match an object name
		if (matchTrack == 1)
		{
			//display statement of work done
			std::cout << std::endl;
			std::cout << studentList[matchLoc].getNameP();
			std::cout << " did ";
			std::cout << studentList[matchLoc].doWork(maxHoursS); 
			std::cout << " hours of homework";

			std::cout << std::endl;
		}
	}
	
	//if user would like an Instructor to do work
	if (chooseWork ==2)
	{
		std::string nameW2;

		std::cout << "Enter the name of the instructor that you want to ";
		std::cout << "do work";
		std::cout << std::endl;

		getline(std::cin, nameW2);

		//steps through instructorList array
		for (int p = 0; p < listNumberI; p++)
		{
			//if user input name matches object name
			if (nameW2 == instructorList[p].getNameP())
			{
				std::cout << std::endl;
				std::cout << "Enter how many hours you would ";
				std::cout << "like " << nameW2 << " to work ";
				std::cout << "(max 10 hours)" << std::endl;
				
				getline(std::cin, tempHoursI);
		
				//input validation for bounds and if integer
				while ((inputVal(tempHoursI) == false ) || 
	       			(strtol(tempHoursI.c_str(), &last5, 10) < 1)||
	      			 (strtol(tempHoursI.c_str(), &last5, 10) > 10))
				{
					std::cout << "The input entered is ";
					std::cout << "invalid" << std::endl;
					std::cout << std::endl;
					std::cout << "Enter how many hours you would ";
					std::cout << "like " << nameW2 << " to work ";
					std::cout << "(max 10 hours)" << std::endl;
				
					getline(std::cin, tempHoursI);
				}
				maxHoursI = strtol(tempHoursI.c_str(), &last5, 10);
				matchTrack2 =1;
				matchLoc2 =p;
			} 
		}

		//if user input name did not match any object name
		if (matchTrack2 == 0)
		{
			std::cout << std::endl;
			std::cout << "The entered name could not be found";
			std::cout << std::endl;
		}

		//if user input name matched an object name
		if (matchTrack2 == 1)
		{
			//display statement of work done
			std::cout << std::endl;
			std::cout << "Instructor ";
			std::cout << instructorList[matchLoc2].getNameP();
			std::cout << " graded papers for ";
			std::cout <<instructorList[matchLoc2].doWork(maxHoursI);
			std::cout  << " hours";

			std::cout << std::endl;
		}
	}
}	



//Function Name: getNameStu()
//Parameters: none
//Return Value: studentName (string holding name of student1)
//Description: Returns studentName
std::string University::getNameStu()
{
	std::string studentName;

	studentName = student1.getNameP();

	return studentName;
}



//Function Name: getNameInst()
//Parameters: none
//Return Value: instructorName (string holding name of instructor1)
//Description: Return instructorName
std::string University::getNameInst()
{
	std::string instructorName;
	
	instructorName = instructor1.getNameP();

	return instructorName;
}



//Function Name: addPerson()
//Parameters: none
//Return Value: none
//Description: Adds either an new Student object to the studentList array
//		of pointers or a new Instructor object to the instructorList
//		array of pointers. Uses prompted user input to fill data 
//		members of new object.
void University::addPerson()
{
	int personTypeAP;
	int ageAP;
	double gpaAP;
	double ratingAP;
	std::string nameAP;
	std::string tempType;	//all temp strings used for data validation
	std::string tempAge;
	std::string tempGpa;
	std::string tempRating;
	char* last2;

	std::cout << std::endl;
	std::cout << "Enter '1' if you would like to add a new student or ";
	std::cout << "'2' if you would like to add a new instructor";
	std::cout << std::endl;
	getline(std::cin, tempType);

	//input validation for bounds and if integer
	while ((inputVal(tempType) == false ) || 
	       (strtol(tempType.c_str(), &last2, 10) < 1)||
	       (strtol(tempType.c_str(), &last2, 10) > 2))
	{
		std::cout << std::endl;
		std::cout << "The input entered is invalid";
		std::cout << std::endl;
		std::cout << "Enter '1' if you would like to add a new student or ";
		std::cout << "2 if you would like to add a new instructor";
		std::cout << std::endl;
		getline(std::cin, tempType);
	}
	personTypeAP = strtol(tempType.c_str(), &last2, 10);

	std::cout << std::endl;
	std::cout << "Enter the name of the person you would like to add";
	std::cout << std::endl;
	getline(std::cin, nameAP);

	std::cout << std::endl;
	std::cout << "Enter the age of the person you would like to add (max 100)";
	std::cout << std::endl;
	getline(std::cin, tempAge);

	//input validation for bounds and if int
	while ((inputVal(tempAge) == false ) || 
	       (strtol(tempAge.c_str(), &last2, 10) < 1)||
	       (strtol(tempAge.c_str(), &last2, 10) > 100))
	{
		std::cout << std::endl;
		std::cout << "The input entered is invalid";
		std::cout << std::endl;
		std::cout << "Enter the age of the person you would like to add (max 100)";
		std::cout << std::endl;
		getline(std::cin, tempAge);
	}
	ageAP = strtol(tempAge.c_str(), &last2, 10);

	if (personTypeAP == 1)	//corresponding to a new student
	{
		std::cout << std::endl;
		std::cout << "Enter the gpa of the new student (max 4.0)";
		std::cout << std::endl;
		getline(std::cin, tempGpa);
		
		//input validation for bounds and if float value
		while ((inputValF(tempGpa) == false ) || 
	       		(strtod(tempGpa.c_str(), &last2) < 0.0 )||
	       		(strtod(tempGpa.c_str(), &last2) > 4.0))
		{
			std::cout << std::endl;
			std::cout << "The input entered is invalid";
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << "Enter the gpa of the new student(max 4.0)";
			std::cout << std::endl;
			getline(std::cin, tempGpa);
		}
		gpaAP = strtod(tempGpa.c_str(), &last2);
	
		//if studentList has an 'empty' Student object
		if (studentList[0].getNameP() == "none")
		{
			studentList[0] = Student(nameAP, ageAP, gpaAP);
			
			listNumberS = 1;
		}	
	
		//if studentList is full
		else 
		{
			//create temporary studentList
			Student* tempList;
			tempList = new Student[listNumberS];

			//save all values of studentList to temporary list
			for (int i = 0; i < listNumberS; i++)
			{
				tempList[i] = studentList[i];
			}

			//create more space for studentList
			extendSList();
	
			//save all values of temporary list to studentList
			for (int j = 0; j < listNumberS; j++)
			{
				studentList[j] = tempList[j];
			}

			//delete temporary list
			delete [] tempList;
			tempList = NULL;

			//add new Student object to studentList
			studentList[listNumberS] = Student(nameAP, ageAP, gpaAP);
			listNumberS++;
		}
	}

	else if (personTypeAP == 2) //corresponds to instructor person type
	{
		std::cout << std::endl;
		std::cout << "Enter the instructor rating of the new instructor";
		std::cout << " (max 5.0)";
		std::cout << std::endl;
		getline(std::cin, tempRating);

		//input validation for bounds and if float value
		while ((inputValF(tempRating) == false ) || 
	       		(strtod(tempRating.c_str(), &last2) < 0.0 )||
	       		(strtod(tempRating.c_str(), &last2) > 5.0))
		{
			std::cout << std::endl;
			std::cout << "The input entered is invalid";
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << "Enter the instructor rating of the";
			std::cout << " new instructor (max 5.0)";
			std::cout << std::endl;
			getline(std::cin, tempRating);
		}
		ratingAP = strtod(tempRating.c_str(), &last2);
	
		//if instructorList has an 'empty' Instructor object
		if (instructorList[0].getNameP() == "none")
		{
			instructorList[0] = Instructor(nameAP, ageAP, ratingAP);
			
			listNumberI = 1;
		}	
	
		//id instructorList is full
		else 
		{
			//create temporary instructorList
			Instructor* tempList2;
			tempList2 = new Instructor[listNumberI];

			//saves each instructorList object to the temporary list
			for (int i = 0; i < listNumberI; i++)
			{
				tempList2[i] = instructorList[i];
			}

			//create more space for instructorList
			extendIList();
	
			//saves each object in temporary list to instructorList
			for (int j = 0; j < listNumberI; j++)
			{
				instructorList[j] = tempList2[j];
			}

			//delete temporary list
			delete [] tempList2;
			tempList2 = NULL;

			//add new Istructor object to instructorList
			instructorList[listNumberI] = Instructor(nameAP, ageAP, ratingAP);

			listNumberI++;
		}
	}	
}

		

//Function Name: extendSList()
//Parameters: none
//Return Value: none
//Description: Deletes current studentList and creates new studentList with
//		1 more dynamically allocated space
void University::extendSList()
{
	delete [] studentList;
	studentList = new Student[listNumberS +1];
}



//Function Name: extendIList()
//Parameters: none
//Return Value: none
//Description: Deletes current instructorList and creates new instructorList 
//		with 1 more dynamically allocated space
void University::extendIList()
{
	delete [] instructorList;
	instructorList = new Instructor[listNumberI + 1];
}



//Function Name: extendSList()
//Parameters: none
//Return Value: none
//Description: Deletes studentList and instructorList arrays of pointers
void University::deleteList()
{
	delete [] studentList;
	
	studentList = NULL;

	delete [] instructorList;
	
	instructorList = NULL;
}

