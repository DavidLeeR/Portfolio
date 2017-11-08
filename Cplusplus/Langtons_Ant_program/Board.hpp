/****************************************************************************
 * File Name: Board.hpp
 * Author: David Ramirez
 * Date: 4/16/17
 * Description: This is the header file for the Board class. The
 * 		Board class represents the board that the ant is located
 * 		on. It is used to create and hold the 2D array that 
 * 		represents the board. It's functionality includes creating the 
 * 		board, printing the board, placing the ant after all checks
 * 		have been made by the Ant class, and returning the board.
 * 		The Board class is used exclusively by the Ant class.
 * *************************************************************************/

#ifndef BOARD_HPP
#define BOARD_HPP



class Board
{
	private:
		char** board;
		int storeRow;
		int storeCol;

	public:
		Board(int, int);
		void print();
		void place(int,int);
		char** getBoard();
};
#endif
