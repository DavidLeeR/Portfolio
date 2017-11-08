/****************************************************************************
 * File Name: Ant.cpp
 * Author: David Ramirez
 * Date: 4/16/17
 * Description: This is the implementation file for the Ant class.
 * 		The Ant class represents the ant moving across the
 * 		board. It is used to keep track of the location of the ant,
 * 		the direction of the ant, the color of the next location
 * 		of the ant, the boundaries of the ant, and the board
 * 		the ant is on. It's functionality includes initializing
 * 		the location of the ant, analyzing if the direction for 
 * 		the ant is valid, analyzing the color of the location of
 * 		the ant to determine direction, completing all moves for
 * 		the ant, and printing the board with the location of the
 * 		ant. The Ant class is used exclusively by the main function. 
 * *************************************************************************/



#include "Ant.hpp"
#include <iostream>


/* This is the constructor for the Ant class. It's parameters are an int to
 * represent row size and an int to represent column size. It uses these
 * parameters in an initialization list to create a Board class object 
 * current. It stores the maxRow and maxCol int variables to represent the
 * borders of the board without having to consult the Board object current. It
 * stores a throw-away value in storeColor, as color is irrelevant for the
 * first move of the ant. */
Ant::Ant (int row, int column):
current(row,column)
{
	storeColor = 5;
	maxRow = row-1;
	maxCol = column-1;
}

/* This is the printStatus function. It has no parameters and is used only
 * in testing to output the values of each variable at any point in the 
 * program. It has no return value. */
void Ant::printStatus()
{
	std::cout << "antRow " << antRow << std::endl;
	std::cout << "antCol " << antCol << std::endl;
	std::cout << "storeDir " << storeDir << std::endl;
	std::cout << "storeColor " << storeColor << std::endl;
	std::cout << "maxRow " << maxRow << std::endl;
	std::cout << "maxCol " << maxCol << std::endl;

}

/* This is the start function. It's parameters are an int to represent the
 * starting row of the ant and an int to represent the starting column of the
 * ant. It imports the board (2D array) from the current object and places
 * the ant at the starting location. It has no return value. */
void Ant::start(int rowStart, int colStart)
{
	char** antBoard2 = current.getBoard();

	antRow = rowStart;
	antCol = colStart;

	antBoard2[rowStart][colStart] = '@';
}

/* This is the move function. It's parameters are 2 ints representing the 
 * next location of the ant. It imports the board (2D array) from the current
 * object. It uses the place function of the current object to move the ant. It
 * also analyzes the color of the recently departed location and makes it 
 * opposite on the board and updates the variables that hold the current
 * location of the ant. It has no return value. */
void Ant::move(int rowLoc, int colLoc)
{
	char** antBoard = current.getBoard();	
	int storeColorOld = storeColor;
	

	if (antBoard[rowLoc][colLoc] == ' ')	//reads and stores color of new position moving ant to
	{
		storeColor = 1;
	}
	else if (antBoard[rowLoc][colLoc] == '#')
	{
		storeColor = 0;
	}

	current.place(rowLoc, colLoc);	//moves ant to new position
	
	if (storeColorOld == 1)		//makes old position opposite color
	{	
	antBoard[antRow][antCol]= '#';
	}
	else if (storeColorOld == 0)
	{
	antBoard[antRow][antCol] = ' ';
	}

	antRow = rowLoc;	//updates variabled for current ant location
	antCol = colLoc;
}

/* This is the moveDir function. It imports the board (2D array) from the 
 * current object. It uses the storeDir data member and analyzeDir function to
 * determine if the next move for the ant is valid. It is called with the
 * expectation that the chooseDir function has already determined the 
 * necessary direction for the ant. If the next move is valid, it is taken.
 * If the next move is invalid, it changes the direction, based on color, and 
 * loops until finding a valid move. If the color the ant is on is white, it 
 * tries the direction to the right, if black, it tries the direction to the
 * left. This function has no return value */
