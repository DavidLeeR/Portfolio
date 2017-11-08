/****************************************************************************
 * File Name: List.cpp
 * Author: David Ramirez
 * Date: 4/30/17
 * Description: This is the implementation file for the List class. The List
 * 		class keeps an array of pointers to Item class objects and 
 * 		an integer representing the number of Item class objects in the 
 * 		list as data members. The List class has member functions
 * 		that add an Item object pointer to the list, remove an Item
 * 		object pointer from the list, output the contents of the list
 * 		to the console window, check if the Item object being added
 * 		to the list is already on the list, and delete the list.
 * *************************************************************************/

#include <string>
#include <iostream>
#include "List.hpp"
#include "Item.hpp"
#include "inputVal.hpp"



//This is the default constructor for the List class. It dynamically allocates
//memory for 4 pointers to Item objects in an array named itemList.
//These 4 pointers are set to point to 'empty' Item objects.  This 
//constructor also sets the variable that keeps track of the number of Item
//objects in the list, named listNumber, to 0. 
List::List()
{
	itemList = new Item[4];	//starts the list with 4 pointers to Item class
				//objects
	listNumber = 0;
}



//This is the addItem function. It has no parameters and has no return value.
//This function prompts the user to enter the information for a new Item
//object to be pointed to by the itemList array. If there is not enough
//space for a new Item object, the addItem function calls the expandList
//function which dynamically allocates more space for itemList. The 
//addItem function then adds the new Item object. This function uses the 
//match function to check if the Item object to be added to itemList is 
//already on the list. If it is, the user is prompted with the option to
//update the Item object information or to leave the list as it is. This 
//function uses the inputVal function to validate certain user input as
//integers.  
void List::addItem()
{
	std::string nameAI,
		    unitAI,
		    tempQuantity,	//strings with prefix 'temp' are used
		    tempPrice;		//for input validation 
	int quantityAI;
	int unitPriceAI;
	char* last;



	std::cout << "Enter the name of the item you would like to add.";
	std::cout << std::endl;
	getline(std::cin, nameAI);
	std::cout << std::endl;

	std::cout << "Enter the unit the item is sold by." << std::endl;
	getline(std::cin, unitAI);
	std::cout << std::endl;

	std::cout << "Enter the quantity of the item you would like to";
	std::cout << " buy." << std::endl;
	getline(std::cin, tempQuantity);
	std::cout << std::endl;
	
	//input validation to make sure the input is an integer
	while ((inputVal(tempQuantity) == false ) || 
	       (strtol(tempQuantity.c_str(), &last, 10) < 1))
	{
		std::cout << "Entered input is invalid.";
		std::cout << std::endl << std::endl;
		std::cout << "Enter the quantity of the item you would like to";
		std::cout << " buy." << std::endl;
		getline(std::cin, tempQuantity);
		std::cout << std::endl;
	}
	quantityAI = strtol(tempQuantity.c_str(), &last, 10);

	std::cout << "Enter the unit price of the item." << std::endl;
	getline(std::cin, tempPrice);
	std::cout << std::endl;

	//input validation to make sure the input is an integer
	while ((inputVal(tempPrice) == false ) || 
	       (strtol(tempPrice.c_str(), &last, 10) < 1))
	{
		std::cout << "Entered input is invalid.";
		std::cout << std::endl << std::endl;
		std::cout << "Enter the unit price of the item." << std::endl;
		getline(std::cin, tempPrice);
		std::cout << std::endl;
	}
	unitPriceAI = (strtol(tempPrice.c_str(), &last, 10));
	

	//creates Item object for first position in array of pointers if the
	//first position does not already have a non-empty Item object
	if (itemList[0].getName() == "none")
	{
		itemList[0] = Item(nameAI, unitAI, quantityAI, 
					unitPriceAI);
		listNumber = 1;

	}

	//creates Item object for second position in array of pointers if the
	//second position does not already have a non-empty Item object
	else if (itemList[1].getName() == "none")
	{
		itemList[1] = Item(nameAI, unitAI, quantityAI, 
					unitPriceAI);
		listNumber = 2;

		match(itemList[1], 2);	//checks if Item object is already 
					//on the list
	}

	//creates Item object for third position in array of pointers if the
	//third position does not already have a non-empty Item object
 	else if (itemList[2].getName() == "none")
	{
		itemList[2] = Item(nameAI, unitAI, quantityAI, 
					unitPriceAI);
		listNumber = 3;

		match(itemList[2], 3);  //checks if Item object is already 
					//on the list

	}

	//creates Item object for fourth position in array of pointers if the
	//fourth position does not already have a non-empty Item object
	else if (itemList[3].getName() == "none")
	{
		itemList[3] = Item(nameAI, unitAI, quantityAI, 
					unitPriceAI);
		listNumber = 4;

		match(itemList[3], 4);  //checks if Item object is already 
					//on the list

	}

	//creates Item object for subsequent position in array of pointers if
	//subsequent position does not already have a non-empty Item object
	else
	{
		Item* tempList;
		tempList = new Item[listNumber]; //create temporary list
		
		//transfers curent list to temporary list
		for (int m = 0; m < listNumber; m++)
		{
			tempList[m] = itemList[m];
		}
		
		//extends original list by 1 pointer to an Item object
		extendList();
		
		//transfers temporary list to extended list
		for (int n = 0; n < listNumber; n++)
		{
			itemList[n] = tempList[n];
		}

		//delets temporary list
		delete [] tempList;
		tempList = NULL;
		
		//adds new item object to be held via pointer in the extended
		//list				
		itemList[listNumber] = Item(nameAI, unitAI, quantityAI, 
					unitPriceAI);
		listNumber++;
		
		//checks if Item object is already on the list
		match(itemList[listNumber-1], (listNumber));

	}	
}



