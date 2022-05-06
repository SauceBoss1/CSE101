#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>

#include "List.h"

#define FRONT_NIL -2147483647 - 1
#define BACK_NIL 2147483647

/*** PRIVATE CONSTRUCTOR(S) ***/

//Node Constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}

/*** CLASS CONTRUCTORS AND DESTRUCTORS ***/

// Creates a new List in the empty state
List::List(){
   frontDummy = new Node(FRONT_NIL);
   backDummy = new Node(BACK_NIL);
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;
}

List::List(const List& L){
   frontDummy = new Node(FRONT_NIL);
   backDummy = new Node(BACK_NIL);
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;
   moveFront();
   for(Node* N = L.frontDummy->next; N->data != backDummy->data; N = N->next ){
      this->insertBefore(N->data);
   }
}

List::~List(){
   moveBack();
   while( num_elements > 0){
      eraseBefore();
   }
   beforeCursor = nullptr;
   afterCursor = nullptr;
   frontDummy->next = nullptr;
   backDummy->prev = nullptr;
   delete frontDummy;
   delete backDummy;
}

/*** ACCESS FUNCTIONS ***/

int List::length() const{
   return num_elements;
}

ListElement List::front() const{
   if (num_elements <= 0){
      throw std::length_error("List: front(): empty List");
   }
   return frontDummy->next->data;
}

ListElement List::back() const{
   if(num_elements <= 0){
      throw std::length_error("List: back(): empty List");
   }
   return backDummy->prev->data;
}

int List::position() const{
   return pos_cursor;
}

ListElement List::peekNext() const{
   if(position() > length()){
      throw std::range_error("List: peekNext(): position > length");
   }
   return afterCursor->data;
}

ListElement List::peekPrev() const{
   if(position() <= 0){
      throw std::range_error("List: peekPrev(): position < 0");
   }
   return beforeCursor->data;
}

/*** MANIPULATION PROCEDURES ***/

void List::clear(){
   if(length() == 0){
      throw std::length_error("List: clear(): length == 0");
   }
   while( length() > 0){
      eraseBefore();
   }
   num_elements = 0;
   pos_cursor = 0;
   return;
}

void List::moveFront(){
   beforeCursor = frontDummy;
   afterCursor = frontDummy->next;
   pos_cursor = 0;
   return;
}

void List::moveBack(){
   afterCursor = backDummy;
   beforeCursor = backDummy->prev;
   pos_cursor = length();
}

ListElement List::moveNext(){
   if(position() >= length()){
      throw std::range_error("List: moveNext(): position > length");
   }
   if(afterCursor != backDummy){
      afterCursor = afterCursor->next;
      beforeCursor = beforeCursor->next;
      pos_cursor++;
   }
   return beforeCursor->data;
}

ListElement List::movePrev(){
   if(position() <= 0){
      throw std::range_error("List: moveNext(): position < 0");
   }
   if(beforeCursor != frontDummy){ //may want to change this
      afterCursor = afterCursor->prev;
      beforeCursor = beforeCursor->prev;
      pos_cursor--;
   }
   return afterCursor->data;
}

void List::insertAfter(ListElement x){
   Node* N = new Node(x);
   if(length() == 0 ){
      frontDummy->next = N;
      backDummy->prev = N;
      N->next = backDummy;
      N->prev = frontDummy;
      afterCursor = N;
      num_elements++;
   } else {
      N->next = afterCursor;
      N->prev = beforeCursor;
      afterCursor->prev = N;
      beforeCursor->next = N;
      afterCursor = N;
      num_elements++;
   }
}

void List::insertBefore(ListElement x){
   Node* N = new Node(x);
   if(length() == 0){
      N->prev = frontDummy;
      N->next = backDummy;
      frontDummy->next = N;
      backDummy->prev = N;
      beforeCursor = N;
      num_elements++;
      pos_cursor++;
   } else {
      N->next = afterCursor;
      N->prev = beforeCursor;
      beforeCursor->next = N;
      afterCursor->prev = N;
      beforeCursor = N;
      num_elements++;
      pos_cursor++;
   }
}

void List::setAfter(ListElement x){
   if(position() > length()){
      throw std::length_error("List(): setAfter(): Position() > Length()");
   }
   if(afterCursor == backDummy){
      throw std::range_error("List(): setAfter(): Error, trying to set element of a non-existing node");
   }
   afterCursor->data = x;
}

void List::setBefore(ListElement x){
   if(position() < 0){
      throw std::length_error("List(): setBefore(): Position() < 0");
   }
   if(beforeCursor == frontDummy){
      throw std::range_error("List(): setBefore(): Error, trying to set element of a non-existing node");
   }
   beforeCursor->data = x;
}

