/***************************************************************
 *** Author: David Ramirez
 *** Date: 11/15/2017
 *** Description: This is a simple shell program. It allows for 
 ***		  redirection of stdin and stdout, supports 
 ***              background and foreground processes, and supports
 ***              comments. This shell also supports three built
 ***              in commands: exit, cd, and status. 
 *****************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pthread.h>
#include <signal.h>

//global constants
#define SIZE_INPUT  (sizeof(char)*2048+1)
#define SIZE_ARGS 513

//declaration of struct to hold command
struct commandData
{	
	char* arguments[SIZE_ARGS];
	int back;
	char* inRedir;
	char* outRedir;
	int numArgs;
};

//*note to the grader: I apologize for the long parameter lists, by the time I figured out
//that global variables were ok to use in this class I had nearly finished this assignment. 

//declaration of functions
char* getInput(int pidParam);
struct commandData* readInput(char* readParam);
int execCommand(struct commandData*,int* prevExit,int* curExit, int* pidArr, int* pidCo, int* sigRExit2, char* input2); //returns 0 if command successful, 1 if not
void backgroundCheck(int* pidArr2, int* pidCo2, int* exitStat2, int* sigRExit);
void killBackground(int* pidArr3, int* pidCo3);
void makeBackground(struct commandData*, int* inDevDescript, int* outDevDescript);
int doRedirect(struct commandData* curCommand3, int* inFileD, int* outFileD); //returns 0 if redirect successful, 1 if not
void handlerSIGTSTP(int);

//global variables
int foregroundPid = -5;
int foregroundOnly= 0;
int SIGTSTPcheck = 0;


int main()
{	
	//signal handling for SIGINT
	struct sigaction SIGINT_parent_action = {0};
        sigfillset(&SIGINT_parent_action.sa_mask);
        SIGINT_parent_action.sa_handler= SIG_IGN;
        sigaction(SIGINT, &SIGINT_parent_action,NULL);

	//signal handling for SIGTSTP
        SIGINT_parent_action.sa_handler= handlerSIGTSTP;
        sigaction(SIGTSTP, &SIGINT_parent_action,NULL);

	char* input;  //holds unformatted command   
	struct commandData* ptrCommStruct;   //holds formatted command
	int exitStat = 0;   
	int prevExitStat = 0;
	int forever = 1;    
	int pid = getpid();  //holds parent pid of parent process
	int pidArray[50];    //array of all unfinished background processes
	int pidCount = 0;    //count of all unfinished background processes
	int sigOrExit = 0;   //keeps track of if previous command exited normally or with a signal, 0 if exit, 1 if signal

	//initialize pidArray
	int index4 = 0;
	for (index4; index4 < 50; index4++)
	{
		pidArray[index4] = 0;
	}

        //main shell program loop
	while (forever == 1)
	{
		SIGTSTPcheck = 0;

		//set prevExitStat to exitStat (before exitStat changes)
		prevExitStat = exitStat;
		if ((prevExitStat > 1)&&(sigOrExit == 0))
			prevExitStat = 1;
		exitStat = 0;

		//check if any background processes have ended, output message if so
		backgroundCheck(pidArray, &pidCount, &prevExitStat, &sigOrExit);
		//get new user input
		input = getInput(pid);
		if (input == NULL)
		{
			continue;
		}
		
		//if SIGINTTSTP maually entered, discard input and start over (after going into FG only mode)
		if (SIGTSTPcheck == 1)
		{
			free(input);
			continue;
		}

		//create struct of command and arguments from input
		ptrCommStruct = readInput(input);
		//execute command and save status of execution
		exitStat = execCommand(ptrCommStruct, &prevExitStat,&exitStat, pidArray, &pidCount, &sigOrExit,input);

		//free curCommand struct
		free(ptrCommStruct->inRedir);
		free(ptrCommStruct->outRedir);
		int i = 0;
		for (i; i < SIZE_ARGS; i++)
		{
			free(ptrCommStruct->arguments[i]);
		}
		free(ptrCommStruct);
		free(input);                                            
	}
	return 0;    
}

//malloc's user input and returns it
char* getInput(int pidParam)
{
	char replacePid[5] = "$$";
	char* pidToken;
	char* pidToken2;
	char* getBuffer = malloc(SIZE_INPUT);
	if (getBuffer == NULL)	
	{
		return NULL;
	}

	//sleep for 50 microseconds so that prompt always last output 	
	usleep(50);
	//output prompt
	printf(": ");
	fflush(stdout);
	//get user input
	fgets(getBuffer, SIZE_INPUT, stdin);
	if (getBuffer[0] == '\n')
	{
		free(getBuffer);
		return NULL;
	}

	//if the SIGTSTP signal was manually entered	
	if (SIGTSTPcheck == 1)
	{
		memset(getBuffer, '\0', sizeof(getBuffer));
		getBuffer[0] = '\n';
	}
	else
	{
		//take out line end character
		getBuffer[strlen(getBuffer)-1] = '\0'; 
	}
	//replace all instances of $$ with pid
	while (strstr(getBuffer,replacePid) != NULL) 
	{
		char testFirst = getBuffer[0];
		char testSecond = getBuffer[1];

		//if the first 2 chars in getBuffer are $$
		if ((testFirst == '$')&&(testSecond == '$'))
		{
			//tokenize everything in getBuffer 
			pidToken2 = strtok(getBuffer, "\0");
			char pidString2[SIZE_INPUT];

			//copy token to string
			if (pidToken2 != NULL)
			{
				strcpy(pidString2, pidToken2);
			}
			//remove the $$
			int index3 = 0;
			for (index3; index3 < 2; index3++)
			{
				if (pidToken2 != NULL)
				{
					int index = 0;
                                	memmove(&pidString2[index], &pidString2[index + 1], strlen(pidString2) - index);
				}
			}
			//remake the getBuffer string
			if (pidToken2 != NULL)
			{
				memset(getBuffer, '\0', sizeof(getBuffer));
				sprintf(getBuffer, "%d%s", pidParam, pidString2);
			} 
		}

		//if $$ is in the string but is not the first 2 chars
		else
		{
			//split string into 2 parts, before and after $ character
			pidToken = strtok(getBuffer, "$");
			pidToken2 = strtok(NULL, "\0");
			char pidString[SIZE_INPUT];
			char pidString2[SIZE_INPUT];
		
			//copy token to string
			if (pidToken != NULL)
			{
				strcpy(pidString, pidToken);
			}
			//copy token to string
			strcpy(pidString2, pidToken2);
			//remove the remaining $ character in pidString2
			if (pidToken2 != NULL)
			{
				int index2 = 0; 
				memmove(&pidString2[index2], &pidString2[index2 + 1], strlen(pidString2) - index2);
			}
			//remake the getBuffer string with pidParam replacing $$
			memset(getBuffer, '\0', sizeof(getBuffer));
		
			//the following 4 if statements are indluded to ensure that
			//no uninitialized strings are accessed
			if ((pidToken != NULL)&&(pidToken2 != NULL))
			{
				sprintf(getBuffer, "%s%d%s", pidString, pidParam, pidString2);
			}
			if ((pidToken == NULL) && (pidToken2 == NULL))
			{
				sprintf(getBuffer, "%d", pidParam);
			}
			if (pidToken == NULL)
			{
				sprintf(getBuffer, "%d%s", pidParam, pidString2);	
			}
			if (pidToken2 == NULL)
			{
				sprintf(getBuffer, "%s%d", pidString, pidParam);
			}
		}
	}
	//return user input string with $$ replaced with pid
	return getBuffer;	
}

//reads the user input string and breaks it up into args, in redirect
//path, out redirect path, and background status
struct commandData* readInput(char* readParam)
{
	//allocated memory for commandData struct and point to it
	struct commandData* curCommand = malloc(sizeof(struct commandData));
	if (curCommand == NULL)
	{
		return NULL;
	}

	//initialize/malloc struct elements
	curCommand->numArgs = 0;
	curCommand->back = 0;
	curCommand->inRedir = malloc(200);
	curCommand->outRedir = malloc(200);
	int i = 0;
	for (i; i < SIZE_ARGS; i++)
	{
		curCommand->arguments[i] = malloc(100);
	}
	//create readBuffer from parameter and declare token
	char readBuffer[SIZE_INPUT];
	char* token;
	strcpy(readBuffer, readParam);
	//start tokenizing readBuffer 
	token = strtok(readBuffer, " ");

	//if the user entered an empty line, set command appropriately
	if ((token == NULL)||(strcmp(token, "\n")==0))
	{
		strcpy(curCommand->arguments[0],"emptyLine");
	}
	//while there is something to read in the buffer, and before that something 
	//is a redirect symbol or a background symbol, it must be an argument
	while ((token != NULL)&&(strcmp(token, "<") != 0)&&(strcmp(token, ">") != 0))
	{	
		char oldToken[200];
		strcpy(oldToken, token);
		token = strtok(NULL, " ");

		//if the last character in the input buffer is &
		if ((strcmp(oldToken, "&")==0)&&(token == NULL))
		{
			curCommand->back = 1;
		}
		else if	((strcmp(oldToken, "&")==0)&&(token != NULL)) 
		{	
			//do nothing
		}
		else
		{
			//copy argument from token
			strcpy(curCommand->arguments[curCommand->numArgs],oldToken); 	
			//increase number of arguments
			curCommand->numArgs ++;
		}
		
	}
	//end argument list with NULL for execvp()
	free(curCommand->arguments[curCommand->numArgs]);
	curCommand->arguments[curCommand->numArgs] = NULL;

	//loop to place path redirect for out and in 
	int inCheck = 0;
	int outCheck = 0;
	while  ((token != NULL) && (strcmp(token,"&")!=0))
	{
		//if token == < (need to include null), get next token and
		//save it to inRedir	
		if ((token != NULL)&&(strcmp(token, "<") == 0))
		{
			token = strtok(NULL, " ");
			strcpy(curCommand->inRedir, token);
			inCheck = 1;
			token = strtok(NULL, " ");
			continue;
		}
		//if token == >, get next token and save it to outRedir 
		if ((token != NULL)&&(strcmp(token, ">") == 0))
		{
			token = strtok(NULL, " ");
			strcpy(curCommand->outRedir, token);
			outCheck = 1;
			token = strtok(NULL, " ");
			continue;
		}	
	} 
	//if no redirect in was read, set value to \0
	if (inCheck == 0)
        {
                strcpy(curCommand->inRedir, "\0");
        }

	//if no redirect out was read, set value to \0
        if (outCheck == 0)
        {
                strcpy(curCommand->outRedir, "\0");
        }

	return curCommand; 
} 

//calls the appropriate function corresponding to the name of commString
//--returns 0 if success
//--1 if not
int execCommand(struct commandData* curCommand, int* prevExit,int* curExit, int* pidArr, int *pidCo, int* sigRExit2, char* input2)
{
	//get first char of first arg to see if it is a comment
	char comment = curCommand->arguments[0][0];
/*******************************************************************************
 *                                exit command
 ******************************************************************************/
	//if the passed command is exit, exit program
	if (strcmp(curCommand->arguments[0], "exit") == 0)
	{
		//call function to kill all background processes and output
		//exit messages
		killBackground(pidArr, pidCo); 

		//free all allocated memory
		free(curCommand->inRedir);
                free(curCommand->outRedir);
                int i = 0;
                for (i; i < SIZE_ARGS; i++)
                {
                        free(curCommand->arguments[i]);
                }
                free(curCommand);
                free(input2);

		kill(0, SIGTERM);
	}
