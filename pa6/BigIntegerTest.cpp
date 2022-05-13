#include <iostream>
#include <stdexcept>
#include <string>

#include "BigInteger.h"

using namespace std;

int main(){
   string x = "123456789";
   string y = "-1234567898";
   string z = "0";
   BigInteger A = BigInteger(y);
   return EXIT_SUCCESS;
}