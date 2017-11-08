/****************************************************************************
 * File Name: Queue.hpp
 * Author: David Ramirez
 * Date: 5/28/17
 * Description: This is the header file for the Queue class.
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



#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "QueueNode.hpp"
#include "Creature.hpp"



class Queue
{
	private:
	QueueNode* front;
	QueueNode* back;

	public:
	Queue();
	~Queue();
	void addBack(Creature*);
	void addFront(Creature*);
	Creature* getFront();
	Creature* getBack();
	void removeFront();
	void print();

};

#endif
