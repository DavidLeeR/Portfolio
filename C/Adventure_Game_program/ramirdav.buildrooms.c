/***************************************************************
 * Author: David Ramirez
 * Date: 10/26/2017
 * Description: This program creates a series of files that hold 
 * 		descriptions of rooms used for a simple text based
 * 		game. The room files also contain the connections
 * 		between rooms.   
 ***************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


//struct to hold data pertaining to each room
struct room
{	
	char* name;
        char* type;
        char* conn[6];
        int numConn;
};

//global array of room structs 
//-- representing the 7 rooms used for the game
struct room roomArr[7];

//global strings representing room names
//-- 7 out of the 10 will be randomly chosen for each program run
/*char* stan = "Stan";
char* rooms[1] = "Phil";
char* rooms[2] = "Carl";
char* rooms[3] = "Kurt";
char* rooms[4] = "Kirk";
char* rooms[5] = "John";
char* rooms[6] = "Pete";
char* rooms[7] = "Ross";
char* rooms[8] = "Bill";
char* rooms[9] = "Ralf";
*/
char* rooms[10] = {"Stan", "Phil", "Carl", "Kurt", "Kirk", "John", "Pete", "Ross", "Bill", "Ralf"};

//global strings representing the template of the room data written to each 
//room file
char* nameTemp = "ROOM NAME: ";
char* typeTemp = "ROOM TYPE: ";
char* connTemp = "CONNECTION";
char* connEnd = ": ";

//all function prototypes
int isFull();
void addConn();
int addFrom(int);
int connExists(int, int);
void connRoom(int, int);
int sameRoom(int, int);
void createFiles();
void fillRooms();
void fillNames();
int sameName(char*);
void initNumConn();
		

//fills the name element of each room in the array
//--7 of the 10 possible names will be chosen (1 per room) with no repeats
void fillNames()
{
	int choice;
	int forever = 1;
	int count = 0;
	int limit = 7;

	//for each struct room in the array
	for (count; count < limit; count++)
	{
		//reset forever to 1 after each iteration of the for loop
		forever = 1;
	
	while (forever == 1)
	{
		//randomly choose a number that represents each room name (0-9)
		choice = rand() % 10;

		//for each of the following 10 if statements the logic is as 
		//follows: check for value of choice, make sure name that 
		//corresponds to value of choice has not already been used,
		//set current room struct name to name that corresponds to 
		//value of choice, move on to next room struct in array
		if (choice == 0 && sameName(rooms[0]) == 0)
		{
			roomArr[count].name = rooms[0];
			//set to 0 to break out of while loop
			forever = 0;
		}
		if (choice == 1 && sameName(rooms[1]) == 0)
                {
                        roomArr[count].name = rooms[1];
                        forever = 0;
                }
		if (choice == 2 && sameName(rooms[2]) == 0)
                {
                        roomArr[count].name = rooms[2];
                        forever = 0;
                }
		if (choice == 3 && sameName(rooms[3]) == 0)
                {
                        roomArr[count].name = rooms[3];
                        forever = 0;
                }
		if (choice == 4 && sameName(rooms[4]) == 0)
                {
                        roomArr[count].name = rooms[4];
                        forever = 0;
                }
		if (choice == 5 && sameName(rooms[5]) == 0)
                {
                        roomArr[count].name = rooms[5];
                        forever = 0;
                }
		if (choice == 6 && sameName(rooms[6]) == 0)
                {
                        roomArr[count].name = rooms[6];
                        forever = 0;
                }
		if (choice == 7 && sameName(rooms[7]) == 0)
                {
                        roomArr[count].name = rooms[7];
                        forever = 0;
                }
		if (choice == 8 && sameName(rooms[8]) == 0)
                {
                        roomArr[count].name = rooms[8];
                        forever = 0;
                }
		if (choice == 9 && sameName(rooms[9]) == 0)
                {
                        roomArr[count].name = rooms[9];
                        forever = 0;
                }
	}
	}
	
}

