/****************************************************************************
 * File Name: Ant.hpp
 * Author: David Ramirez
 * Date: 4/16/17
 * Description: This is the header file for the Ant class.
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



#ifndef ANT_HPP
#define ANT_HPP
#include "Board.hpp"



class Ant
{
	private:
		Board current;
		int antRow;
		int antCol;	
		int storeDir;
		int storeColor;
		int maxRow;
		int maxCol;

	public:
		Ant(int,int);
		void printStatus();
		void start(int, int);
		void move(int, int);
		void moveDir();
		void initialNorth();
		void chooseDir();
		bool analyzeDir();
		void printAnt();
};
#endif
