/****************************************************************************
 * File Name: List.hpp
 * Author: David Ramirez
 * Date: 5/14/17
 * Description: This is the header file for the List class.
 * 		The List class implements a doubly linked list using the
 * 		Node struct. This class keeps 3 pointers to Node (head,tail
 * 		and point) to keep track of the ends of the list and to 
 * 		traverse the list. The List class has a default constructor
 * 		and a destructor. It has member functions to add or remove 
 * 		a Node from the head or tail of the list, print the list in
 * 		reverse, print the head or tail of the list, and load values
 * 		from a text file to create a list. 	
  *************************************************************************/




#ifndef LIST_HPP
#define LIST_HPP

#include "Node.hpp"

class List
{
	private:
	Node* head;
	Node* tail;
	Node* point;

	public:
	List();
	~List();
	void addHead(int);
	void addTail(int);
	void addTail2(int);
	void remHead();
	void remTail();
	void revPrint();
	void printHead();
	void printTail();
	void loadList();
};

#endif
