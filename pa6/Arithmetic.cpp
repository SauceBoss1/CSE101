#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>

#include "BigInteger.h"

using namespace std;

int main(int argc, char* argv[]){

   /*** ARG PARSER***/

   if(argc != 3){
      cerr << "Usage: " << argv[0] << " <input file> <output file" << endl;
      return EXIT_FAILURE;
   }

   ifstream inFile; 
   ofstream outFile;

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

   string num_1 = "";
   string num_2 = "";
   string dumm_line = "";
   getline(inFile, num_1);
   getline(inFile, dumm_line);
   getline(inFile, num_2);
   
   BigInteger A = BigInteger(num_1);
   BigInteger B = BigInteger(num_2);

   cout << A << endl;
   cout << B << endl;
   
   return EXIT_SUCCESS;
}