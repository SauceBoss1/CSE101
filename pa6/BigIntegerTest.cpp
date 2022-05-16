#include <iostream>
#include <stdexcept>
#include <string>

#include "BigInteger.h"

using namespace std;

int main(){
   string x = "123456788";
   string y = "123456708";
   string z = "0";
   //x = "968509";
   //y = "905860";
   BigInteger A = BigInteger(x);
   BigInteger B = BigInteger(y);
   BigInteger X = A.add(B);
   X = A.sub(B);
   cout << A.compare(B) << endl;
   cout << X.sign() <<endl;
   return EXIT_SUCCESS;
}