/******************************************************************************
 *                               comment line (#)
 *****************************************************************************/
	else if ((strcmp(curCommand->arguments[0], "commentLine")==0)||(comment =='#'))
	{
		return 0;
	}
/******************************************************************************
 *                               cd command
 *****************************************************************************/                               
	//else if command is cd, change directory depending on arguments
	else if (strcmp(curCommand->arguments[0], "cd") == 0)
	{
		int dirCheck;

		//if there are no arguments, change directory to home directory
		if (curCommand->numArgs == 1)
		{
			dirCheck = chdir(getenv("HOME"));			
                        if (dirCheck == -1)
                        {
                                printf("\nerror: could not open directory\n");
				fflush(stdout);
				return 1;
                        }

		}	
		//if there is one argument, change directory to provided path
		else if (curCommand->numArgs == 2)
		{
			//if the argument is &, ignore it 
			if (strcmp(curCommand->arguments[1],"&")==0)
			{
				dirCheck = chdir(getenv("HOME"));
        	                if (dirCheck == -1)
                	        {
                        	        printf("\nerror: could not open directory\n");
                               	 	fflush(stdout);
                               		return 1;
                       		}

			}
			//if argument is not &, change directory to provided path
			else
			{
				dirCheck = chdir(curCommand->arguments[1]);

				if (dirCheck == -1)
				{
					printf("\nerror: could not open directory\n");
					fflush(stdout);
					return 1;
				}
			
			}
		}
		//if there is more than one argument, output error
		else if (curCommand->numArgs > 2)
		{
			//if the second argument is &, ignore it
			if (curCommand->arguments[2] == "&")
			{
				dirCheck = chdir(curCommand->arguments[1]);

                                if (dirCheck == -1)
                                {
                                        printf("\nerror: could not open directory\n");
                                        fflush(stdout);
                                        return 1;
                                }
	
			}
			//if the second argument is not &, there are too many arguments
			else
			{
				printf("\nerror: too many arguments provided\n");
				fflush(stdout);
				return 1;
			}
		}
	}
