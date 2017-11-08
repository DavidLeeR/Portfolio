/****************************************************************************
* File Name: HarryPotter.cpp
* Author: David Ramirez
* Date: 5/28/17
* Description: This is the function implementation file for the HarryPotter
* 		class, which is derived from the Creature class. The HarryPotter
* 		class represents a "Harry Potter" creature fighter. It uses
* 		the inhereted base class data members, as well as a data member 
* 		"hog", int which keeps track of the use of the special ability. 
*		For member functions, it uses the  base class "get" functions 
*		to return class data members. This class uses the overidden 
* 		base class functions attack(), defend(), and damage(). The 
* 		Harry Potter class has special ability "Hogwarts" implemented 
*		in the damage() member function.
*************************************************************************/

#include <string>
#include <iostream>
#include "HarryPotter.hpp"



//Function name: default constructor
//Parameters: none
//Return Value: none 
//Description: Makes all data member values representative of the HarryPotter
//	           derived class
HarryPotter::HarryPotter()
{
	name = "wizard Harry Potter";
	attStr = "2d6";
	defStr = "2d6";
	armor = 0;
	strength = 10;
	baseStrength = 10;
	hog = 0;
	special = "Hogwarts (Harry is revived with 20 strength points)";
}


//Function name: attack()
//Parameters: round (int representing round number)
//Return Value: int (representing attack roll)
//Description: Generates 2 random numbers between 1 and 6, sums them, and
//		returns the sum. This sum represents 2 six sided dice rolls
//		to represent an attack.
int HarryPotter::attack(int round)
{
	return ((rand() % 6 + 1) + (rand() % 6 + 1));
}


//Function name: defend()
//Parameters: def (int representing attack roll of opponent)
//	          round (int representing round number)
//Return Value: int (representing opponent attack roll minus Barbarian defense
//		        roll)
//Description: Generates 2 random numbers between 1 and 6 to represent defense
//	           roll of 2 six sided dice. Subtracts the 2 defense roll 
//	           numbers from the def paramteter and returns the difference, 
//	           representing damage done after defending. 
int HarryPotter::defend(int def, int round)
{
	int dTaken;

	dTaken = (def - ((rand() % 6 + 1) + (rand() % 6 + 1)));

	//makes sure damage is not negative
	if (dTaken < 0)
	{
		dTaken = 0;
	}

	return dTaken;
}



//Function name: damage()
//Parameters: dam (int representing damage done after defending)
//			  round (int representing round number)
//Return Value: none 
//Description: Subtracts armor from dam to represent the damage done to the 
//		creature. This function also implements the special 
//	        ability "Hogwarts", which revives Harry Potter 1 time and sets 
//		the strength points to 20. 
void HarryPotter::damage(int dam, int round)
{
	int dFelt;

	//subtract armor from damage done
	dFelt = dam - armor;
	
	//makes sure there are no negative numbers
	if (dFelt < 0)
	{
		dFelt = 0;
	}

	//subtract damage from strength points
	strength -= dFelt;

	//if strength points are below 1 and the Hogwarts special ability
	//has not yet been used, use it (set strength points to 20, hog to
	//1, and output Hogwarts message)
	if ((strength < 1) && (hog == 0))
	{
		//if round is odd, Harry Potter is fighter 2 (for outputting 
		//correct message)
		if (round % 2 != 0)
		{
			std::cout << std::endl;
			std::cout << "Player 2's fighter, the wizard Harry, Potter is ";
			std::cout << "left with 0 strength points.";
			std::cout << std::endl << std::endl;
			std::cout << "Player 2's fighter, the wizard Harry Potter, regenerated";
			std::cout << std::endl;
			std::cout << "with 20 strength";
			std::cout << " points using Hogwarts!!";
			std::cout << std::endl;
		}

		//if round is even, Harry Potter is fighter 1 (for outputting 
		//correct message)
		else if (round % 2 == 0)
		{
			std::cout << std::endl;
			std::cout << "Player 1's fighter, the wizard Harry Potter, is ";
			std::cout << "left with 0 strength points.";
			std::cout << std::endl << std::endl;
			std::cout << "Player 1's fighter, the wizard Harry Potter, regenerated";
			std::cout << std::endl;
			std::cout << "with 20 strength";
			std::cout << " points using Hogwarts!!";
			std::cout << std::endl;

		}

		//set data member strength = 20
		strength = 20;
		baseStrength = 20;

		//set data member hog to 1, so Hogwarts special ability will not
		//be used again
		hog = 1;
	}

	//makes sure that strength is never negative
	if (strength < 0)
	{
		strength = 0;
	}
}	

