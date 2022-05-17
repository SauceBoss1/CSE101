/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA6
* Shuffle.c 
* Source file that contains the implmentations for the List ADT (NOTE: ListElement is long now)
*********************************************************************************/
#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>

#include "List.h"

#define FRONT_NIL -2147483647 - 1 //smallest integer
#define BACK_NIL 2147483647 //biggest integer

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

/**
 * Copy constructor
 */
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

/**
 * List Destructor
 */
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

/**
 * length()
 * Returns the length of the list
 */
int List::length() const{
   return num_elements;
}

/**
 * front()
 * returns the front element of the list
 * 
 * pre: length() > 0
 */
ListElement List::front() const{
   if (num_elements <= 0){
      throw std::length_error("List: front(): empty List");
   }
   return frontDummy->next->data;
}

/**
 * back()
 * returns the back element of the list 
 * 
 * pre: length() > 0
 */
ListElement List::back() const{
   if(num_elements <= 0){
      throw std::length_error("List: back(): empty List");
   }
   return backDummy->prev->data;
}

/**
 * position()
 * returns the position of the cursor on the list
 * 
 * NOTE: Cursor can never be undefined
 */
int List::position() const{
   return pos_cursor;
}

/**
 * peekNext()
 * returns the element after the cursor
 * 
 * pre: position < length
 */
ListElement List::peekNext() const{
   if(position() > length()){
      throw std::range_error("List: peekNext(): position > length");
   }
   return afterCursor->data;
}

/**
 * peekPrev()
 * Returns the element before the cursor
 * 
 * pre: position > 0
 */
ListElement List::peekPrev() const{
   if(position() <= 0){
      throw std::range_error("List: peekPrev(): position < 0");
   }
   return beforeCursor->data;
}

/*** MANIPULATION PROCEDURES ***/

/**
 * clear()
 * Deletes all elements in the list.
 * Sets the list back to the empty state
 */
void List::clear(){
   moveBack(); //remember to set the cursor to the back
               //if this is not here, then list will be
               //partially cleared
   while( length() > 0){
      eraseBefore();
   }
   num_elements = 0;
   pos_cursor = 0;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   return;
}

/**
 * moveFront()
 * Moves cursor to position 0
 */
void List::moveFront(){
   beforeCursor = frontDummy;
   afterCursor = frontDummy->next;
   pos_cursor = 0;
   return;
}

/**
 * moveBack()
 * moves cursor to position length()
 */
void List::moveBack(){
   afterCursor = backDummy;
   beforeCursor = backDummy->prev;
   pos_cursor = length();
}

/**
 * moveNext()
 * moves cursor to the next position, returns element that as passed over.
 * 
 * pre: position<length
 */
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

/**
 * movePrev()
 * moves cursor to the previus position, returns element that was passed over
 * 
 * pre: position > 0
 */
ListElement List::movePrev(){
   if(position() <= 0){
      throw std::range_error("List: moveNext(): position < 0");
   }
   if(beforeCursor != frontDummy){
      afterCursor = afterCursor->prev;
      beforeCursor = beforeCursor->prev;
      pos_cursor--;
   }
   return afterCursor->data;
}

/**
 * insertAfter()
 * inserts element after the cursor
 */
void List::insertAfter(ListElement x){
   Node* N = new Node(x);
   if(length() == 0 ){ //stitch initial element to front and back
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

/**
 * insertBefore()
 * inserts element before the cursor
 */
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

/**
 * setAfter()
 * Overwrites the list element after the cursor with x
 * 
 * pre: position < length
 */
void List::setAfter(ListElement x){
   if(position() > length()){
      throw std::length_error("List(): setAfter(): Position() > Length()");
   }
   if(afterCursor == backDummy){
      throw std::range_error("List(): setAfter(): Error, trying to set element of a non-existing node");
   }
   afterCursor->data = x;
}
/**
 * setBefore()
 * Overwrites the list element before the cursor with x
 * 
 * pre: position > 0
 */
void List::setBefore(ListElement x){
   if(position() < 0){
      throw std::length_error("List(): setBefore(): Position() < 0");
   }
   if(beforeCursor == frontDummy){
      throw std::range_error("List(): setBefore(): Error, trying to set element of a non-existing node");
   }
   beforeCursor->data = x;
}

/**
 * eraseAfter()
 * Deletes element after cursor
 * 
 * pre: position < length
 */
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

/**
 * eraseBefore()
 * Deletes element before cursor
 * 
 * pre: postion > 0
 */
void List::eraseBefore(){
   if(position() <= 0){
      throw std::range_error("List(): eraseBefore(): position < 0");
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

/**
 * findNext()
 * Starting from the current cursor position and then moving next,
 * this finds the first occurance of element x
 * 
 * returns -1 if not found
 */
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

/**
 * findPrev()
 * Starting from the current cursto position and them moving previous,
 * this find the first occurance of element x
 * 
 * return -1 if not found
 */
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

/**
 * cleanup()
 * Removes any repeated elements from list
 * leaving only unique elements,
 * 
 * This function will also leave the cursor in the same position
 */
void List::cleanup(){
   int pseudo_pos = 0;
   for(Node* N = frontDummy->next; N != backDummy; N=N->next){
      Node* M = N->next;
      int pseudo_pos_inner = pseudo_pos;
      while(M != backDummy){
         if(M->data == N->data){
            if(M==beforeCursor){ //case if the repeated element is at the cursor
               M=M->next;
               eraseBefore();
            } else if(M==afterCursor){
               M=M->next;
               eraseAfter();
            } else {
               Node* prev_M = M;
               M = M->next;
               prev_M->prev->next = prev_M->next;
               prev_M->next->prev = prev_M->prev;
               prev_M->next = nullptr;
               prev_M->prev = nullptr;
               delete prev_M;
               num_elements--;
               if(pseudo_pos_inner < position()){
                  pos_cursor--;
               }
            }
         } else {
            M = M->next;
         }
         
         pseudo_pos_inner++;
      }
      pseudo_pos++;
   }
}

/**
 * concat()
 * Returns a new list consisting of the leemnts of this list and List L.
 * 
 * NOTE: Cursor will be set to 0
 */
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

/**
 * to_string()
 * Returns a string representation of this list
 */
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

   return ""; //string should be empty if the list is empty
}

/**
 * equals()
 * Checks if this List and R is equal
 */
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

/**
 * operator<<()
 * Inserts the string representation of L into a stream
 */
std::ostream& operator<<( std::ostream& stream, const List& L ){
   return stream<< L.List::to_string();
}

/**
 * operator==()
 * Returns true iff A is the same int sequence as B
 * Cursor in both lists will be unchanged
 */
bool operator==( const List& A, const List& B ){
   return A.List::equals(B);
}

/**
 * operator=()
 * Overwrites this list with state of L
 */
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