/***************************************************************
 ** Author: David Ramirez
 ** Date: 10/26/2017
 ** Description: This program uses the room files created by the
 ** 		 the buildrooms.c program to let the user play
 **		 a very simple text based adventure game.
 **		 The player is presented a UI with the current
 **              room and connections to other rooms, and the user
 **              traverses rooms until the end room is found. 
 ****************************************************************/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pthread.h>
#include <time.h>


//declaration of struct to hold room info
struct roomStruct
{           
        char* name;
        char* type;
        int conn[6];
        int numConn;    
};

//mutex declaration
pthread_mutex_t mutex;

//all function prototypes
void* timeIn();
void timeOut();
void thread();
const char* startHere();                  
char* mostRecentDir();
int readFile(struct roomStruct* room, char roomName[100]);
int conExist(struct roomStruct* room, char roomName[50]);

//declaration of rooms and types
char* rooms[10] = {"Stan", "Phil", "Carl", "Kurt", "Kirk", "John", "Pete", "Ross", "Bill", "Ralf"}; 
char* types[3] = {"START_ROOM", "END_ROOM", "MID_ROOM"};


//function that creates the time text file used for reading the current time
//-- this function is modified code from various sources:
//   http://www.cplusplus.com/reference/ctime/localtime/
//   https://stackoverflow.com/questions/25420933/c-create-txt-file-and-append-current-date-and-time-as-a-name
void* timeIn()
{ 
	//buffer to hold time for file
        char buffer[100];
	//holds time info
        struct tm *info;
	//holds time file
	FILE* timeFile;
	//create file                            
        timeFile = fopen("time.txt", "w+");

	//time variable
        time_t current = time (0);
	//convert time variable to gmtime (I live in FL but I figured to set it to Oregon time)
        info = gmtime (&current);
	//place info in buffer
        strftime (buffer, 100, "%Y-%m-%d %H:%M:%S", info);
	//place buffer in file
        fputs(buffer, timeFile);
	//close time file
        fclose(timeFile);
}


//function to start threading, allowing to do multiple processes at once
//-- this function is modified code from various sources:
//   https://www.cs.nmsu.edu/~jcook/Tools/pthreads/library.html
//   http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html
//   http://man7.org/linux/man-pages/man3/usleep.3.html 
void thread()
{
	//declare pthread (acts as handle for new thread
	pthread_t pThread;   
	//create mutex                        
	pthread_mutex_init(&mutex, NULL);
	//lock mutex (thread blocks)
        pthread_mutex_lock(&mutex);

	//create pthread so that timIn function is run concurrently
        int t = pthread_create(&pThread, NULL, timeIn, NULL);
	//unlock mutex (thread continues)
        pthread_mutex_unlock(&mutex);
	//get rid of mutex
        pthread_mutex_destroy(&mutex);
	//wait for threaded process to finish
        usleep(300);
}                      


//function to read time from time file
void timeOut()
{
	//create file object
        FILE* timeFile;
	//set file object to point to time.txt file
        timeFile = fopen("time.txt", "r");  
	//holds infor from time file
        char buffer[100];

	//as long as the file is able to be accessed, get info and print
        if(timeFile != NULL)
        {
                fgets(buffer, 100, timeFile);    
                printf("\n%s\n", buffer);
                fclose(timeFile);
        }
}


//function to return the name of the room of type START_ROOM
const char* startHere()
{                       
	//holds name of room
        char* start= malloc(sizeof(char) * 20);
	//get the most recent dir (the one buildrooms.c made)
        char* directory = mostRecentDir();	
        DIR* thisDir;                                  
        struct dirent* find;
  
	//if the directory is able to be opened
        if((thisDir = opendir(directory)) != NULL)
        {
		//if there are files to read 
                while((find = readdir(thisDir)) != NULL)
                {
			//dont use the hidden directories "." and ".."
                        if(!strcmp(find -> d_name, "..") || !strcmp(find -> d_name, "."))
                        {        
                                continue;
                        }
       
			//place room name in start (holds first room)
                        strcpy(start, find -> d_name);

			//return name of first room
                        return start;
                }
        }
}


//function to read room file info and place into struct
int readFile(struct roomStruct* room, char roomName[100])
{        
	char dirName[100];                            
        char fileName[100];
	//copy most recent dir name to variable
	sprintf(dirName, mostRecentDir()); 
	//create path for file
        sprintf(fileName, "./%s/%s", dirName, roomName);     
	//holds file        
        FILE* thisFile;  
	//holds each read line         
	char buffer[100];               
 
	//read file
        thisFile = fopen(fileName, "r");      
        room -> name = rooms[0]; 
	//initialize connections
        room -> numConn = 0;            
  
	//read from file
        fgets(buffer, 100, thisFile);
  
	//separeate buffer based on the space and new line in the file
        char* name = strtok(buffer, " ");   
        name = strtok(NULL, " ");
        name = strtok(NULL, "\n");           
  
	//iterate through list of possible names
        int count=0;
        for(count; count < 10; count++)
        {             
                if(strcmp(name, rooms[count]) == 0)
                {
                        room -> name = rooms[count];
                        count = 10;
                }
        }
  
	//while more can be read from file (getting connections)
        while(fgets(buffer, 100, thisFile) != NULL)
        {  
                char* testName = strtok(buffer, " ");

		//when the word connection is read from file
                if(strcmp(testName, "CONNECTION") == 0)
                {    
                        testName = strtok(NULL, " ");
                        testName = strtok(NULL, "\n");

			//iterate through each connection and save amount of iterations
			count = 0;
                        for(count; count < 10; count++)
                        {                  
                                if(strcmp(testName, rooms[count]) == 0)
                                {
                                        room -> conn[room -> numConn] = count;
                                        count = 10;
                                }
                        }
                        
                        room -> numConn++;         
                }
    
		//when connection no longer found, that means the room type is next
                else
                {
                        testName = strtok(NULL, " ");             
                        testName = strtok(NULL, "\n");
	
			//iterate through room names
			count = 0;
                        for(count; count < 10; count++)
                        {
                                if(strcmp(testName, types[count]) == 0)
                                {
                                        room -> type = types[count];
                                        count = 10;
                                }
                        }
                }
        }
        
        return 0;                                     //Success
}


