/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA7
* Dictionary.cpp 
* Source file that contains the implementation of the Dictionary ADT
*********************************************************************************/
#include <iostream>
#include <string>

#include "Dictionary.h"

#define NIL_VAL 2147483647 //used for the nil node

#define BLACK -1
#define RED -2

/*** PRIVATE CONSTRUCTORS ***/

//Node Constructor
Dictionary::Node::Node(keyType k, valType v){
   key = k;
   val = v;
   parent = nullptr;
   left = nullptr;
   right = nullptr;
   color = BLACK;
}

/*** CLASS CONSTRUCTORS AND DESTRUCTORS ***/

//public dictionary constructor
Dictionary::Dictionary(){
   nil = new Node("\0\0",NIL_VAL);
   nil->parent = nullptr;
   nil->left = nullptr;
   nil->right = nullptr;
   root = nil;
   current = nil;
   num_pairs = 0;
}

//public dictionary copy constructor
Dictionary::Dictionary(const Dictionary &D){
   nil = new Node("\0\0", NIL_VAL);
   nil->parent = nullptr;
   nil->left = nullptr;
   nil->right = nullptr;
   root = nil;
   current = nil;
   num_pairs = 0;
   preOrderCopy(D.root, nil);
}

//public dictionary destructor
Dictionary::~Dictionary(){
   postOrderDelete(root);
   nil->left = nullptr;
   nil->right = nullptr;
   nil->parent = nullptr;
   root = nil;
   current = nil;
   delete nil;
}
/*** HELPER FUNCTIONS ***/

/******************************************************
 * inOrderString()
 * prints out the string representation of the 
 * BST in an in-order walk
 ******************************************************/
void Dictionary::inOrderString(std::string &s, Node* R) const{
   if( R != nil ){
      inOrderString(s, R->left);
      s += R->key + " : " + std::to_string(R->val) + "\n";
      inOrderString(s,R->right);
   }
}

/******************************************************
 * preOrderString()
 * prints out the string representation of the
 * BST in an pre-order walk
 ******************************************************/
void Dictionary::preOrderString(std::string &s, Node *R) const{
   if( R != nil){
      s += R->key +"\n";
      preOrderString(s, R->left);
      preOrderString(s, R->right);
   }
}

/******************************************************
 * preOrderCopy()
 * copys the BST from Node R to Node N recursively
 * to this Dictionary using a pre-order tree walk
 ******************************************************/
void Dictionary::preOrderCopy(Node *R, Node *N){
   if(R != nil && R->key != N->key){
      setValue(R->key, R->val);
      preOrderCopy(R->left, N);
      preOrderCopy(R->right, N);
   }
}

/******************************************************
 * postOrderDelete()
 * deletes the BST using a post-order walk
 ******************************************************/
void Dictionary::postOrderDelete(Node *R){
   if( R != nil && num_pairs > 0){
      postOrderDelete(R->left);
      postOrderDelete(R->right);
      R->left = nil;
      R->right = nil;
      delete R;
      num_pairs--;
   }
}

/******************************************************
 * search()
 * searches the BST to tree to see where key k is
 * if k is not in the tree then it returns nil
 ******************************************************/
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
   if(R == nil || R->key == k){
      return R;
   } else if(k < R->key){
      return search(R->left, k);
   } else {
      return search(R->right, k);
   }
}

/******************************************************
 * findMin()
 * finds the minimum of the BST
 * returns the minimum node else it returns nil
 * if the tree is empty
 ******************************************************/
Dictionary::Node* Dictionary::findMin(Node *R){
   if(num_pairs <=0){
      return nil;
   }
   Node* x = R;
   while(x->left != nil){
      x = x->left;
   }
   return x;
}

/******************************************************
 * findMax()
 * finds the maximum node of the BST
 * returns the maximum node else it returns nil
 * if the tree is empty
 ******************************************************/
Dictionary::Node* Dictionary::findMax(Node *R){
   if(num_pairs <=0){
      return nil;
   }
   Node* x = R;
   while(x->right != nil){
      x = x->right;
   }
   return x;
}

/******************************************************
 * findNext()
 * finds the successor from the subtree of Node N
 * and returns its corresponding node
 ******************************************************/
Dictionary::Node* Dictionary::findNext(Node *N){
   if(N->right != nil){ //case 1
      return findMin(N->right);
   }
   Node *x = N; //case 2
   Node *y = N->parent;
   while(y != nil && x == y->right){
      x = y;
      y = y->parent;
   }
   return y;
}

