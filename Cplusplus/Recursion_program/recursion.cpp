/*****************************************************************************
 * File Name: recursion.cpp
 * Author: David Ramirez
 * Date: 5/7/17
 * Description: This is the implementation file for the 3 recursive functions
 * 		reverse(), sum(), and tri(). The reverse() function reverses
 * 		and prints a string. The sum() function adds user inputted
 * 		integers and returns the sum. The tri() function calculates
 * 		the triangular number from a user inputted integer. 
 * *************************************************************************/

#include <string>
#include <iostream>
#include "recursion.hpp"



//Function Name: reverse()
//Parameters: line (the string to be reversed)
//Return Value: none
//Description: takes a string and recursively displays it in reverse
//		to the console window
void reverse(std::string line)
{
	//if there is only 1 letter in the passed string
	if (line.length() == 1)
	{
		//output the last (originally the first) character of the 
		//string and an end line character
		std::cout << line[0];
		std::cout << "\n";
	}

	else
	{
		//output the last letter of the passed string
		std::cout << line.at(line.length()-1);
		
		//call reverse for each character in the string (passing it
		//a substring of the original string) as long as there are
		//at least 2 characters in the string
		reverse(line.substr(0, line.length()-1));
	}
}



//Function Name: sum()
//Parameters: numbers (array of integers to be added together), size
//			(number of integers in numbers array)
//Return Value: int (representing the sum of the integers)
//Description: recursively adds all integers in the passed array and returns
//		the sum.
int sum(int numbers[], int size)
{
	//if the size of the array is 0
	if (size == 0)
	{
		//end function;
		return 0;
	}

	//if array is holding at least 1 integer
	else
	{
		//Return the value of the last integer plus the 
		//value of each integer from last to first (done
		//recursively).
		//Passes sum the numbers array with size being decremented,
		//meaning that the "last" integer in the array for each
		//subsequent call will be different.
		return (numbers[size-1] + sum(numbers, (size - 1)));
	}	
}



//Function Name: tri()
//Parameters: rows (integer to calculate triangular number from)
//Return Value: int (representing the triangular number of the integer)
//Description: recursively calculates the triangular number of a passed integer
int tri(int rows)
{
	//if the integer representing the number of rows has been 
	//decremented to 0
	if (rows == 0)
	{
		//end function;
		return 0;
	}

	//if rows still contains a value
	else
	{
		//Return the value of rows plus the value of each instance of
		//the rows variable with each call to tri. 
		//Passes the tri() function decremented rows integer so the 
		//'rows' variable will hold a different value with eacch call to
		//tri().
		return (rows + tri(rows-1));
	}
}
