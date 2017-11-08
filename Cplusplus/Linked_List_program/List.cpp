/****************************************************************************
 * File Name: List.cpp
 * Author: David Ramirez
 * Date: 5/14/17
 * Description: This is the function implementation file for the List class.
 * 		The List class implements a doubly linked list using the
 * 		Node struct. This class keeps 3 pointers to Node (head,tail
 * 		and point) to keep track of the ends of the list and to 
 * 		traverse the list. The List class has a default constructor
 * 		and a destructor. It has member functions to add or remove 
 * 		a Node from the head or tail of the list, print the list in
 * 		reverse, print the head or tail of the list, and load values
 * 		from a text file to create a list. 	
  *************************************************************************/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include "List.hpp"



//Function name: default constructor
//Parameters: none
//Return Value: none 
//Description: Creates an empty List class object
List::List()
{
	head = NULL;
	tail = NULL;
	point = NULL;
}



//Function name: destructor
//Parameters: none
//Return Value: none 
//Description: Traverses doubly linked list and deletes all Nodes until 
//	       list is empty
List::~List()
{
	if (head != NULL)
	{
		point = head;

		while (point->next != NULL)
		{
			point = point->next;
	
			delete point->prev;
			point->prev = NULL;
		}

		delete point;
		point = NULL;
		head = NULL;
		tail = NULL;
	}
}



//Function name: addHead()
//Parameters: input (integer representing value to be saved in Node)
//Return Value: none 
//Description: Dynamically allocates a new Node holding user input and places
//	       it at the head of the linked list
void List::addHead(int input)
{	//if the list is empty
	if(head == NULL)
	{	//dynamically allocate a new Node for head to point to
		head = new Node;
		tail = head;
		//fill in the values for the new Node
		head->value = input;
		head->next = NULL;
		head->prev = NULL;
	}

	else
	{
		//set the moving pointer to the head to start traversing
		point = tail;
		
		//while there is another Node past the one pointed to by point
		while (point->prev != NULL)
		{
			//set the moving pointer to the next Node
			point = point->prev;
		}

		//when the end of the list is reached, make a new node
		point->prev = new Node;

		//make tail point to the newly created last Node in the list
		head = point->prev;
		//fill in new node values
		head->value = input;
		head->next = point;
		head->prev = NULL;
	}
	//point to head to start traversing list
	point = head;

	//output list message
	std::cout << "The linked list holds: ";
	std::cout << point->value << " ";
	
	//traverse list (head to tail) and print
	while (point->next != NULL)
	{
		point = point->next;
		
		std::cout << point->value << " ";
	}		
}



//Function name: addTail()
//Parameters: input (integer representing value to be saved in Node)
//Return Value: none 
//Description: Dynamically allocates a new Node holding user input and places
//	       it at the tail of the linked list
void List::addTail(int input)
{
	//if the list is empty
	if (head == NULL)
	{
		//dynamically allocate a new Node for head to point to
		head = new Node;
		tail = head;
		//fill in values for new head Node
		head->value = input;
		head->next = NULL;
		head->prev = NULL;
	}

	//if the list is not empty
	else
	{
		//set the moving pointer to the head to start traversing
		point = head;
		
		//while there is another Node past the one pointed to by point
		while (point->next != NULL)
		{
			//set the moving pointer to the next Node
			point = point->next;
		}

		//when the end of the list is reached, make a new node
		point->next = new Node;

		//make tail point to the newly created last Node in the list
		tail = point->next;
		//fill in new node values
		tail->value = input;
		tail->next = NULL;
		tail->prev = point;
	}
	
	//point to head of list to start traversing
	point = head;
	
	//output list message
	std::cout << "The linked list holds: ";
	std::cout << point->value << " ";
	
	//traverse list (head to tail) and print
	while (point->next != NULL)
	{
		point = point->next;
		
		std::cout << point->value << " ";
	}
}


//Function name: addTail2()
//Parameters: input (integer representing value to be saved in Node)
//Return Value: none 
//Description: Dynamically allocates a new Node holding user input and places
//	       it at the tail of the linked list. The difference between 
//	       addTail() and addTail2() is that the latter does not have
//	       print functionality and is used by the load() function
//	       to create a list from file input.
void List::addTail2(int input)
{
	//if the list is empty
	if (head == NULL)
	{
		//dynamically allocate a new Node for head to point to
		head = new Node;
		tail = head;
		//fill in values for new head Node
		head->value = input;
		head->next = NULL;
		head->prev = NULL;
	}

	//if the list is not empty
	else
	{
		//set the moving pointer to the head to start traversing
		point = head;
		
		//while there is another Node past the one pointed to by point
		while (point->next != NULL)
		{
			//set the moving pointer to the next Node
			point = point->next;
		}

		//when the end of the list is reached, make a new node
		point->next = new Node;

		//make tail point to the newly created last Node in the list
		tail = point->next;
		//fill in new node values
		tail->value = input;
		tail->next = NULL;
		tail->prev = point;
	}

}



