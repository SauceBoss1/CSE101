/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA6
* Arithmetic.cpp 
* Main Client file that uses the Big Integer ADT
*********************************************************************************/
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
   
   BigInteger temp_A, temp_B, ans;
   temp_A = A; temp_B = B;

   outFile << A << endl;
   outFile << B << endl;

   /*** A + B ***/
   ans = temp_A + temp_B;
   outFile << ans << endl;

   /*** A - B ***/
   ans = temp_A - temp_B;
   outFile << ans << endl;

   /*** A - A ***/
   ans = temp_A - temp_A;
   outFile << ans << endl;

   /*** 3A - 2B ***/ 
   BigInteger three = BigInteger("3");
   BigInteger two = BigInteger("2");

   ans = (three * temp_A) - (two * temp_B);
   outFile << ans << endl;
   temp_A = A; temp_B = B;

   /*** AB ***/
   ans = temp_A * temp_B;
   outFile << ans << endl;

   /*** A^2 ***/
   temp_A *= temp_A;
   outFile << temp_A << endl;
   temp_A = A;

   /*** B^2 ***/
   temp_B *= temp_B;
   outFile << temp_B << endl;
   temp_B = B;

   /*** 9A^4 + 16B^5***/ //wrong
   BigInteger nine = BigInteger("9");
   BigInteger sixteen = BigInteger("16");

   temp_A = A * A * A * A;
   temp_B = B * B * B * B * B;

   ans = (nine * temp_A) + (sixteen * temp_B);

   outFile << ans << endl;
   temp_A = A; temp_B = B;

   return EXIT_SUCCESS;
}