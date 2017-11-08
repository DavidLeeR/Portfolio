**Fighting Tournament program for Intro to Computer Science II at Oregon State University.**

**Description:** Implements a fantasy combat tournament 

**Steps to compile and run program:**
Requires g++ (GNU) compiler version 4.8.5                                        
1) Download this directory (Fighting_Tournament_program)
2) navigate to Fighting_Tournament_program directory with command line
3) enter the command **make fight** to compile the program
4) enter the command **./fight** to run the program

**Demonstrates:** Inheritance, using linked structure to hold and manipulate data, abstract classes

**Requirements:** In this project, you will write a program to run a tournament.  Start with your project 3 program for creatures. If you had issues with project 3 and need to begin fresh, reference the creature descriptions from project 3 to build your fighters.

This is a one-user-two-players game. A user will enter the number of fighters both players will use.  (You can limit the number of fighters in each team, but set it a little bit larger, like 10, or 20 to allow the enough testing.) The user should also enter the type of creatures and fighter names. You can give fighters different names.  So player A’s first fighter could by Harry Potter and he could name the Harry Potter Creature "Larry Snotter" or just Harry Potter No.1. One team could have more than 1 of the same character (e.g. Team A has 3 members: 2 barbarians and 1 harry potter). The first player supplies a lineup of creatures in order. The second player then supplies his lineup of creatures in order. By lineup I mean something like a batting order in baseball or softball. The head of each lineup fight in the same way they fight in project 3. The winner gets put at the back of her/his team’s lineup; the loser goes to the container for those who lost (there should be only one loser pile shared between both sides). The lineup order cannot be changed once the players are entered. Similarly, the loser pile should have the last loser at the top and the first loser at the bottom.

Even if a creature wins, she/he may have taken damage. You should restore some percentage of the damage when they get back in line. Make this simple as you are adding a new member function to the parent class. Some examples are: generate a random integer in some ranges, e.g., on a roll of 5 they recover 50% of the damage they lost, or some scheme of your own. If you want to use a different recovery function for each character, that is fine. Remember to use polymorphism if the recovery is different for different creatures!

After each round, you will display which type of creatures fought and which won on screen (For example, Round 1: Team A Blue man No.1 VS. Team B Harry Potter No.1, Harry Potter No.1 won!). At the end of the tournament (when one team or both run out of fighters in the lineup), your program will display final total points for each team (you can determine how to score each round of fight, for example, winner team +2, loser team -1, tie +1).  You must display which team won the tournament. This is another element you must define in the analysis and design stage. You must have a method to determine the winner and you can determine it by yourself. Also provide an option at the end of the tournament to display the contents of the loser pile, i.e. print them out in order with the loser of the first round displayed last.

You should be using polymorphism and all creatures will inherit from the Creature class. Each object should be instantiated and put into their lineup. You will only use pointers to creatures in your program. A creature pointer can then be used to indicate an object of a subclass and polymorphism will ensure the correct function is called. Ask your TA if you are uncertain what this means.

NOTE: Depending upon your implementation in Project 3, you could have ties. How does that tie change your end of match logic? What do you do if the final match is a tie? Specifically, where do you put the fighters?  For this program, you should use stack-like or queue-like structures to hold the lineups and the loser pile. Which will you use for the lineup? Which will you use for the loser pile?

This is a programming assignment and not a complete game! Other than entering the lineup, the players just wait for the results. They should take no further actions. Make sure you test your program with instances of all creature types you’ve created. You may not be able to do an exhaustive test, but make it as extensive as you can. In the menu, please add an option that ask players if they would like to play again once the winner has been declared (it's nice for grading since we run it multiple times).

For this project, 4 please use your own containers like queue and linked list instead of the STL containers.

Note that this project uses project 3 as a starting point.  Since we could not release a sample code of project 3 now because some of you will turn in it late, so you have to figure out how to implement those details based on project 3 by yourself. But you will not be penalized twice. 
