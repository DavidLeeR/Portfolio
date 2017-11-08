**Linked List program for Intro to Computer Science II at Oregon State University**

**Demonstrates:** creating double linked lists with pointers, manipulating linked lists

**Steps to compile and run program:**                                                   
Requires g++ (GNU) compiler version 4.8.5                                                            
1) Download this directory (Fighting_Tournament_program)                                      
2) navigate to Grocery_List_program directory with command line                                
3) enter the command **make linkedlist** to compile the program                                 
4) enter the command **./linkedlist** to run the program                                       

**Assignment description:** In this lab, you will create a simple double linked structures consisting of Node objects. Each node will have a pointer to the next node and a pointer to the previous node.  You will use a head pointer to keep track of the first node in the linked list, and a tail pointer to keep track of the last node in the linked list. Set both head and tail to NULL when the list is empty. You will store an integer in each node.  You can assume all the integers are positive numbers.  You will create the list dynamically by user input.

Implement following functions in the linked list:

    Add a new node to the head;
    Add a new node to the tail;
    Delete from head (the first node in the list);
    Delete from tail (the last node in the list);
    Traverse the list reversely, that is to print the node from back to the forth.

When user tries to add a new node (functions 1&2), your program will prompt the user to enter a number and validate the input, create a new node in the list, store the value properly, change the head/tail pointers and print the current whole list from head to the tail.

When user tries to delete a node (functions 3&4), your program should check whether the list is empty, if so, give a warning message, and if not, delete the node properly and free the memory, then point the head/tail pointers to the new position, and print out the whole list.

When user tries to print the list from tail to the head (functions 5), your program will print the value from the last node to the first node. If the list is empty, print a message to indicate that.

You need to add one more option in your menu to exit the program.

For this lab, you will not implement the linked list operations using functions/methods that from an outside source.  That means you need to write all the functions by yourself.

Extra credit

Task 1 (10%): add two more options to print the head or the tail node value.

Task 2 (15%): create a linked list from reading a text file. You can create your own text file with some numbers in it, and your program should have an option to create the list from the text file at the very beginning. Then users will continue to manipulate on the existing list.

You need to indicate the grader that you did extra credit task at the beginning of your program to get the credit.
