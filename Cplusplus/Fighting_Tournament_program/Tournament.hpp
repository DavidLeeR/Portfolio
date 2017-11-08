/****************************************************************************
 * File Name: Tournament.hpp
 * Author: David Ramirez
 * Date: 5/28/17
 * Description: This is the header file for the Tournament class. This class
 * 		represents a tournament with 2 teams fighting against each
 * 		other. As data members, the Tournament class holds 3 Queue
 * 		class objects representing the team of fighters for player
 * 		1, the team of fighters for player 2, and the fighters that
 * 		have lost. It also holds as data members integers representing
 * 		the size of each team and integers representing the score of
 * 		each team. The tournament class holds member functions to 
 * 		facilitate the simulated fighting in the tournament such
 * 		as attackSeq() (simulates fight between 2 fighter creatures
 * 		of opposing teams), start() (uses attackseq to start 
 * 		tournament), queueMake() (used to make the two teams), and
 *		chooseFighter()(to match user input with a creature and 
 *		dynamically create it). It also has member functions to 
 *		display the status of the tournament which are print() 
 *		(prints out each queue), printLoss() (prints losers queue),
 *		and ending() (displays the results of the tournament). 
 * *************************************************************************/



#ifndef TOURNAMENT_HPP
#define TOURNAMENT_HPP

#include "Queue.hpp"
#include "Creature.hpp"

class Tournament
{
	private:
		int queueNum;
		int queueNum2;
		int score1;
		int score2;
		Queue queue1;
		Queue queue2;
		Queue queueL;
	public:
		Tournament();
		void attackSeq();
		void queueMake();
		void start();
		void print();
		Creature* chooseFighter(int);
		void printLoss();
		void ending();
};

#endif
