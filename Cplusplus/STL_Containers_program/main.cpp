/****************************************************************************
 * File Name: inputVal.hpp
 * Author: David Ramirez
 * Date: 6/4/17
 * Description: This is the implementation file for the randomNum(), 
 * randomPerc(), and main() functions for lab 9. The randomNum() function 
 * returns a psuedo-random number between 0 and 1000 while the randumPerc()
 * function returns a random number between 0 and 100. The main() function
 * uses the randomPerc(), randomNum(), and menu() functions to demonstrate
 * functionalities of the queue and stack STL abstract data types. The 
 * queue is first demonstrated by displaying the average queue size and the
 * stack is demonstrated by using it to display the palindrome of a user
 * entered string.
 * *************************************************************************/



#include <iostream>
#include <queue>
#include <stack>
#include <ctime>
#include <string>
#include "menu.hpp"



//Function name: randomNum()
//Parameters: none
//Return Value: int (psuedo-random number generated) 
//Description: Returns a psuedo-random number between 1 and 1000
int randomNum()
{
	return (rand() % 1000 + 1);
}




//Function name: randomPerc()
//Parameters: none
//Return Value: int (psuedo-random number generated) 
//Description: Returns a psuedo-random number between 1 and 100
int randomPerc()
{
	return (rand() % 100 + 1);
}



int main()
{
	int percIn;
	int percOut;
	int rounds;
	int size;
	std::string word1;
	unsigned seed = time(0);
	std::queue<int> queue1;
	std::stack<char> stack1;

	std::cout << std::endl;
	std::cout << "Welcome to Lab 9: Queue and Stack by David Ramirez";
	std::cout << std::endl;

	rounds = menu1();
	percIn = menu2();
	percOut = menu3();

	for (int i = 0; i < rounds; i++)
	{
		int randomN;
		int randomP1;
		int randomP2;
		int trash;
		double avgLength;
		double prevLength;


		randomN = randomNum();
		randomP1 = randomPerc();
		randomP2 = randomPerc();
		
		if (randomP1 <= percIn)
		{
			queue1.push(randomN);
		}	

		if (randomP2 <= percOut)
		{
			if (queue1.size() >= 1)
			{
				queue1.pop();
			}
		
			else
			{
				//do nothing
			}
		}

		if (i == 0)
		{
			avgLength = queue1.size();
			prevLength = avgLength;
		}

		else
		{
			avgLength = (prevLength * i +queue1.size())/ (i+1);
			prevLength = avgLength;
		}
	
		std::cout << std::endl;
		std::cout << "The average length of the queue for round ";
		std::cout << i+1 << " is: " << avgLength;
		std::cout << std::endl;
	}
	
	word1 = menu4();
	size = word1.size();

	for (int i = 0; i < size; i++)
	{
		stack1.push(word1.at(i));
	}

	for (int k = 0; k < size; k++)
	{
		word1.append(1, stack1.top());
		stack1.pop();
	}
	
	std::cout << std::endl;
	std::cout << "The word you entered with it's palindrome is: ";
	std::cout << std::endl;
	std::cout << word1;
	std::cout << std::endl;
	
		
}		

