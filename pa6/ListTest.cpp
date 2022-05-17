/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA5
* ListTest.c 
* Main testing harness for the List ADT
*********************************************************************************/
#include <iostream>
#include <string>
#include <stdexcept>

#include "List.h"
using namespace std;
int main(){
   List A, B;
   for(int i = 1; i <= 10; ++i){
      A.insertBefore(1);
      A.insertAfter(i);
      A.insertAfter(69);

   }
   cout << "A = " << A << endl;
   cout << "A.length(): " << A.length() << endl;
   A.cleanup();
   cout << "AFTER CLEANUP-> A = " << A << "\n" << endl;

   for(int i = 0; i <= 25; ++i){
      B.insertBefore(i);
   }
   cout << "B = " << B << "\n";
   cout << "B.length() = " << B.length() << "\n" << endl;
   B.moveFront();
   A.moveBack();

   cout << "A pos (moveBack) = " << A.position() << ", B pos (moveFront) = " << B.position() << endl;

   cout << "A front: " << A.front() << ", B back:" << B.back() << endl;

   for(int i = 0; i <= 5; ++i){
      A.movePrev();
      B.moveNext();
   }

   cout << "A pos = " << A.position() << ", B pos = " << B.position() << endl;
   A.setAfter(21);
   B.setBefore(420);

   B.moveNext();
   B.eraseAfter();
   A.movePrev();
   A.eraseBefore();

   cout << "A: " << A << endl;
   cout << "B: " << B << endl;

   B.clear();
   for(int i = 0; i <= 15; ++i){
      B.insertAfter(i);
      B.insertBefore(i);
      B.insertBefore(i*2);
   }
   cout << "\nnew B: " << B << endl;

   B.moveFront();
   cout << "Finding 2 in B: " << B.findNext(2) << endl;
   B.moveBack();
   cout << "Finding 3 in B: " << B.findPrev(3) << "\n" << endl;

   B.cleanup();
   cout << "cleaned B:" << B << endl;

   List C = A;
   bool test = (C == A);
   cout << "C == A ? " << test << endl;

   List D = A.concat(B);
   cout << "D: " << D << endl;
   
   return EXIT_SUCCESS;
}