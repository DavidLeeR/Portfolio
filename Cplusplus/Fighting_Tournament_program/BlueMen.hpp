/****************************************************************************
* File Name: BlueMen.cpp
* Author: David Ramirez
* Date: 5/28/17
* Description: This is the header file for the BlueMen
* 		class, which derived from the Creature class. The BlueMen
* 		class represents a "BlueMen" creature fighter. It has only
* 		the inhereted base class data members. For member functions,
* 		it uses the  base class "get" functions to return class
* 		data members. This class uses the base class damage()
* 		function and uses the overidden base class functions
* 		attack() and defend(). The BlueMen class has special ability
*		"Mob" implemented in the defend() member function.
*************************************************************************/

#ifndef BLUE_MEN_HPP
#define BLUE_MEN_HPP

#include <string>
#include "Creature.hpp"



class BlueMen: public Creature
{
	public:
		BlueMen();
		int attack(int);
		int defend(int,int);

};

#endif
