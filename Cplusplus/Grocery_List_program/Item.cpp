/****************************************************************************
 * File Name: Item.cpp
 * Author: David Ramirez
 * Date: 4/30/17
 * Description: This is the implementation file for the Item class. The Item
 * 		class keeps variables that represent the name of an item, the 
 * 		unit of an item, the quanihtity of an item to buy, the unit 
 * 		price of an item, and the extended price of an item as data
 * 		members. Member fucntions include a default constructor that
 * 		initializes an 'empty' Item object, a constructor that 
 * 		initializes an Item object, a function to return an Item
 * 		object name, a function to return an Item object unit, a
 * 		function to return an Item object quantity to buy, a function
 * 		to return an Item object unit price, and a function to 
 * 		return an Item object extended price.  
  *************************************************************************/

#include <string>
#include "Item.hpp"



//This is the default constructor for the Item class. It initializes an
//'empty' object by creating an Item object with a 'none' or '0' value  for all 
//data members. 'Empty' Item objects are used to represent space in the 
//itemList array for a new Item object. 
Item::Item()
{
	name = "none";
	unit = "none";
	quantity = 0;
	unitPrice = 0;
	extPrice = 0;
}



//This is the constructor for the Item class. As parameters, it takes a 
//string representing the Item name, a string representing the Item unit name,
//an integer representing the quantity of the item to buy, and an integer
//representing the unit price of the Item. It uses these parameters to fill
//the data members of a non-empty Item object.
Item::Item(std::string nameC, std::string unitC, int quantityC, int unitPriceC)
{
	name = nameC;
	unit = unitC;
	quantity = quantityC;
	unitPrice = unitPriceC;
	extPrice = (quantity * unitPrice);

}



//This is the getName function. It has no parameters and has no return value. 
//This function returns the name data variable of an Item object. 
std::string Item::getName()
{
	return name;
}



//This is the getUnit function. It has no parameters and has no return value. 
//This function returns the unit data variable of an Item object. 
std::string Item::getUnit()
{
	return unit;
}



//This is the getQuantity function.It has no parameters and has no return value.
//This function returns the quantity data variable of an Item object. 
int Item::getQuantity()
{
	return quantity;
}



//This is the getUnitPrice function. It has no parameters and has no return 
//value. This function returns the name unitPrice variable of an Item object. 
int Item::getUnitPrice()
{
	return unitPrice;
}



//This is the getExtPrice function.It has no parameters and has no return value.
//This function returns the extendedPrice data variable of an Item object. 
int Item::getExtPrice()
{
	return extPrice;
}



//This the function that overloads the '==' operator for use with 2 Item
//objects. It allows these Item objects to be compared based only on the
//Item object name. 
bool Item::operator==(Item &right)
{
	if ((*this).getName() != (*&right).getName())
	{
		return false;
	}

	else
	{
		return true;
	}
}
