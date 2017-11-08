/****************************************************************************
 * File Name: Item.hpp
 * Author: David Ramirez
 * Date: 4/30/17
 * Description: This is the header file for the Item class. The Item
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



#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item
{
	private:
		std::string name;
		std::string unit;
		int quantity;
		int unitPrice;
		int extPrice;

	public:
		bool operator==(Item &right);
		Item();
		Item(std::string, std::string, int, int);
		std::string getName();
		std::string getUnit();
		int getQuantity();
		int getUnitPrice();
		int getExtPrice();


};

#endif
