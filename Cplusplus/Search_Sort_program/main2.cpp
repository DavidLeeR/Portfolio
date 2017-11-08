/****************************************************************************
 * File Name: main2.cpp
 * Author: David Ramirez
 * Date: 5/28/17
 * Description: This is the implementation file for the main() function of 
 * 		the second program for lab 8. This program reads four files
 * 		(named data1.txt, data2.txt, data3.txt, and data4.txt),
 * 		uses a bubble sort algorithm to sort the values from the 
 * 		files, and saves the sorted values to new files which are
 * 		named by the user. A while loop containing a series
 * 		of if statements allow the main() function to read 
 * 		all 4 files and write all 4 new files. 
  *************************************************************************/



#include <iostream>
#include <fstream>

int main()
{
	//declare input and output file variable names
	std::ifstream inputFile;	
	std::ofstream outputFile;

	//output intro
	std::cout << "This is the second program for lab 8, using bubble sort.";
	std::cout << std::endl << std::endl;
	std::cout << "The results of this program can be checked by checking ";
	std::cout << "the output files created.";
	std::cout << std::endl << std::endl;

	//iterate 4 times for each file to be read and written
	for (int i=0; i < 4; i++)
	{
		int list1[9];
		int list2[10];
		int fileIn;
		int temp;

		//if this is the first iteration, open first file for reading
		//and open new file for writing
		if (i == 0)
		{
			std::string outName;
			std::string endFile = ".txt";

			//open input file
			inputFile.open("data1.txt");
			
			//display prompt to name new file for writing
			std::cout << "Enter a file name for the output file ";
			std::cout << "for the sorted contents of file 1.";
			std::cout << std::endl;
			getline(std::cin, outName);
			
			//create and open new output file
			outputFile.open(outName + endFile);
		}
		
		//if this is the second iteration, open second file for reading
		//and open new file for writing
		if (i == 1)
		{
			std::string outName;
			std::string endFile = ".txt";

			//open input file
			inputFile.open("data2.txt");
		
			//display prompt to name new file for writing
			std::cout << "Enter a file name for the output file ";
			std::cout << "for the sorted contents of file 2.";
			std::cout << std::endl;
			getline(std::cin, outName);
	
			//create and open new output file
			outputFile.open(outName + endFile);

		}
		
		//if this is the third iteration, open the third file for reading
		//and open a new file for writing
		if (i == 2)
		{
			std::string outName;
			std::string endFile = ".txt";

			//open input file
			inputFile.open("data3.txt");
	
			//display prompt to name new file for writing
			std::cout << "Enter a file name for the output file ";
			std::cout << "for the sorted contents of file 3.";
			std::cout << std::endl;
			getline(std::cin, outName);

			//create and open new output file
			outputFile.open(outName + endFile);

		}

		//if this is the fourth iteration, open the fourth file for reading
		//and open a new file for writing
		if (i == 3)
		{
			std::string outName;
			std::string endFile = ".txt";

			//open input file
			inputFile.open("data4.txt");

			//display prompt to name new file for writing	
			std::cout << "Enter a file name for the output file ";
			std::cout << "for the sorted contents of file 4.";
			std::cout << std::endl;
			getline(std::cin, outName);

			//create and open new output file
			outputFile.open(outName + endFile);

		}

		//if this is the first iteration,only read 9 lines (there are 9
		//integers)
		if (i == 0)
		{
			for (int m = 0; m < 9; m++)
			{
				//fill array list1
				inputFile >> fileIn;
				list1[m] = fileIn;
			}
		}
	
		//if this is after the first iteration, read 10 lines (there are
		//10 integers
		else 
		{
			for (int m = 0; m < 10; m++)
			{
				//fill array list2
				inputFile >> fileIn;
				list2[m] = fileIn;
			}
		}
				

		//if this is the first iterations, sort and save 9 integers
		if (i == 0)
		{
			//This bubble sort algorithm is modified code 
			//from the "Sort-Bubble" powerpoint slide 5 of the 
			//week 8 readings for CS162 
			for (int k = 8; k >= 0; k--)
			{
				for (int j = 1; j <= k; j++)
				{
					//if second value smaller than 
					//first value, switch them
					if (list1[j-1] > list1[j])
					{
						temp = list1[j-1];	
						list1[j-1] = list1[j];
						list1[j] = temp;
					}
				}
			}
	
			//save array of values to output file
			for (int p = 0; p < 9; p++)
			{
				outputFile << list1[p];
				outputFile << std::endl;
			}	
		
			inputFile.close();
			outputFile.close();
 
		}

		//if this is after the first iteration, sort and save 10 integers
		else
		{
			//This bubble sort algorithm is modified code 
			//from the "Sort-Bubble" powerpoint slide 5 of the 
			//week 8 readings for CS162 
			for (int k = 9; k >= 0; k--)
			{
				for (int j = 1; j <= k; j++)
				{
					//if second value smaller than 
					//first value, switch them
					if (list2[j-1] > list2[j])
					{
						temp = list2[j-1];	
						list2[j-1] = list2[j];
						list2[j] = temp;
					}
				}
			}
		
			//save array of values to output file
			for (int p = 0; p < 10; p++)
			{
				outputFile << list2[p];
				outputFile << std::endl;
			}	
			
			//close input and output files
			inputFile.close();
			outputFile.close();
		}

	}

	//end program
	return 0;
}
