/****************************************************************************
 * File Name: Barbarian.cpp
 * Author: David Ramirez
 * Date: 5/28/17
 * Description: This is the function implementation file for the Barbarian 
 * 		class, which derived from the Creature class. The Barbarian
 * 		class represents a barbarian creature fighter. It has only
 * 		the inhereted base class data members. For member functions, 
 * 		it uses the  base class "get" functions to return class
 * 		data members. This class uses the base class damage()
 * 		function and uses the overidden base class functions 
 * 		attack() and defend()
  *************************************************************************/



#include <string>
#include "Barbarian.hpp"

//Function name: default constructor
//Parameters: none
//Return Value: none 
//Description: Makes all data member values representative of the Barbarian
//	       derived class
Barbarian::Barbarian()
{
	name = "Barbarian";
	attStr = "2d6";
	defStr = "2d6";
	armor = 0;
	strength = 12;
	baseStrength = 12;
	special = "None (real men don't need special abilities)";
}


//Function name: attack()
//Parameters: round (int representing round number)
//Return Value: int (representing attack roll)
//Description: Generates 2 random numbers between 1 and 6, sums them, and 
//	       returns the sum. This sum represents 2 6 sided dice rolls to
//     	       represent an attack.
int Barbarian::attack(int round)
{
	return ((rand() % 6 + 1) + (rand() % 6 + 1));
}


//Function name: defend()
//Parameters: def (int representing attack roll of opponent)
//	      round (int representing round number)
//Return Value: int (representing opponent attack roll minus Barbarian defense
//		     roll)
//Description: Generates 2 random number between 1 and 6 to represent defense
//	       roll of 2 six sided dice. Subtracts the 2 defense roll numbers
//	       from the def paramteter and returns the difference, 
//	       representing damage done after defending.
int Barbarian::defend(int def, int round)
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


