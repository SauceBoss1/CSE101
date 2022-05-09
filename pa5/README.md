# Programming Assignment 5:
## The Perfect Shuffle (C++)

### Description/Synopsis:
This program takes an integer input and creates a deck size from 1 to the integer input the user typed in. The program will then perfectly shuffle the deck until it is back into its original state. The number next to the deck size will tell us how many shuffles it took to go back to the original state of the deck.

This program was tested with a deck size if 1000 cards and it works perfectly fine.

### Files:

- List.h
  - A header file the contains the ***class*** declaration and properties of the List ADT.
- List.cpp
  - A C++ source file that contiains the implementations of the List ADT.
- ListTest.cpp
  - A C++ source file that contains the main test harness of the List ADT
- Shuffle.cpp
  - A C++ source file that is the main client file for the List ADT. This perfectly shuffles a deck of *n* cards until the deck returns to the original state.
- Makefile
  - A file that compilers, and links all the C++ files and headers together to create one executable.

### Usage:
- When all the source and header files are obtained into one folder, type in `make` in the terminal to get the `Shuffle` exectuable.
- When the executable is produced, use the following command to use the program:
  - `./Shuffle <deck size>`
- When you are done using the executable, use the following command to clean up all executables and object files:
  - `make clean`

### Bonus commands:
- `make ListTest`
  - Creates the executbale to run the List's test harness
    - Use `./ListTest` to run

### Error/Problems:
So far, there are no major problems with the program.