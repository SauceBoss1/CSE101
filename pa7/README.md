# Programming Assignment 7:
## Binary Search Trees

### Description/Synopsis:
This program takes in a file that has a random word on each line. The `Order` executable then uses a binary search tree to alphabetize the words using an in-order tree walk. As a bonus, a pre-order tree walk string representation is outputted as well.

The program was tested with `infile5.txt` with valgrind and it runs in under 13 seconds.

### Files:

- Dictionary.h
  - A header file that contains the Dictionary class structure along with its ***public*** and ***private*** member functions.
- Dictionary.cpp
  - A C++ source file that contains the implementation of the Dictionary ADT.
- DictionaryTest.cpp
  - A C++ that contains the main testing harness of the Dictionary ADT.
- Order.cpp
  - A C++ source file that contains the top-level client function of the Dictionary ADT.
- Makefile
  - A file that compiles and links all the C++ files and headers together to create an executable

### Usage:
- When all the files are obtained and collected into one folder, type in `make` in the terminal to get the `Order` executable.
- When the exectuable is successfully produced, you can run the program with the following command:
  - `./Order <inFile> <outFile>`
- When you are done with the executable, use the following commands:
  - `make clean`

### Bonus commands:
- `make DictionaryTest`
  - Creates the main testing harness of the Dictionary ADT.

### Errors/Problems:
So far, there are no major problems with the program. However, the program takes roughly 13 seconds to run infile5.txt with valgrind.

Withou valgrind, the program runs in less than a second.