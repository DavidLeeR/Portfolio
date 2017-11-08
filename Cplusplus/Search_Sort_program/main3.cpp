/****************************************************************************
 * File Name: main3.cpp
 * Author: David Ramirez
 * Date: 5/28/17
 * Description: This is the implementation file for the main() function of 
 * 		the third program for lab 8. This program reads one file
 * 		(named sorted2.txt) and uses a binary search algorithm to 
 * 		display whether the file contains the target value, which 
 * 		is set by the user. The main() function uses the inputVal() 
 * 		function to validate user input for the target value. 
  *************************************************************************/




#include "inputVal.hpp"
#include <string>
#include <iostream>
#include <fstream>  


int main()
{
	std::string title;
	std::string tempTarget;
	int target;
	int fileIn;
	int check;
	int list[10];
	char* last;

	//display intro
	std::cout << "This is the third program for lab 8, using a binary search.";
	std::cout << std::endl << std::endl;

	std::cout << "Enter an integer from 0 to 100 (inclusive) to search for: ";
	getline(std::cin, tempTarget);

	//input validation for if in and in range
	while ((inputVal(tempTarget) == false ) || 
	    (strtol(tempTarget.c_str(), &last, 10) < 0)||
	    (strtol(tempTarget.c_str(), &last, 10) > 100))
	{
		std::cout << "Entered input is invalid, try again.";
		std::cout << std::endl;

		getline(std::cin, tempTarget);
	}

	target = strtol(tempTarget.c_str(), &last, 10);
	std::cout << std::endl;
	
	//declare input file variable name
	std::ifstream inputFile;

	//open input file
	inputFile.open("sorted2.txt");
	title = "File 1";
		
	//read contents of input file into array list
	for (int i = 0; i < 10; i++)
	{
		inputFile >> list[i];
	}
	
	//This binary search algorithm is modified code 
	//from the "Searching" powerpoint slide 11 of the 
	//week 8 readings for CS162 
	int low = 0;
	int high = 9;
	while (low <= high)
	{
		int mid = (low + high)/2;
		int diff = list[mid] - target;

		//middle of array equals target value
		if (diff == 0)
		{
			//display target found message
			std::cout << title << " contains target value ";
			std::cout << target << "." << std::endl;

			//increment check to target not found message not 
			//displayed
			check = 1;
		
			break;
		}

		//middle of the array is less than target value
		else if (diff < 0)
		{
			low = mid + 1;
		}
		
		
		else
		{
			high = mid -1;
		}
	}

	if (check ==0)
	{
		//display target not found message
		std::cout << title << " does not contain target value ";
		std::cout << target << "." << std::endl;
	}

	//close input file
	inputFile.close();
	return 0;

}
						
