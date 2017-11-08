/****************************************************************************
 * File Name: Tournament.cpp
 * Author: David Ramirez
 * Date: 5/28/17
 * Description: This is the implementation file for the Tournament class. This 
 * 		class represents a tournament with 2 teams fighting against each
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





#include <string>
#include <iostream>
#include <cstdlib>
#include "menu.hpp"
#include "Creature.hpp"
#include "Tournament.hpp"
#include "Vampire.hpp"
#include "Barbarian.hpp"
#include "BlueMen.hpp"
#include "Medusa.hpp"
#include "HarryPotter.hpp"
#include "inputVal.hpp"


//Function Name: default constructor
//Parameters: none
//Return Value: none
//Description: Creates a tournament with all data values set to 0
Tournament::Tournament()
{
	score1 = 0;
	score2 = 0;
	queueNum = 0;
	queueNum2 = 0;
}



//Function Name: attackSeq()
//Parameters: none
//Return Value: none
//Description: Simulates a fight between 2 objects of classes derived from
//	       the creature class by using the respective objects attack()
//	       and defend() functions. Outputs an introduction for the 
//	       fighters, a round summary per round, and a fight summary. The 
//	       2 Creature class derived objects are taken from the front
//	       of each teams queue.
void Tournament::attackSeq()
{
	int round = 1;			//keep track of round # for display

	int roundTrack = (rand() % 10 + 1);
	
	//Set attacker1 to point to the first creature derived object
	//on team 1. Set attacker2 to point to the first creature derived
	//objects on team 2.
	Creature* attacker1 = queue1.getFront();
	Creature* attacker2 = queue2.getFront();


	//display intro for Player 1's figher
	std::cout << std::endl;
	std::cout << "For Player 1's fighter, we have the fearless ";
	std::cout << attacker1->getName(); 
	std::cout << " \"" << attacker1->getCustomName();
	std::cout << "\"....." << std::endl;
	std::cout << "		Attack: " << attacker1->getAttack();
	std::cout << std::endl;
	std::cout << "		Defense: " << attacker1->getDefense();
	std::cout << std::endl;
	std::cout << "		Armor: " << attacker1->getArmor();
	std::cout << std::endl;
	std::cout << "		Strength: " << attacker1->getStrength();
	std::cout << std::endl;
	std::cout << "		Special: " << attacker1->getSpecial();
	std::cout << std::endl << std::endl;

	//display intro for Player 2's fighter
	std::cout << "And for Player 2's fighter, we have the mighty ";
	std::cout << attacker2->getName();
	std::cout << " \"" << attacker2->getCustomName();
	std::cout << "\"....." << std::endl;
	std::cout << "		Attack: " << attacker2->getAttack();
	std::cout << std::endl;
	std::cout << "		Defense: " << attacker2->getDefense();
	std::cout << std::endl;
	std::cout << "		Armor: " << attacker2->getArmor();
	std::cout << std::endl;
	std::cout << "		Strength: " << attacker2->getStrength();
	std::cout << std::endl;
	std::cout << "		Special: " << attacker2->getSpecial();
	std::cout << std::endl << std::endl;
	
	//while both attckers have strength above zero, keep fighting
	while ((attacker1->getStrength() > 0) && (attacker2->getStrength() >0))		{
		//display round intro
		std::cout << std::endl << std::endl << std::endl;
		std::cout << "Round " << round <<"....." << std::endl;
		std::cout << std::endl << "FIGHT!!" << std::endl;

		//if roundTrack is odd, attacker1 attacks
		if ((roundTrack % 2) != 0)	
		{	
			int atk;
			int dam;

			//roll from attack() function saved in atk
			atk = attacker1->attack(roundTrack);
			
			//display fight commentary for fighter1 attack
			std::cout << std::endl;	
			std::cout << "Player 1's figher, the " << attacker1->getName();
			std::cout << " \"" << attacker1->getCustomName();
			std::cout << "\", attacked for " << atk << " points!!";
			std::cout << std::endl;
		
			//result of atk - attacker2 defend() roll saved in dam
			dam = attacker2->defend(atk, roundTrack);	
	
			//display fight commentary for fighter2 defend
			std::cout << std::endl;
			std::cout << "Player 2's fighter, the " << attacker2->getName();
			std::cout << " \"" << attacker2->getCustomName();
			std::cout << "\", defended for " << atk - dam;
			std::cout << " points!!" << std::endl;
			
			//fighter2 takes damage, after fighter2 defends
			attacker2->damage(dam, roundTrack);
			
			//display round summary
			std::cout << std::endl;
			std::cout << "Player 2's fighter, the " << attacker2->getName();
			std::cout << " \"" << attacker2->getCustomName();
			std::cout << "\", is left with "<< attacker2->getStrength();
			std::cout << " strength points." << std::endl;
		}
	
		//if roundTrack is even, attacker2 attacks
		if ((roundTrack % 2) == 0)	
		{	
			int atk2;
			int dam2;

			//roll from attack() function saved in atk
			atk2 = attacker2->attack(roundTrack);
			
			//display fight commentary for fighter2 attack
			std::cout << std::endl;
			std::cout << "Player 2's fighter, the " << attacker2->getName();
			std::cout << " \"" << attacker2->getCustomName();
			std::cout << "\", attacked for " << atk2 << " points!!";
			std::cout << std::endl;
			
			//result of atk - attacker2 defend() roll saved in dam2
			dam2 = attacker1->defend(atk2, roundTrack);
			
			//makes sure there are no negative attributes
			if ((atk2 - dam2) < 0)
			{
				atk2 = 0;
				dam2 = 0;
			}
		
			//display fight commentary for fighter1 defend
			std::cout << std::endl;
			std::cout << "Player 1's fighter, the " << attacker1->getName();
			std::cout << " \"" << attacker1->getCustomName();
			std::cout << "\", defended for " << atk2 - dam2;
			std::cout << " points!!" << std::endl; 
			
			//fighter1 takes damage, after fighter1 defends
			attacker1->damage(dam2, roundTrack);
			
			//display round summary
			std::cout << std::endl;
			std::cout << "PLayer 1's fighter, the " << attacker1->getName();
			std::cout << " \"" << attacker1->getCustomName();
			std::cout << "\", is left with "<< attacker1->getStrength();
			std::cout << " strength points." << std::endl;
			
		}	

		//increment round to accurately display round #
		//increment roundTrack so next round it will have opposite 
		//parity
		round++;
		roundTrack++;
	}

	//if fighter1 has zero strength
	if (attacker1->getStrength() < 1)
	{
		//display winning statement for fighter2
		std::cout << std::endl << std::endl;
		std::cout << "Player 2's fighter, the " << attacker2->getName();
		std::cout << " \"" << attacker2->getCustomName();
		std::cout << "\", won the fight with " << attacker2->getStrength();
		std::cout << " strength points left!!" << std::endl;
		
		//add first fighter from team 1 to the loser queue
		queueL.addFront(queue1.getFront());
		//remove the first creature derived object from team 1
		queue1.removeFront();
		//reduce variable keeping track of queue size of team 1
		queueNum -=1 ;
		
		//add first fighter in queue for team 2 to the back of team 2
		queue2.addBack(queue2.getFront());
		//remove the first fighter from team 2 (they are now the last)
		queue2.removeFront();
		//regain some strength for winning creature
		queue2.getBack()->regainStrength();
		//increment team 2's score
		score2 += 1; 

		//display current points for each team
		std::cout << std::endl;
		std::cout << "Player 1's team now has " << score1 << " points!";
		std::cout << std::endl;
		std::cout << "Player 2's team now has " << score2 << " points!";
		std::cout << std::endl;

	}

	//if fighter2 has zero strength
	if (attacker2->getStrength() < 1)
	{
		//display winning statement for fighter1
		std::cout << std::endl << std::endl;
		std::cout << "Player 1's fighter, the " << attacker1->getName();
		std::cout << " \"" << attacker1->getCustomName();
		std::cout << "\", won the fight with " << attacker1->getStrength();
		std::cout << " strength points left!!" << std::endl;
	
		//add first creature on team 2 to losers queue
		queueL.addFront(queue2.getFront());
		//remove the first creature from team 2
		queue2.removeFront();
		//decrement the variable holding team 2 size
		queueNum2 -= 1;

		//add first creature form team 1 to the back of team 1
		queue1.addBack(queue1.getFront());
		//remove first creature from team 1 (they are now the back)
		queue1.removeFront();
		//regain some strength for the winning creature
		queue1.getBack()->regainStrength();
		//increment team 1's score
		score1 += 1;  

		//display current points for each team
		std::cout << std::endl;
		std::cout << "Player 1's team now has " << score1 << " points!";
		std::cout << std::endl;
		std::cout << "Player 2's team now has " << score2 << " points!";
		std::cout << std::endl;
		 
	}
		
}



//Function Name: queueMake()
//Parameters: none
//Return Value: none
//Description: uses the menu2() and chooseFighter() functions to have the 
//		user choose the fighters for both Player 1's team and Player
//		2's team
void Tournament::queueMake()
{
	int fightNum;
	std::string tempName;
	std::string tempName2;

	//get user input in integer form
	queueNum = menu2(1);
	queueNum2 = menu2(2);

	//for however large the user wants team 1
	for (int i=0; i < queueNum; i++)
	{
		//show fighter number
		std::cout << std::endl;
		std::cout << "Player 1, fighter ";
		std::cout << i+1 << ":" << std::endl;

		//have user choose fighter type in integer form
		std::cout << "Choose fighter type.";
		std::cout << std::endl;
		fightNum = menu();

		//add creature derived object corresponding to user input to 
		//back of team 1
		queue1.addBack(chooseFighter(fightNum));

		//have user set creature object's custom name
		std::cout << "Name this fighter.";
		getline(std::cin, tempName);

		queue1.getBack()->setCustomName(tempName);
	}

	//for however large the user wants team 2
	for (int i=0; i < queueNum2; i++)
	{
		//show fighter number
		std::cout << std::endl;
		std::cout << "Player 2, fighter ";
		std::cout << i + 1 << ":" << std::endl;

		//have user choose fighter type in integer form
		std::cout << "Choose fighter type.";
		std::cout << std::endl;
		fightNum = menu();

		//add creature derived object corresponding to user's choice to
		//back of team 2
		queue2.addBack(chooseFighter(fightNum));

		//have user set custom name for creature derived object
		std::cout << "Name this fighter.";
		getline(std::cin, tempName2);

		queue2.getBack()->setCustomName(tempName2);

	}
}



//Function Name: queueMake()
//Parameters: none
//Return Value: none
//Description: Initiates the attackSeq() function for as long as both teams
//		have at least 1 fighter.
void Tournament::start()
{
	//while both player 1 and player 2 have fighters left
	while ((queueNum2 > 0)&&(queueNum > 0))
	{
		attackSeq();
	}
					
}



//Function Name: print()
//Parameters: none
//Return Value: none
//Description: Displays the contents of all 3 queues held by the Tournament
//		class. 
void Tournament::print()
{
	queue1.print();
	std::cout << std::endl << std::endl;
	queue2.print();
	std::cout << std::endl << std::endl;
	queueL.print();
}
		


//Function Name: chooseFighter()
//Parameters: fChoice (int representing the users choice of fighter) 
//Return Value: Creature* (pointer to a selected dynamically allocated fighter)
//Description: Dynamically allocates and returns a new object of class derived 
//	       from creature class to represent the selected fighter.
Creature* Tournament::chooseFighter(int fChoice)
{
	//if choice is 1, dynamically allocate new Vampire class object and 
	//return it
	if (fChoice == 1)
	{
		Creature* vamp = new Vampire();

		return vamp;
	}

	//if choice is 2, dynamically allocate new Barbarian class object and 
	//return it
	if (fChoice == 2)
	{
		Creature* barb = new Barbarian();

		return barb;
	}

	//if choice is 3, dynamically allocate new BlueMen class object and 
	//return it
	if (fChoice == 3)
	{
		Creature* men = new BlueMen();
		
		return men;
	}

	//if choice is 4, dynamically allocate new Medusa class object and 
	//return it
	if (fChoice == 4)
	{
		Creature* med = new Medusa();
		
		return med;
	}	

	//if choice is 5, dynamically allocate new HarryPotter class object and 
	//return it
	if (fChoice == 5)
	{
		Creature* harry = new HarryPotter();
		
		return harry;
	}
}



//Function Name: printLoss()
//Parameters: none
//Return Value: none
//Description: Displays the contents of the loser queue.
void Tournament::printLoss()
{
	//have user decide whether or not to display the loser list
	int lossChoice = menu3();

	//if user decide to, display the loser list
	if (lossChoice == 1)
	{	
		queueL.print();
		std::cout << std::endl;
	}

	//clear all dynamically allocated memory for tournament
	queue1.~Queue();
	queue2.~Queue();
	queueL.~Queue();
}



//Function Name: ending()
//Parameters: none
//Return Value: none
//Description: Decide the winner and display the results of the tournament.
void Tournament::ending()
{
	if (score1 > score2)
	{
		std::cout << std::endl;
		std::cout << "Player 1 won the tournament with " << score1;
		std::cout << " points!" << std::endl;
		std::cout << "Player 2 lost the tournament with " << score2;
		std::cout << " points." << std::endl;
	}

	if (score2 > score1)
	{
		std::cout << std::endl;
		std::cout << "Player 2 won the tournament with " << score2;
		std::cout << " points!" << std::endl;
		std::cout << "Player 1 lost the tournament with " << score1;
		std::cout << " points." << std::endl;
	}

	if (score2 == score1)
	{
		std::cout << std::endl;
		std::cout << "The tournament is a draw!" << std::endl;
		std::cout << "Both Player 1 and Player 2 finished the ";
		std::cout << "tournament with " << score1 << " points.";
		std::cout << std::endl;
	}
}

