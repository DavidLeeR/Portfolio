/****************************************************************************
* File Name: Creature.cpp
* Author: David Ramirez
* Date: 5/28/17
* Description: This is the function implementation file for the Creature
* 		abstract class. This class represents a creature fighter. Data
*		members include a string to hold the name (name), a string to 
*		hold the user defined name (customName), a string to 
*		hold attack strength (attStr), a string to hold defense strength
*		(defStr), a string to hold the creature's special ability 
*		(special),an int to hold armor points (armor), and an int to hol*		d strengthpoints (strength). This class's member functions 
*		contain "get" functions to return data members and the damage() *		function to subtract armor points from damage taken, and finally* 		substract the difference from the creature's strength points 
*		(strength). There is also a "set" member function for the 
*		customName data member.
*************************************************************************/

#include <string>
#include <iostream>
#include "Creature.hpp"



//Function name: default constructor 
//Parameters: none
//Return Value: none 
//Description: Makes all data members representative of an "empty" 
//		creature class object.
Creature::Creature()
{
	name = "empty";
	attStr = "0";
	defStr = "0";
	armor = 0;
	strength = 0;
	baseStrength = 0;
	special = "empty";
}



//Function name: damage()
//Parameters: dam (int representing damage done after defending)
//	      round (int representing round number)
//Return Value: none 
//Description: Subtracts armor from dam to represent the damage done to the 
//		creature
void Creature::damage(int dam, int round)
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

	//makes sure strength is never negative
	if (strength < 0)
	{
		strength = 0;
	}
}



//Function name: getStrength()
//Parameters: none
//Return Value: int (representing strength points)
//Description: Returns the strength points of a creature
int Creature::getStrength()
{
	return strength;
}



//Function name: getBaseStrength()
//Parameters: none
//Return Value: int (representing base strength points)
//Description: Returns the base strength points of a creature. Used by
//the regainStrength() function to determine the difference between strength 
//points before and after a match.
int Creature::getBaseStrength()
{
	return baseStrength;
}



//Function name: regainStrength()
//Parameters: none
//Return Value: none
//Description: Determines how many strength points a creature has lost after
//a fight and regains a pseudo-random amount of strength points for that
//creature between 1 and the amount of strength points lost.
void Creature::regainStrength()
{
	//starting strength - strength now
	int diff = (baseStrength - strength);
	int gained;

	if (diff == 0)
	{
	//gain nothing because fighter at full strength
	std::cout << std::endl;
	std::cout << "The " << getName() << " \"" << getCustomName();
	std::cout << "\" did not regain strength points because they are full!" << std::endl;

	}

	else 
	{
		//gain amount of strength between 1 and amount of strength 
		//points lost
		gained = (rand() % diff +1);
		strength += gained;

		//display gain strength message (after each fight)
		std::cout << std::endl;
		std::cout << "The " << getName() << " \"" << getCustomName();
		std::cout << "\" regained some strength points!" << std::endl;
	}
}



//Function name: getArmor()
//Parameters: none
//Return Value: int (representing armor points)
//Description: Returns the armor points of a creature
int Creature::getArmor()
{
	return armor;
}



//Function name: getAttack()
//Parameters: none
//Return Value: string (representing attack strength)
//Description: Returns the attack strength of a creature
std::string Creature::getAttack()
{
	return attStr;
}



//Function name: getDefense()
//Parameters: none
//Return Value: string (representing defense strength)
//Description: Returns the defense strength of a creature
std::string Creature::getDefense()
{
	return defStr;
}



//Function name: getName()
//Parameters: none
//Return Value: string (representing the name of a creature)
//Description: Returns the name of a creature
std::string Creature::getName()
{
	return name;
}



//Function name: getSpecial()
//Parameters: none
//Return Value: string (representing special ability)
//Description: Returns the special ability of a creature
std::string Creature::getSpecial()
{
	return special;
}


//Function name: getCustomName()
//Parameters: none
//Return Value: string (representing user defined name)
//Description: Returns the user defined name of a creature
std::string Creature::getCustomName()
{
	return customName;
}



//Function name: setCustomName()
//Parameters: string (representing user defined name)
//Return Value: none
//Description: Sets the customName data member of a creature to the parameter
//string
void Creature::setCustomName(std::string custom)
{
	customName = custom;
}
