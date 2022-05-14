#include <iostream>
#include <stdexcept>
#include <string>

#include "List.h"
#include "BigInteger.h"

#define BASE 100
#define POWER 2
#define DIGITS "0123456789"

/*** CLASS CONSTRUCTORS AND DESTRUCTORS ***/

// Creates the BigInteger ADT in its empty state
BigInteger::BigInteger(){
   signum = 0;
   List digits;
}

BigInteger::BigInteger(std::string s){

   if(s.empty()){
      throw std::invalid_argument("BigInteger: FromString contructor: s is empty");
   }
   signum = 0;

   if (s[0] == '+'){
      signum = 1;
      s.erase(0,1);
   } else if (s[0] == '-'){
      signum = -1;
      s.erase(0,1);
   }
   
   if(s.length() == 1 && s[0] == '0'){
      signum = 0;
      return;
   }

   int s_len = s.length();
   if(s.find_first_not_of(DIGITS,1) != std::string::npos){
      throw std::invalid_argument("BigInteger: FromString contructor: invalid input s");
   }
   
   std::string x = "";
   int count = 0;
   for(int i = s_len - 1; i >= 0; --i){
      if(count == POWER){
         long final = stol(x);
         this->digits.insertAfter(final);
         x="";
         count = 0;
      }
      x.insert(0,1,s[i]);
      count++;
   }
   if(x.empty() == false){
      this->digits.insertAfter(stol(x));
   }

   if(signum == 0){
      signum = 1;
   }
   return;
}

BigInteger::BigInteger(const BigInteger& N){
   signum = N.signum;
   digits = N.digits;
}

/*** ACCESS FUNCTIONS ***/

int BigInteger::sign() const{
   return signum;
}

int BigInteger::compare(const BigInteger& N) const{
   if (signum > N.signum){
      return 1;
   } else if(signum < N.signum){
      return -1;
   }

   int this_length = digits.length();
   int N_length = N.digits.length();
   if(this_length > N_length){
      return 1;
   } else if (this_length < N_length){
      return -1;
   }

   if(digits == N.digits){
      return 0;
   }

   List A = digits;
   List B = N.digits;

   A.moveFront();
   B.moveFront();
   while(A.position() < A.length() && B.position() < B.length()){
      long x = A.moveNext();
      long y = B.moveNext();
      if(x > y){
         return 1;
      }
      if(x < y){
         return -1;
      }
   }
   return 0;
}

/*** MAINPULATION PROCEDURES ***/

void BigInteger::makeZero(){
   signum = 0;
   digits.clear();
}

void BigInteger::negate(){
   if(signum != 0){
      signum *= -1;
   }
}