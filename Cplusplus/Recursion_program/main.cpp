/****************************************************************************
 * File Name: main.cpp
 * Author: David Ramirez
 * Date: 5/7/17
 * Description: This file contains implementation of the main() function. 
 * 		The main function uses the menu() function to get user
 * 		input and calls a one of three recursive functions
 * 		(reverse(), sum(), or tri()) based on that input. 
 * *************************************************************************/

#include <string>
#include <iostream>
#include "recursion.hpp"
#include "menu.hpp"
#include "inputVal.hpp"




int main()
{
	int option;
	int count;
	int number;
	std::string revString;
	std::string tempCount = "11";
	std::string tempNumber = "101";
	char* last2;

	
	//if user has not selected to quit
	while (option != 4)
	{
		//get user choice from menu()
		option = menu();

		//corresponding to 'execute reverse() function'
		if (option == 1)
		{
			std::cout << std::endl;
			std::cout << "Enter a string that you would like to ";
			std::cout << "have reversed";
			std::cout << std::endl;

			getline(std::cin, revString);

			std::cout << std::endl;
			std::cout << "Here is the reversed string: ";
			std::cout << std::endl;

			reverse(revString);
		}

		//corresponding to 'execute sum() function'
		if (option == 2)
		{
			//input validation for bounds and if int
			while ((inputVal(tempCount) == false ) || 
	 		   (strtol(tempCount.c_str(), &last2, 10) < 1)||
	   		   (strtol(tempCount.c_str(), &last2, 10) > 10))
			{
				std::cout << std::endl;
				std::cout << "Enter a number representing how many ";
				std::cout << "integers you would like to sum (max 10)";
				std::cout << std::endl;

				getline(std::cin, tempCount);
			}
			//save validated input in 'count'
			count = strtol(tempCount.c_str(), &last2, 10);

			//create array based on user input ('count')
			int passNumbers[count];

			std::cout << std::endl;
			std::cout << "Enter the values of the integers";
			std::cout << std::endl;

			//iterates for number of times given by 'count'
			for (int a = 0; a < count; a++)
			{
				std::cout << std::endl;
				std::cout << "For position " << a;
				std::cout << ": ";
				std::cin >> passNumbers[a];
				std::cout << std::endl;
			}

			std::cout << std::endl;
			std::cout << "The sum of the entered numbers is: ";
			std::cout << sum(passNumbers, count);
			std::cout << std::endl;

			std::cin.clear();
			std::cin.ignore();

			//make tempCount out of bounds to execute while loop
			//if option 2 is selected again
			tempCount = "11";
		}
		
		//corresponds to 'execute tri() function'
		if (option == 3)
		{
			//input validation for bounds and if int
			while ((inputVal(tempNumber) == false ) || 
	    		(strtol(tempNumber.c_str(), &last2, 10) < 1)||
	    		(strtol(tempNumber.c_str(), &last2, 10) > 100))
			{
				std::cout << std::endl;
				std::cout << "Enter an integer to calculate";
				std::cout << " it's triangular number (max 100)";
				std::cout << std::endl;
				
				getline(std::cin, tempNumber);
			}
			//save validated input to 'number'
			number = strtol(tempNumber.c_str(), &last2, 10);

			std::cout << std::endl;
			std::cout << "The triangular number for the entered ";
			std::cout << "integer is: " << tri(number);
			std::cout << std::endl;
	
			//make tempNumber out of bounds to execute while loop
			//if option 3 is selected again
			tempNumber = "101";
		}		
	}
	
	return 0;
}
