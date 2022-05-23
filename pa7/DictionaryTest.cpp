#include <iostream>
#include <stdexcept>
#include <string>

#include "Dictionary.h"

using namespace std;

int main(){
   Dictionary A;
   string S[] = {"one", "two", "foo", "bar", "happy", "is", "three", "par"};

   for(int i=0; i<8; i++){
      A.setValue(S[i], i+1);
   }

   cout << A << endl;

   cout << "A.size() = " << A.size() << endl << endl;

   for(A.begin(); A.hasCurrent(); A.next()){
      cout << A.currentKey() << endl;
   }
   cout << endl;
   Dictionary B;
   B = A;

   cout << "B\n" <<B << endl;
   B.clear();
   cout << "B.size() = " << B.size() << endl;

   return EXIT_SUCCESS;
}