/*****************************************************************************
 *                             status command
 ****************************************************************************/  
	else if (strcmp(curCommand->arguments[0], "status") == 0)
	{
		//if there is the correct number of arguments
		if (curCommand->numArgs == 1)
		{ 
			//if it is a normal exit value (not signal)
			if (*sigRExit2 == 0)
			{
				printf("\nPrevious process exit value: %d\n", *prevExit);
				fflush(stdout);
				return 0;
			}
			//if it is a signal value
			else if (*sigRExit2 == 1)
                        {
                                printf("\nPrevious process terminating signal value %d\n", *prevExit);
                                fflush(stdout);
                                return 0;
                        }

		}		
		//if there are too many arguments
		else if( curCommand->numArgs ==2 )
		{
			//if the second argument is &, ignore it
			if (strcmp(curCommand->arguments[1],"&")==0)
			{
				//if it is a normal exit value (not signal)
                        	if (*sigRExit2 == 0)
                        	{
                                	printf("\nPrevious process exit value: %d\n", *prevExit);
                                	fflush(stdout);
                                	return 0;
                        	}
                       	 	//if it is a signal value
                        	else if (*sigRExit2 == 1)
                        	{
                                	printf("\nPrevious process terminating signal value %d\n", *prevExit);
                                	fflush(stdout);
                                	return 0;
                        	}
	
			}
			//else, there are too many arguments
			else
			{
				printf("\nerror: too many arguments provided\n");
				fflush(stdout);
				return 1;
			}
		}
		//if there are more than 2 arguments, there is no need to ignore &
		else
		{
			 printf("\nerror: too many arguments provided\n");
                         fflush(stdout);
                         return 1;
		}
	}
