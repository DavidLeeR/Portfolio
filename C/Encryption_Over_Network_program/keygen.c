/******************************************************************************
 * Author: David Ramirez
 * Date: 11/24/17
 * Description: Creates a keyfile of specified length. Use this program with
 * 		"keygen <length of key>"
 * ***************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main(int argc, char *argv[])
{
	//make sure 1 argument is provided, print error if not
	if (argc != 2)
	{
		fprintf(stderr, "\nError: incorrect number of arguments for keygen\n");
		exit(1);
	}

	//convert string argument to int
	int keyLength = atoi(argv[1]);

	//string that will hold the generated key
	char key[keyLength+1];

	//seed random
	srand(time(NULL));

	//loop to generate key of capital letters and spaces
	int i;
	for (i; i < keyLength; i++)
	{
		//get random number from 0 to 26
		int asciiAdd = rand() % 27;

		//if random number is 26, insert a space into the key
		if (asciiAdd == 26)
		{
			key[i] = ' ';
			continue;
		}		
	
		//insert the random capital letter into the key
		key[i] = 'A' + asciiAdd;	
	}

	//add end line char to end of key
	key[keyLength] = '\n';
	//print key
	printf("%s", key);
			
	return 0;
		
}
