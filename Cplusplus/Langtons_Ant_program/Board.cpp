/****************************************************************************
 * File Name: Board.cpp
 * Author: David Ramirez
 * Date: 4/16/17
 * Description: This is the implementation file for the Board class. The
 * 		Board class represents the board that the ant is located
 * 		on. It is used to create and hold the 2D array that 
 * 		represents the board. It's functionality includes creating the 
 * 		board, printing the board, placing the ant after all checks
 * 		have been made by the Ant class, and returning the board. The
 * 		Board class is used exclusively by the Ant class.
 * *************************************************************************/



#include "Board.hpp"
#include "Ant.hpp"
#include <iostream>


/*This is the constructor fot the Board class. It's parameters are an int
 * representing the number of rows for the array and an int representing
 * the number of columns for the array. It creates a 2D array based on 
 * these parameters and fills the array with a blank space per value. */
Board::Board(int rowSize, int colSize)
{
	storeRow = rowSize;
	storeCol = colSize;

	board = new char*[rowSize];
	for(int i = 0; i < rowSize; i++)
	{
    		board[i] = new char[colSize];    
	}	

	
	for (int m = 0; m < rowSize; m++) //steps through the rows of  2D array
	{
		for (int n = 0; n < colSize; n++) //steps through the columns
		{			      	  //of the 2D array	
			
			board[m][n]=' ' ;      //initializes all board location
					       // to "."

		}
	}
}

/* This the print function. It is used to output the current status of the
 * board array member function. It has no return value and is used by 
 * the printAnt function of the Ant class. */
void Board::print()
{
	for (int x = 0; x < storeRow; x++)	//displays the board (2D array)
	{
		for (int y = 0; y < storeCol; y++)
		{
			std::cout << board [x][y] << " ";
		}
		
		std::cout << std::endl;
	}
}

/* This is the place function. It's parameters are 2 ints representing the 
 * new location of the ant. It places an @ symbol in the new location 
 * of the 2d array board, representing the ant. It is used by the move
 * function of the Ant class. It has no return values. */
void Board::place(int rowLoc2, int colLoc2)
{
	board[rowLoc2][colLoc2] = '@';
}

/* This is the getBoard function. It returns the 2D array board. It is used
 * by various Ant functions to import the board of a Board class object. */
char** Board::getBoard()
{
	return board;
}	