//Function name: remHead()
//Parameters: none
//Return Value: none 
//Description: Deletes the Node at the head of the list and frees
//	       the dynamically allocated memory
void List::remHead()
{
	int empty = 0;	//used to prevent the 'empty' message from repeating

	//if list is empty, print message
	if (head == NULL)
	{
		std::cout << std::endl;
		std::cout << "The list is empty." << std::endl;

		//increment to 1 so 'empty' message at end of function
		//is not printed 
		empty = 1;
	}

	//if list only has 1 Node, delete the Node and free the memory
	else if (head->next == NULL)
	{
		delete head;
		head = NULL;
		tail = NULL;
	}

	//if the list has more than 1 node, move the head pointer down
	//the list by 1 and delete the previous Node
	else
	{
		head = head->next;
		point = head->prev;
		delete point;
		head->prev = NULL;
	}
	
	//if list not empty, print the list contents
	if (head != NULL)
	{
		point = head;
		std::cout << "The linked list holds: ";
		std::cout << point->value << " ";
	
		//traverse list (head to tail) and print
		while (point->next != NULL)
		{
			point = point->next;
		
			std::cout << point->value << " ";
		}
	}
	
	//if list is now empty and the 'empty' message has not already
	//been displayed, display it
	if ((head == NULL)&&(empty ==0 ))
	{
		std::cout << std::endl;
		std::cout << "The list is empty." << std::endl;
	}
}



//Function name: remTail()
//Parameters: none
//Return Value: none 
//Description: Deletes the Node at the tail of the list and frees
//	       the dynamically allocated memory
void List::remTail()
{
	int empty = 0;	//used to prevent the 'empty' message from repeating

	//if list is empty, print message
	if (head == NULL)
	{
		std::cout << std::endl;
		std::cout << "The list is empty." << std::endl;
		
		//increment to 1 so 'empty' message at end of function
		//is not printed
		empty = 1;
	}

	//if list only has 1 Node, delete the Node and free the memory
	else if (tail->prev == NULL)
	{
		delete tail;
		tail = NULL;
		head = NULL;
	}

	//if the list has more than 1 Node. move the head pointer down
	//the list by 1 and delete the previous Node
	else
	{
		tail = tail->prev;
		point = tail->next;
		delete point;
		tail->next = NULL;
	}

	//if list is not empty, print the list contents
	if (head != NULL)
	{
		point = head;
		std::cout << "The linked list holds: ";
		std::cout << point->value << " ";
	
		//traverse the list (head to tail) and print
		while (point->next != NULL)
		{
			point = point->next;
		
			std::cout << point->value << " ";
		}
	}
	
	//if list is now emoty and the 'empty' message has not already
	//been displayed, display it
	if ((head == NULL)&&(empty == 0))
	{
		std::cout << std::endl;
		std::cout << "The list is empty." << std::endl;
	}

}



//Function name: revPrint()
//Parameters: none
//Return Value: none 
//Description: Traverses the list reversly and prints the contents of each
//	       Node
void List::revPrint()
{
	//if list is empty, output message
	if (head == NULL)
	{
		std::cout << std::endl;
		std::cout <<"The list is empty." << std::endl;
	}

	//if list is not empty, traverse list reversely and print contents of
	//each Node
	else
	{
		//start at tail of list
		point = tail;
		std::cout << "The linked list in reverse holds: ";
		std::cout << point->value << " ";	

		//traverse list (tail to head) and print
		while (point->prev != NULL)
		{
			point = point->prev;
	
			std::cout << point->value << " ";
		}
	}
}



//Function name: printHead()
//Parameters: none
//Return Value: none 
//Description: Outputs the contents of the Node at the head of the list
void List::printHead()
{
	//if list is empty, ouput message
	if (head == NULL)
	{
		std::cout << std::endl;
		std::cout << "The list is empty." << std::endl;
	}

	//if the list is not empty, print the contents of the Node at the head
	else 
	{
		std::cout << std::endl;
		std::cout << "The head of the list holds: ";
		std::cout << head->value << std::endl;
	}
}



//Function name: printTail()
//Parameters: none
//Return Value: none 
//Description: Outputs the contents of the Node at the tail of the list
void List::printTail()
{
	//if list is empty, output message
	if (head == NULL)
	{
		std::cout << std::endl;
		std::cout << "The list is empty." << std::endl;
	}

	//if list is not empty, output the content of the Node at the tail
	else 
	{
		std::cout << std::endl;
		std::cout << "The tail of the list holds: ";
		std::cout << tail->value << std::endl;
	}
}



//Function name: loadList()
//Parameters: none
//Return Value: none 
//Description: Creates a doubly linked list from file (data.txt) input by 
//	       dynamically allocating new Nodes. Uses the addTail2() function.
void List::loadList()
{
	//holds input from file
	int fileIn;
	
	std::ifstream inputFile;

	//open file
	inputFile.open("data.txt");
	
	//while end of file not yet reached, add new Node holding file input 
	//to tail of linked list 
	while (inputFile >> fileIn)
	{
		this->addTail2(fileIn);
	}

	//close file
	inputFile.close();

	//point to head to traverse list
	point = head;
	std::cout << "The linked list holds: ";
	std::cout << point->value << " ";
	
	//traverse list (head to tail) and print
	while (point->next != NULL)
	{
		point = point->next;
		
		std::cout << point->value << " ";
	}
	
}	

