/****************************************************************************
 * File Name: menu.cpp
 * Author: David Ramirez
 * Date: 4/30/17
 * Description: This is the implementation file for the menu function. This 
 * 		function provides user feedback to the main function in
 * 		in order for the user to control the next function to 
 * 		execute. 
 * *************************************************************************/

#include <string>
#include <iostream>
#include "inputVal.hpp"
#include "menu.hpp"



//Function Name: menu()
//Parameters: instance (integer representing which version of the menu to 
//		display), university1M (University class object used to 
//		access information from University class object created in 
//		main())
//Return Value: integer (integer representing user choice in program 
//		next function execution)
//Description: Prompts the user with options for the functions the program
//		can execute and returns an integer representing this choice
//		to the main() function
int menu (int instance,University university1M)
{
	int choose;
	int modify = instance;
	std::string inputM1,
	            inputM2;
	char* last3;

	//if modify is equal to 0, the menu function will display the 
	//program menu
	if (modify ==0)
	{
		std::cout << std::endl;		
		std::cout << "Please choose an option from the program menu:";
		std::cout << std::endl;
		std::cout << "1: print the information of all buildings in ";
		std::cout << "the university" << std::endl;
		std::cout << "2: print the information of all people in the ";
		std::cout << "university" << std::endl;
		std::cout << "3: choose person to do work" << std::endl;
		std::cout << "4: add a person to the University" << std::endl;
		std::cout << "5: save university person data" << std::endl;
		std::cout << "6: load university person data" << std::endl;
		std::cout << "7: exit program" << std::endl;

		getline(std::cin, inputM1);
		std::cout << std::endl;
		
		std::cin.clear();
		
		//validates user input to be an integer and in bounds
		while ((inputVal(inputM1) == false ) || 
			    (strtol(inputM1.c_str(), &last3, 10) < 1)||
			    (strtol(inputM1.c_str(), &last3, 10) > 7))
		{
			std::cout << std::endl;
			std::cout << "The input entered is invalid";
			std::cout << std::endl << std::endl;
			std::cout << "Please choose an option from the program menu:";
			std::cout << std::endl;
			std::cout << "1: print the information of all buildings in ";
			std::cout << "the university" << std::endl;
			std::cout << "2: print the information of all people in the ";
			std::cout << "university" << std::endl;
			std::cout << "3: choose person to do work" << std::endl;
			std::cout << "4: add a person to the University" << std::endl;
			std::cout << "5: save university person data" << std::endl;
			std::cout << "6: load university person data" << std::endl;
			std::cout << "7: exit program" << std::endl;

			getline(std::cin, inputM1);
			std::cout << std::endl;

			std::cin.clear();
		}
		choose = strtol(inputM1.c_str(), &last3, 10);	
			
		//corresponds to 'print building info'
		if (choose == 1)
		{
			return 1;	//returns user choice to main
		}
	
		//corresponds to 'print person info'
		if (choose == 2)
		{
			return 2;	//returns user choice to main
		}
		
		//corresponds to 'choose person to do work
		if (choose == 3)
		{
			return 3;
		}

		//corresponds to 'add a person to the university"
		if (choose == 4)
		{
			return 4;
		}

		//corresponds to "save person data"
		if (choose == 5)
		{
			return 5;
		}

		//corresponds to "load person data"	
		if (choose == 6)
		{
			return 6;
		}

		//corresponds to "exit program"
		if (choose == 7)
		{
			return 7;
		}

	}

	//if modify is equal to 1, the person menu is displayed
	if (modify ==1) 
	{
	
		std::cout << std::endl;
		std::cout << "Please choose a person in the University to do ";
		std::cout << "work:";
		std::cout << std::endl;
		std::cout << "1: select student 1 ("<<university1M.getNameStu();
		std::cout << ") to do work" << std::endl;
		std::cout << "2: select instructor 1 (";
		std::cout << university1M.getNameInst() << ") to do work";
		std::cout << std::endl;
		std::cout << "3: select another person to do work";
		std::cout << std::endl;
 

 
		getline(std::cin, inputM2);
		std::cout << std::endl;

		std::cin.clear();

		//validates user input to be an integer and in bounds
		while ((inputVal(inputM2) == false ) || 
			    (strtol(inputM2.c_str(), &last3, 10) < 1)||				            
			    (strtol(inputM2.c_str(), &last3, 10) > 3))
		{
			std::cout << std::endl;
			std::cout << "The input entered is invalid";
			std::cout << std::endl << std::endl;
			std::cout << "Please choose a person in the University to do ";
			std::cout << "work:";
			std::cout << std::endl;
			std::cout << "1: select student 1 (" << university1M.getNameStu();
			std::cout << ") to do work" << std::endl;
			std::cout << "2: select instructor 1 (";
			std::cout << university1M.getNameInst() << ") to do work";
			std::cout << std::endl;
			std::cout << "3: select another person to do work";
			std::cout << std::endl;
 
			getline(std::cin, inputM2);
			std::cout << std::endl;

			std::cin.clear();
		}
		choose = strtol(inputM2.c_str(), &last3, 10);	
			
		//corresponds to 'select student1 to do work'	
		if (choose == 1)
		{
			return 1;	//returns user choice to main
		}
	
		//corresponds to 'select instructor1 to do work'
		if (choose == 2)
		{
			return 2;	//returns user choice to main
		}

		//corresponds to 'search for person to do work"
		if (choose == 3)
		{
			return 3;	//returns user choice to main
		}
	
	}
}





