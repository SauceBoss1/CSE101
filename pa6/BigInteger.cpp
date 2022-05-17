/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA6
* BigInteger.cpp 
* Source file that contains the implmentations for the Big Integer ADT
*********************************************************************************/
#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>

#include "List.h"
#include "BigInteger.h"

#define BASE 1000000000 //used as the base during calculations
#define POWER 9 //used to divide up the digits into one list element
#define DIGITS "0123456789"

#define SUB_ABS(a,b) ((a-b) > 0) ? (a-b) : -1*(a-b)

/*** CLASS CONSTRUCTORS AND DESTRUCTORS ***/

// Creates the BigInteger ADT in its empty state
BigInteger::BigInteger(){
   signum = 0;
   List digits;
}

//Parses a string into the list where each element is POWER digits long
BigInteger::BigInteger(std::string s){

   if(s.empty()){
      throw std::invalid_argument("BigInteger: Constructor: empty string");
   }
   signum = 0;

   //check if there are signs
   if (s[0] == '+'){
      signum = 1;
      s.erase(0,1);
   } else if (s[0] == '-'){
      signum = -1;
      s.erase(0,1);
   }
   
   //the case where we only have a 0
   if(s.length() == 1 && s[0] == '0'){
      signum = 0;
      return;
   }

   if(s.length() == 0){
      throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
   }
   if(s.find_first_not_of(DIGITS,1) != std::string::npos){
      throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
   }
   

   //get rid of all leading zeros
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

   //flush out remaining digits
   if(x.empty() == false){
      this->digits.insertAfter(stol(x));
   }
   
   if(signum == 0){
      signum = 1;
   }

   //std::cout << "digits: " << digits << std::endl;
   return;
}

//copy contructor
BigInteger::BigInteger(const BigInteger& N){
   signum = N.signum;
   digits = N.digits;
}

/*** ACCESS FUNCTIONS ***/

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
   return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
   //case 1: checking the signs
   if (signum > N.signum){
      return 1;
   } else if(signum < N.signum){
      return -1;
   }

   //case 2: checking the lengths
   int this_length = digits.length();
   int N_length = N.digits.length();
   if(this_length > N_length){
      return 1;
   } else if (this_length < N_length){
      return -1;
   }

   //case 3: if they are the same list
   if(digits == N.digits){
      return 0;
   }

   List A = digits;
   List B = N.digits;

   //case 4: if the list lengths are the same but the digits are not
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

      //when dealing the 2 negative lists, the list with the smaller digits is greater
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

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
   signum = 0;
   digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
   if(signum != 0){
      signum *= -1;
   }
}

/*** HELPER FUNCTIONS ***/

/**
 * negateList()
 * flips the sign of all elementes in the list
 */
void negateList(List &L){
   if(L.length() > 0){
      for(L.moveFront(); L.position() < L.length(); L.moveNext()){
         L.setAfter(L.peekNext() * -1);
      }
   }
}

/**
 * sumList()
 * adds two list together with the following formula:
 * A + sign*B
 */