void List::eraseAfter(){
   if( position() >= length()){
      throw std::range_error("List(): eraseAfter(): position > length");
   }
   if(length() == 1 && afterCursor != backDummy){
      Node* N = afterCursor;
      N->next = nullptr;
      N->prev = nullptr;
      frontDummy->next = backDummy;
      backDummy->prev = frontDummy;
      afterCursor = backDummy;
      num_elements--;
      delete N;
   } else if(afterCursor != backDummy){
      Node* N = afterCursor;
      beforeCursor->next = N->next;
      afterCursor->next->prev = beforeCursor;
      afterCursor = N->next;
      N->next = nullptr;
      N->prev = nullptr;
      num_elements--;
      delete N;
   }
}

void List::eraseBefore(){
   if(position() <= 0){
      throw std::range_error("List(): eraseAfter(): position < 0");
   }
   if(length() == 1 && beforeCursor != frontDummy){
      Node* N = beforeCursor;
      N->next = nullptr;
      N->prev = nullptr;
      frontDummy->next = backDummy;
      backDummy->prev = frontDummy;
      beforeCursor = frontDummy;
      num_elements--;
      pos_cursor--;
      delete N;
   } else if(beforeCursor != frontDummy){
      Node *N = beforeCursor;
      beforeCursor->prev->next = afterCursor;
      afterCursor->prev = N->prev;
      beforeCursor = N->prev;
      N->next = nullptr;
      N->prev = nullptr;
      num_elements--;
      pos_cursor--;
      delete N;
   }
}

/*** OTHER FUNCTIONS ***/

int List::findNext(ListElement x){
   while (position() < length()){
      if(afterCursor->data == x){
         moveNext();
         return position();
      } else if(afterCursor == backDummy) {
         return -1;
      } else {
         moveNext();
      }
   }
   return -1;
}

int List::findPrev(ListElement x){
   while(position() > 0){
      if(beforeCursor->data == x){
         movePrev();
         return position();
      } else if (beforeCursor == frontDummy){
         return -1;
      } else{
         movePrev();
      }
   }
   return -1;
}

//TODO: CLEANUP
void List::cleanup(){
   //std::cout <<"Pos: " << this->pos_cursor << std::endl;
   for(Node *N = frontDummy->next; N != backDummy; N=N->next){
      //std::cout << "this = " << this->to_string() << std::endl;
      for(Node* M = N->next; M != backDummy; M=M->next){
         //std::cout << "M: " << M->data << std::endl;
         if(M->data == N->data && beforeCursor == M){
            Node* X = M;
            beforeCursor = M->prev;
            M->prev->next = M->next;
            M->next->prev = M->prev;
            pos_cursor--;
            num_elements--;
            if(M->next == backDummy){
               delete X;
               break;
            }
            std::cout <<"Pos: " << this->pos_cursor << std::endl;
            delete X;
         } else if (M->data == N->data && afterCursor == M){
            Node* X = M;
            afterCursor = M->next;
            M->prev->next = M->next;
            M->next->prev = M->prev;
            num_elements--;
            if(M->next == backDummy){
               delete X;
               break;
            }
            delete X;
         }else if(M->data == N->data && M->next == backDummy){
            Node* X = M;
            M->prev->next = M->next;
            M->next->prev = M->prev;
            num_elements--;
            delete X;
            break;
         } else if(M->data == N->data){
            Node* X = M;
            M->prev->next = M->next;
            M->next->prev = M->prev;
            num_elements--;
            delete X;
         }
      }
   }
}

List List::concat(const List& L) const{
   List X;
   Node* N = frontDummy->next;
   Node* M = L.frontDummy->next;

   while(N != backDummy){
      X.insertBefore(N->data);
      N=N->next;
   }
   while(M != L.backDummy){
      X.insertBefore(M->data);
      M=M->next;
   }
   X.moveFront();
   return X;
}

std::string List::to_string() const{
   Node *N = nullptr;
   if(length() > 0){
      std::string s = "(";
      for(N = frontDummy->next; N != backDummy; N=N->next){
         if(N->next == backDummy){
            s += std::to_string(N->data)+") ";
         } else{
            s += std::to_string(N->data)+", ";
         }
      }
      return s;
   }

   return "";
}

bool List::equals(const List& R) const{
   bool eq = false;
   Node* N = nullptr;
   Node* M = nullptr;

   eq = ( length() == R.length());
   N = frontDummy->next;
   M = R.frontDummy->next;
   while(eq && N!= nullptr){
      eq = (N->data == M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}

/*** OVERRIDES ***/

std::ostream& operator<<( std::ostream& stream, const List& L ){
   return stream<< L.List::to_string();
}

bool operator==( const List& A, const List& B ){
   return A.List::equals(B);
}

List& List::operator=(const List& L){
   if(this != &L){
      List temp = L;
      std::swap(num_elements, temp.num_elements);
      std::swap(pos_cursor, temp.pos_cursor);
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(afterCursor, temp.afterCursor);
      std::swap(beforeCursor, temp.beforeCursor);
   }

   return *this;
}