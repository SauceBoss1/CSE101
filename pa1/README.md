# Programming Assignment 1:
## Building an integer List ADT to alphabetize lines in a file.

### Files:
- List.h
  - A header file that contains all the ***public*** functions avaliable to the client
- List.c
  - A C file that contains all the implmentations and definitions of the List ADT
- Lex.c
  - Contains the `main()` function of the program.
  - This file takes in an input file and an output file.
  - Then it sorts (using a insertion sort idea and the List ADT) the lines of the file into alphabetical order.
  - Lastly, it outputs the sorted product to the output file.
- ListTest.c
  - This file is a dummy client file that tests the List ADT.

## Usage:
- When all the files are obtained, type in `make` into the terminal.
- When the executable is produced use the following:
  - `./Lex <input file> <output file>`
- When you are done using the program, use the following command:
  - `make clean`

## Bonus make commands:
- `make ListTest`
  - Creates the executable to test the List ADT.
    - Use `./ListTest` to run the executable.

## Errors/Problems:

So far, there are no memory leaks or problems with either the List ADT or the Lex program itself. :)