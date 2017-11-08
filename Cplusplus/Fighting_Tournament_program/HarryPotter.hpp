/****************************************************************************
* File Name: HarryPotter.hpp
* Author: David Ramirez
* Date: 5/28/17
* Description: This is the header file for the HarryPotter
* 		class, which is derived from the Creature class. The HarryPotter
* 		class represents a "Harry Potter" creature fighter. It uses
* 		the inhereted base class data members, as well as a data member "hog",
*		an int which keeps track of the use of the special ability. For member
*		functions, it uses the  base class "get" functions to return class
* 		data members. This class uses the overidden base class functions
* 		attack(), defend(), and damage(). The Harry Potter class has special
*		ability "Hogwarts" implemented in the damage() member function.
*************************************************************************/

#ifndef HARRY_POTTER_HPP
#define HARRY_POTTER_HPP

#include <string>
#include "Creature.hpp"



class HarryPotter: public Creature
{
	private:
		int hog;
	public:
		HarryPotter();
		int attack(int);
		int defend(int,int);
		void damage(int,int);

};

#endif
