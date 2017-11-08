**STL Containers program 8 for Intro to Computer Science II at Oregon State University.**

**Demonstrates:** implementing linear data strutures using STL containers

**Steps to compile and run program:**                                                   
Requires g++ (GNU) compiler version 4.8.5                                                            
1) Download this directory (STL_Container_program)                                      
2) navigate to STL_Container_program directory with command line                                
3) enter the command **make stlcontainer** to compile the program                                 
4) enter the command **./stlcontainer** to run the program                                       

**Requirements:** In this lab, you will create two data structures: a stack and a queue. You will use STL containers to for these data structures. Look up Standard Template Library in the back of the Gaddis book if you have it.

 

Queue

For the queue, you will simulate a buffer. Remember it is first-in-first-out. The user will enter a number for the number of rounds to run your simulation. You need one function that randomly generates a number. You will also have a user specified percentage, and the function uses this percentage to randomly put the generated number in the buffer.  For example, if the user enters 25, then there is a 25% chance of the randomly generated number been put into the queue. You will have another user specified percentage, which is the chance of a value being removed from the buffer. For example, if the user enters 50, then there is a 50% chance of the number in the buffer been removed in this round.

 

Examples:

round starts 

   roll a random number (you can restrict it to 1-1000 for example)
   roll a random between 1-100, and if the outcome is less than the number the user chose for % chance, the number from step 1 gets added to the buffer
    roll another random between 1-100, and if the outcome is less than the number the user chose for % chance that something gets removed from the buffer, then pop the first number off the buffer (if there is anything to pop). It takes from the front of the buffer.

round is over, start over if there are more rounds to do

 (The buffer is first-in-first-out. 

  remove from here ---> [97][5][1][6][3][81] <--- add new ones here)

You need to record the length of the queue in each round.  After each round of the simulation, calculate and display the average length of the queue. Equation to calculate the average length would be: ALi = (ALi-1 * (i-1) + Li ) / i, where ALi and ALi-1 are the average length in the ith and i-1th round and Li is queue length in the ith round.  (It is enough to print the average length of the queue after each round. You may find that it is helpful to print additional info to show that your program is working, but the contents of the queue don't need to be printed to meet the assignment requirements.) Does your buffer behave as expected, i.e. get longer if the input chance is greater, and get shorter if the removing chance is greater? Your program needs to handle the situation when the queue is empty and still try to remove a value.  You can start the simulation with a queue of certain length.

 

Stack

Use a stack to create a function that creates a palindrome, i.e. a string that is the same forwards and backwards. It does not need to be an actual word. The function will receive a string from user input and it will return the string with the palindrome.  For example, if you enter a string “abc”, your program will return “abccba”. If you added in all the values of the original string sequentially to the stack, they would be in reverse order when you then went to pop them off, which you might then use to add those characters on to the original string.

 

Testing program

Create a menu program for the user to test your buffer and to create a palindrome. For the queue, prompt the user to enter the two chances and the total number of rounds. Display the results to the screen in each round. For the stack, prompt them to enter a string. Create the palindrome and then display it.  You can determine how this menu program should look like as long as it test the queue and stack properly.