void Ant::moveDir()
{
	char** antBoard3 = current.getBoard();
	int antRowOld = antRow;
	int antColOld = antCol;


	do
	{
		int storeDirOld = storeDir;
	
		if ((storeDirOld == 1) && (analyzeDir() == true)) //if ant pointing north and space available
		{
			move(antRow-1, antCol);
		}
		else if ((storeDirOld == 1) && (storeColor == 1))
		{	
			storeDir = 2;
		}
		else if ((storeDirOld == 1) && (storeColor == 0))
		{
			storeDir = 4;
		}
	
		if ((storeDirOld == 2) && (analyzeDir() == true)) //if ant pointing east and space available
		{
			move(antRow, antCol+1);
		}
		else if ((storeDirOld == 2) && (storeColor == 1))
		{	
			storeDir = 3;
		}
		else if ((storeDirOld == 2) && (storeColor == 0))
		{
			storeDir = 1;
		}
	
		if ((storeDirOld == 3) && (analyzeDir() == true)) //if ant pointing south and space available
		{
			move(antRow+1, antCol);
		}
		else if ((storeDirOld == 3) && (storeColor == 1))
		{	
			storeDir = 4;
		}
		else if ((storeDirOld == 3) && (storeColor == 0))
		{
			storeDir = 2;
		}
		
		if ((storeDirOld == 4) && (analyzeDir() == true)) //if ant pointing north and space available
		{
			move(antRow, antCol-1);
		}
		else if ((storeDirOld == 4) && (storeColor == 1))
		{	
			storeDir = 1;
		}
		else if ((storeDirOld == 4) && (storeColor == 0))
		{
			storeDir = 3;
		}

	} while(antBoard3[antRowOld][antColOld] == '@');
}

/* This is the initialNorth function. It is used to perform the first move of
 * the ant. For the first move, the color of the space the ant is on is 
 * irrelevent. The ant will attempt to move north. If the move north is 
 * invalid (out of bounds) the ant will attempt to move in the direction
 * to the right until a valid move is found. This function has no return
 * value */
void Ant::initialNorth()
{
	storeColor = 1;


	if (antRow-1 >= 0)
	{
		move(antRow-1, antCol);
		storeDir = 1;    //1 = north, 2 = east, 3 = south, 4 = west
		
	}

	else if (antCol+1 <= maxCol)
	{
		move(antRow, antCol+1);
		storeDir = 2;
	}


	else if (antRow+1 <= maxRow)
	{
		move(antRow+1, antCol);
		storeDir = 3;
	}

	else if (antCol-1 >= 0)
	{
		move(antRow, antCol-1);
		storeDir = 4;
	}
	
	else	//if there is only one space
	{
		move(antRow,antCol);
		storeDir = 1;
	}
}

/* This is the chooseDir function. It is used to choose a direction for the
 * ant to move in based on the color of the current space it is on.*/ 
void Ant::chooseDir()  //chooses direction based on color
{

	if (storeColor == 1)	//ant is on white space, will go right
	{
		if (storeDir == 1)
		{
			storeDir = 2;
		}
		else if (storeDir == 2)
		{
			storeDir = 3;
		}
		else if (storeDir == 3)
		{
			storeDir = 4;
		}
		else if (storeDir == 4)
		{
			storeDir = 1;
		}	
	}

	if (storeColor == 0)	//ant is on black space, will go left
	{
		if (storeDir == 1)
		{
			storeDir = 4;
		}
		else if (storeDir == 2)
		{
			storeDir = 1;
		}
		else if (storeDir == 3)
		{
			storeDir = 2;
		}
		else if (storeDir == 4)
		{
			storeDir = 3;
		}	
				
	}

}

/* This the analyzeDir function. It determines if the next move is valid.It
 * is used by the moveDir function.  If the next move is valid, true is 
 * returned. If the next move is invalid, false is returned. It is used by
 * the moveDir function */
bool Ant::analyzeDir()	//shows if next move is valid
{
	if (storeDir == 1)	//north
	{
		if (antRow - 1 >= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (storeDir == 2)	//east
	{
		if (antCol + 1 <= maxCol)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (storeDir == 3)	//south
	{
		if (antRow + 1 <= maxRow)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (storeDir ==4)	//west
	{
		if (antCol - 1 >= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

/* This is the printAnt function. It uses the print function of the current
 * object to print the board as well as the ant location. It is used by main
 * for each step that Langton's Ant takes. It has no return value. */
void Ant::printAnt()
{
	current.print();
}
