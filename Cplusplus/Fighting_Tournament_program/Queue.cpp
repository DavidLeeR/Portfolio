/****************************************************************************
 * File Name: Queue.cpp
 * Author: David Ramirez
 * Date: 5/28/17
 * Description: This is the function implementation file for the Queue class.
 * 		The Queue class implements a doubly linked circular queue using
 * 		the QueueNode struct. This class keeps 2 pointers to QueueNode 
 * 		(front and back) to keep track of the ends of the list and
 * 		to traverse the list. The Queue class has a default constructor
 * 		and a destructor. It has member functions to add a QueueNode 
 * 		to the back the queue, display the contents of the first 
 * 		QueueNode, remove the first QueueNode from the queue,
 * 		display the contents of each QueueNode in the queue (from
 * 		front to back), remove the last QueueNode from the queue, and
 * 		get the first and last QueueNode of the queue.
  *************************************************************************/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include "Queue.hpp"
#include "Creature.hpp"



//Function name: default constructor
//Parameters: none
//Return Value: none 
//Description: Creates an empty Queue class object
Queue::Queue()
{
	front = NULL;
	back = NULL;
}



//Function name: destructor
//Parameters: none
//Return Value: none 
//Description: Traverses doubly linked circular queue and deletes all
//	       dynamically allocated elements. 
Queue::~Queue()
{
	//if the list is not empty
	if (front != NULL)
	{
		//while the QueueNode behind the QueueNode pointed to by 
		//front is not the QueueNode pointed to by back
		while (front->prev != back)
		{
			//point front to the QueueNode behind it
			front = front->prev;
	
			//delete the QueueNode in front of the QueueNode pointed
			//to by front
			delete front->next->fighter;
			delete front->next;
		}
		
		//if there is only one QueueNode in the queue
		if (front == back)
		{
			//delete that QueueNode and set all pointer to NULL
			delete front->fighter;
			delete front;
			front = NULL;
			back = NULL;
		}

		//if there are 2 QueueNodes in the queue
		else 
		{
			//delete the QueueNode pointed to by front and point
			//front to NULL
			delete front->fighter;
			delete front;
			front = NULL;

			//delete the QueueNode pointed to by back and point 
			//back to NULL
			delete back->fighter;
			delete back;
			back = NULL;
		}
	}
}



//Function name: addBack()
//Parameters: creat (pointer to Creature to be saved in QueueNode)
//Return Value: none 
//Description: Dynamically allocates new QueueNode holding pointer to Creature
//and places it at the back of the queue.
void Queue::addBack(Creature* creat)
{
	//if the list is empty
	if(front == NULL)
	{	//dynamically allocate a new Node for front to point to
		front = new QueueNode;
		back = front;

		//fill in the value for the new QueueNode
		front->fighter = creat;
		
		//make the queue circular
		front->next = back;
		front->prev = back;
	}

	//if the queue has only 1 QueueNode in it
	else if (front == back)
	{
		//dynamically allocate a new QueueNode and place at back of 
		//queue
		back->prev = new QueueNode;

		//fill in all values for new QueueNode
		back->prev->fighter= creat;
		back->prev->next = back;
		back->prev->prev = front;

		//point back to new QueueNode (because it is at the very back
		//of the queue)
		back = back->prev;

		//keep the queue circular
		front->next = back;
		front->prev = back;
	}
	
	//if the queue has more than one QueueNode in it
	else
	{
		//dynamically allocate a new QueueNode and place at back of 
		//queue
		back->prev = new QueueNode;

		//fill in all values for new QueueNode
		back->prev->fighter = creat;
		back->prev->next = back;
		back->prev->prev = front;

		//point back to new QueueNode (because it is at the very back
		//of the queue)
		back = back->prev;

		//keep queue circular
		front->next = back;
	}
}



