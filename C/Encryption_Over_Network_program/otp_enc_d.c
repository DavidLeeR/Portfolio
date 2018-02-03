/********************************************************************************
 * Author David Ramirez
 * Date: 11/24/17
 * Description: Recieves plain text and key from otp_enc program, performs one-time
 * 		pad style encryption, and return encrypted text to otp_enc. This program
 * 		is meant to be run in the background as a daemon. Use this program with
 * 		command "otp_enc_d port".
 * *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

//global constant
#define MAX_REC_SIZE 70000

//global variables
int portNumber;

//error function used for reporting issued
void errorMsg(const char *msg) 
{ 
	perror(msg); 
} 

//encrypts plain text using otp
char* encrypt(int recLen, char* totalPT, char* totalK)
{
	char keyChar;
	char textChar;
	char encChar;
	char* encText = malloc(recLen);
	memset(encText, '\0', sizeof(encText));

	//for each char in the plain text
	int i =0;
	for (i; i < (recLen-1); i++)
	{
		keyChar = totalK[i];
		//if key character is a space, set it to value right after capital letters
		if (keyChar == 32)
		{
			keyChar = 91;
		}
		
		textChar = totalPT[i];
		//if text character is a space, set it to value right after capital letters
		if (textChar == 32)
		{
			textChar = 91;
		}
	
		//subtract 65 from both key and text chars to have possible values represented as 0-26
		keyChar -= 65;
		textChar -= 65;
		encChar = ((keyChar + textChar)%27); 
	
		//if char is space, change to reflect space
		if (encChar == 26)
		{
			encChar = 32;
			encText[i] = encChar;
		}
		//else, make capital char
		else
		{
			encChar += 65;
			encText[i] = encChar;
		}
	}

	//return the encrypted text
	return encText;
}

//connects to client and recieves the key and the plain text
void connRecSend()
{
	int listenSocketFD, establishedConnectionFD,  charsRead;
	socklen_t sizeOfClientInfo;
	char buffer[256];
	struct sockaddr_in serverAddress, clientAddress;


	// Set up the address struct for this process (the server)
	memset((char *)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverAddress.sin_addr.s_addr = INADDR_ANY; // Any address is allowed for connection to this process

	// Set up the socket
	listenSocketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (listenSocketFD < 0) 
	{
		errorMsg("OTP_ENC_D: ERROR opening socket");
		exit(1);
	}

	// Enable the socket to begin listening
	if (bind(listenSocketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to port
	{
		errorMsg("OTP_ENC_D: ERROR on binding");
		exit(1);
	}

	listen(listenSocketFD, 5); // Flip the socket on - it can now receive up to 5 connections

	while (1){
		// Accept a connection, blocking if one is not available until one connects
		sizeOfClientInfo = sizeof(clientAddress); // Get the size of the address for the client that will connect
		establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo); // Accept
		if (establishedConnectionFD < 0)
		{
			errorMsg("OTP_ENC_D: ERROR on accept");
			exit(1);
		}
	
		//create child process for each connection
		pid_t pid = fork();
		switch(pid)
		{
			case -1:
				errorMsg("OTP_ENC_D: ERROR creating child process");

			//child process
			case 0:
				// Get the message from the client 
				memset(buffer, '\0', 256);
				charsRead = recv(establishedConnectionFD, buffer, 1, 0); // Read the client's message from the socket
				if (charsRead < 0)
				{
					errorMsg("OTP_ENC_D: ERROR reading from socket");
					exit(1);
				}

				//if the client is not the correct encryption client
				if (strcmp(buffer, "e") != 0)
				{
					int incorrectClient = 1;
					//send code representing incorrect client to client
					int charsWritten = send(establishedConnectionFD, &incorrectClient, 1, 0);
					if (charsWritten < 0)
					{
						errorMsg("OTP_ENC_D: ERROR writing to socket");
						exit(1);  
					}
					fprintf(stderr, "OTP_ENC_D: ERROR incorrect client");
					exit(1);
				}
			
				int correctClient = 0;
				//send code representing correct client to client
                                int charsWritten = send(establishedConnectionFD, &correctClient, 1, 0);
                                if (charsWritten < 0)
                                {
                                       errorMsg("OTP_ENC_D: ERROR writing to socket");
                                       exit(1);
                                }

				//recieve the length of the plain text
				int recLen;
				charsRead = recv(establishedConnectionFD, &recLen, sizeof(recLen), 0); 
				recLen +=1;
			
				//recieve key	
				char* totalKey = malloc(recLen);
				memset(totalKey, '\0', sizeof(totalKey));
				int totalRead = 0;
				while (totalRead < recLen)
				{

					//make sure the text to be received is not more than max
					if (recLen > MAX_REC_SIZE)
					{
						recLen = MAX_REC_SIZE;
					}
				
					//create buffer to hold each received message
					char recText[recLen - totalRead];

					//receive key from client
					charsRead = recv(establishedConnectionFD, recText, sizeof(recText), 0);
					totalRead += charsRead;
					strcat(totalKey, recText);
				}

				//recieve plain text
				totalRead = 0;
				char* totalPlainText = malloc(recLen);
				memset(totalPlainText, '\0', sizeof(totalPlainText));

				while (totalRead < recLen)
				{
					//make sure the text to be received is not more than max
					if (recLen > MAX_REC_SIZE)
					{
						recLen = MAX_REC_SIZE;
					}
				
					//create buffer to hold each received message
					char recText[recLen - totalRead];

					//receive key from client
					charsRead = recv(establishedConnectionFD, recText, sizeof(recText), 0);
					totalRead += charsRead;
					strcat(totalPlainText, recText);
				}

				//perform encryption
				char* encText = encrypt(recLen,totalPlainText, totalKey);

				//send encrypted text to client
				//while not all of the character have been sent, keep sending key
        			int totalChars = 0;
        			charsWritten = 0;
        			while (totalChars < recLen)
        			{

                			int sendLength;
                			//if the length of the sent text is less than the max send
                			//then send the enitre text. If not, send max send size of text
                			if (recLen <= MAX_REC_SIZE)
                			{
                			        sendLength = recLen;
                			}
                			else
                			{
                			        sendLength = MAX_REC_SIZE;
        		        	}
		
        	        		//copy unwritten chars in keyBuff to sendThis
        	        		char sendThis[sendLength - totalChars +1];
        	        		memset(sendThis, '\0', sizeof(sendThis));
        	        		strncpy(sendThis, encText + totalChars, sizeof(sendThis)-1);
	
	                		//send unwritten chars to server
	                		charsWritten = send(establishedConnectionFD,sendThis,sizeof(sendThis), 0);
          		      		if (charsWritten < 0)
                			{
                			        errorMsg("OTP_ENC_D: ERROR");
                			        exit(1);
                			}

                			//keep track of total chars written to server
                			totalChars += charsWritten;
        			}
	
				//free all mallocd memory
				free(encText);
				free(totalPlainText);
				free(totalKey);				
			
				//exit child preocess
				exit(0);
		}
	}
	close(listenSocketFD);
}

int main(int argc, char *argv[])
{
	//make sure there are least 2 args provided
	if (argc < 2) 
	{ 
		fprintf(stderr,"OTP_ENC_D: USAGE ERROR %s port\n", argv[0]); 
		exit(1); 
	} // Check usage & args
	portNumber = atoi(argv[1]); // Get the port number, convert to an integer from a string

	//connect and recieve the key and text and send back encrypted text
	connRecSend();

	return 0;
}	
