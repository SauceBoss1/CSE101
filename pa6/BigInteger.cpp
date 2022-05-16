#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>

#include "List.h"
#include "BigInteger.h"

#define BASE 10
#define POWER 1
#define DIGITS "0123456789"

#define SUB_ABS(a,b) ((a-b) > 0) ? (a-b) : -1*(a-b)

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


   if(s.find_first_not_of(DIGITS,1) != std::string::npos){
      throw std::invalid_argument("BigInteger: FromString contructor: invalid input s");
   }
   

   s.erase(0, s.find_first_not_of('0'));
   int s_len = s.length();


   std::string x = "";
   int count = 0;
   digits.moveFront();
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

   std::cout << "digits: " << digits << std::endl;
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
      if(x > y && signum == 1 && N.signum == 1){
         return 1;
      }
      if(x < y && signum == 1 && N.signum == 1){
         return -1;
      }
      if (signum == -1 && N.signum == -1 && x > y){
         return -1;
      }
      if (signum == -1 && N.signum == -1 && x < y){
         return 1;
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

/*** HELPER FUNCTIONS ***/

void negateList(List &L){
   if(L.length() > 0){
      for(L.moveFront(); L.position() < L.length(); L.moveNext()){
         L.setAfter(L.peekNext() * -1);
      }
   }
}

void sumList(List &S, List A, List B, int sign){
   S.clear();

   if(A.length() == 0 && B.length() != 0){
      S = B;
      return;
   } else if (A.length() != 0 && B.length() == 0){
      S = A;
      return;
   }

   int len_diff = SUB_ABS(A.length(), B.length());

   List big, little;

   if(A.length() < B.length()){
      big = B;
      little = A;
   } else {
      big = A;
      little = B;
   }

   big.moveFront();
   little.moveFront();
   S.moveFront();
   while(big.position() < big.length()){
      if(big.position() < len_diff){
         if(B == big){
            S.insertBefore(sign * big.peekNext());
         }else {
            S.insertBefore(big.peekNext());
         }
         big.moveNext();
      } else {
         if(B == big){
            S.insertBefore(little.peekNext() + (sign * big.peekNext()));
         } else{
            S.insertBefore(big.peekNext() + (sign * little.peekNext()));
         }
         big.moveNext();
         little.moveNext();
      }
   }

   if(S.front() == 0){
      S.moveFront();
      while(S.moveNext() == 0 && S.position() < S.length()){
         S.eraseBefore();
      }
      if( S.length() == 1 && S.front() == 0){
         S.clear();
      }
   }
   return;
}

int normalize(List &L){
   if(L.length() == 0){
      return 0;
   }

   L.moveBack();  

   while(L.position() > 0){
      L.movePrev();
      long ele = L.peekNext();
      if(ele >= BASE){
         long multiple = floor(ele / BASE);
         L.setAfter(ele % (multiple * BASE));
         if(L.position() == 0){
            L.insertBefore(multiple);
            return 1;
         } else {
            long prev_ele = L.peekPrev();
            L.setBefore(prev_ele + multiple);
         }
      } else if(ele < 0){
         long multiple = (-1 * floor(ele / BASE)) == 0 ? 1 : (-1 * (ele / BASE));
         if(L.front() == ele){
            negateList(L);
            normalize(L);
            return -1;
         }
         L.setAfter( (multiple * BASE) % ele);
         if(L.position() == 0){
            L.insertBefore(multiple);
            return -1;
         } else {
            long prev_ele = L.peekPrev();
            L.setBefore(prev_ele - multiple);
         }
      }
   }
   return 1;
}

void shiftList(List &L, int p){
   int ele_nums = p;

   L.moveBack();
   for(int i = 0; i < ele_nums; ++i){
      L.insertBefore(0);
   }
   L.moveFront();
   return;
}

void scalarMultiList(List &L, ListElement m){
   if(m == 1){
      return;
   }
   if(m == 0){
      L.clear();
      return;
   }
   L.moveFront();
   while (L.position() < L.length()){
      L.setBefore(L.moveNext() * m);
   }
   return;
}

BigInteger BigInteger::add(const BigInteger& N) const{
   List right_op = N.digits;
   List left_op = digits;

   /**
    * TODO: fix the case of -A + B = B - A
    */

   List ans;

   if(signum == -1 && N.signum == 1){
      BigInteger y = N.add(*this);
      return y;
   }

   sumList(ans, left_op, right_op, N.signum);
   int final_sign = normalize(ans);


   BigInteger x;

   x.signum = final_sign;
   x.digits = ans;


   std::cout << ans << std::endl;
   return x;
}

BigInteger BigInteger::sub(const BigInteger &N) const{
   /**
    * things to watch out for:
    *    A-B <-good!
    *    -A - -B <- fixed!
    *    -A -B <-good!
    *     A -- B <- good!
    *     A-B when A<B <-works!
    */
   List left_op = digits;
   List right_op = N.digits;

   int comparison = this->compare(N); //this = left op, N = right op
   //-1 -> this < N
   //1 -> this > N
   //0 -> this == N
   BigInteger x;

   //this = A
   //N = B
   if( comparison == -1){
      x = N.sub(*this);
      x.signum = -1;
      return x;
   }
   if(N.signum == -1 && signum == -1){
      BigInteger y = N; //B
      BigInteger z = *this;
      y.signum = 1;
      z.signum = 1;
      x = y.sub(z);
      return x;
   }
   List ans;

   sumList(ans, left_op, right_op, -1*N.signum);
   int final_sign = normalize(ans);

   x.signum = final_sign;
   x.digits = ans;

   std::cout << ans << std::endl;
   return x;

}

BigInteger BigInteger::mult(const BigInteger &N) const{
   List left_op = this->digits;
   List right_op = N.digits;
   List ans;
   List prev_answer;

   int shift = 0;
   for(right_op.moveBack(); right_op.position() > 0; right_op.movePrev()){
      List temp_vector = left_op;
      shiftList(temp_vector, shift);
      scalarMultiList(temp_vector, right_op.peekPrev());
      sumList(ans, temp_vector, prev_answer,1);
      normalize(ans);
      prev_answer = ans;
      shift++;
   }

   BigInteger x;
   if (signum == -1 || N.signum == -1){
      x.signum = -1;
   } else {
      x.signum = 1;
   }

   x.digits = ans;
   std::cout << "Mult: " << ans << std::endl;
   return x;
}
