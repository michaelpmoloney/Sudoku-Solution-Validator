# Sudoku-Solution-Validator
Multithreaded Linux application that determines whether the solution to a Sudoku puzzle is valid.

Objective: To understand and experiment with thread creation using Pthread library in Linux.

Problem Statement: Design and implement a Sudoku Solution Validator using Pthreads library in Linux.
Use 11 children threads. The 9x9 data grids to be tested are stored in two txt files, grid1 and grid2,
which are provided. The name of the txt files will be the input to the program via command line. The
output message stating whether or not the tested grid is a Sudoku puzzle should be finally printed to the
screen.

/*************************************************************************************************/

Sudoku Puzzle Information: A Sudoku puzzle uses a 9×9 grid in which each column and row, as well as each 
of the nine 3×3 subgrids, must contain all of the digits 1 through 9.

/************************************************************************************************/

Advantages/Disadvantages:

-Using 11 children threads

Advantage: Even though the cpu most likely doesn't have 11 cores, this will still speed up the computation. The threads can be sent to an available core when one becomes available. This may be faster than assigning tasks to only 3 threads. Plus this will take advantage of the fact that threads have a much lower overhead, speeding up the process.

-Using 3 threads(one for all rows, one for all columns, one for all 3x3 subgrids)

Advantage: This will split up the work among different cores, greatly speeding up computation.
Disadvantage: The work can be broken up into even more threads. This is not taking full advantage of that.

-Using only one single child thread to do all checking

Disadvantage: This is just a linear run-through of the code. This will not take advantage of multi-cores, and each segment of the program will have to wait its turn.

/*******************************************************************************************************/

High Level Description:
Threading splits the work up, but the threads still share resources. This was useful in the program because I was able to create a 2D array from the input file and assign threads to handle different parts of the array at the same time. My program first checks if there is an input argument. If there is one, the file is read into a 2D array and then displayed. The 9x9 Sudoku is split into 11 sections(all rows,all columns, and 9 subgrids) and their coordinates are stored in 11 different structs that are kept in an array. 11 threads are 
then created, and these structs are each set as an input for a thread. The three thread methods take the struct's coordinates and create a 9 element array, whether it be a row, column, or a subgrid. This extracted array is then sorted and compared against a global array variable containing 0 thru 9. If the two arrays match then 1 is returned to an array of size 11 that all threads have access to. Finally, the array of size 11 is checked to see if all indexes are 1. If they are, then the Sudoku is valid. If they are not, then the Sudoku is invalid.

/*****************************************************************************************************/

Output of Program:

![alt text](https://raw.githubusercontent.com/michaelpmoloney/Sudoku-Solution-Validator/blob/master/Moloney_grid1.png)

![alt text](https://raw.githubusercontent.com/michaelpmoloney/Sudoku-Solution-Validator/blob/master/Moloney_grid2.png)
