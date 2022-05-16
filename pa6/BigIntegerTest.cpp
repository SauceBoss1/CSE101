#include <iostream>
#include <stdexcept>
#include <string>

#include "BigInteger.h"

using namespace std;

int main(){
   string x = "123456788";
   string y = "123456708";
   string z = "0";
   //x = "00000000000000000000000000000";
   y = "968509";
   x = "905860";

   //x = "999";
   //y = "999";
   BigInteger A = BigInteger(x);
   BigInteger B = BigInteger(y);
   BigInteger X = A.add(B);
   X = A.sub(B);
   X = A.mult(B);
   cout << A.compare(B) << endl;
   cout << X.sign() <<endl;

   return EXIT_SUCCESS;
}