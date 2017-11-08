**Langton's Ant program for Intro to Computer Science II at Oregon State University**

**Description:**
C++ implementation of "Langton's Ant", a two-dimensional universal turing machine.

**Steps to compile and run program:**                                                   
Requires g++ (GNU) compiler version 4.8.5                                                            
1) Download this directory (Langtons_Ant_program)                                      
2) navigate to Langtons_Ant_program directory with command line                                
3) enter the command **make ant** to compile the program                                 
4) enter the command **./ant** to run the program                                       

**Demonstrates:** arrays                                   
                                                              
**Requirements:** You will design, implement, and test a program that implements a simulation of Langton's Ant.  For a brief explanation consider Wikipedia:  https://en.wikipedia.org/wiki/Langton%27s_ant (Links to an external site.)Links to an external site..  Note that it can be considered as a cellular automaton.  This means that you have an array or matrix of cells.  Each turn or step, the value of each cell may change based upon a simple rule. 

For the Ant there are two simple rules.  The rules are: 

    In a white square, turn right 90o and change the square to black.
    In a black square, turn left 90o and change the square to white.

You should use a blank character for a white space, and use the number sign for the black space.  And for the Ant?  "@" works fine. (You can use other sign as long as it is easy to see.) Left ?  Right?  Those are relative directions!  How are you going to keep track of the direction the Ant is facing?  How will you remember what color the current cell occupied by the Ant is or was?  You will create an Ant class to help organize, hold, and manipulate this information. 

Your program will prompt the user to enter the number of rows and columns for the 2D array.  You should also prompt the user for the number of steps.  If you want to limit the size of the board or number of steps, suggest values to the user.  (You are suggested to choose a size that is no larger than the default width 80 when you are developing).  Your program should display each step by printing out the whole board.  Use functional decomposition to develop functions to validate the input. (You can make a validation class if you would like.)  You should start by asking the user for the starting location of the Ant.  For testing purposes, always start the Ant at the same location.  Then try different locations. Remember that when you create the array dynamically, you need to de-allocate the space to avoid memory leaks. You can use valgrind to check for memory leaks.

Then what if the ant meets a wall collision (i.e. ant attempts to step out of the bounds of the array)? Think about the corner case. For example, the ant makes it to the edge of the game board, and according to the rule, it needs to make a turn and end up getting out of the game board. It is your design decision, and make sure it is properly handled. Previously, students tried different actions, such as â€œskip the step forward step, make another turn and then continue on, or wrap the board around so that the ant will appear on the other side, or turn the ant around and send it back onto the board.  As long as it makes sense, you are fine. But do not terminate the game before it reaches the designated step.

In this project, you are asked to implement a menu function that can be reused in later programs. A menu function is something that is printed to the screen that gives the user options, as if you were using a DVD menu, or a video game menu.  It should then verify the user's input and return something to tell the rest of the program what the user chose.  For example:

1) Start program

2) Do task 1

3) Do task 2

4) Do task 3

5) Play again

6) Quit

It can be used in future programs by having it be easily changeable to whatever program you are writing. If you want to write a menu class instead of a menu function, that is totally fine as well.

You will create your design document BEFORE you start coding and include that in your reflections.  Simply stated, program design is identifying the problem to be solved, identify the inputs, specify the desired output, and then develop the algorithm(s) to convert the input into the output.  In your reflections document, you should also explain how you have to change the design because your first idea didnâ€™t work.  Explain what you learned during this project.  The TA will grade on how well your implementation matches your design.

Note:  There are a lot of details that are not determined in this requirement.  They are left for you to decide, as long as your program meets the required rules in the grading part.  For more questions, ask your grading TA for clarification or post it on Piazza.

 

Extra Credit (5%):

Add the option for the user to have a random starting location of the Ant.  If you have this option, you must tell users at beginning and give instructions on how to choose this option. Otherwise, TA wonâ€™t test this function and give extra credit.