/******************************************************
 * findPrev()
 * finds the predecessor from the subtree of Node N
 * and returns its corresponding node
 ******************************************************/
Dictionary::Node* Dictionary::findPrev(Node *N){
   if(N->left != nil){
      return findMax(N->left);
   }
   Node *x = N;
   Node *y = N->parent;
   while(y != nil && x == y->left){
      x = y;
      y = y->parent;
   }
   return y;
}

/*** RB HELPER FUNCTIONS ***/

void Dictionary::LeftRotate(Node *N){
   Node *x = N;

   //set y
   Node *y = x->right;

   //turn y's left subtree into x's right subtree
   x->right = y->left;
   if(y->left != nil){ // not necessary if using sentinal nil node
      y->left->parent = x;
   }

   // link y's parent to x
   y->parent = x->parent;
   if(x->parent == nil){
      root = y;
   } else if(x == x->parent->left){
      x->parent->left = y;
   } else {
      x->parent->right = y;
   }

   // put x on y's left
   y->left = x;
   x->parent = y;
}

void Dictionary::RightRotate(Node *N){
   Node *x = N;

   //set y
   Node *y = x->left;

   //turn y's subtree into x's left subtree
   x->left = y->right;
   if(y->right != nil){ // not necessary if using sentinal nil node
      y->right->parent = x;
   }

   //link y's parent to x
   y->parent = x->parent;
   if(x->parent == nil){
      root = y;
   } else if(x == x->parent->right){
      x->parent->right = y;
   } else {
      x->parent->left = y;
   }

   // put x on y's right
   y->right = x;
   x->parent = y;
}

void Dictionary::RB_InsertFixUp(Node* N){
   Node *z = N;
   while(z->parent->color == RED){
      if(z->parent == z->parent->parent->left){
         Node *y = z->parent->parent->right;
         if(y->color == RED){
            z->parent->color = BLACK; // case 1
            y->color = BLACK; // case 1
            z->parent->parent->color = RED; //case 1
            z = z->parent->parent; //case 1
         } else {
            if (z == z->parent->right){ //case 2
               z = z->parent; //case 2
               LeftRotate(z); //case 2
            }
            z->parent->color = BLACK; //case 3
            z->parent->parent->color = RED; //case 3
            RightRotate(z->right->parent);
         }
      } else {
         Node *y = z->parent->parent->left;
         if(y->color == RED){
            z->parent->color = BLACK; // case 4
            y->color = BLACK; // case 4
            z->parent->parent->color = RED; // case 4
            z = z->parent->parent; //case 4
         } else {
            if(z == z->parent->left){
               z = z->parent; // case 5
               RightRotate(z); // case 5
            }
            z->parent->color = BLACK; //case 6
            z->parent->parent->color = RED; //case 6
            LeftRotate(z->parent->parent); //case 6
         }
      }
   }
   root->color = BLACK;
}

void Dictionary::RB_Transplant(Node *u, Node *v){
   if(u->parent == nil){
      root = v;
   } else if(u == u->parent->left){
      u->parent->left = v;
   } else {
      u->parent->right = v;
   }
   v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node *n){
   Node *x = n;
   while(x != root && x->color == BLACK){
      if(x == x->parent->left){
         Node *w = x->parent->right;
         if(w->color == RED){
            w->color = BLACK;
            x->parent->color = RED;
            LeftRotate(x->parent);
            w = x->parent->right;
         }
         if(w->left->color == BLACK && w->right->color == BLACK){
            w->color = RED;
            x = x->parent;
         } else {
            if(w->right->color == BLACK){
               w->left->color = BLACK;
               w->color = RED;
               RightRotate(w);
               w = x->parent->right;
            }
            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->right->color = BLACK;
            LeftRotate(x->parent);
            x = root;
         }
      } else {
         Node *w = x->parent->left;
         if(w->color == RED){
            w->color = BLACK;
            x->parent->color = RED;
            RightRotate(x->parent);
            w = x->parent->left;
         }
         if(w->right->color == BLACK && w->left->color == BLACK){
            w->color = RED;
            x = x->parent;
         } else {
            if(w->left->color == BLACK){
               w->right->color = BLACK;
               w->color = RED;
               LeftRotate(w);
               w = x->parent->left;
            }
            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->left->color = BLACK;
            RightRotate(x->parent);
            x = root;
         }
      }
   }
   x->color = BLACK;
}

