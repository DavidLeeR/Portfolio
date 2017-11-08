/****************************************************************************
 * File Name: menu.hpp
 * Author: David Ramirez
 * Date: 5/28/17
 * Description: This is the implementation file for the menu() functions. These 
 * 		functions provides user feedback to various Tournament class 
 * 		member functions in order for the user to control program input
 * 		as well as function execution. The menu4() function is used by
 * 		main().
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

	//display list of fighters
	std::cout << std::endl;		
	std::cout << "1: Vampire" << std::endl;
	std::cout << "2: Barbarian" << std::endl;
	std::cout << "3: Blue Men" << std::endl;
	std::cout << "4: Medusa" << std::endl;
	std::cout << "5: Harry Potter" << std::endl;
	
	getline(std::cin, inputM1);
	std::cout << std::endl;
		
	std::cin.clear();
		
	//validates user input to be an integer and in bounds
	while ((inputVal(inputM1) == false ) || 
	    (strtol(inputM1.c_str(), &last3, 10) < 1)||
	    (strtol(inputM1.c_str(), &last3, 10) > 5))
	{	
		//display invalid input message and display fighter list again
		std::cout << std::endl;
		std::cout << "The input entered is invalid";
		std::cout << std::endl << std::endl;		
		std::cout << "Please choose a fighter from the list:"; 
		std::cout <<  std::endl;
		std::cout << "1: Vampire" << std::endl;
		std::cout << "2: Barbarian" << std::endl;
		std::cout << "3: Blue Men" << std::endl;
		std::cout << "4: Medusa" << std::endl;
		std::cout << "5: Harry Potter" << std::endl;
		
		//save input in string for data validation
		getline(std::cin, inputM1);
		std::cout << std::endl;

		std::cin.clear();
	}
	//save user choice after data validation
	choose = strtol(inputM1.c_str(), &last3, 10);	
			
	//corresponds to Vampire
	if (choose == 1)
	{
		return 1;	//returns user choice to main
	}

	//corresponds to to Barbarian
	if (choose == 2)
	{
		return 2;	//returns user choice to main
	}
	
	//corresponds to Blue Men
	if (choose == 3)
	{
		return 3;	//returns user choice to main

	}
	//corresponds to Medusa
	if (choose == 4)
	{
		return 4;	//returns user choice to main

	}

	//corresponds to Harry Potter
	if (choose ==5)
	{
		return 5;	//returns user choice to main

	}
}



//Function Name: menu2()
//Parameters: player (integer representing which player)
//Return Value: integer (representing amount of fighters for a team)
//Description: Prompts and and returns user input for amount of fighters on a 
//team (team designated by int parameter)
int menu2(int player)
{
	int choose;
	std::string inputM1;
	char* last3;

	//display correct message for player 1
	if (player == 1)
	{
		std::cout << std::endl;
		std::cout << "Enter how many fighters you would like Player 1 to have (max 10).";
		std::cout << std::endl;
	}

	//display correct message for player 2
	else if (player == 2)
	{
		std::cout << std::endl;
		std::cout << "Enter how many fighters you would like Player 2 to have (max 10).";
		std::cout << std::endl;
	}

	getline(std::cin, inputM1);
	std::cout << std::endl;

	std::cin.clear();

	//validates user input to be an integer and in bounds
	while ((inputVal(inputM1) == false) ||
		(strtol(inputM1.c_str(), &last3, 10) < 1) ||
		(strtol(inputM1.c_str(), &last3, 10) > 10))
	{
		std::cout << std::endl;
		std::cout << "Entered input invalid, try again.";
		std::cout << std::endl;

		//display correct message for player 1
		if (player == 1)
		{
			std::cout << std::endl;
			std::cout << "Enter how many fighters you would like Player 1 to have (max 10).";
				std::cout << std::endl;
		}

		//display correct message for player 2
		else if (player == 2)
		{
			std::cout << std::endl;
			std::cout << "Enter how many fighters you would like Player 2 to have (max 10).";
			std::cout << std::endl;
		}
	}

	choose = strtol(inputM1.c_str(), &last3, 10);

	return choose;

}



//Function Name: menu3()
//Parameters: none
//Return Value: integer (representing whether to show loser list or close
//		program)
//Description: Prompts and and returns user input for whether to show the 
//list of losers and close to the program, or just close the program. 
int menu3()
{
	int choose;
	std::string inputM1;
	char* last3;
	
	//display prompt for displaying loser list or ending program
	std::cout << std::endl;
	std::cout << "The tournament is over." << std::endl;
	std::cout << "Enter \"1\" to display the list of losers." << std::endl;
	std::cout << "Enter \"0\" to continue without displaying list of losers." << std::endl;

	getline(std::cin, inputM1);
	std::cout << std::endl;

	//input validation for if int and within bounds
	while ((inputVal(inputM1) == false) ||
	(strtol(inputM1.c_str(), &last3, 10) < 0) ||
	(strtol(inputM1.c_str(), &last3, 10) > 1))
	{
		std::cout << std::endl;
		std::cout << "Entered input invalid, try again.";
		std::cout << std::endl;

		getline(std::cin, inputM1);
	}

	//save user choice as choose after validation
	choose = strtol(inputM1.c_str(), &last3, 10);

	//return user choice
	return choose;
}
	
//Function Name: menu4()
//Parameters: none
//Return Value: integer (representing whether start new tournament or end program)
//Description: Prompts and and returns user input for whether to start a 
//new tournament or quit the program.
int menu4()
{
	int choose;
	std::string inputM1;
	char* last3;

	//display user option
	std::cout << std::endl;
	std::cout << "Enter \"1\" to start a new tournament.";
	std::cout << std::endl;
	std::cout << "Enter \"0\" to end the program.";
	std::cout << std::endl;
	
	//get user input as a string for input validation
	getline(std::cin, inputM1);	

	//input validation for if int and within bounds
	while ((inputVal(inputM1) == false) ||
	(strtol(inputM1.c_str(), &last3, 10) < 0) ||
	(strtol(inputM1.c_str(), &last3, 10) > 1))
	{
		//display incorrect input message
		std::cout << std::endl;
		std::cout << "Entered input invalid, try again.";
		std::cout << std::endl;

		//get user input
		getline(std::cin, inputM1);
	}
	//save user input as int after validation
	choose = strtol(inputM1.c_str(), &last3, 10); 

	//return user input
	return choose;
}

