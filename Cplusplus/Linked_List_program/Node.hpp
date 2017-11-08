/****************************************************************************
 * File Name: Node.hpp
 * Author: David Ramirez
 * Date: 5/14/17
 * Description: This is the header file for the Node structure. This file 
 * 	        containes the declaration of the Node structure. The Node 
 * 	        structure is designed to be used in a doubly linked
 * 	        list. The Node structure holds an integer value and 2 pointers 
 * 	        to Node in order to poin to the next Node and the previous Node.
  *************************************************************************/



#ifndef NODE_HPP
#define NODE_HPP


struct Node
{
	int value;
	Node* next;
	Node* prev;
};

#endif
