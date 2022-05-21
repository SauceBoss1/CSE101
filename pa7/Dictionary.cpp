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

Dictionary::Dictionary(const Dictionary &D){
   nil = new Node("", NIL_VAL);
   root = nullptr;
   current = nullptr;
   num_pairs = 0;
   preOrderCopy(D.root, nullptr);
}

Dictionary::~Dictionary(){
   postOrderDelete(root);
   nil->left = nullptr;
   nil->right = nullptr;
   nil->parent = nullptr;
   root = nullptr;
   current = nullptr;
   delete nil;

}
/*** HELPER FUNCTIONS ***/

void Dictionary::postOrderDelete(Node *R){
   if( R != nil ){
      postOrderDelete(R->left);
      postOrderDelete(R->right);
      R->parent = nullptr;
      R->left = nullptr;
      R->left = nullptr;
      delete R;
   }
}