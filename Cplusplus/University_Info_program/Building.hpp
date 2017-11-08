/****************************************************************************
 * File Name: Building.hpp
 * Author: David Ramirez
 * Date: 4/30/17
 * Description: This is the header file for the Building class. The 
 * 		Building class holds as data members a string holding the 
 * 		building name, a string holding the building address, and
 * 		an integer holding the building area in square feet. The 
 * 		member functions of the Building class consist of gatNameB()
 * 		for returning the building name, getAddress() for returning
 * 		the building address, and getSqFeet() for returning the 
 * 		building area.
 * *************************************************************************/

#ifndef BUILDING_HPP
#define BUILDING_HPP

#include <string>



//The Building class represents a building on the university campus
class Building
{
	private:
		std::string nameB;
		std::string address;
		int sqFeet;
	public:
		Building(std::string, std::string, int);
		std::string getNameB();
		std::string getAddress();
		int getSqFeet();
};
#endif