//Function name: addFront()
//Parameters: creat (pointer to Creature class to be saved in QueueNode)
//Return Value: none 
//Description: Dynamically allocates new QueueNode holding pointer to Creature
//and places it at the front of the queue.
void Queue::addFront(Creature* creat)
{
	//if the list is empty
	if(front == NULL)
	{	//dynamically allocate a new Node for front to point to
		front = new QueueNode;
		back = front;

		//fill in the value for the new QueueNode
		front->fighter = creat;
		
		//make the queue circular
		front->next = back;
		front->prev = back;
	}

	//if the queue has only 1 QueueNode in it
	else if (front == back)
	{
		//dynamically allocate a new QueueNode and place at back of 
		//queue
		front->next = new QueueNode;

		//fill in all values for new QueueNode
		front->next->fighter= creat;
		front->next->next = back;
		back->next->prev = front;

		//point back to new QueueNode (because it is at the very back
		//of the queue)
		front = front->next;

		//keep the queue circular
		back->next = front;
		back->prev = front;
	}
	
	//if the queue has more than one QueueNode in it
	else
	{
		//dynamically allocate a new QueueNode and place at back of 
		//queue
		front->next = new QueueNode;

		//fill in all values for new QueueNode
		front->next->fighter = creat;
		front->next->next = back;
		front->next->prev = front;

		//point back to new QueueNode (because it is at the very back
		//of the queue)
		front = front->next;

		//keep queue circular
		back->prev = front;
	}
}

//Function name: print()
//Parameters: none
//Return Value: none 
//Description: Traverses the queue from fron to back and prints the name 
//contents of each creature held by each QueueNode.
void Queue::print()
{
	//if queue is empty, output message
	if (front == NULL)
	{
		std::cout << std::endl;
		std::cout <<"The list of losers is empty." << std::endl;
	}

	//if queue is not empty, traverse queue from front to back and print 
	//name contents of each QueueNode creature
	else
	{
		//output queue prompt
		std::cout << "The list of losers holds: ";
		std::cout << front->fighter->getName() << " ";	
		std::cout << "\"" << front->fighter->getCustomName() << "\", ";

		//traverse queue (front to back) and print name contents of 
		//each QueueNode creature
		while (front->prev != back)
		{
			front = front->prev;
	
			std::cout << front->fighter->getName() << " ";
			std::cout << "\"" << front->fighter->getCustomName() << "\", ";

		}

		//if, after traversal, the front pointer (the one traversing) 
		//is in front of the back pointer
		if (front != back)
		{
			//display name contents of QueueNode creature
			//pointed to by back
			std::cout << back->fighter->getName() << " ";
			std::cout << "\"" << back->fighter->getCustomName() << "\" ";

		}

		//traverse the list (back to front) with the front pointer to 
		//place at the front of the list again
		while (front->next != back)
		{
			front = front->next;
		}
	}
}



//Function name: getFront()
//Parameters: none
//Return Value: Creature* (the contents of the first QueueNode in the queue) 
//Description: Returns the contents of the QueueNode at the front of the queue
Creature* Queue::getFront()
{
	//if queue is empty, return null
	if (front == NULL)
	{
		return NULL;
	}

	//if the queue is not empty, return the contents of the QueueNode at 
	//the front
	else 
	{
		return front->fighter;
	}
}



//Function name: getBack()
//Parameters: none
//Return Value: Creature* (the contents of the last QueueNode in the queue) 
//Description: Returns the contents of the QueueNode at the back of the queue
Creature* Queue::getBack()
{
	//if queue is empty, return null
	if (back == NULL)
	{
	
		return NULL;
	}

	//if the queue is not empty, return the contents of the QueueNode at 
	//the front
	else 
	{
		return back->fighter;
	}
}
//Function name: removeFront()
//Parameters: none
//Return Value: none
//Description: Deletes the QueueNode at the front of the queue and keeps all
//	       other QueueNodes in the queue doubly and circularly linked via
//	       pointers.
void Queue::removeFront()
{
	//if the queue is empty
	if (front == NULL)
	{
		//output statement
		std::cout << std::endl;
		std::cout << "The queue is empty." << std::endl;
	}

	//if there is only 1 QueueNode in the queue
	else if (front == back)
	{
		//delete that node and point both front and back to NULL
		delete front;
		front = NULL;
		back = NULL;
	}

	//if there is more than 1 QueueNode in the queue
	else
	{
		//point front to the QueueNode behind the first QueueNode
		front = front->prev;
		
		//delete the first QueueNode in the queue
		delete front->next;
		
		//keep the queue circularly connected
		front->next = back;

		//if there is only 1 QueueNode left in the queue after the 
		//removal
		if (front == back)
		{
			//keep queue circularly connected
			front->next = back;
			front->prev = back;
		}
			
	}
}
	