//Randomly fills the type element of each room struct in the array
//-- start and end are used only once, and mid is used for each other room
void fillTypes()
{
	char* start = "START_ROOM";
        char* mid = "MID_ROOM";
        char* end = "END_ROOM";

	int select = rand() % 7;
	int hasType; //keeps track of which room is has start type
	int hasType2;  //keeps track of which room has end type

	//using randomly genereated int (select), assign a room in the array
	//the start type and keep track of this room
	switch(select)
	{
		case 0: 
			roomArr[select].type = start;
			hasType = select;
                        break;

		case 1:
                        roomArr[select].type = start;
			hasType = select;
			break;
		case 2:
                        roomArr[select].type = start;
			hasType = select;
                        break;
		case 3:
                        roomArr[select].type = start;
			hasType = select;
                        break;
		case 4:
                        roomArr[select].type = start;
			hasType = select;
                        break;
		case 5:
                        roomArr[select].type = start;
			hasType = select;
                        break;
		case 6:
                        roomArr[select].type = start;
			hasType = select;
                        break;
	}

	select = rand() % 7;

	//using randomly genereated int (select), assign a room in the array,
	//that does not have the start type, the end type and keep track of this
	//room
        switch(select)
        {	
                case 0:
			if (hasType != 0)
			{
                        	roomArr[select].type = end;
				hasType2 = select;
                        	break;
			}
                case 1:
			if (hasType != 1)
                        {
                        	roomArr[select].type = end;
				hasType2 = select;
                        }	break;
                case 2:
			if (hasType != 2)
                        {
                        	roomArr[select].type = end;
				hasType2 = select;
                        	break;
			}
                case 3:
			if (hasType != 3)
                        {
                        	roomArr[select].type = end;
				hasType2 = select;
                        	break;
			}
                case 4:
			if (hasType != 4)
                        {

                        	roomArr[select].type = end;
				hasType2 = select;
                       		break;
			}
                case 5:
			if (hasType != 5)
			{
                        	roomArr[select].type = end;
				hasType2 = select;
                        	break;
			}
                case 6:
			if (hasType != 6)
                        {
                        	roomArr[select].type = end;
				hasType2 = select;
                        	break;
			}
	}

	//iterate through each room in array, assigning each room that does not
	//already have a type to the mid type
	int count = 0;
	int limit = 7;
	for (count; count < limit; count++)
	{
		if ((count != hasType)&&(count != hasType2))
			roomArr[count].type = mid;
	}
	
}
	
//returns 1 is the parameter name is already in use by the array of rooms and
//returns 0 if not
int sameName(char* testName)
{
	//iterate through each room in array and check if parameter name matches
	//room name
	int limit = 7;
	int count = 0;
	for(count; count < limit; count++)
	{
		if (roomArr[count].name == testName)
			return 1;
	}

	return 0;
}



//returns 1 if each room has 3 - 6 outbound connections, 0 if not
int isFull()
{
	int check = 0;  //keeps track of if <3 connection in a room

	//iterate through each room in array, checking if connection are <3
	int count = 0;
	int limit = 7;
	for (count; count < limit; count++)
	{
		if (roomArr[count].numConn < 3)
			check = 1;
	}

	if (check == 0)
		return 1;
	else
		return 0;		
}

//performs logic checks that make sure that the appropriate connections are 
//being added to each room in the array
void addConn()
{
	int roomNumA;
	int roomNumB;
	int check = 1;

	//search room array for room that can have connection added
	while(check == 1)
	{
		//used for index in room array
		roomNumA = rand() % 7;

		//if the room in question can have a connection added, break 
		//from loop
		if (addFrom(roomNumA) == 1)
			check = 0;
	}

	//keep looking for room in array that can have a connection added,
	//is not the same room as the previously chosen room, and does not
	//already have a connection to the room previously chosen
	do
	{
		//used for index in room array
		roomNumB = rand() % 7;
	}
	while(addFrom(roomNumB) == 0 || sameRoom(roomNumA, roomNumB) == 1 || 
	connExists(roomNumA, roomNumB) == 1);

	//add connection to both eligable rooms
	connRoom(roomNumA, roomNumB);
	connRoom(roomNumB, roomNumA);
}