//function to check if a connection exists, returns 1 if it does, 0 if not
int conExist(struct roomStruct* thisRoom, char name[50])
{
	//iterate through each connection in this room
        int count = 0;
        for(count; count < thisRoom -> numConn; count++)
        {                      
		//if the name and the room connection passed match, return 1
                if(strcmp(name, rooms[thisRoom -> conn[count]]) == 0)
                {
                        return 1;
                }
        }

	//return 0 if no match
        return 0;
}

//function to fill data in array of rooms from room files of most recent directory
//-- this function is modified code taken from the class reading 2.4: Manupulating
//   Directories
//
char* mostRecentDir()
{
	//modified timestamp of newest subdir
        int mostRecent = -1; 
	//target prefix
        char targetDirPrefix[32] = "ramirdav.rooms."; 
	//name of prefixed newest dir
        char newestDir[256]; 
        memset(newestDir, '\0', sizeof(newestDir));
	//directory to start in
        DIR* startDir; 
	//current subdir
        struct dirent *fileInDir;
	//hold dir info 
        struct stat dirStat; 

	//open current directory
        startDir = opendir("."); 

	//if dir can be opened
        if (startDir > 0) 
        {
		//read through each element in dir
                while ((fileInDir = readdir(startDir)) != NULL) 
                {
			//if prefix found
                        if (strstr(fileInDir->d_name, targetDirPrefix) != NULL)
                        {
				//get file info
                                stat(fileInDir->d_name, &dirStat); 

				//if time more recent
                                if ((int)dirStat.st_mtime > mostRecent) 
                                {
                                        mostRecent = (int)dirStat.st_mtime;
                                        memset(newestDir, '\0', sizeof(newestDir));
                                        strcpy(newestDir, fileInDir->d_name);
				
					//return most recent dir name
                                        return fileInDir->d_name;;
                                }
                        }
                }
        }
}

//main function that applies the high level logic to run the game
int main() 
{           
	//holds list of visited rooms                 
        char* listRooms[1000];
	//holds name of room to start in
	char start[50];
	strcpy(start,startHere());
	//holds number of turns taken to find end room
	int turns = 0;     
	//holds name of current room                                       
        char roomName[50]; 
	//holds struct of current room
        struct roomStruct* room = malloc(sizeof(struct roomStruct));
	
	int holder;
        readFile(room, start);

	//keep running until END_ROOM found
	int forever = 0;
        while (forever == 0)
        {
		//print UI for current room
		printf("\n");
                printf("CURRENT LOCATION: %s\n", room -> name);      
                printf("POSSIBLE CONNECTIONS:");
                printf(" %s,", rooms[room -> conn[0]]);

		//print connections for current room
                for(holder = 1; holder < room -> numConn; holder++)
                {   
                        printf(" %s,", rooms[room -> conn[holder]]);
                }
		
		//more UI
		printf(". \n");
                printf("WHERE TO? >");
	
		//get user input for room name          
                scanf("%s", roomName);              

		//if the user entered time, then show the current time
                if(strcmp(roomName, "time") == 0)
                {
                        thread();        
                        timeOut();
                }

		//if the user input does not match a connection
                else if(conExist(room, roomName) != 1)
                {             
			printf("\n");
                        printf("HUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n");  
                }

		//if user entered a valid connection
                else
                {       
			//add room to list of visited rooms
                        listRooms[turns] = room -> name;
                        turns++;                         
			//hold index to new room in holder variable     
                        holder = readFile(room, roomName);    
                }

		//if the room the user goes to is the end room
                if(room -> type == "END_ROOM")
                {         
			//break out of while loop, ending game
                        forever =1;
                }
        }
        
         printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");            
         printf("YOU TOOK %i STEPS. YOUR PATH TO VICTORY WAS:\n", turns);
        
	 int count = 1;        
         for(count; count < turns; count++)
         {          //Loop through and print each spot in the path
                printf("%s\n", listRooms[count]);
         }
	
	//print last room the user went to (end room)
	printf("%s\n", room -> name);
                
	//free room struct
        free(room); 
	//remove rime file
	remove("time.txt");          

        return 0;
}
