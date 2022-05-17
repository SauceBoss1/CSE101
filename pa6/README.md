# Programming Assignment 6:
## Calculating Big Integers (C++)

### Description/Synopsis:
This program takes a Big Integer (BI) file and does arithmetic on those BIs.
The following is the calculations that are outputted:
- A
- B
-  A + B 
-  A - B 
-  A - A 
-  3A - 2B 
-  AB 
-  A^2 
-  B^2 
-  9A^4 + 16B^5 

The program was tested with in5 which is the biggest BI file given to use for testng and it takes about 30 seconds to run.

### Files:

- List.h
  - A header file the contains the ***class*** declaration and properties of the List ADT.
  - ***NOTE:*** The List ADT was modfied to deal with longs rather than ints
- List.cpp
  - A C++ source file that contiains the implementations of the List ADT.
- ListTest.cpp
  - A C++ source file that contains the main test harness of the List ADT
- BigInteger.h
  - A header file that contains the ***class*** declaration and properties of the BI ADT.
- BigInteger.cpp
  - Contains the implementations of the declarations in the corresponding header.
- BigIntergerTest.cpp
  - Contains the main test harness of the BI ADT.
- Arithmetic.cpp
  - Contains the main client file that takes in the BI files and does arithmetic on them.
- Makefile
  - A file that compiles and links all the C++ files and headers together to create on executable

### Usage:
- When all the source and header files are collected into one folder, type in `make` in the termiansl to get the `Arithemetic` exectuable.
- When the executable is produced, use the following command to run the program:
  - `./Arithmetic <input File> <output File>`
- When you are done using the executable, use the following command to clean up al the executables and object files:
  - `make clean`

### Bonus commands:
- `make ListTest`
- `make BigIntegerTest`
The above commands create the test harnesses for the List ADT and the BI ADT

### Errors/Problems:
So far, there are no major problems with the program. However, the program takes roughly 30 seconds to run in5. :)