void Dictionary::RB_Delete(Node *N){
   Node *z = N;
   Node *y = z;
   Node *x;
   int y_original_color = y->color;
   if(z->left == nil){
      x = z->right;
      RB_Transplant(z, z->right);
   } else if (z->right == nil){
      x = z->left;
      RB_Transplant(z,z->left);
   } else {
      y = findNext(z);
      y_original_color = y->color;
      x = y->right;
      if(y->parent == z){
         x->parent = y;
      } else {
         RB_Transplant(y, y->right);
         y->right = z->right;
         y->right->parent = y;
      }
      RB_Transplant(z,y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
   }
   if(y_original_color == BLACK){
      RB_DeleteFixUp(x);
   }
}
/*** ACCESS FUNCTIONS ***/

/******************************************************
 * size()
 * returns the size or the number of pairs (key, value)
 * in the tree
 ******************************************************/
int Dictionary::size() const{
   return num_pairs;
}

/******************************************************
 * conatins()
 * returns true of key k exists in the tree else false
 ******************************************************/
bool Dictionary::contains(keyType k) const{
   Node *x = search(root, k);
   if( x == nil ){
      return false;
   }
   return true;
}

/******************************************************
 * getValue()
 * returns a reference of the value at key k
 * 
 * pre: the BST must contain k
 ******************************************************/
valType& Dictionary::getValue(keyType k) const{
   if(contains(k)){
      Node* x = search(root, k);
      return x->val;
   } else {
      throw std::logic_error("Dictionary: getValue(): key \""+ k + "\" does not exist");
   }
}

/******************************************************
 * hasCurrent()
 * returns true if the current field if not nil
 * else false
 ******************************************************/
bool Dictionary::hasCurrent() const{
   if(current != nil){
      return true;
   }
   return false;
}

/******************************************************
 * currentKey()
 * returns the key that is currently in the current
 * field
 * 
 * pre: hasCurrent() must be true
 ******************************************************/
keyType Dictionary::currentKey() const{
   if(hasCurrent()){
      return current->key;
   } else {
      throw std::logic_error("Dictionary: currentKey(): current undefined");
   }
}

/******************************************************
 * currentVal()
 * returns the value in the current field as a
 * reference
 * 
 * pre: hasCurrent() must be true
 ******************************************************/
valType& Dictionary::currentVal() const{
   if(hasCurrent()){
      return current->val;
   } else {
      throw std::logic_error("Dictionary: currentVal(): current undefined");
   }
}

/*** Manipulation procedures ***/

/******************************************************
 * clear()
 * deletes all nodes in the BST using a 
 * post-order walk
 * it then resets the Dictionay into its empty state
 ******************************************************/
void Dictionary::clear(){
   if(num_pairs > 0){
      postOrderDelete(root);
   }
   current = nil;
   num_pairs = 0;
   root = nil;
}

/******************************************************
 * setValue()
 * If a pair with key==k exists, overwrites the 
 * corresponding value with v, otherwise inserts the 
 * new pair (k, v).
 ******************************************************/
void Dictionary::setValue(keyType k, valType v){
   Node *z = new Node(k,v);
   Node *y = nil;
   Node *x = root;

   while(x != nil){
      y = x;
      if(z->key < x->key){
         x = x->left;
      } else if(x->key == z->key){
         x->val = v;
         delete z;
         return; //short-circuit the algorithm if we are only
                 //editing the current key
      } else {
         x = x->right;
      }
   }

   z->parent = y;
   z->left = nil;
   z->right = nil;
   if(y == nil){
      root = z; //if tree is empty
   } else if(z->key < y->key){
      y->left = z;
   } else {
      y->right = z;
   }
   num_pairs++;
}


/******************************************************
 * transplant()
 * swaps two nodes in the tree while keeping the
 * properties of the BST
 ******************************************************/
void Dictionary::transplant(Node* U, Node* V){
   if(U->parent == nil){
      root = V;
   } else if (U == U->parent->left){
      U->parent->left = V;
   } else {
      U->parent->right = V;
   }
   if(V != nil){
      V->parent = U->parent;
   }
}

/******************************************************
 * remove()
 * Deletes the pair for which key==k. If the pair
 * is current, then current becomes undefined
 * 
 * pre: contains(k)
 ******************************************************/
void Dictionary::remove(keyType k){
   if(!contains(k)){
      throw std::logic_error("Dictionary: remove(): key \""+ k +"\" does not exist");
   }
   Node *z = search(root, k);
   if(z == current){
      current = nil;
   }
   if(z->left == nil){ //case 1 or 2.1 (right only)
      transplant(z,z->right);
   } else if (z->right == nil){ //case 2.2 (left only)
      transplant(z,z->left);
   } else { //case 3
      Node *y = findNext(z);
      if(y->parent != z){
         transplant(y,y->right);
         y->right = z->right;
         y->right->parent = y;
      }
      transplant(z,y);
      y->left = z->left;
      y->left->parent = y;
   }
   z->parent = nullptr;
   z->left = nullptr;
   z->right = nullptr;
   delete z;
   num_pairs--;
}

/******************************************************
 * If non-empty, places current iterator at the first
 * (key, value) pair.
 * Otherwise do nothing.
 ******************************************************/
void Dictionary::begin(){
   current = findMin(root);
}

/******************************************************
 * If non-empty, places current iterator at the last
 * (key, value) pair, otherwise do nothing
 ******************************************************/
void Dictionary::end(){
   current = findMax(root);
}

/******************************************************
 * next()
 * If the current iterator is not at the last pair, 
 * advance to the next pair.
 * If the current iterator is at the last pair,
 * makes current undefined.
 * 
 * pre: hasCurrent() must be true
 ******************************************************/
void Dictionary::next(){
   if(!hasCurrent()){
      throw std::logic_error("Dictionary: next(): current not defined");
   }
   current = findNext(current);
}

/******************************************************
 * prev()
 * if the current iterator is not at the first pair,
 * moves current to the previous pair.
 * if the current iterator is at the first pair,
 * makes the current undefined
 * 
 * pre: hasCurrent() must be true
 ******************************************************/
void Dictionary::prev(){
   if(!hasCurrent()){
      throw std::logic_error("Dictionary: prev(): current not defined");
   }
   current = findPrev(current);
}

/*** OTHER FUNCTIONS ***/

/******************************************************
 * to_string()
 * Returns a string representation of the dictionary
 * using an in-order tree walk
 * NOTE: the value of the node is also printed
 ******************************************************/
std::string Dictionary::to_string() const{
   std::string s = "";
   inOrderString(s,root);
   return s;
}

/******************************************************
 * pre_string()
 * Returns a string representation of the dictionary
 * using an pre-order tree walk
 ******************************************************/
std::string Dictionary::pre_string() const{
   std::string s = "";
   preOrderString(s,root);
   return s;
}

/******************************************************
 * equals()
 * Returns true iff this dictionary contains
 * the same (key, value) pairs as Dictionary D
 ******************************************************/
bool Dictionary::equals(const Dictionary &D) const{
   Dictionary x = D;
   Dictionary y = *this;

   x.begin();
   y.begin();

   bool eq = (x.size() == y.size());
   while(x.hasCurrent() && eq){
      if(x.currentKey() != y.currentKey()){
         eq = false;
      }
      if (x.currentVal() != y.currentVal()){
         eq = false;
      }
      x.next();
      y.next();
   }
   return eq;
}

/*** OVERLOADS ***/

/******************************************************
 * operator<<()
 * Inserts a string representation of Dictionary D
 * into the stream.
 * Here, we will use out to_string function
 ******************************************************/
std::ostream& operator<<( std::ostream& stream, Dictionary& D){
   return stream<< D.Dictionary::to_string();
}

/******************************************************
 * operator==()
 * Returns true iff Dictionary A equals Dictionay B.
 * Here, we will use the equals() function
 ******************************************************/
bool operator==( const Dictionary& A, const Dictionary& B ){
   return A.Dictionary::equals(B);
}

/******************************************************
 * operator=
 * Overwrites the state of this dictionary with state
 * of D, and returns a reference of this Dictionary.
 ******************************************************/
Dictionary& Dictionary::operator=(const Dictionary& D){
   if(this != &D){
      Dictionary temp = D;
      std::swap(num_pairs, temp.num_pairs);
      std::swap(nil, temp.nil);
      std::swap(root, temp.root);
      std::swap(current, temp.current);
   }
   return *this;
}