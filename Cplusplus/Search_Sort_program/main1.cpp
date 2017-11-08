/****************************************************************************
 * File Name: main1.cpp
 * Author: David Ramirez
 * Date: 5/28/17
 * Description: This is the implementation file for the main() function of 
 * 		the first program for lab 8. This program reads four files
 * 		(named data1.txt, data2.txt, data3.txt, and data4.txt) and
 * 		uses a linear search algorithm to display whether each file
 * 		contains the target value, which is set by the user. The 
 * 		main() function uses the inputVal() function to validate
 * 		user input for the target value. A while loop containing a 
 * 		series of if statements allow the main() function to read 
 * 		all 4 files. 
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
	char* last;

	//display intro
	std::cout << "This is the first program for lab 8, using a linear search.";
	std::cout << std::endl << std::endl;

	std::cout << "Enter a integer from 0 to 100 (inclusive) to search for: ";
	getline(std::cin, tempTarget);

	//input validation for if int and range
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
	std::ifstream inputFile;

	//iterate 4 times to read the 4 input files
	for (int i=0; i < 4; i++)
	{
		//if this is the first iteration, open and read first file
		if (i == 0)
		{
			inputFile.open("data1.txt");
			title = "File 1";
		}

		//if this is the second iteration, open and read second file	
		if (i == 1)
		{
			inputFile.open("data2.txt");
			title = "File 2";
		}

		//if this is the third iteration, open and read third file
		if (i == 2)
		{
			inputFile.open("data3.txt");
			title = "File 3";
		}

		//if this is the fourth iteration, open and read fourth file
		if (i == 3)
		{
			inputFile.open("data4.txt");
			title = "File 4";
		}
		
		//while the end of inputFile has not been reached
		while (inputFile >> fileIn)
		{	
			//This linear search algorithm is modified code 
			//from the "search" powerpoint slide 6 of the 
			//week 8 readings for CS162 
			
			//if value read matches target value
			if (fileIn == target)
			{
				//display found message
				std::cout << title << " target value " << target;
				std::cout << " found." << std::endl;
				std::cout << std::endl;

				//increment so not found message not displayed
				check = 1;
			}
		}

		//if the target value was ot found
		if (check == 0)
		{
			//display not found message
			std::cout << title << " target value " << target;
			std::cout << " not found." << std::endl;
			std::cout << std::endl;
		}
	
		//reset check to 0
		check = 0;

		//close input file
		inputFile.close();
	}
	
	//end program
	return 0;
}
				
