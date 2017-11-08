/****************************************************************************
 * File Name: menu.cpp
 * Author: David Ramirez
 * Date: 6/4/17
 * Description: This is the implementation file for the menu1(), menu2(),
 * menu3(), and menu4() functions. The menu1(), menu2(), and menu3() functions
 * are used by the main() function to prompt and return user integer input
 * for rounds the number of rounds to iterate the program, the chance
 * to add a number to the queue, and the chance to remove a number from the 
 * queue. The menu4() function is used by the main() funtion to prompt and 
 * return user string input for displaying the palindrome. 
 * *************************************************************************/

#include <iostream>
#include "inputVal.hpp"
#include "menu.hpp"



//Function name: menu1()
//Parameters: none
//Return Value: int (user input) 
//Description: prompts and returns user integer input for the number of rounds
//to iterate the queue portion of the program
int menu1()
{
	int choose;
	std::string inputM1;
	char* last3;

	std::cout << std::endl;
	std::cout << "Enter how many rounds you would like to run the simulation for (max 1000):";
	std::cout << std::endl;
	getline(std::cin, inputM1);

	while ((inputVal(inputM1) == false ) || 
	(strtol(inputM1.c_str(), &last3, 10) < 1)||
	(strtol(inputM1.c_str(), &last3, 10) > 1000))
	{
		std::cout << std::endl;
		std::cout << "Entered input is invalid, try again.";
		std::cout << std::endl;

		getline(std::cin, inputM1);
	}
	
	choose = strtol(inputM1.c_str(), &last3, 10);

	return choose;
}



//Function name: menu2()
//Parameters: none
//Return Value: int (user input) 
//Description: prompts and returns user integer input for the percentage
//chance to include generated number in the queue
int menu2()
{
	int choose;
	std::string inputM1;
	char* last3;

	std::cout << std::endl;
	std::cout << "Enter a percentage for the chance to place generated number in buffer (max 100):";
	std::cout << std::endl;
	getline(std::cin, inputM1);

	while ((inputVal(inputM1) == false ) || 
	(strtol(inputM1.c_str(), &last3, 10) < 0)||
	(strtol(inputM1.c_str(), &last3, 10) > 100))
	{
		std::cout << std::endl;
		std::cout << "Entered input is invalid, try again.";
		std::cout << std::endl;

		getline(std::cin, inputM1);
	}
	
	choose = strtol(inputM1.c_str(), &last3, 10);

	return choose;
}



//Function name: menu3()
//Parameters: none
//Return Value: int (user input) 
//Description: prompts and returns user integer input for the percentage
//chance to remove generated number in the queue
int menu3()
{
	int choose;
	std::string inputM1;
	char* last3;

	std::cout << std::endl;
	std::cout << "Enter a percentage for the chance to remove generated number from buffer";
	std::cout << std::endl << "(max 100):";
	std::cout << std::endl;
	getline(std::cin, inputM1);

	while ((inputVal(inputM1) == false ) || 
	(strtol(inputM1.c_str(), &last3, 10) < 0)||
	(strtol(inputM1.c_str(), &last3, 10) > 100))
	{
		std::cout << std::endl;
		std::cout << "Entered input is invalid, try again.";
		std::cout << std::endl;

		getline(std::cin, inputM1);
	}
	
	choose = strtol(inputM1.c_str(), &last3, 10);

	return choose;
}



//Function name: menu4()
//Parameters: none
//Return Value: int (user input) 
//Description: prompts and returns user string input for displaying the
//palindrome of the input using a stack
std::string menu4()
{
	std::string word;
	std::cout << std::endl;
	std::cout << "Enter a word to show it's palindrome:" << std::endl;
	getline(std::cin, word);

	return word;
}	
	