/****************************************************************************
 ****************************************************************************
 * 				NON-BUILT IN COMMANDS
 ****************************************************************************
 ***************************************************************************/ 
	else
	{
		int status = 0;
		pid_t childPid = -5;
	
		//create child process	
		childPid = fork();
		switch(childPid)
		{
			//could not create process
			case -1: 
			{
				printf("\nError: could not create child process\n");
				fflush(stdout);
				return 1;
			}
			//child process
			case 0:
			{
				//if this is a background process
				if (curCommand->back == 1)
				{
					//set signal handler to ignore SIGINT
					struct sigaction SIGINT_child_noaction = {0};
					sigfillset(&SIGINT_child_noaction.sa_mask);
					SIGINT_child_noaction.sa_handler= SIG_IGN;
					sigaction(SIGINT, &SIGINT_child_noaction,NULL); 
				}
				//if this is a foreground process
				else
				{	
					//set signal handler to execute SIGINT
					struct sigaction SIGINT_child_noaction2 = {0};
                                        sigfillset(&SIGINT_child_noaction2.sa_mask);
                                        SIGINT_child_noaction2.sa_handler= SIG_DFL;
                                        sigaction(SIGINT, &SIGINT_child_noaction2,NULL);
	
					foregroundPid = getpid();
				}			
	
				//file descriptors
				int inFileDescript = -5;
				int outFileDescript= -5;
				int inDevNull = -5;
				int outDevNull = -5;
			
				//call function to check and and make process background
				makeBackground(curCommand, &inFileDescript, &outFileDescript);
				//call function to check and perform redirect
				status = doRedirect(curCommand, &inFileDescript, &outFileDescript);
				//execute command and output message if error encountered
				if(execvp(curCommand->arguments[0], curCommand->arguments) < 0)
				{
					printf("\nError: no such file or directory %s\n", curCommand->arguments[0]);
					exit(1);
				}	

				//closes any files that have been opened
				if (inFileDescript > 0)
					close(inFileDescript);
				if (outFileDescript > 0)
					close(outFileDescript);
				if (inDevNull > 0)
					close(inDevNull);
				if (outDevNull > 0)
					close(outDevNull);

				break;
			}
			//parent process	
			default:
			{
				//if the forked command is a background process and the program
				//is not in foreground only mode
				if ((curCommand->back == 1)&&(foregroundOnly ==0))
				{
					//add child Process to pidArray and move on
					pidArr[*pidCo] = childPid;
                                	(*pidCo)++;
					break;
				}
				//if the forked command is not a background process, or if program
				//is in foreground only mode
				else 
				{
					//wait for child process to finish, and return its exit status
					int childExitStatus2;
					int exitChildPid2;
					exitChildPid2= waitpid(childPid,&childExitStatus2, 0);
					if (exitChildPid2 != 0)
					{
						//if foreground process terminated by signal, output message
						if (WIFSIGNALED(childExitStatus2) !=0)
						{
							printf("\nForeground process %d has been terminated by signal %d\n", childPid, WTERMSIG(childExitStatus2));

							*sigRExit2 = 1;
							*curExit= WTERMSIG(childExitStatus2);	
						}
					}
					//return status of child process
					return childExitStatus2;
				}
			}
		}
	}
	//success
	return 0;		
}

