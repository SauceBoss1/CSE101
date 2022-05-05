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
      return beforeCursor->data;
   }
   return beforeCursor->data;
}

ListElement List::movePrev(){
   if(position() < 0){
      throw std::length_error("List: moveNext(): position < 0\n");
   }
   if(beforeCursor != frontDummy){
      afterCursor = afterCursor->prev;
      beforeCursor = beforeCursor->prev;
      pos_cursor--;
      return afterCursor->data;
   }
   return afterCursor->data;
}


