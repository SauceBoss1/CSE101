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

   //x = "999";
   //y = "999";
   BigInteger A = BigInteger(x);
   cout << "A: " << A << endl;
   BigInteger B = BigInteger(y);
   cout << "B: " << B << endl;

   BigInteger X = A.add(B);
   cout << "X add: " << X << endl;

   X = B - A;
   cout << "X sub: " << X << endl;

   cout << A << endl;
   X = A * B;
   cout << "X mult: " << X << endl;
   cout << A.compare(B) << endl;
   cout << X.sign() <<endl;

   return EXIT_SUCCESS;
}