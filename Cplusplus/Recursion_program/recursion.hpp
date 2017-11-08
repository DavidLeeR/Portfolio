/*****************************************************************************
 * File Name: recursion.hpp
 * Author: David Ramirez
 * Date: 5/7/17
 * Description: This is the header file for the 3 recursive functions
 * 		reverse(), sum(), and tri(). The reverse() function reverses
 * 		and prints a string. The sum() function adds user inputted
 * 		integers and returns the sum. The tri() function calculates
 * 		the triangular number from a user inputted integer. 
 * *************************************************************************/



#ifndef RECURSION_HPP
#define RECURSION_HPP

#include <string>



void reverse(std::string line);

int sum(int numbers[], int size);

int tri(int rows);

#endif

