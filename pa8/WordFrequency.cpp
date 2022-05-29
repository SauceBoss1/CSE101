#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <algorithm>

#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[]){
   size_t begin, end, len;
   ifstream inFile;
   ofstream outFile;
   string line, token;
   string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789"; //delimiter

   Dictionary freq;

   /*** ARG PARSER ***/

   if(argc != 3){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
   }

   inFile.open(argv[1]);
   if(!inFile.is_open()){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
   }

   outFile.open(argv[2]);
   if( !outFile.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for writng" << endl;
   }

   while( getline(inFile, line) ){
      len = line.length();

      //get first token
      begin = min(line.find_first_not_of(delim, 0), len);
      end   = min(line.find_first_of(delim, begin), len);
      token = line.substr(begin, end-begin);
      transform(token.begin(), token.end(), token.begin(), ::tolower);

      while( token != ""){
         //update dictionary 
         
         try{
            freq.getValue(token) += 1;
         } catch(logic_error& e){
            freq.setValue(token, 1);
         }

         //get next token
         begin = min(line.find_first_not_of(delim, end+1), len);
         end   = min(line.find_first_of(delim, begin), len);
         token = line.substr(begin, end-begin);
         transform(token.begin(), token.end(), token.begin(), ::tolower);
      }
   }

   //print results
   outFile << freq << endl;

   //closing procedures

   inFile.close();
   outFile.close();

   return EXIT_SUCCESS;
}