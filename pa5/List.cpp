#include <iostream>
#include <string>
#include <stdexcept>

#include "List.h"

#define FRONT_NIL -9999
#define BACK_NIL -8888

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
   int pos_cursor = 0;
   int num_elements = 0;
}

List::List(const List& L){
   frontDummy = new Node(FRONT_NIL);
   backDummy = new Node(BACK_NIL);
   beforeCursor = frontDummy;
   afterCursor = backDummy;

   for(Node* N = L.frontDummy->next; N != nullptr; N = N->next ){
      this->setBefore(N->data);
   }
}

List::~List(){
   while( num_elements > 0){
      eraseBefore();
   }
   beforeCursor = nullptr;
   afterCursor = nullptr;
   delete frontDummy;
   delete backDummy;
}

/*** ACCESS FUNCTIONS ***/

int List::length() const{
   return num_elements;
}

ListElement List::front() const{
   if (num_elements < 0){
      throw std::length_error("List: front(): empty List\n");
   }
   return frontDummy->next->data;
}

ListElement List::back() const{
   if(num_elements < 0){
      throw std::length_error("List: back(): empty List\n");
   }
   return backDummy->prev->data;
}

int List::position() const{
   return pos_cursor;
}

ListElement List::peekNext() const{
   if(position() > length()){
      throw std::length_error("List: peekNext(): position > length\n");
   }
   return afterCursor->data;
}

ListElement List::peekPrev() const{
   if(position() > length()){
      throw std::length_error("List: peekPrev(): position > length\n");
   }
   return beforeCursor->data;
}

/*** MANIPULATION PROCEDURES ***/

void List::clear(){
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
   if(position() > length()){
      throw std::length_error("List: moveNext(): position > length\n");
   }
   if(afterCursor != backDummy){
      afterCursor = afterCursor->next;
      beforeCursor = beforeCursor->next;
      pos_cursor++;
   }
   return beforeCursor->data;
}

ListElement List::movePrev(){
   if(position() < 0){
      throw std::length_error("List: moveNext(): position < 0\n");
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
      throw std::length_error("List(): setAfter(): Position() > Length()\n");
   }
   if(afterCursor == backDummy){
      throw std::range_error("List(): setAfter(): Error, trying to set element of a non-existing node");
   }
   afterCursor->data = x;
}

void List::setBefore(ListElement x){
   if(position() < 0){
      throw std::length_error("List(): setBefore(): Position() > Length()\n");
   }
   if(beforeCursor == frontDummy){
      throw std::range_error("List(): setAfter(): Error, trying to set element of a non-existing node");
   }
   beforeCursor->data = x;
}

void List::eraseAfter(){
   if( position() > length()){
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
   if(position() < 0){
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
}

List List::concat(const List& L) const{
   List X;
   Node* N = frontDummy->next;
   Node* M = L.frontDummy->next;

   while(N != backDummy){
      X.insertBefore(N->data);
      N=N->next;
   }
   while(M != backDummy){
      X.insertBefore(M->data);
      M=M->next;
   }
   return X;
}

std::string List::to_string() const{
   Node *N = nullptr;
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