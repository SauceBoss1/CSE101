# Programming Assignment 8:
## Red-Black Trees

### Description/Synopsis:
This project creates two exectuables:
- Order:
  - which like in PA7 outputs the inOrder String of a file input and the preorder string of an input
- WordFrequency:
  - which counts the word frequency of an input text

### Files:
- Dictionary.h
  - A header file that contains the Dictionary class structure along with its ***public*** and ***private*** member functions.
- Dictionary.cpp
  - A C++ source file that contains the implementation of the Dictionary ADT.
- DictionaryTest.cpp
  - A C++ that contains the main testing harness of the Dictionary ADT.
- Order.cpp
  - A C++ source file that contains the top-level client function of the Dictionary ADT.
- WordFrequency.cpp
  - A C++ source file that contains the second top-level client function of the Dictionary ADT.
- Makefile
  - A file that contains and links all the C++ files and headers together to create an executable

### Usage:

- Order:
  - When all the files are obtained and collected into one folder, type in `make Order` in the terminal to get the `Order` executable.
  - When the exectuable is successfully produced, you can run the program with the following command:
    - `./Order <inFile> <outFile>`
  - When you are done with the executable, use the following commands:
    - `make clean`
- WordFrequency:
  - When all the files are obtained and collected into one folder, type in `make` in the terminal to get the `WordFrequency` executable.
  - When the executable is successfully produced, you can run the program with the following:
    - `./WordFrequency <inFile> <outFile>`
  - When you are done with the executable, use the following command:
    - `make clean`

### Bonus commands:
- `make DictionaryTest`
  - Creates the main testing harness of the Dictionary ADT.

### Errors/Problems:
So far, there are no major problems with the program.