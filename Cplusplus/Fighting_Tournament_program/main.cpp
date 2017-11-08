/****************************************************************************
 * File Name: main.cpp
 * Author: David Ramirez
 * Date: 5/28/17
 * Description: This is the implementation file for the main() function of 
 * 		project 4. This function is used to facilitate the simulated
 * 		tournament of 2 teams of up to 10 selected fighters. The 
 * 		main() function displays a program introductuon then uses 
 * 		Tournament class member functions to simulate the tournament.  
  *************************************************************************/



#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Queue.hpp"
#include "Tournament.hpp"
#include "menu.hpp"

int main()
{
	unsigned seed = time(0);	//create seed for random generation
	int quit = 1;
			//pointer to second fighter

	//seed random to generate random numbers later in the program
	srand(seed);
	std::cout << std::endl;
	std::cout << "Welcome to Program 4: Fighter Tournament, ";
	std::cout << "created by David Ramirez.";
	std::cout << std::endl << std::endl;

	while (quit != 0)
	{
		Tournament tournament1;
		tournament1.queueMake();
		tournament1.start();
		tournament1.ending();
		tournament1.printLoss();
	
		quit = menu4();
	}

	return 0;
}
