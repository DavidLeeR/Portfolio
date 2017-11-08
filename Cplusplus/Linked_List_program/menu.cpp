/****************************************************************************
 * File Name: menu.cpp
 * Author: David Ramirez
 * Date: 5/14/17
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
	
	//output prompt for linked list options
	std::cout << std::endl;
	std::cout << "Make a choice from the following menu: ";
	std::cout << std::endl;		
	std::cout << "1: add new node to head of list" << std::endl;
	std::cout << "2: add new node to tail of list" << std::endl;
	std::cout << "3: delete from head of list" << std::endl;
	std::cout << "4: delete from tail of list" << std::endl;
	std::cout << "5: reversely traverse list and print" << std::endl;
	std::cout << "6: print contents of node at head of list" << std::endl;
	std::cout << "7: print contents of node at tail of list" << std::endl;
	std::cout << "8: quit program" << std::endl;
	//save as string for input validation
	getline(std::cin, inputM1);
	std::cout << std::endl;
		
	std::cin.clear();
		
	//validates user input to be an integer and in bounds
	while ((inputVal(inputM1) == false ) || 
	    (strtol(inputM1.c_str(), &last3, 10) < 1)||
	    (strtol(inputM1.c_str(), &last3, 10) > 8))
	{	
		//output invalid input message and output options again
		std::cout << std::endl;
		std::cout << "The input entered is invalid";
		std::cout << std::endl << std::endl;		
		std::cout << "Make a choice from the following menu: ";
		std::cout << std::endl;		
		std::cout << "1: add new node to head of list" << std::endl;
		std::cout << "2: add new node to tail of list" << std::endl;
		std::cout << "3: delete from head of list" << std::endl;
		std::cout << "4: delete from tail of list" << std::endl;
		std::cout << "5: reversely traverse list and print" << std::endl;
		std::cout << "6: print contents of node at head of list" << std::endl;
		std::cout << "7: print contents of node at tail of list" << std::endl;
		std::cout << "8: quit program" << std::endl;
		
		getline(std::cin, inputM1);
		std::cout << std::endl;

		std::cin.clear();
	}
	//save input after validation
	choose = strtol(inputM1.c_str(), &last3, 10);	
			
	//corresponds to 'add new node to head of list' 
	if (choose == 1)
	{
		return 1;	//returns user choice to main
	}

	//corresponds to 'add new node to tail of list'
	if (choose == 2)
	{
		return 2;	//returns user choice to main
	}
	
	//corresponds to 'delete from head of list'
	if (choose == 3)
	{
		return 3;	//return user choice to main
	}

	//corresponds to 'dete from tail of list'
	if (choose == 4)
	{
		return 4;	//return user choice to main
	}

	//corresponds to 'reversely traverse list and print'
	if (choose ==5)
	{
		return 5;	//return user choice to main
	}

	//corresponds to 'print head of list'
	if (choose == 6)
	{
		return 6;	//return user choice to main
	}

	//corresponds to 'print tail of list'
	if (choose == 7)
	{
		return 7;	//return user choice to main
	}

	//corresponds to 'quit program'
	if (choose == 8)
	{
		return 8;	//return user choice to main
	}
}


int menu2()
{
	int choose;
	std::string inputM1;
	char* last3;
	
	//output prompt for linked list options
	std::cout << std::endl;
	std::cout << "Make a choice from the following menu: ";
	std::cout << std::endl;		
	std::cout << "1: start with empty list" << std::endl;
	std::cout << "2: load list from text file" << std::endl;
	//save as string for input validation
	getline(std::cin, inputM1);
	std::cout << std::endl;
		
	std::cin.clear();
		
	//validates user input to be an integer and in bounds
	while ((inputVal(inputM1) == false ) || 
	    (strtol(inputM1.c_str(), &last3, 10) < 1)||
	    (strtol(inputM1.c_str(), &last3, 10) > 2))
	{	
		//output invalid input message and output options again
		std::cout << std::endl;
		std::cout << "The input entered is invalid";
		std::cout << std::endl << std::endl;		
		std::cout << "Make a choice from the following menu: ";
		std::cout << std::endl;		
		std::cout << "1: start with empty list" << std::endl;
		std::cout << "2: load list from text file" << std::endl;

		getline(std::cin, inputM1);
		std::cout << std::endl;

		std::cin.clear();
	}
	//save input after validation
	choose = strtol(inputM1.c_str(), &last3, 10);	
			
	//corresponds to 'start with empty list' 
	if (choose == 1)
	{
		return 1;	//returns user choice to main
	}

	//corresponds to 'load list from file'
	if (choose == 2)
	{
		return 2;	//returns user choice to main
	}
}
