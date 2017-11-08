/****************************************************************************
 * File Name: main.cpp
 * Author: David Ramirez
 * Date: 4/30/17
 * Description: This file contains the main function for the Grocery List 
 * 		program. It uses while and if statements to facilitate
 * 		the use of the menu function in prompting and evaluating
 * 		user input. It creates a List object, then calls the menu 
 * 		function and uses the return value to execute a member 
 * 		function of the List object. The program is only ended
 * 		when the user chooses to end the program via the 
 * 		menu function. 
 * *************************************************************************/




#include <string>
#include <iostream>
#include "Item.hpp"
#include "List.hpp"
#include "menu.hpp"



int main()
{
	int mainOption,
	    progOption;
	int infinity = 0;
	std::string removeName;
	List list1;
	
	//Keep looping until user chooses to quit
	while (infinity == 0)
	{
		mainOption = menu(0);

		while (mainOption == 1)
		{

			progOption = menu(1);

			if (progOption == 1)
			{
				list1.addItem();
			}

			if (progOption == 2)
			{
				list1.removeItem();
			}

			if (progOption == 3)
			{
				list1.displayList();
			}	

			if (progOption == 4)
			{
				mainOption = 3;
			}
		 
		}
	
		if (mainOption == 2)
		{
			list1.deleteList();

			return 0;
		}
	}
}