//returns 1 if connection can be added to parameter indexed room, 0 if not
int addFrom(int roomNum)
{
	//if parameter room has more than 5 connections, return 0
	if (roomArr[roomNum].numConn > 5)
		return 0;
	
	else
		return 1;
}


//returns 1 if connection between the passed rooms exists, 0 if not
int connExists(int roomNum1, int roomNum2)
{
	//step through each room in array, checking if the connection value
	//matches the name value of the other parameter room
	int limit = roomArr[roomNum1].numConn;
	int count = 0;
	for(count; count < limit; count++)
	{
		if (roomArr[roomNum1].conn[count] == roomArr[roomNum2].name)
			return 1;
	} 

	return 0;
}


//connects the two parameter rooms
void connRoom(int roomNum1, int roomNum2)
{
	//find index to add connection to
	int index = roomArr[roomNum1].numConn;
	
	//add connection
	roomArr[roomNum1].conn[index] = roomArr[roomNum2].name;	

	//had to include this if/else because it would assign an address to 
	//numConn when above 5 otherwise (not sure why)
	if (index == 5)
		roomArr[roomNum1].numConn = 6;
	
	else
		roomArr[roomNum1].numConn = roomArr[roomNum1].numConn + 1; 

}


//returns 1 if the two parameter rooms share the same name, 0 if else
int sameRoom(int roomNum1, int roomNum2)
{
	//if index of room 1 == index of room 2
	if (roomNum1 == roomNum2)
		return 1;
	else
		return 0;
}


