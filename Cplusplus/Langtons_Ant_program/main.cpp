/****************************************************************************
 * File Name: main.cpp
 * Author: David Ramirez
 * Date: 4/16/17
 * Description: This is the client file for the Langton's Ant program. It's
 * 		only content is the main function. The main function uses
 * 		the menu function to select how the user would like to start
 * 		the program or if the user would like to exit the program.
 * 		It then uses the Ant class to create an object and modify
 * 		the object based on user input using Ant class functions. 
 * 		The main function determines the order of Ant class 
 * 		functions in order to demonstrate and output a demonstration
 * 		of Langton's Ant. 
 * *************************************************************************/




#include "Board.hpp"
#include "Ant.hpp"
#include "menu.hpp"
#include <iostream>
#include <ctime>



int main()
{
	int rowSize = 51;      //set to 51 or 10001 so that the while loop to
	int colSize = 51;      //check correct input is activated initially
	int steps = 10001;
	int rowLoc = 51;
	int colLoc = 51;
	int option;

	option = menu();	//calls menu to select value for option

	if (option == 3)	//corresponds to quit option in menu
	{
		return 0;
	}

	//the following block is the output for introducing the program
	std::cout << std::endl << std::endl;
	std::cout << "Welcome to a demonstration of Langton's ant,\n";
	std::cout << "created by David Ramirez for project 1 in CS 162.";
	std::cout << std::endl << std::endl;
	std::cout << "**This assignment contains the required code \n";
	std::cout << "for extra credit: option for random ant location.**";
	std::cout << std::endl << std::endl;
	std::cout << "Please press \"Enter\" to continue." ;
	std::cout << std::endl << std::endl;
	std::cin.ignore();
	std::cin.ignore();

	//ask user for size of board and save input 
	while (((rowSize > 50) || (rowSize < 2))  || 
               ((colSize > 50) || (colSize < 2)))   // 2 < input >= 50
	{	
		std::cout << "Please enter the size of the board. ";
		std::cout << "(from 2 to 50 spaces)" << std::endl;

		std::cout << "Rows: ";				 					    
 		std::cin >> rowSize; 	
		std::cout << std::endl;

		std::cout << "Columns: ";	//prompts and saves column 
		std::cin >> colSize; 		//size
		std::cout << std::endl;

		//provides message if input for rowSize or colSize is invalid
		if (((rowSize > 50) || (rowSize < 2))  || 
		    ((colSize > 50) || (colSize < 2)))	 
		{								
			std::cout << "Please enter a valid size."; 			
			std::cout << std::endl;	
		}	
	}

	Ant ant1(rowSize,colSize);

	//ask user for number of steps and save input
	while ((steps > 10000) || (steps < 1))	// 1 < input >= 50
	{
		std::cout << "Please enter the number of steps you "; 		
		std::cout << "would like Langton's ";
		std::cout << "ant to take. (from 1 to 10,000 steps)";				
     		std::cout << std:: endl;
		std::cin >> steps;							
	if ((steps > 10000) || (steps < 1))	//provides message if input 
	{						//for steps is invalid
		std::cout << "Please enter a valid number of steps.";		        		 
	  	std::cout << std::endl;
	}
	}	

	//ask user for starting location of ant and save input
	while (((rowLoc >= rowSize) || (rowLoc < 0))  ||
 	       ((colLoc >= colSize) || (colLoc < 0)))         // -1 < input >= 50

	{	
		if (option == 1)	//corresponds to generate random ant
		{			//location in menu
			unsigned seed = time(0);	//generate random location
			srand(seed);			//for ant
			rowLoc = rand() % (rowSize-1) + (1);
			colLoc = rand() % (colSize-1) + (1);
		}
		
		if (option == 2)	//corresponds to choose custom ant
		{			//location in menu
			std::cout << "Please enter a location on the board ";
			std::cout << "for Langton's ant to start in. ";
			std::cout << std::endl;
			std::cout << "(row: from 0 to " << rowSize -1 << ")";			
			std::cout << std::endl;
			std::cout << "(column: from 0 to " << colSize-1 << ")";
			std::cout << std::endl;
	
			std::cout << "Row number: ";	//prompts and saves 
			std::cin >> rowLoc;		//row location	
			std::cout << std::endl;
	
			std::cout << "Column number: ";	//prompts and saves 
			std::cin >> colLoc;		//column location
			std::cout << std::endl;

		//provides message if input to rowLoc or colLoc is invalid
			if (((rowLoc >= rowSize) || (rowLoc < 0))  ||
	    		    ((colLoc >= colSize) || (colLoc < 0)))		
			{
				std::cout << "Please enter a valid location on";		
				std::cout << " the board." << std::endl;
				std::cout << std::endl;
			}
		}
	}

	ant1.start(rowLoc, colLoc);	//calls start function of Ant class
					//to place the ant on the board
	//iterates Langdon's ant for specified number of steps
	for (int i = 0; i < steps; i++)
	{	
		if (i == 0)	//if on the first step
		{
		std::cout << "This is the initial placement of the ant.";
		std::cout << std::endl;
		ant1.printAnt();		//prints initial placement of ant
		std::cout << std::endl;

		ant1.initialNorth();		//completes first move (ant 
						//attempts to move north)
		std::cout << "This is the result of step 1:";
		std::cout << std::endl;
		ant1.printAnt();		//print board and location of ant 
		std::cout << std::endl;		//after first move
		}
		
		if (i > 0)	//if after the first step
		{
		std::cout << "This is the result of step " << i+1 << ":";
		std::cout << std::endl;

		ant1.chooseDir();	//choose direction for next move
		ant1.moveDir();		//make next move based on direction
	
		ant1.printAnt();	//print board and location of ant
		std::cout << std::endl;	//after the move
		std::cout << std::endl;
		}
		
		std::cout << std::endl;		
	}

	return 0;
}
