#include <iostream>
#include <stdexcept>
#include <string>

#include "BigInteger.h"

using namespace std;

int main(){
   string x = "-123456788";
   string y = "-123456708";
   string z = "0";
   //x = "00000000000000000000000000000";
   //y = "968509";
   //x = "905860";

   //x = "999";
   //y = "999";
   BigInteger A = BigInteger(y);
   cout << "A: " << A << endl;
   BigInteger B = BigInteger(x);
   cout << "B: " << B << endl;

   BigInteger X = A.add(B);
   cout << "X add: " << X << endl;

   X = A.sub(B);
   cout << "X sub: " << X << endl;

   X = A.mult(B);
   cout << "X mult: " << X << endl;
   cout << A.compare(B) << endl;
   cout << X.sign() <<endl;

   return EXIT_SUCCESS;
}