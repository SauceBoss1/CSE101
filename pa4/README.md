# Programming Assignment 4:
## Building a Matrix ADT to do Sparse Matrices calculations

### Description/Synopsis:
This program takes in a file with the matrix coordinates and its corresponding values and does Transpose, Scalar Multiplication, Sum, Difference, and Product calculations on them. The results of these calculations can be found in the outputted `<output file>`.

This program was tested with a 1000000 x 1000000 sized matrix and it works perfectly with its run time being less than 20-15 seconds

### Files:

- List.h
  - A header file that contains all the ***public*** functions avaliable to the client. (This will be used as a Queue for the Graph ADT)
- List.c
  - A C file that contains the implementations of the List ADT. (NOTE: The List ADT has been modified to use void* instead of an int).
- Matrix.h
  - A header file that containts all the ***public*** functions and macros avaliable to the client. (This will be used mainly by Sparse.c to so sparse matrix calcuations.)
- Matrix.c
  - A C file that contains the implementations of the Matrix ADT.
- MatrixTest.c
  - A C file that contains the main testing harness of the Matrix ADT.
- ListTest.c
  - A C file that contains the main testing harness of the modified List ADT.
- Sparse.c
  - The main client file for the Matrix ADT that does sparse Matrix calculations.
- Makefile
  - A file that compiles, and links all C files and headers togther to create one executable.

### Usage:
- When all the source and header files are obtained into one folder, type in `make` in the terminal to create the `Sparse` executable.
- When the executable is produced, use the following command to use the program:
  - `./Sparse <input file> <output file>`
- When you are done using the program, use the following command to clean up all exectubles and object files:
  - `make clean`

### Bonus commands:
- `make ListTest`
  - Creates the executable to run the List's test harness
    - Use `./ListTest` to run
- `make MatrixTest`
  - Creates the executable to run the Matrix ADT's test harness
    - Use `./MatrixTest` to run
- `make all`
  - Creates *ALL* exectutables including the Tantalo written Client Tests.

### Error/Problems:
So far, there are no major problems with the program however, the 1 million sized matrices can take up to 20 seconds to run.