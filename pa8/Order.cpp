/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA8
* Order.cpp 
* Source file that contains the first top-client program of the Dictionary ADT
*********************************************************************************/
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>

#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[]){
   
   /*** ARG PARSER ***/

   if(argc != 3){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return EXIT_FAILURE;
   }

   ifstream inFile;
   ofstream outFile;
   string line;

   inFile.open(argv[1]);
   if(!inFile.is_open()){
      cerr << "Unable to open file " << argv[1] << " for reading"<<endl;
      return EXIT_FAILURE;
   }

   outFile.open(argv[2]);
   if(!outFile.is_open()){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return EXIT_FAILURE;
   }

   /*** INPUT PARSING ***/

   Dictionary A;

   int val = 1;
   while( getline(inFile, line) ){
      A.setValue(line, val);
      val++;
   }

   /*** OUTPUT ***/
   outFile << A << endl << endl;
   outFile << A.pre_string() << endl;

   /*** CLOSING OPERATIONS ***/
   inFile.close();
   outFile.close();
   
   return EXIT_SUCCESS;
}