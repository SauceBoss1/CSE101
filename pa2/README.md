# Programming Assignment 2:
## Building a Graph ADT to find the shortest path given a set of vertices

### Description/Synopsis:
This program takes in a file with a set of vertices and a set of sources and their destination. The program then finds the shortest path (using BFS) from the source vertex to the destination vertex.

The program was tested with around 1500 vertices and it works perfectly/

### Files:
- List.h
   - A header file that contains all the ***public*** functions avaliable to the client. (This will be used as a Queue for the Graph ADT)
- List.c
   - A C file that contains the implementations of the List ADT.
- Graph.h
   - A header file that contains all the ***public*** functions and macros avaliable to the client. (This will be used by FindPath.c to find the shortest path of a set of vertices.)
- Graph.c
   - A C file that contains all the definitions and implementations of the Graph ADT.
- GraphTest.c
   - A C file that contains the test harness of the Graph ADT.
- FindPath.c
   - A C file that contains the main() function of the program. This will be where the user inputs a file and receives and output.
- Makefile
   - A file that compiles, and links the C files and headers together to create one executable.

### Usage:
- When all the files are obtained, type in `make` into the terminal or the command line. This will compiler the program and create and executable.
- When the executable is produced use the following command to use the program:
   - `./FindPath <input file> <output file>`
- When you are done using the program, use the following command to clean up all object files and executables:
   - `make clean`

### Bonus make commands:
- `make GraphTest`
   - Creates the executable to run the Graph ADT's test harness.
      - Use `./GraphTest` to run the executable.

### Errors/Problems:
So far, there are no memory leaks or problems with either the FindPath program or the Graph ADT. :)