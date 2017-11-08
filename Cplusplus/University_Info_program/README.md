**University Info program for Intro to Computer Science II at Oregon State University**

**Demonstrates:** inheritance, polymorphsm

**Steps to compile and run program:**                                                   
Requires g++ (GNU) compiler version 4.8.5                                                            
1) Download this directory (University_Info_program)                                      
2) navigate to University_Info_program directory with command line                                
3) enter the command **make university** to compile the program                                 
4) enter the command **./university** to run the program                                       
                                                                                           
**Requirements:** In this lab, you will write an information system for Oregon State University. Use classes as well as demonstrate a basic understanding of inheritance and polymorphism.

You will create a representation of an Oregon State University information system that contains information about the university. The university will contain a name of the university, n number of buildings, and m number of people. Buildings and people are contained in university as members. People can be either a student or an instructor. Every person will have a name and an age. Every student will have also have a GPA, but an instructor will NOT have a GPA. Instead, every instructor will have an instructor rating. Every building will have a name, the size in sqft (preferred the real value which you need to look up, and an address (stored as a string, also preferred to look this up). Note: If you choose to get the actual address and sizes of buildings that exist on campus, here is the link to look this up http://facilities.oregonstate.edu/buildings (Links to an external site.)Links to an external site., but this is not a hard requirement.

People will contain a method called “do_work(x)” that will take in an integer x as a parameter and generate a random number that represents how many hours they will do work for (you can set a range for the random number to make the working hours look realistic). If the person is a student, a message will be printed to the screen that says “PERSON_NAME did X hours of homework.” If the person is an instructor, a message will be printed to the screen that says “Instructor PERSON_NAME graded papers for X hours.” You will need to fill in the appropriate values.

The student GPA can either be an input from the user or a randomized number, but it must be between 0.0 and 4.0. It cannot be preset. The instructor rating can either be an input from the user or randomized, but it must be between 0.0 and 5.0. The ages of a person can be randomized or an input, but make it realistic.

The university will contain a method that will print the information of all the buildings in its information system (name, address and building's size) and another method that will print the information all the people (name, age, GPA or Rating). The name of the university MUST be “Oregon State University”.

You will have a menu that does at least the following:

1) Prints information of all the buildings

2) Prints information of everybody at the university

3) Choose a person to do work

4) Exit the program

You can add more options in the menu such as enter a new object information, that is up to you.

Note that option 3 will require you to print another menu that gives options for each person.

You may create any other functions, methods, member variables, etc. to modularize your code and complete the lab. You will manually instantiate at least 1 student, 1 instructor, and 2 buildings, then give them values and store them appropriately in the university object. You can do this in whatever fashion you wish, which means you can either instantiate those in your code, or have the user do the input.

Note: You may use vectors for this assignment if you so choose.

In your implementation, make sure that you include a program header in your program, in addition to proper indentation/spacing and other comments! Make sure you review the style guidelines for this class, and begin trying to follow them, i.e. don’t align everything on the left or put everything on one line! Also view the “Things not to do in the code” page and the “Things you need to do in your code” page as you will be held to these. Check your program on the flip to eliminate any compiling error or memory leak.

Electronically submit your C++ program files (only the source files, not the executable) along with a makefile in a zip file on TEACH. As usual, your zip file should not create a directory when unzipped and your makefile must be able to remove all files that are not .cpp or .hpp files (or any other source file) with a “make clean” command.
