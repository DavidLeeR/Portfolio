**Bash shell script written for the course "Operating Systems" at Oregon State University**

**Description:** Bash shell script that computes statistics from user input or an input file. 

**Demonstrates:** Unix shell programming, Unix utilities, standard input, standard output, standard error, process ids, exit values, signals

**Requirements:** In this assignment, you will write a bash shell script to calculate mean averages and medians of numbers that can be input to your script from either a file or via stdin. This is the sort of calculation I might do when figuring out the grades for this course. The input will have whole number values separated by tabs, and each line will have the same number of values (for example, each row might be the scores of a student on assignments). Your script should be able to calculate the mean and median across the rows (like I might do to calculate an individual student's course grade) or down the columns (like I might do to find the average score on an assignment).

You will probably need commands like these, so please read up on them: while, cat, read, expr, cut, head, tail, wc, and sort.

Your script must be called simply "stats". The general format of the stats command is:

stats {-rows|-cols} [input_file]

Note that when things are in curly braces separated by a vertical bar, it means you should choose one of the things; here for example, you must choose either -rows or -cols. The option -rows calculates the mean and median across the rows; the option -cols calculates the mean and median down the columns. When things are in square braces it means they are optional; you can include them or not, as you choose. If you specify input_file the data is read from that file; otherwise, it is read from stdin.
