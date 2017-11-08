/****************************************************************************
 * File Name: inputVal.cpp
 * Author: David Ramirez
 * Date: 4/30/17
 * Description: This is the inplementation file for the inputVal function.
 * 		The inputVal function makes certain that the input passed
 * 		to it by the main function is an integer, in which case
 * 		the inputVal function returns true. If the input is found
 * 		not to be an integers, the inputVal function returns false.
 * *************************************************************************/

#include <iostream>
#include <cstdlib>
#include <climits>
#include <cerrno>
#include <string>
#include "inputVal.hpp"



bool inputVal(std::string input)
{

	//This input validation function is modified code from a 
	//tutorial post on dreamincode.net by author "Tapas Bose".
	//www.dreamincode.net/forums/topic/162924-inout-validation-of-integer-
	//and-floating-point-number-using-strtol-a/
	char *last;

	if (input.empty()) //if there is no input
	{ 
		return false; 
	}
	
	errno = 0;	//keeps track of underflow or overflow of int type
	int integerVal = strtol(input.c_str(), &last, 10);		
	
	
	//if overflow or underflow or if any input conversion error 
	if (((errno == ERANGE) && 	
	    (integerVal == INT_MAX || integerVal == INT_MIN)) || 
	    (errno != 0 && integerVal == 0)) 
	{
			 
		return false; 
	}
	
	//if input string contains a character
	else if (last == input || *last != '\0') 
	{		
		return false; 
	}

	return true;		
}

