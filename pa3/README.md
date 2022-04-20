# Programming Assignment 3:
## Building a Graph ADT to find the strongest connected components using DFS

### Description/Synopsis:
This program takes in a file with the number of vertices and pairs of integers that will be used to create the graph. The program then find the strongest connected components using the DFS algorithm. The results of its findings will be outputted to the `<output file>`.

This program was tested with around 1000 vertices and it works perfectly.

### Files:
- List.h
  - A header file that contains all the ***public*** functions avaliable to the client. (This will be used as a Queue for the Graph ADT)
- List.c
  - A C file that contains the implementations of the List ADT.
- Graph.h
  - A header file that contains all the ***public*** functions and macros avaliable to the client. (This will mainly be used by FindComponents.c to find the strongest connected components.)
- Graph.c
  - A C file that contains all the definitions and implementations of the Graph ADT.
- GraphTest.c
  - A C file that contains the main testing harness of the Graph ADT
- FindComponents.c
  - A C file that contains the main() function of the program. This will be where the user inputs a file and receives the output file.
- Makefile
  - A file that compiles, and links the C files and headers together to create one executable.

### Usage:
- When all the files are obtained, type in `make` into the terminal or the command line. This will compile the program and create an `FindComponents` executable.
- When the executable is produced, use the following command to use the program:
  - `./FindComponents <input file> <output file>`
- When you are done using the program, use the following command to clean up all executables and object files:
  - `make clean`

### Bonus make commands:
- `make GraphTest`
  - Creates the executable to run the Graph ADT's test harness.
    - Use `./GraphTest` to run the executable.

### Errors/Problems:
So far, there are no memory leaks or problesm with either the FindComponents program or the Graph ADT. :)