/****************************************************************************
 * File Name: menu.cpp
 * Author: David Ramirez
 * Date: 4/30/17
 * Description: This file contains implementation of the main() function. 
 * 		The main function uses the menu() function to get user
 * 		input and calls a University class member function 
 * 		based on that input. 
 * *************************************************************************/

#include <iostream>
#include "menu.hpp"
#include "University.hpp"



//Function Name: main()
//Parameters: none
//Return Value: none
//Description: Uses the menu() function to obtain user input and calls a 
//		University class function based on the input. Uses a 
//		while loop to keep the program from ending before the 
//		user chooses to quit and uses if statements to determine
//		function to call from user input.
int main()
{
	int progOption = 0;
	int personOption;
	int check = 0;
	University university1;

	std::cout << std::endl;
	std::cout << "Welcome to the program for lab 4, created by ";
	std::cout << std::endl;
	std::cout << "David Ramirez";
	std::cout << std::endl << std::endl;
	std::cout << "This program contains the extra credit option of ";
	std::cout << "saving and loading person contents. This option can ";
	std::cout << "be accessed via the menu.";
	std::cout << std::endl;
		
	//while user does not choose to quit
	while (progOption != 7)
	{
		if (check == 0)
		{
			progOption = menu(0, university1);
			check ==1;
		}
		
		if (progOption == 1)
		{
			university1.printBuildings();
		}
	
		if (progOption == 2)
		{
			university1.printPeople();
		}

		//opens person menu
		if (progOption == 3)
		{
			personOption = menu(1, university1);
				
			if (personOption == 1)
			{
				university1.s1DoWork();
			}
				
			if (personOption == 2)
			{
				university1.i1DoWork();
			}

			if (personOption == 3)
			{
				university1.otherDoWork();
			}
		}

		if (progOption == 4)
		{
			university1.addPerson();
		}
		
		if (progOption == 5)
		{
			university1.save();
		}

		if (progOption == 6)
		{
			university1.load();
		}

		check = 0;
			
	}

	//delete all dynamically allocated memory
	university1.deleteList();
	
	return 0;
}
