/****************************************************************************
* File Name: BlueMen.cpp
* Author: David Ramirez
* Date: 5/28/17
* Description: This is the function implementation file for the BlueMen
* 		class, which derived from the Creature class. The BlueMen
* 		class represents a "BlueMen" creature fighter. It has only
* 		the inhereted base class data members. For member functions,
* 		it uses the  base class "get" functions to return class
* 		data members. This class uses the base class damage()
* 		function and uses the overidden base class functions
* 		attack() and defend(). The BlueMen class has special ability
*		"Mob" implemented in the defend() member function.
*************************************************************************/

#include <string>
#include <iostream>
#include "BlueMen.hpp"



//Function name: default constructor
//Parameters: none
//Return Value: none 
//Description: Makes all data member values representative of the BlueMen
//	       derived class
BlueMen::BlueMen()
{
	name = "Blue Men";
	attStr = "2d10";
	defStr = "3d6";
	armor = 3;
	strength = 12;
	baseStrength = 12;
	special = "Mob (some Blue Men don't survive the battle, lowering defense)";
}



//Function name: attack()
//Parameters: round (int representing round number)
//Return Value: int (representing attack roll)
//Description: Generates 2 random numbers between 1 and 10, sums them, and
//	       returns the sum. This sum represents 2 ten sided dice
//	       rolls to represent an attack.
int BlueMen::attack(int round)
{
	return ((rand() % 10 + 1) + (rand() % 10 + 1));
}



//Function name: defend()
//Parameters: def (int representing attack roll of opponent)
//	      round (int representing round number)
//Return Value: int (representing opponent attack roll minus Barbarian defense
//		     roll)
//Description: Generates 3 random numbers between 1 and 6 to represent defense
//	       roll of 3 six sided dice. Subtracts the 3 defense roll numbers
//	       from the def paramteter and returns the difference, 
//	       representing damage done after defending. This function also 
//		   implements the special move "mob", which decreases the amount of
//		   defense random numbers generated based on BlueMen strength.
int BlueMen::defend(int def, int round)
{
	int dTaken;
	
	//if strength is less than 5, roll only one defense die and 
	//ouput a message
	if (getStrength() < 5)
	{
		dTaken = (def - (rand() % 6 + 1));
		
		//if round is odd, BlueMen is fighter 2
		if (round % 2 != 0)
		{	
		std::cout << std::endl;
		std::cout << "Player 2's fighter, the Blue Men, have very low defense"; 
		std::cout << " due to Mob!!";
		std::cout << std::endl;
		}
	
		//if round is even, BlueMen is fighter 1
		else if (round % 2 == 0)
		{	
		std::cout << std::endl;
		std::cout << "Player 1's fighter, the Blue Men, have very low defense"; 
		std::cout << " due to Mob!!";
		std::cout << std::endl;
		}
	}
	
	//if strength is less than 9, roll 2 defense dice and output message
	else if (getStrength() < 9)
	{
		dTaken = (def - ((rand() % 6 + 1) + (rand() % 6 + 1)));
		
		//if round is odd, BlueMen is fighter 2
		if (round % 2 != 0)
		{	
		std::cout << std::endl;
		std::cout << "Player 2's fighter, the Blue Men, have lower defense"; 
		std::cout << " due to Mob!!";
		std::cout << std::endl;
		}
	
		//if round is even, BlueMen is fighter1
		else if (round % 2 == 0)
		{	
		std::cout << std::endl;
		std::cout << "Player 1's fighter, the Blue Men, have lower defense"; 
		std::cout << " due to Mob!!";
		std::cout << std::endl;
		}

	}

	//if strength is 9 or above,  roll all 3 defense dice 
	else 
	{
		dTaken = (def - ((rand() % 6 + 1) + (rand() % 6 + 1) +
		 (rand() % 6 + 1)));
	}

	//makes sure damage is not negative
	if (dTaken < 0)
	{
		dTaken = 0;
	}
	
	return dTaken;
}




