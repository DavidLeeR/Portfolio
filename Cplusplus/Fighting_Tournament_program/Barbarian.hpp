/****************************************************************************
* File Name: Barbarian.hpp
* Author: David Ramirez
* Date: 5/28/17
* Description: This is the header file for the Barbarian
* 		class, which derived from the Creature class. The Barbarian
* 		class represents a barbarian creature fighter. It has only
* 		the inhereted base class data members. For member functions,
* 		it uses the  base class "get" functions to return class
* 		data members. This class uses the base class damage()
* 		function and uses the overidden base class functions
* 		attack() and defend()
*************************************************************************/

#ifndef BARBARIAN_HPP
#define BARBARIAN_HPP

#include <string>
#include "Creature.hpp"



class Barbarian: public Creature
{
	public:
		Barbarian();
		int attack(int);
		int defend(int,int);

};

#endif
