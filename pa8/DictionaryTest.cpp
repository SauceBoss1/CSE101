/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA7
* DictionaryTest.cpp
* Source file that contains the main test harness for the Dictionary ADT
*********************************************************************************/
#include <iostream>
#include <stdexcept>
#include <string>

#include "Dictionary.h"

using namespace std;

int main(){
   Dictionary A;
   string S[] = {"one", "two", "foo", "bar", "happy", "is", "three", "par"};
   string S2[] = {"uno", "dos", "tres", "quatro", "cinco", "seis", "siete", "ocho", "nueve", "diez"};

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
   cout << "B.size() after clearing it: " << B.size() << endl;

   Dictionary C = A;

   for(int i = 0; i < 10; ++i){
      C.setValue(S2[i],i);
   }

   cout << "\nC:\n" << C << endl;

   for(C.end(); C.hasCurrent(); C.prev()){
      cout << "<" << C.currentKey() << ", " << (++C.currentVal()) << ">"<< endl; 
   } 

   cout << "\nC.contains(\"once\") ? " << (C.contains("once") ? "true":"false") << endl;

   cout << "\nC.getValue(\"uno\"): " << C.getValue("uno") << "\nincreaseVal: " << (C.getValue("uno") += 9) << endl;

   C.remove("bar");
   cout << "\nC.remove(\"bar\")\n" << C.pre_string() << endl;

   Dictionary D = C;

   cout << "\n(D==C)? " << ((D == C) ? "true":"false") << endl << endl;
   cout << "(C == A)? " << ((C == A) ? "true":"false") << endl << endl;

   return EXIT_SUCCESS;
}