void sumList(List &S, List A, List B, int sign){
   S.clear();

   //if one list is 0, then you only need to return the other lists
   if(A.length() == 0 && B.length() != 0){
      S = B;
      return;
   } else if (A.length() != 0 && B.length() == 0){
      S = A;
      return;
   }

   //combine the lists
   A.moveBack();
   B.moveBack();
   S.moveBack();
   while(A.position() != 0 && B.position() != 0){
      S.insertAfter(A.peekPrev() + (sign * B.peekPrev()));
      B.movePrev();
      A.movePrev();
   }
   
   //we need to see if there still elements left in either A or B
   if(A.position() != 0){
      while(A.position() != 0){
         S.insertAfter(A.peekPrev());
         A.movePrev();
      }
   }

   if(B.position() != 0){
      while(B.position() != 0){
         S.insertAfter(sign * B.peekPrev());
         B.movePrev();
      }
   }

   //gets rid of any leading zeros
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

/**
 * normalize()
 * deals with the carrying function in arithmetic operations
 */
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
         L.setAfter(ele - (multiple * BASE));

         if(L.position() == 0){
            L.insertBefore(multiple);
            return 1;
         } else {
            long prev_ele = L.peekPrev();
            L.setBefore(prev_ele + multiple);
         }
      } else if(ele < 0){

         //we cant have a multiple of 0
         //multiples can only be as small as 1
         long multiple = (-1 * floor(ele / BASE)) == 0 ? 1 : (-1 * (ele / BASE)); 
         
         //if the front element is negative, then negate and recurse
         if(L.front() == ele){
            negateList(L);
            normalize(L);
            return -1;
         }

         L.setAfter( ele + (multiple * BASE));
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

/**
 * shiftList()
 * appends p 0s to the list
 */
void shiftList(List &L, int p){
   int ele_nums = p;

   L.moveBack();
   for(int i = 0; i < ele_nums; ++i){
      L.insertBefore(0);
   }
   L.moveFront();
   return;
}

/**
 * scalarMultiList()
 * multiples a List by m
 */
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

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
   List right_op = N.digits;
   List left_op = digits;

   /**
    * Cases to check:
    * 1) -A + -B
    * 2) A + -B
    * 3) -A + B
    */
   List ans;
   BigInteger x;


   if(signum == -1 && N.signum == 1){
      BigInteger y = N.add(*this);
      return y;
   }
   
   if(signum == -1 && N.signum == -1){
      BigInteger left = *this;
      BigInteger right = N;
      left.signum = 1;
      right.signum = 1;
      x = left.add(right);
      x.signum = -1;
      return x;
   }

   sumList(ans, left_op, right_op, N.signum);
   int final_sign = normalize(ans);

   if(ans.length() == 0){
      final_sign = 0;
   }
   x.signum = final_sign;
   x.digits = ans;

   return x;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
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

   return x;

}

// mult()
// Returns a BigInteger representing the product of this and N.
BigInteger BigInteger::mult(const BigInteger &N) const{
   List left_op = this->digits;
   List right_op = N.digits;

   /**
    * Cases to look for:
    * 1) -A * B
    * 2) A * -B
    * 3) -A * -B
    */

   List ans;
   List prev_answer;
   BigInteger x;
   if(signum == 0 || N.signum == 0){
      x.signum = 0;
      return x;
   }

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

   if ((signum == -1 && N.signum == -1)){
      x.signum = 1;
   }else if (signum == -1 || N.signum == -1){
      x.signum = -1;
   } else {
      x.signum = 1;
   }

   x.digits = ans;
   return x;
}

/*** OTHER FUNCTIONS ***/

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
   std::string final_output = "";
   if(digits.length() > 0){
      if(signum == -1){
         final_output += "-";
      }
      for(digits.moveFront(); digits.position() < digits.length(); digits.moveNext()){
         std::string quick_convert = std::to_string(digits.peekNext());
         if(digits.position() == 0){
            final_output += quick_convert;
         
         //add leading zeros if the element is less than POWER digits
         } else if (quick_convert.length() < POWER){
            int num_of_chars = POWER - quick_convert.length();
            quick_convert.insert(0,num_of_chars,'0');

            final_output += quick_convert;
         } else {
            final_output += quick_convert;
         }
      }
      return final_output;
   }
   return "0";
}

/*** OVERRIDEN OPERATORS ***/

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<(std::ostream& stream, BigInteger N){
   return stream<< N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==(const BigInteger &A, const BigInteger &B){
   return (A.compare(B) == 0) ? true : false;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<(const BigInteger &A, const BigInteger &B){
   return (A.compare(B) == -1) ? true : false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B.
bool operator<=(const BigInteger &A, const BigInteger &B){
   int comparison = A.compare(B);
   return (comparison == -1 || comparison == 0) ? true : false;
}

// operator>()
// Returns true if and only if A is greater than B.
bool operator>(const BigInteger &A, const BigInteger &B){
   return (A.compare(B) == 1) ? true : false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B.
bool operator>=(const BigInteger &A, const BigInteger &B){
   int comparison = A.compare(B);
   return (comparison == 1 || comparison == 0) ? true : false;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+(const BigInteger &A, const BigInteger &B){
   return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B.
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
   A = A.add(B);
   return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-(const BigInteger &A, const BigInteger &B){
   return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B.
BigInteger operator-=(BigInteger &A, const BigInteger &B){
   A = A.sub(B);
   return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*(const BigInteger &A, const BigInteger &B){
   return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=(BigInteger &A, const BigInteger &B){
   A = A.mult(B);
   return A;
}