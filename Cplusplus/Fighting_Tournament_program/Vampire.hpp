/****************************************************************************
* File Name: Vampire.hpp
* Author: David Ramirez
* Date: 5/28/17
* Description: This is the header file for the Vampire
* 		class, which is derived from the Creature class. The Vampire
* 		class represents a "Vampire" creature fighter. It uses only
* 		the inhereted base class data members. For member
*		functions, it uses base class "get" functions to return class
* 		data members, the base class damage() function,
*		and the overidden base class functions attack() and defend(). 
*		The Vampire class has special ability "Charm", implemented in 
*		the defend() function.
*************************************************************************/

#ifndef VAMPIRE_HPP
#define VAMPIRE_HPP

#include <string>
#include "Creature.hpp"



class Vampire: public Creature
{
	public:
		Vampire();
		int attack(int);
		int defend(int,int);

};

#endif
