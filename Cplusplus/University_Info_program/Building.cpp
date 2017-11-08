/****************************************************************************
 * File Name: Building.cpp
 * Author: David Ramirez
 * Date: 4/30/17
 * Description: This is the implementation file for the Building class. The 
 * 		Building class holds as data members a string holding the 
 * 		building name, a string holding the building address, and
 * 		an integer holding the building area in square feet. The 
 * 		member functions of the Building class consist of gatNameB()
 * 		for returning the building name, getAddress() for returning
 * 		the building address, and getSqFeet() for returning the 
 * 		building area.
 * *************************************************************************/

#include <string>
#include "Building.hpp"



//Function Name: constructor
//Parameters: bName (string holding building name), bAddress (string holding
//		building address), bSqFeet (integer holding building area)
//Return Value: none
//Description: Sets the nameB, address, and sqFeet data members from the 
//		passed parameters.
Building::Building(std::string bName, std::string bAddress, int bSqFeet)
{
	nameB = bName;
	address = bAddress;
	sqFeet = bSqFeet;
}



//Function Name: getNameB() 
//Parameters: none
//Return Value: nameB (string holding building name)
//Description: Returns data member 'nameB '
std::string Building::getNameB()
{
	return nameB;
}



//Function Name: getAddress()
//Parameters: none
//Return Value: address (string holding building address)
//Description: Returns data member 'address'
std::string Building::getAddress()
{
	return address;
}



//Function Name: getSqFeet() 
//Parameters: none
//Return Value: sqFeet (integer holding building area)
//Description: Returns the data member 'sqFeet'
int Building::getSqFeet()
{
	return sqFeet;
}
