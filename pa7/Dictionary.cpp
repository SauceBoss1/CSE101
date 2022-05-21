#include <iostream>
#include <string>

#include "Dictionary.h"

#define NIL_VAL 2147483647

/*** PRIVATE CONSTRUCTORS ***/

//Node Constructor
Dictionary::Node::Node(keyType k, valType v){
   key = k;
   val = v;
   parent = nullptr;
   left = nullptr;
   right = nullptr;
}

/*** CLASS CONSTRUCTORS AND DESTRUCTORS ***/

Dictionary::Dictionary(){
   nil = new Node("",NIL_VAL);
   root = nullptr;
   current = nullptr;
   num_pairs = 0;
}