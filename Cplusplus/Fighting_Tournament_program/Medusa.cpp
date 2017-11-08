/****************************************************************************
* File Name: Medusa.cpp
* Author: David Ramirez
* Date: 5/28/17
* Description: This is the function implementation file for the Medusa
* 		class, which is derived from the Creature class. The Medusa
* 		class represents a "Medusa" creature fighter. It uses only
* 		the inhereted base class data members. For member
*		functions, it uses base class "get" functions to return class
* 		data members, the base class damage() function, 
*		and the overidden base class functions attack() and defend().
*		The Medusa class has special ability "Glare", implemented in the
*		attack() member function.
*************************************************************************/

#include <string>
#include <iostream>
#include "Medusa.hpp"



//Function name: default constructor
//Parameters: none
//Return Value: none 
//Description: Makes all data member values representative of the Medusa
//	           derived class
Medusa::Medusa()
{
	name = "Medusa";
	attStr = "2d6";
	defStr = "1d6";
	armor = 3;
	strength = 8;
	baseStrength = 8;
	special = "Glare (the Medusa turns the opponent to stone)";
}



//Function name: attack()
//Parameters: round (int representing round number)
//Return Value: int (representing attack roll)
//Description: Generates 2 random numbers between 1 and 6, sums them, and
//		returns the sum. This sum represents 2 six sided dice rolls
//		to represent an attack. This function also implements the
//		"Glare" special ability (if the sum of the attack dice rolls
//		is equal to 12, the opponent is turned to stone and Medusa
//		wins the fight.
int Medusa::attack(int round)
{
	int atkStr;
 
	atkStr = ((rand() % 6 + 1) + (rand() % 6 + 1));
	
	//if sum of attack dice rolls is 12, Glare is used
	if (atkStr == 12)
	{
		//make attack = 100 (defeats any opponent)
		atkStr = 100;

		//if round is odd, Medusa is fighter 1 (output correct
		//Glare use message
		if (round % 2 != 0)
		{
			std::cout << std::endl;
			std::cout << "Player 1's fighter, the Medusa, turned Player 1's fighter";
			std::cout << " into stone using Glare!!";
			std::cout << std::endl;
		}

		//if round is even, Medusa is fighter 2 (output correct
		//Glare use message
		if (round % 2 == 0)
		{
			std::cout << std::endl;
			std::cout << "Player 2's fighter, the Medusa, turned Player 1's fighter";
			std::cout << " into stone using Glare!!";
			std::cout << std::endl;
		}
	}
	
	//return 100 if Glare is used, return sum of dice rolls if not
	return atkStr;
}



//Function name: defend()
//Parameters: def (int representing attack roll of opponent)
//	          round (int representing round number)
//Return Value: int (representing opponent attack roll minus Barbarian defense
//		        roll)
//Description: Generates 1 random number between 1 and 6 to represent defense
//	           roll of 1 six sided die. Subtracts the 1 defense roll number
//	           from the def paramteter and returns the difference, 
//	           representing damage done after defending. 
int Medusa::defend(int def, int round)
{
	int dTaken;

	dTaken = (def - (rand() % 6 + 1));

	//makes sure damage is not negative
	if (dTaken < 0)
	{
		dTaken = 0;
	}

	return dTaken;
}




