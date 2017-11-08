**Search and Sort program for Intro to Computer Science II  at Oregon State University**

**Demonstrates:** search algorithms, sort algorithms 

**Steps to compile and run program:**                                                   
Requires g++ (GNU) compiler version 4.8.5                                                            
1) Download this directory (Search_Sort_program)                                      
2) navigate to Search_Sort_program directory with command line                                
3) enter the command **make all** to compile the 3 programs                                 
4) enter the command **./simplesearch** to run the search program
5) enter the command **./sortprog** to run the sort program
6) enter the command **./binarysearch** to run the binary seach program                                                         
**Requirements:**                                                                
                                                                            
**Create data files**

You will need at least four text files filled with random integer values. You don’t need a large number of values. This will just make testing easier. For example, you can create a file with a random collection of the values; 1, 2, 3, 4, 5, 6, 7, 8, & 9. Save it. Make 3 copies. In each copy put in a single value of 0: towards the beginning of one file, around the middle of another and towards the end of the third. Rename each as appropriate, i.e. early, middle, etc. Keep the original one without a 0. You can make the files beforehand, which means you don’t need to write a function to generate these files.

 **Search for the target value** (i.e. 0).

The book or the lecture has several examples of the code for searching algorithms. Implement one of them in a program that searches for the target value in your data files. Test the results (whether the file contains the targeted value). A sample output could be something like:

File 1 target value “0” not found;

File 2 target value “0” found;

File 3 target value “0” found;

            ……

You cannot use binary search yet. Why? Cite which one you used (page # or slide #).

 
 **Sort a set of values**

The book or the lecture has several examples of the code for sorting algorithms. Implement one of them in a program. Cite which one you used (page # or slide #). After you read the input file and sort it, ask the user for output file name, and then output the sorted values into the output file. Sort all input files and compare the results. Does your sorting algorithm work on all 3 input files (are the output file's number all the same)? You can just compare the output files manually to see that the sorting algorithm handles each input correctly.

 

   **Search for the target value**

Find an algorithm for binary search. Implement it in a program that searches for the target value in your data file. Remember that you cannot use any of the original files since they are not sorted. Create the data files that suitable for this task, or use the output files from task 3. Cite the reference for the algorithm you use in the comment.

This article about binary search is interesting and I think you might enjoy it.

https://research.googleblog.com/2006/06/extra-extra-read-all-about-it-nearly.html (Links to an external site.)Links to an external site.

 

For the searching, you will not hard code the function to search for "0".  Instead, you will ask the user which number to search for. 

You don’t need to provide a testing table or something similar to show your testing results, but provide a method that allows TAs to check the data by either printing it to the screen or writing into a file.

For this lab, you can implement each as a separate program or create a single program giving the user the choice of which activity to perform and instructions to run your program. If you implemented each as a separate program, then you also use one makefile. You can use an "all" target in your makefile whose dependencies are your two executable files. The makefile would then look like:

all: program1 program2

statement(s) to compile program1

statement(s) to compile program2

clean:
rm -f program1 program2