//checks if redirection is necessary and performs redirection
int doRedirect(struct commandData* curCommand3, int *inFile, int* outFile)
{
	//if both the input and
	//output redirect files are specified
	if ((strcmp(curCommand3->outRedir,"\0")!=0)&&(strcmp(curCommand3->inRedir,"\0")!=0))
	{
		*outFile = open(curCommand3->outRedir, O_WRONLY | O_CREAT | O_TRUNC,744);
		if (*outFile == -1)
		{
			printf("\nError: could not open output file %s\n", curCommand3->outRedir);		
			fflush(stdout);
			exit(1);
		}
		//if file successfully opened, perform redirect 
		else
		{
			dup2(*outFile, 1);
		} 
			
		*inFile = open(curCommand3->inRedir, O_RDONLY);
		if (*inFile == -1)
		{
			printf("\nError: could not open input file %s\n",curCommand3->inRedir);
			fflush(stdout);
			exit(1);
		}
		//if file successfully opened, perform redirect
		else
		{
			dup2(*inFile, 0);
		}		
	}
	//else if the output 
	//redirect file is specified, and the input redirect file is undefined
	else if ((strcmp(curCommand3->outRedir,"\0")!=0)&&(strcmp(curCommand3->inRedir,"\0")==0))
	{
		*outFile = open(curCommand3->outRedir, O_WRONLY | O_CREAT | O_TRUNC,744);
                if (*outFile == -1)
                {
                        printf("\nError: could not open output file %s\n", curCommand3->outRedir);
			fflush(stdout);
                        exit(1);
                }
		//if file successfully opened, perform redirect
                else
                {
                        dup2(*outFile, 1);
                }
	}
	 //else if the output
	 //redirect file is undefined, and the input redirect file is specified
	 else if ((strcmp(curCommand3->outRedir,"\0")==0)&&(strcmp(curCommand3->inRedir,"\0")!=0))
        {
		*inFile = open(curCommand3->inRedir, O_RDONLY);
                if (*inFile == -1)
                {
                        printf("\nError: could not open input file %s\n",curCommand3->inRedir);
			fflush(stdout);
                        exit(1);
                }
		//if file successfully opened, perform redirect
                else
                {
                        dup2(*inFile, 0);
                }
        }
	//success
	return 0;
}