//creates directory as well as files for each room in the array and writes 
//data from each room in the array to a separate file
void createFiles()
{
	//postfix of room file for file path
	char roomPost1[50] = "/";
	strcat(roomPost1, roomArr[0].name);
	strcat(roomPost1,"\0");

	//get process id, convert to string, and save to variable "pid"
	char pid[10];
	int pidNum = getpid();
	sprintf(pid, "%d", pidNum);
	
	//prefix for room file path
	char dirPrefix[15] = "ramirdav.rooms.";
	strcat(dirPrefix, pid);
	char dirPre1[50];
	strcpy(dirPre1, dirPrefix);

	//cat room1, prefix, and postfix to make complete file path
	char room1[] = "./";
	strcat(room1, dirPre1);
	strcat(room1, roomPost1);

	//create endings for each subsequent file
	char num2[] = "2";
	char num3[] = "3";
	char num4[] = "4";
	char num5[] = "5";
	char num6[] = "6";
	char num7[] = "7";

	//create variables to hold room path for each subsequent file
	char room2[50];
	char room3[50];
	char room4[50];
	char room5[50];
	char room6[50];
	char room7[50];

	//modify first file path to make path for file 2
	int nameLen = strlen(room1);
	strncpy(room2, room1, nameLen - 4);
	room2[nameLen -4] = 0;
	strcat(room2, roomArr[1].name);

	//modify first file path to make path for file 3
	strncpy(room3, room1, nameLen - 4);
        room3[nameLen -4] = 0;
        strcat(room3, roomArr[2].name);

	//modify first file path to make path for file 4
	strncpy(room4, room1, nameLen - 4);
        room4[nameLen -4] = 0;
        strcat(room4, roomArr[3].name);

	//modify first file path to make path for file 5
	strncpy(room5, room1, nameLen - 4);
        room5[nameLen -4] = 0;
        strcat(room5, roomArr[4].name);

	//modify first file path to make path for file 6
	strncpy(room6, room1, nameLen - 4);
        room6[nameLen -4] = 0;
        strcat(room6, roomArr[5].name);

	//modify first file path to make path for file 7
	strncpy(room7, room1, nameLen - 4);
        room7[nameLen -4] = 0;
        strcat(room7, roomArr[6].name);

	//create directory
	mkdir(dirPrefix, 0755);
	
	//create files within the directory and write room data to them
	//file1
	FILE* file1 = fopen(room1, "a+");
	fprintf(file1, "%s%s\n", nameTemp,roomArr[0].name);
	int index = 1;
	for (index; index < roomArr[0].numConn+1; index++)
	{
		fprintf(file1,"%s %d: %s\n", connTemp, 
			index, roomArr[0].conn[index-1]);
	}
	fprintf(file1, typeTemp);
	fprintf(file1, roomArr[0].type);
	
	//file2
	FILE* file2 = fopen(room2, "a+");
        fprintf(file2, "%s%s\n", nameTemp,roomArr[1].name);
        index = 1;
        for (index; index < roomArr[1].numConn+1; index++)
        {
                fprintf(file2,"%s %d: %s\n", connTemp,
                        index, roomArr[1].conn[index-1]);
        }
        fprintf(file2, typeTemp);
        fprintf(file2, roomArr[1].type);

	//file3
	FILE* file3 = fopen(room3, "a+");
        fprintf(file3, "%s%s\n", nameTemp,roomArr[2].name);
        index = 1;
        for (index; index < roomArr[2].numConn+1; index++)
        {
                fprintf(file3,"%s %d: %s\n", connTemp,
                        index, roomArr[2].conn[index-1]);
        }
        fprintf(file3, typeTemp);
        fprintf(file3, roomArr[2].type);

	//file4
	FILE* file4 = fopen(room4, "a+");
        fprintf(file4, "%s%s\n", nameTemp,roomArr[3].name);
        index = 1;
        for (index; index < roomArr[3].numConn+1; index++)
        {
                fprintf(file4,"%s %d: %s\n", connTemp,
                        index, roomArr[3].conn[index-1]);
        }
        fprintf(file4, typeTemp);
        fprintf(file4, roomArr[3].type);
	
	//file5
	FILE* file5 = fopen(room5, "a+");
        fprintf(file5, "%s%s\n", nameTemp,roomArr[4].name);
        index = 1;
        for (index; index < roomArr[4].numConn+1; index++)
        {
                fprintf(file5,"%s %d: %s\n", connTemp,
                        index, roomArr[4].conn[index-1]);
        }
        fprintf(file5, typeTemp);
        fprintf(file5, roomArr[4].type);

	//file6
	FILE* file6 = fopen(room6, "a+");
        fprintf(file6, "%s%s\n", nameTemp,roomArr[5].name);
        index = 1;
        for (index; index < roomArr[5].numConn+1; index++)
        {
                fprintf(file6,"%s %d: %s\n", connTemp,
                        index, roomArr[5].conn[index-1]);
        }
        fprintf(file6, typeTemp);
        fprintf(file6, roomArr[5].type);

	//file7
	FILE* file7 = fopen(room7, "a+");
        fprintf(file7, "%s%s\n", nameTemp,roomArr[6].name);
        index = 1;
        for (index; index < roomArr[6].numConn+1; index++)
        {
                fprintf(file7,"%s %d: %s\n", connTemp,
                        index, roomArr[6].conn[index-1]);
        }
        fprintf(file7, typeTemp);
        fprintf(file7, roomArr[6].type);

	fclose(file1);
	fclose(file2);
	fclose(file3);
	fclose(file4);
	fclose(file5);
	fclose(file6);
	fclose(file7);

}


//prints the array for testing purposes
void printArray()
{
	int count = 0;
	int limit = 7;
	for (count; count < limit; count++)
	{
		printf("%s\n", roomArr[count].name);
		printf("%s\n", roomArr[count].type);
		printf("%d\n", roomArr[count].numConn);

		int count2 = 0;
		for (count2; count2 < roomArr[count].numConn; count2++)
		{
			printf("%s\n", roomArr[count].conn[count2]);
		}
	}	

}


//initializes the numConn element of each room struct in the array to 0
void initNumConn()
{
	int count = 0;
	int limit = 7;

	for (count; count < limit; count++)
	{
		roomArr[count].numConn = 0;
	}

}


int main()
{
	//seed random for future use
	srand(time(NULL));

	//fill names of each room in array
	fillNames();
	//fill types of each room in array
	fillTypes();
	//initialize numConn to 0 for each room in the array
	initNumConn();

	//while there is a room in the array that has less than the acceptable
	//amount of connections (at least 3), keep adding connections
        while (isFull() == 0)
        {
             	addConn();
        }

	//create directory with files and write and write data from each room
	//struct in the array
	createFiles();
}

