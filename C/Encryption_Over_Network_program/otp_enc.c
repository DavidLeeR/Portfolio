/******************************************************************************
 ** Author: David Ramirez
 ** Date: 11/24/17
 ** Description: Connects to otp_enc_d daemon program and requests it to perform
 **		 a one-time pad style encryption. Use this program with command
 **		 format "otp_enc plaintext key port".
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
int textLen;	   //length of plain text
int portNumber;    //holds specified port number
char* keyBuff;     //buffer to hold key
char* textBuff;    //buffer to hold plain text
char* finalCipher;  //holds encoded text

//passes message parameter to perror to output fill error message to stderr
void errorMsg(const char *msg)
{
	perror(msg);
	exit(1);
}

//recieves the encoded text from the server
void recText(int socketFile)
{
	//allocate memory for finalCipher to hold amount of text to 
	//recieve +1 for the newline
	finalCipher = malloc(textLen+1);
	memset(finalCipher, '\0', sizeof(finalCipher));	
	//holds number of chars read in one transmission
	int charsRead;
	//holds number of total chars read from all transmissions
	int totalCharsRead = 0;

	//while there are still chars that need to be read
	while (totalCharsRead < textLen)
	{
		//holds cipher text to be recieved
		char cipherBuff[textLen];
		memset(cipherBuff, '\0', sizeof(cipherBuff)+1);
		//read from socket
		charsRead = recv(socketFile, cipherBuff, sizeof(cipherBuff), 0);
		if (charsRead < 0)
		{
			errorMsg("OTP_ENC: ERROR reading from socket");
			exit(1);
		}

		//add chars from this transmission to the complete cipher
		strcat(finalCipher, cipherBuff);	
		totalCharsRead += charsRead;
	}	
}

//sends key and plain text to server
void sendText(int socketFile)
{
 	
	//send number of chars to read to server, use textLen because
	//we only need the portion of the key whose length is equal to the 
	//length of of the plain text
	int charsWritten = send(socketFile, &textLen, sizeof(textLen), 0);
	if (charsWritten < sizeof(textLen))
	{
		fprintf(stderr, "\nOTP_ENC: ERROR writing to server\n");
	}

	//while not all of the character have been sent, keep sending key
	int totalChars = 0;
	charsWritten = 0;
	while (totalChars < textLen)
	{
				
		int sendLength;
		//if the length of the sent text is less than the max send 
		//then send the enitre text. If not, send max send size of text
		if (textLen <= MAX_SEND_SIZE)
		{
			sendLength = textLen;
		}
		else
		{
			sendLength = MAX_SEND_SIZE;		
		}

		//copy unwritten chars in keyBuff to sendThis
		char sendThis[sendLength - totalChars +1];
		memset(sendThis, '\0', sizeof(sendThis));
		strncpy(sendThis, keyBuff + totalChars, sizeof(sendThis)-1);
		

		//send unwritten chars to server
		charsWritten = send(socketFile,sendThis,sizeof(sendThis), 0);
		if (charsWritten < 0)
		{
			errorMsg("OTP_ENC: ERROR");
			exit(1);
		}
		
		//keep track of total chars written to server
		totalChars += charsWritten;
	}

	//while not all of the character have been sent, keep sending key
	totalChars = 0;
	charsWritten = 0;
	while (totalChars < textLen)
	{
				
		int sendLength;
		//if the length of the sent text is less than the max send 
		//then send the enitre text. If not, send max send size of text
		if (textLen <= MAX_SEND_SIZE)
		{
			sendLength = textLen;
		}
		else
		{
			sendLength = MAX_SEND_SIZE;		
		}

		//copy unwritten chars in keyBuff to sendThis
		char sendThis[sendLength - totalChars +1];
		memset(sendThis, '\0', sizeof(sendThis));
		strncpy(sendThis, textBuff + totalChars, sizeof(sendThis)-1);

		//send unwritten chars to server
		charsWritten = send(socketFile,sendThis,sizeof(sendThis), 0);
		if (charsWritten < 0)
		{
			errorMsg("OTP_ENC: ERROR");
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
	//holds total written message
	int totalCharsWritten = 0;
	//e for encryption
	char* whichClient = "e";

	//while the client still has data to write to the server, keep writing
	while (charsWritten < 1)
	{
		charsWritten = send(socketFile, whichClient,1, 0);
		if (charsWritten < 0)
		{
			errorMsg("OTP_ENC: ERROR authenticating server");
			exit(1);	
		}	
	}

	//receive whether connected to correct program
	int charsRead = recv(socketFile, &serverYesNo, 1, 0);
	if (charsRead < 0)
	{
		errorMsg("OTP_ENC: ERROR reading from socket");
		exit(1);
	}

	//if connected to wrong program, error and exit
	if (serverYesNo == 1)
	{
		fprintf(stderr, "OTP_ENC: ERROR cannot connect to otp_dec_d");
		close(socketFile);
		exit(1);
	}		
}

//checks plain text and key for invalid characters
void charCheck()
{
	//for each char in the key, check to make sure the char is upper
	//case or a space
	int i = 0;
	for (i; i < keyLen; i++)
	{
		//if the char is not a capital letter or space
		if ((keyBuff[i] > 90 || keyBuff[i] < 65)&&(keyBuff[i] != 32)) 
		{
			fprintf(stderr, "\nOTP_ENC: ERROR invalid char in key\n");
			exit(1);
		}
	}

	//for each char in the text, check to make sure the char is upper
	//case or a space
	i = 0;
	for (i; i < textLen; i++)
        {
                //if the char is not a capital letter or space
                if ((textBuff[i] > 90 || textBuff[i] < 65)&&(textBuff[i] != 32))
                {
                        fprintf(stderr, "\nOTP_ENC: ERROR invalid char in plain text\n");
			exit(1);
                }
        }
}
	
//connects to host server (otp_enc_d)
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
		fprintf(stderr, "OTP_ENC: ERROR no such host\n"); 
		exit(1); 
	}
	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length); // Copy in the address

	//set up the socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (socketFD < 0) 
	{
		errorMsg("OTP_ENC: ERROR opening socket");
		exit(1);
	}
	//connect to server
	int thisErr = connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)); // Connect socket to address
	if (thisErr < 0)
	{
		fprintf(stderr,"\nOTP_ENC: ERROR connecting to port number %d\n",portNumber);
		exit(2);
	}

	//authenticate server
	checkServer(socketFD);

	//send plain text and key to server
	sendText(socketFD);

	//recieve cipher from server
	recText(socketFD);
}


int main(int argc, char *argv[])
{
	//make sure 3 arguments are provided
	if (argc < 4)
        {
                fprintf(stderr, "\nOTP_ENC: ERROR incorrect number of arguments for otp_enc\n");
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
		errorMsg("OTP_ENC: ERROR key file");
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
	FILE *textFile = fopen(argv[1], "r");
	if (textFile == NULL)
	{
		errorMsg("OTP_ENC: ERROR plain text file error");
		exit(1);
	}
	//find length of file and save as textLen
	fseek(textFile, 0, SEEK_END);
        textLen = ftell(textFile);
	//do not read the newline char
	textLen = textLen - 1;
	//reset file pointer
        fseek(textFile, 0, SEEK_SET);

	//make sure that key is at least as long as plain text
	if (textLen >= keyLen)
	{
		fprintf(stderr, "\nOTP_ENC: ERROR key length is shorter than plain text length\n");
		exit(1);
	} 
	
	//read from key file into key buffer 
	keyBuff = malloc(keyLen+1);
	memset(keyBuff, '\0', sizeof(keyBuff));
	fread(keyBuff,1, keyLen, keyFile);
	//close key file
	fclose(keyFile);

	//read from text file into text buffer
	textBuff = malloc(textLen+1);
        memset(textBuff, '\0', sizeof(textBuff));
        fread(textBuff,1, textLen, textFile);
        //close key file
        fclose(textFile);
       
	//check for invalid chars in key and plain text buffers
	charCheck();
	
	//connect to port and send data
	connectAndSend();		

	//ouput the cipher text to std out
	printf("%s\n", finalCipher);

	//free all mallocd memory
	free(keyBuff);
	free(textBuff);
	free(finalCipher);	
}



		