//redirects stdin and stdout for creating a background process, checks to make sure 
//redirection has not already happened first
void makeBackground(struct commandData* curCommand2,int* inDevDescript, int* outDevDescript)
{
	//if the program is not in foreground only mode, check if it is a background process
	if (foregroundOnly == 0)
	{
		//if it is a background process, output message and perform redirect
		if (curCommand2->back == 1)
		{
			printf("\nBackground process %d is starting\n", getpid());
			fflush(stdout);

			if (strcmp(curCommand2->inRedir, "\0") == 0)
			{
				*inDevDescript = open("/dev/null", O_RDONLY);
				dup2(*inDevDescript, 0);	
			} 

			if (strcmp(curCommand2->outRedir, "\0") == 0)
			{
				*outDevDescript = open("/dev/null", O_WRONLY);
				dup2(*outDevDescript, 1);
			}
		}
	}
}

//checks if any background processes have exited,
//outputs exit statement and edits pidArray if so
void backgroundCheck(int* pidArr2, int* pidCo2, int* exitStat2,int* sigRExit)
{
	int childExitStatus = 0;
	int exitChildPid = 0;		

	//step through array of background process pids
	int index = 0;	
	for (index; index < *pidCo2; index++)
	{
		//check if child process has ended
		exitChildPid =waitpid(pidArr2[index],&childExitStatus, WNOHANG);
		//if child process has ended
		if (exitChildPid != 0)			
		{
			if(WIFEXITED(childExitStatus) != 0)
			{
				printf("\nBackground process %d has ended with exit value %d\n", pidArr2[index], WEXITSTATUS(childExitStatus));
				fflush(stdout);
				//so that status command, if next, will output this exit status
				*exitStat2= WEXITSTATUS(childExitStatus);
				//so that status command will know to say "exit" or "signal"
				*sigRExit = 0;
				
			}

			else if (WIFSIGNALED(childExitStatus) != 0)
			{
				printf("\nBackground process %d has been terminated by signal %d\n", pidArr2[index], WTERMSIG(childExitStatus));
				fflush(stdout);
				//so that status command, if next, will output this signal
				*exitStat2 = WTERMSIG(childExitStatus);
				//so that status command will know to say "exit" or "signal"
				*sigRExit = 1;
			}

			int index2 = index;
			for (index2; index2 < *pidCo2; index2++)
			{
				pidArr2[index2] = pidArr2[index2+1];
			}
			pidArr2[(*pidCo2)-1] = 0;
			(*pidCo2)--;
		}
		
	}
}

//kills the background processes when user enters exit command
void killBackground(int* pidArr3, int* pidCo3)
{
	int exitChildPid = 0;
	int childExitStatus = 0;

        //step through array of background process pids and terminate them
        int index = 0;
        for (index; index < *pidCo3; index++)
        {
		kill(pidArr3[index], SIGTERM);
		
		//check if child process has ended
                exitChildPid =waitpid(pidArr3[index],&childExitStatus, WNOHANG);
                //if child process has ended
                if (exitChildPid != 0)
                {
                        if(WIFEXITED(childExitStatus) != 0)
                        {
                                printf("\nBackground process %d has ended with exit value %d\n", pidArr3[index], WEXITSTATUS(childExitStatus));
                                fflush(stdout);
                        }

                        else if (WIFSIGNALED(childExitStatus) != 0)
                        {
                                printf("\nBackground process %d has been terminated by signal %d\n", pidArr3[index], WTERMSIG(childExitStatus));
                                fflush(stdout);
                        }

                	int index2 = index;
                	for (index2; index2 < *pidCo3; index2++)
                	{	
                       		pidArr3[index2] = pidArr3[index2+1];
                	}
               		pidArr3[(*pidCo3)-1] = 0;
			(*pidCo3)--;

		}
        }

}

//enables or disables foreground only mode with each SIGTSTP received by program
void handlerSIGTSTP(int nothing)
{
	if (foregroundOnly == 0)
	{
		foregroundOnly = 1;
		printf("\nEntered foreground only mode\n");	
	}

	else if (foregroundOnly == 1)
	{
		foregroundOnly = 0;
		printf("\nExited foreground only mode\n");
	}

	//set to 1 so that input buffer clears and there
	//is no seg fault
	SIGTSTPcheck = 1;
}
