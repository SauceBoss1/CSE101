/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA6
* BigInteger.cpp 
* Main Testing harness for the Big Integer ADT
*********************************************************************************/
#include <iostream>
#include <stdexcept>
#include <string>

#include "BigInteger.h"

using namespace std;

int main(){
   string x =             "9128734667000004389234563456345619187236478";
   string y = "9876545439000000000000000200000000000006543654365346534";
   string z = "0";
   //x = "00000000000000000000000000000";
   //y = "968509";
   //x = "905860";
   //x = "-968509";
   //x = "999";
   //y = "999";
   BigInteger A = BigInteger(x);
   cout << "A: " << A << endl;
   BigInteger B = BigInteger(y);
   cout << "B: " << B << endl;

   BigInteger X = A + B;
   cout << "X add: " << X << endl;
   cout << "X.sign() = " << X.sign() << endl;

   X = B - A;
   cout << "X sub: " << X << endl;

   X = A * B;
   cout << "X mult: " << X << endl;

   cout << "(B == A)? " << ((B == A) ? "true" : "false") << endl;
   cout << "B.sign() = "<< B.sign() <<endl;
   cout << "(A <= B)? " << ((A <= B) ? "true" : "false") << endl;
   cout << "(A >= B)? " << ((A >= B) ? "true" : "false") << endl;
   cout << "(B < A)? " << ((B < A)? "true" : "false") << endl;
   cout << "(B > A)? " << ((B > A)? "true" : "false") << endl;

   cout << endl;

   A += A;
   cout << "A += A: " << A << endl;

   B -= B;
   cout << "B -= B: " << B << endl;

   X *= X;
   cout << "X *= X: " << X << endl;

   X.makeZero();
   cout << "X.makeZero() = " << X << endl;

   A.negate();
   cout << "A.negate() = " << A << endl;

   return EXIT_SUCCESS;
}