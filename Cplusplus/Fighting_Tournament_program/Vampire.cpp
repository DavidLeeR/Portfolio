/****************************************************************************
* File Name: Vampire.cpp
* Author: David Ramirez
* Date: 5/28/17
* Description: This is the function implementation file for the Vampire
* 		class, which is derived from the Creature class. The Vampire
* 		class represents a "Vampire" creature fighter. It uses only
* 		the inhereted base class data members. For member
*		functions, it uses base class "get" functions to return class
* 		data members, the base class damage() function,
*		and the overidden base class functions attack() and defend(). 
*		The Vampire class has special ability "Charm", implemented in 
*		the defend() member function.
*************************************************************************/

#include <string>
#include <iostream>
#include "Vampire.hpp"



//Function name: default constructor
//Parameters: none
//Return Value: none 
//Description: Makes all data member values representative of the Vampire
//	           derived class
Vampire::Vampire()
{
	name = "Vampire";
	attStr = "1d12";
	defStr = "1d6";
	armor = 1;
	strength = 18;
	baseStrength = 18;
	special = "Charm (the Vampire does not get attacked for a round)";
}



//Function name: attack()
//Parameters: round (int representing round number)
//Return Value: int (representing attack roll)
//Description: Generates 1 random numbers between 1 and 12 and
//		returns the number. This number represents 1 six sided die roll
//		to represent an attack.
int Vampire::attack(int round)
{
	return rand() % 12 + 1;
}



//Function name: defend()
//Parameters: def (int representing attack roll of opponent)
//	          round (int representing round number)
//Return Value: int (representing opponent attack roll minus Barbarian defense
//		        roll)
//Description: Generates 1 random number between 1 and 6 to represent defense
//	      roll of 1 six sided die. Subtracts the 1 defense roll number
//	      from the def paramteter and returns the difference, 
//	      representing damage done after defending. This function also
//	      contains the implementation for the "Charm" special ability
//	      (1 or 2 is randomly chosen, if 2 is chosen the opponent does
//	      no damage this turn; this happens by the damage being negated
//	      within the Vampire class)
int Vampire::defend(int def, int round)
{
	int dTaken;	
	//make charm = 1 or 2, randomly
	int charm = rand()% 2 + 1;
	
	dTaken = (def - (rand() % 6 + 1));

	//makes sure damage is not negative
	if (dTaken < 0)
	{
		dTaken = 0;
	}

	//if charm == 2, the Charm special ability is used
	if (charm == 2)
	{
		//if round is odd, Vampire is fighter 2 (output correct
		//Charm use message
		if (round % 2 != 0)
		{
			std::cout << std::endl;
			std::cout << "Player 2's fighter, the Vampire, used Charm!!";
			std::cout << std::endl;
		}

		//if round is even, Vampire is fighter 1 (output correct
		//Charm use message
		if (round % 2 == 0)
		{
			std::cout << std::endl;
			std::cout << "Player 1's fighter, the Vampire, used Charm!!";
			std::cout << std::endl;
		}
		
		//when charm is used, make damage taken = 0
		dTaken = 0;
	}

	return dTaken;
}



