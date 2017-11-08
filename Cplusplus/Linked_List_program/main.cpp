/****************************************************************************
 * File Name: main.cpp
 * Author: David Ramirez
 * Date: 5/14/17
 * Description: This is the implementation file for the main() function of 
 * 		lab6. The main() function calls the menu() function to 
 * 		retrieve user input as to which functions to call in the
 * 		program. It uses while loops and if statements to call
 * 		List class functions based on saved user input. 
  *************************************************************************/




#include <iostream>
#include <string>
#include <cstdlib>
#include "Node.hpp"
#include "menu.hpp"
#include "inputVal.hpp"
#include "List.hpp"

int main()
{
	int storeNum;
	int storeNum2;
	int choice2;
	int choice = 1;		
	int firstMenu = 0;	
	List list1;
	std::string tempNum1;	//used for data validation
	std::string tempNum2;
	char* last4;

	
	//output introduction and extra credit info
	std::cout << std::endl;
	std::cout << "Welcome to lab 6: Doubly Linked List by David Ramirez.";
	std::cout << std::endl << std::endl;

	std::cout << "This program contains extra credit options 1 and 2.";
	std::cout << std::endl;
	std::cout << "It has 2 extra options for printing the head and ";
	std::cout << std::endl;
	std::cout << "tail of the list, and it has an option of loading";
	std::cout << std::endl;
	std::cout << "a list from a text file.";
	std::cout << std::endl;

	//call menu2 only once in the beginning
	while (firstMenu == 0)
	{
		//menu2() gives user choice to load list or start new list
		choice2 = menu2();

		//if choice is to make new list
		if (choice2 == 1)
		{
		//do nothing
		}

		//if choice is to load list
		else if (choice2 == 2)
		{
			//call function that loads list from text file
			list1.loadList();
		}

		//make firstMenu 1 so menu2() is not called again for the
		//remainder of the program
		firstMenu =1;
	}

	//while user has not chosen to quit
	while (choice != 8)
	{
		//have user pick choice from program menu
		choice = menu();

		//if user choice to add Node to head of list1
		if (choice == 1)
		{
			//prompt and save user input for value to store in Node
			std::cout << "Enter a positive integer to store ";
			std::cout << "(max 10000): ";
			getline(std::cin, tempNum1);

			//input validatioin for if int and bounds
			while ((inputVal(tempNum1) == false ) || 
	   		 (strtol(tempNum1.c_str(), &last4, 10) < 0)||
	   		 (strtol(tempNum1.c_str(), &last4, 10) > 10000))
			{	
				//output invalid input message and prompt and
				//save user input again
				std::cin.clear();
				std::cout << "Input is invalid.";
				std::cout << std::endl;
				std::cout << "Enter a positive integer to store ";
				std::cout << "(max 10000): ";
				getline(std::cin, tempNum1);
			}
			//store user input after validation
			storeNum =strtol(tempNum1.c_str(), &last4, 10);
				
			//call function to add Node to head of list1 and pass
			//user input for value to store
			list1.addHead(storeNum);
	
			std::cin.clear();

		}

		//if user choice to add Node to tail of list1
		if (choice == 2)
		{
			//prompt and save user input for value to store in Node
			std::cout << "Enter a positive integer to store";
			std::cout << "(max 10000): ";
			getline(std::cin, tempNum2);
	
			//input validation for if int and bounds
			while ((inputVal(tempNum2) == false ) || 
	   		 (strtol(tempNum2.c_str(), &last4, 10) < 0)||
	   		 (strtol(tempNum2.c_str(), &last4, 10) > 10000))
			{
				//output invalid input message and prompt and 
				//save user input again
				std::cin.clear();	
				std::cout << "Input is invalid.";
				std::cout << std::endl;
				std::cout << "Enter a positive integer to store ";
				std::cout << "(max 10000): ";
				getline(std::cin, tempNum2);
			}
			//store user input after validation
			storeNum2 =strtol(tempNum2.c_str(), &last4, 10);
			
			//call function to add Node to tail of list1 and pass
			//user input for value to store
			list1.addTail(storeNum2);

			std::cin.clear();


		}

		//if user choice to remove Node at head of list1
		if (choice == 3)
		{
			//call list1 member function to rmove Node at head 
			list1.remHead();
		}

		//if user choice to remove Node at tail of list1
		if (choice == 4)
		{
			//call list1 member function to remove Node at tail
			list1.remTail();
		}

		//if user choice to print list1 in reverse
		if (choice == 5)
		{
			//call list1 member function to traverse the list
			//reversely, printing as it traverses
			list1.revPrint();
		}
	
		//if user choice to print contents of Node at head of list1
		if (choice == 6)
		{
			//call list1 member function to print contents of 
			//head Node
			list1.printHead();
		}

		//if user choice to print contents of Node at tail of list1
		if (choice == 7)
		{
			//call list1 member function to print contents of
			//tail Node
			list1.printTail();
		}

	}

	//quit program
	return 0;
}
