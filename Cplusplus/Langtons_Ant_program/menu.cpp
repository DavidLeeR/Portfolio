/****************************************************************************
 * File Name: menu.cpp
 * Author: David Ramirez
 * Date: 4/16/17
 * Description: This is the implementation file for the menu function. The
 * 		menu function provides the user with an initialization 
 * 		menu for the Langton's Ant program. It returns an int
 * 		to main represting the user's choice. 
 * *************************************************************************/



#include <iostream>
#include "menu.hpp"

/* This is the menu function. It presents the user with three options and 
 * accepts user input corresponding to which option is chosen. It uses a 
 * while loop and an if statement to validate input. It uses various
 * if statements to execute the users choice and return an int value
 * to main representing the choice of the user. This function has no return
 * values. */
int menu ()
{
	int choose;
	int quit = 0;
	int optionM = 0;


	while ((quit == 0) || (choose < 1) || (choose > 3)) 
	{
		std::cout << "Please choose an option from the menu:" << std::endl;
		std::cout << "1: start Langton's Ant program" << std::endl;
		std::cout << "2: choose to start the ant in a random" << std::endl;
		std::cout << "   location or enter a custom location," << std::endl;
		std::cout << "   then start the program." << std::endl;
		std::cout << "3: quit program" << std::endl;
		std::cout << std::endl;

		std::cin >> choose;

		if ((choose < 1) || (choose > 3))
		{
			std::cout << "Please enter a valid choice.";
			std::cout << std::endl;
			std::cout << std::endl;
		}
	
		if (choose == 1)
		{
			optionM = 2;
			return optionM;	//returns user choice to main
		}

		if (choose == 2)
		{

			//implementation of option to generate random location for ant
			//to start in
			while ((optionM < 1) || (optionM > 2))	
			{
				std::cout << "Please enter \"1\" to generate a random ";
				std::cout <<"location for the ant to start in or enter";
				std::cout << " \"2\" to manually enter a location for ";
				std::cout << "the ant to start in.";
				std::cout << std::endl;
				std::cin >> optionM;
		
				if ((optionM < 1) || (optionM > 2))	
				{ 
					std::cout << "Please enter either a valid ";
					std::cout << "number.";
					std::cout << std::endl;
				}
			}	
			
			return optionM;	//returns user choice to main
		}
		
		if (choose == 3)
		{
			optionM = 3;
			return optionM;	//returns user chouce to main
		}
	}

}




