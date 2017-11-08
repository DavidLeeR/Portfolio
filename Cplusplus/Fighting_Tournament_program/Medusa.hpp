/****************************************************************************
* File Name: Medusa.hpp
* Author: David Ramirez
* Date: 5/28/17
* Description: This is the header file for the Medusa
* 		class, which is derived from the Creature class. The Medusa
* 		class represents a "Medusa" creature fighter. It uses only
* 		the inhereted base class data members. For member
*		functions, it uses base class "get" functions to return class
* 		data members, the base class damage() function,
*		and the overidden base class functions attack() and defend().
*		The Medusa class has special ability "Glare", implemented in the
*		attack() member function.
*************************************************************************/

#ifndef MEDUSA_HPP
#define MEDUSA_HPP

#include <string>
#include "Creature.hpp"



class Medusa: public Creature
{
	public:
		Medusa();
		int attack(int);
		int defend(int,int);

};

#endif
