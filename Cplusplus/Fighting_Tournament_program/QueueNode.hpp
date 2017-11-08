/****************************************************************************
 * File Name: QueueNode.hpp
 * Author: David Ramirez
 * Date: 5/28/17
 * Description: This is the header file for the QueueNode structure. This file 
 * 	        containes the declaration of the QueueNode structure. This 
 * 	        structure is designed to be used in a doubly linked circular
 * 	        queue. This structure holds a pointer to a Creature class object
 * 	        and 2 pointers to QueueNode in order to point to the next 
 * 	        QueueNode and the previous QueueNode.
  *************************************************************************/



#ifndef NODE_HPP
#define NODE_HPP

#include "Creature.hpp"

struct QueueNode
{
	Creature* fighter;
	QueueNode* next;
	QueueNode* prev;
};

#endif
