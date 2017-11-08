/****************************************************************************
* File Name: Creature.hpp
* Author: David Ramirez
* Date: 5/28/17
* Description: This is the header file for the Creature
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



#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <string>

class Creature
{
	protected:
		std::string name;
		std::string customName;
		std::string attStr;
		std::string defStr;
		std::string special;
		int armor;
		int strength;
		int baseStrength;
	public:
		Creature();	
		virtual int attack(int) = 0;		//pure virtual function
		virtual int defend(int,int)=0;		//pure virtual function
		virtual void damage(int,int);
		virtual int getStrength();
		virtual int getBaseStrength();
		virtual void regainStrength();
		virtual int getArmor();
		virtual std::string getAttack();
		virtual std::string getDefense();
		virtual std::string getName();
		virtual std::string getCustomName();
		virtual void setCustomName(std::string);
		virtual std::string getSpecial();
		
};

#endif
