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