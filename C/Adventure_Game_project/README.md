**Adventure Game project created for the course "Operating Systems" at Oregon State University**

**Description:** Simple text based survival game with randomized rooms.

**Instructions to compile and run programs:**                                      
Requires gcc (GNU) compiler 4.8.5                                                   
1)compile ramirdav.buildRooms.c with the command **gcc ramirdav.buildRooms.c -o build**                                 
2)run ramirdav.buildRooms.c with the command **./build** to create the room files needed for ramirdav.adventure.c            
3)compile ramirdav.adventure.c with the command **gcc ramirdav.adventure.c -o game**                                        
4)run ramirdav.adventure.c with the command **./game**    
                                                                            
**Demonstrates:** file I/O, multithreading, mutexes (linux)                                                                                             
**Requirements:** This assignment is split up into two programs. The first program (hereafter called the "rooms program") will be contained in a file named "<STUDENT ONID USERNAME>.buildrooms.c", which when compiled with the same name (minus the extension) and run creates a series of files that hold descriptions of the in-game rooms and how the rooms are connected.

The second program (hereafter called the "game") will be called "<STUDENT ONID USERNAME>.adventure.c" and when compiled with the same name (minus the extension) and run provides an interface for playing the game using the most recently generated rooms.

In the game, the player will begin in the "starting room" and will win the game automatically upon entering the "ending room", which causes the game to exit, displaying the path taken by the player.

During the game, the player can also enter a command that returns the current time - this functionality utilizes mutexes and multithreading.
