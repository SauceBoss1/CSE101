#include <iostream>
#include <string>
#include <stdexcept>

#include "List.h"
using namespace std;
int main(){
   List A;
   for(int i = 1; i <= 10; ++i){
      A.insertBefore(1);
      A.insertAfter(i);
   }
   cout << "A = " << A << endl;
   A.cleanup();
   cout << "A = " << A << endl;
   return EXIT_SUCCESS;
}