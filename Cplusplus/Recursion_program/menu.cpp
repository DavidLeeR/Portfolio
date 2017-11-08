/****************************************************************************
 * File Name: menu.cpp
 * Author: David Ramirez
 * Date: 5/7/17
 * Description: This is the implementation file for the menu() function. This 
 * 		function provides user feedback to the main() function in
 * 		in order for the user to control the next function to 
 * 		execute. 
 * *************************************************************************/

#include <string>
#include <iostream>
#include "inputVal.hpp"
#include "menu.hpp"



//Function Name: menu()
//Parameters: none
//Return Value: integer (integer representing user choice in program 
//		next function execution)
//Description: Prompts the user with options for the functions the program
//		can execute and returns an integer representing this choice
//		to the main() function
int menu ()
{
	int choose;
	std::string inputM1;
	char* last3;

	std::cout << std::endl;		
	std::cout << "Please choose an option from the program menu:";
	std::cout << std::endl;
	std::cout << "1: execute the reverse() function to reverse a string";
	std::cout << std::endl;
	std::cout << "2: execute the sum() function to calculate the sum of an";
	std::cout << " array" << std::endl;
	std::cout << "3: execute the tri() function to calculate a triangular";
	std::cout << " number" << std::endl;
	std::cout << "4: quit the program" << std::endl;
	
	getline(std::cin, inputM1);
	std::cout << std::endl;
		
	std::cin.clear();
		
		//validates user input to be an integer and in bounds
	while ((inputVal(inputM1) == false ) || 
	    (strtol(inputM1.c_str(), &last3, 10) < 1)||
	    (strtol(inputM1.c_str(), &last3, 10) > 4))
	{
		std::cout << std::endl;
		std::cout << "The input entered is invalid";
		std::cout << std::endl << std::endl;
		std::cout << "Please choose an option from the program menu:";
		std::cout << std::endl;
		std::cout << "1: execute the reverse() function to reverse a string";
		std::cout << std::endl;
		std::cout << "2: execute the sum() function to calculate the sum of an";
		std::cout << " array" << std::endl;
		std::cout << "3: execute the tri() function to calculate a triangular";
		std::cout << " number" << std::endl;
		std::cout << "4: quit the program" << std::endl;
		

		getline(std::cin, inputM1);
		std::cout << std::endl;

		std::cin.clear();
	}
	choose = strtol(inputM1.c_str(), &last3, 10);	
			
	//corresponds to 'execute reverse()'
	if (choose == 1)
	{
		return 1;	//returns user choice to main
	}

	//corresponds to 'execute sum()'
	if (choose == 2)
	{
		return 2;	//returns user choice to main
	}
	
	//corresponds to 'execute tri()'
	if (choose == 3)
	{
		return 3;
	}
	//corresponds to 'quit program'
	if (choose == 4)
	{
		return 4;
	}
}
