/******************************************************************************
 ** Author: David Ramirez
 ** Date: 11/24/17
 ** Description: Connects to otp_dec_d daemon program and requests it to perform
 **		 a one-time pad style decryption. Use this program with command
 **		 format "otp_dec ciphertext key port".
 ** ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h> 


//global contant
#define MAX_SEND_SIZE 70000   //max length of sent transmission to server

//global variables
int keyLen;	   //length of key
int cipherLen;	   //length of cipher text
int portNumber;    //holds specified port number
char* keyBuff;     //buffer to hold key
char* cipherBuff;    //buffer to hold plain text
char* finalText;   //holds decoded text

//passes message parameter to perror to output fill error message to stderr
void errorMsg(const char *msg)
{
	perror(msg);
	exit(1);
}

//recieves the decoded text from the server
void recText(int socketFile)
{
	//allocate memory for finalText to hold amount of text to
	//receive +1 for the newline
	finalText = malloc(cipherLen+1);
	memset(finalText, '\0', sizeof(finalText));	
	//holds number of chars read in one transmission
	int charsRead;
	//holds number of total chars read from all transmissions
	int totalCharsRead = 0;

	//while there are still chars that need to be read
	while (totalCharsRead < cipherLen)
	{	
		//holds cipher text to be recieved
		char cipherBuff[cipherLen];
		memset(cipherBuff, '\0', sizeof(cipherBuff)+1);
		//read from socket
		charsRead = recv(socketFile, cipherBuff, sizeof(cipherBuff), 0);
		if (charsRead < 0)
		{
			errorMsg("OTP_DEC: ERROR reading from socket");
			exit(1);
		}

		//add chars from this transmission to the complete cipher
		strcat(finalText, cipherBuff);	
		totalCharsRead += charsRead;
	}	
}

//sends key and plain text to server
void sendText(int socketFile)
{
 	
	//send number of chars to read to server, use cipherLen because
	//we only need the portion of the key whose length is equal to the 
	//length of of the plain text
	int charsWritten = send(socketFile, &cipherLen, sizeof(cipherLen), 0);
	if (charsWritten < sizeof(cipherLen))
	{
		fprintf(stderr, "\nOTP_DEC: ERROR writing to server\n");
	}
	
	//while not all of the character have been sent, keep sending key
	int totalChars = 0;
	charsWritten = 0;
	while (totalChars < cipherLen)
	{
				
		int sendLength;
		//if the length of the sent text is less than the max send 
		//then send the enitre text. If not, send max send size of text
		if (cipherLen <= MAX_SEND_SIZE)
		{
			sendLength = cipherLen;
		}
		else
		{
			sendLength = MAX_SEND_SIZE;		
		}

		//copy unwritten chars in keyBuff to sendThis
		char sendThis[sendLength - totalChars +1];
		memset(sendThis, '\0', sizeof(sendThis));
		strncpy(sendThis, keyBuff + totalChars, sizeof(sendThis)-1);

		//printf("\n%s\n", sendThis);
		//send unwritten chars to server
		charsWritten = send(socketFile,sendThis,sizeof(sendThis), 0);
		if (charsWritten < 0)
		{
			errorMsg("OTP_DEC: ERROR");
			exit(1);
		}
		
		//keep track of total chars written to server
		totalChars += charsWritten;
	}

	//while not all of the character have been sent, keep sending key
	totalChars = 0;
	charsWritten = 0;
	while (totalChars < cipherLen)
	{
				
		int sendLength;
		//if the length of the sent text is less than the max send 
		//then send the enitre text. If not, send max send size of text
		if (cipherLen <= MAX_SEND_SIZE)
		{
			sendLength = cipherLen;
		}
		else
		{
			sendLength = MAX_SEND_SIZE;		
		}

		//copy unwritten chars in keyBuff to sendThis
		char sendThis[sendLength - totalChars +1];
		memset(sendThis, '\0', sizeof(sendThis));
		strncpy(sendThis, cipherBuff + totalChars, sizeof(sendThis)-1);

		//printf("\n%s\n", sendThis);
		//send unwritten chars to server
		charsWritten = send(socketFile,sendThis,sizeof(sendThis), 0);
		if (charsWritten < 0)
		{
			errorMsg("OTP_DEC: ERROR");
			exit(1);
		}
		
		//keep track of total chars written to server
		totalChars += charsWritten;
	}

}

//checks to make sure that otp_enc does not connect to otp_dec_d
void checkServer(int socketFile)
{
	//0 if correct server, 1 if incorrect server
	int serverYesNo;
	//holds number of chars written in one transmission
	int charsWritten =0;
	//hold total written message
	int totalCharsWritten = 0;
	//d for decryption
	char* whichClient = "d";

	//while the client still has chars to write to the server, keep writing
	while (charsWritten < 1)
	{
		charsWritten = send(socketFile, whichClient,1, 0);
		if (charsWritten < 0)
		{
			errorMsg("OTP_DEC: ERROR authenticating server");
			exit(1);	
		}	
	}

	//recieve whether connected to correct program
	int charsRead = recv(socketFile, &serverYesNo, 1, 0);
	if (charsRead < 0)
	{
		errorMsg("OTP_DEC: ERROR reading from socket");
		exit(1);
	}

	//if connected to wrong program, error and exit
	if (serverYesNo == 1)
	{
		fprintf(stderr, "OTP_DEC: ERROR cannot connect to otp_enc_d");
		close(socketFile);
		exit(1);
	}		
}

//checks plain text and key for invalid characters
void charCheck()
{
	//for each char in key, check chars	
	int i = 0;
	for (i; i < keyLen; i++)
	{
		//if the char is not a capital letter or space
		if ((keyBuff[i] > 90 || keyBuff[i] < 65)&&(keyBuff[i] != 32)) 
		{
			fprintf(stderr, "\nOTP_DEC: ERROR invalid char in key\n");
			exit(1);
		}
	}

	//for each char in cipher, check chars
	i = 0;
	for (i; i < cipherLen; i++)
        {
                //if the char is not a capital letter or space
                if ((cipherBuff[i] > 90 || cipherBuff[i] < 65)&&(cipherBuff[i] != 32))
                {
                        fprintf(stderr, "\nOTP_DEC: ERROR invalid char in plain text\n");
			exit(1);
                }
        }
}
	
//connects to host server
void connectAndSend()
{
	int socketFD, charsWritten, charsRead;
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
	char buffer[256];
	
	//set up the server address struct
	memset((char*)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverHostInfo = gethostbyname("localhost"); // Convert the machine name into a special form of address
	if (serverHostInfo == NULL) 
	{ 
		fprintf(stderr, "OTP_DEC: ERROR no such host\n"); 
		exit(1); 
	}
	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length); // Copy in the address

	//set up the socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (socketFD < 0) 
	{
		errorMsg("OTP_DEC: ERROR opening socket");
		exit(1);
	}
	//connect to server
	int thisErr = connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)); // Connect socket to address
	if (thisErr < 0)
	{
		fprintf(stderr,"\nOTP_DEC: ERROR connecting to port number %d\n",portNumber);
		exit(2);
	}

	//authenticate server
	checkServer(socketFD);

	//send key and cipher text to server
	sendText(socketFD);

	//recieve decoded text from server
	recText(socketFD);

}


int main(int argc, char *argv[])
{
	//make sure 3 areguments are provided, print error and exit if not
	if (argc < 4)
        {
                fprintf(stderr, "\nOTP_DEC: ERROR incorrect number of arguments\n");
                exit(1);
        }

	//save port number to global var 
	portNumber = atoi(argv[3]);


	//Open key file and find length of file.
	//this block of code is modified from
	//https:stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c
	FILE *keyFile = fopen(argv[2], "r");
	if(keyFile == NULL)
	{
		errorMsg("OTP_DEC: ERROR key file");
		exit(1);
	}
	//find length of file and save as keyLen, then reset file pointer
	fseek(keyFile, 0, SEEK_END);
	keyLen = ftell(keyFile);
	//do not read the newline char
	keyLen = keyLen - 1;
	fseek(keyFile, 0, SEEK_SET);

	//Open key file and find length of file.
	//this block of code is modified from
	//https:stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c
	FILE *cipherFile = fopen(argv[1], "r");
	if (cipherFile == NULL)
	{
		errorMsg("OTP_DEC: ERROR opening cipher text file");
		exit(1);
	}
	//find length of file and save as cipherLen, then reset file pointer
	fseek(cipherFile, 0, SEEK_END);
        cipherLen = ftell(cipherFile);
	cipherLen = cipherLen -1;
        fseek(cipherFile, 0, SEEK_SET);

	//make sure that key is at least as long as plain text
	if (cipherLen >= keyLen)
	{
		fprintf(stderr, "\nOTP_DEC: ERROR key length is shorter than cipher text length\n");
		exit(1);
	} 
	
	//read from key file into key buffer 
	keyBuff = malloc(keyLen);
	memset(keyBuff, '\0', sizeof(keyBuff));
	fread(keyBuff,1, keyLen, keyFile);
	//close key file
	fclose(keyFile);

	//read from text file into text buffer
	cipherBuff = malloc(cipherLen);
        memset(cipherBuff, '\0', sizeof(cipherBuff));
        fread(cipherBuff,1, cipherLen, cipherFile);
        //close key file
        fclose(cipherFile);
        
	//check for invalid chars in key and plain text buffers
	charCheck();
	
	//connect to port and send data
	connectAndSend();		

	//ouput the decrypted text to std out
	printf("%s\n", finalText);

	//free all mallocd memory
	free(keyBuff);
	free(cipherBuff);
	free(finalText);

	
}



		