//This is the removeItem function. It has no parameters and does not have a 
//return value. The removeItem function prompts the user to enter the 
//name of the Item object they would like to remove from itemList. It then
//steps through the itemList array and attempts to match the user inputted
//name to each Item object name. If a match is found, the Item object is 
//removed from itemList and each Item object following the removed object
//is moved up 1 location in the array. A message is displayed to the console
//window stating whether the Item object was found and removed from the list
//or if the Item object was not found on the list. 
void List::removeItem()
{
	int removeThis;
	int gotName = 0;	//tracks if name was matched to an Item object
	std::string removeName;

	std::cout << "Enter the name of the item you would like to remove ";
	std::cout << "from the list." << std::endl;
	getline(std::cin, removeName);
	
	//steps through Item object pointers in list
	for (int x = 0; x < listNumber; x++)
	{
		//if the name of the 
		if (itemList[x].getName() == removeName)
		{
			removeThis = x;

			listNumber--;

			gotName = 1;
		}	
	}

	for (removeThis; removeThis < listNumber; removeThis++)
	{
		itemList[removeThis] = itemList[removeThis+1];

	}

	if (gotName == 1)
	{
		std::cout << std::endl;
		std::cout << removeName << " has been removed from the list.";
		std::cout << std::endl << std::endl;
	}

	else if (gotName == 0)
	{
		std::cout << std::endl;
		std::cout << removeName << " was not found on the list.";
		std::cout << std::endl << std::endl;
        }	
}



//This is the displayList function. It has no parameters and has no return 
//value. This function outputs the contents of the itemList array to the
//console window in a readable format. It also calculates and displays the 
//total price of all Item objects on itemList by adding each Item object's
//extended price. 
void List::displayList()
{
	int listTotal =0;

	for (int y = 0; y < listNumber; y++)
	{
		std::cout << "Item name: " << itemList[y].getName();
		std::cout << std::endl;
		
		std::cout << "Item unit: " << itemList[y].getUnit();
		std::cout << std::endl;

		std::cout << "Quantity of item to purchase: ";
		std::cout << itemList[y].getQuantity();
		std::cout << std::endl;	

		std::cout << "Unit price of item: ";
		std::cout << itemList[y].getUnitPrice();
		std::cout << std::endl;

		std::cout << "Extended price of item: ";
		std::cout << itemList[y].getExtPrice();
		std::cout << std::endl << std::endl;
		
	}

	for (int z = 0; z < listNumber; z++)
	{
		listTotal += itemList[z].getExtPrice();
	}

	std::cout << "Total price of all items on list: $";
	std::cout << listTotal;
	std::cout << std::endl << std::endl;		
}



//This is the extendList function. It has no parameters and has no return value.
//This function deletes the current itemList and dynamically allocates space 
//for a new iteration of itemList with 1 more space. This function is used by
//the addItem function when there is not enough space in the itemList array
//for a pointer to a new Item object. 
void List::extendList()
{
	delete [] itemList;
	itemList = new Item[listNumber+1];
}



//This is the match function. It takes an Item and an int as parameters and has
//no return value. This function is used by the addItem function to check if
//the Item object being added to the list is already on the list. If the Item
//object is already on the list, the user is prompted with the option to update
//the Item object's information or leave the Item object as is. This function
//uses the inputVal function to validate user input as an integer. 
void List::match(Item current, int itemCount)
{
	std::string tempUpdate;
	int update;
	char* last2;

	for (int r = 0; r < listNumber-1; r++)
	{
		//This if statement uses the overloaded == operator for
		//use with Item objects
		if (current == itemList[r])
		{
			std::cout << "This item is already on the list";
			std::cout << "." << std::endl;
			std::cout << "If you would you like to update this ";
			std::cout << std::endl;
			std::cout << "item, enter \"1\". If not, enter \"0\".";
			std::cout << std::endl;
			getline(std::cin, tempUpdate);

			std::cin.clear();
	
			while ((inputVal(tempUpdate) == false ) || 
	       		       (strtol(tempUpdate.c_str(), &last2, 10) < 0) || 
				(strtol(tempUpdate.c_str(), &last2, 10) > 1))
			{
				std::cout << "Entered input is invalid.";
				std::cout << std::endl << std::endl;
				std::cout << "This item is already on the list";
				std::cout << "." << std::endl;
				std::cout << "If you would you like to update";
				std::cout << " this ";
				std::cout << std::endl;
				std::cout << "item, enter \"1\". If not, enter";
				std::cout << " \"0\".";
				std::cout << std::endl;
				getline(std::cin, tempUpdate);

				std::cin.clear();
			}
			update = strtol(tempUpdate.c_str(), &last2, 10);

			//Item object information is updated in current 
			//array location if user decides to update Item object
			if (update == 1)  
			{
				itemList[r] = current;
				itemList[itemCount-1] = Item();
	
				listNumber--;
			}
		
			//If user decides not to update the item information,
			//the new Item Object in itemList is turned into an
			//'empty' Item object
			if (update == 0)
			{
				itemList[itemCount-1] = Item();

				listNumber--;	
			}

		}
	}
}



//This is the deleteList function. It has no parameters and has no return 
//value. It is used to delete the dynamically allocated itemList at the end
//of the program to avoid memory leaks. 
void List::deleteList()
{
	delete [] itemList;

	itemList =NULL;
}			
