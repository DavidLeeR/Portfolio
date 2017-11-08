
/****************************************************************************
 * File Name: List.hpp
 * Author: David Ramirez
 * Date: 4/30/17
 * Description: This is the header file for the List class. The List
 * 		class keeps an array of pointers to Item class objects and 
 * 		an integer representing the number of Item class objects in the 
 * 		list as data members. The List class has member functions
 * 		that add an Item object pointer to the list, remove an Item
 * 		object pointer from the list, output the contents of the list
 * 		to the console window, check if the Item object being added
 * 		to the list is already on the list, and delete the list.
 * *************************************************************************/



#ifndef LIST_HPP
#define LIST_HPP

#include <string>
#include "Item.hpp"

class List
{
	private:
		Item* itemList;		
		int listNumber;		//keeps track of number of items in 
					//list
	public:
		List();	
		void addItem();
		void removeItem();
		void displayList();
		void extendList();
		void match(Item, int);
		void deleteList();
};
# endif
