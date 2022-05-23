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
   nil = new Node("\0\0",NIL_VAL);
   root = nil;
   current = nullptr;
   num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary &D){
   clear();
   nil = new Node("\0\0", NIL_VAL);
   root = nullptr;
   current = nullptr;
   num_pairs = 0;
   preOrderCopy(D.root, nullptr);
}

Dictionary::~Dictionary(){
   //postOrderDelete(root);
   clear();
   nil->left = nullptr;
   nil->right = nullptr;
   nil->parent = nullptr;
   root = nullptr;
   current = nullptr;
   delete nil;

}
/*** HELPER FUNCTIONS ***/

void Dictionary::inOrderString(std::string &s, Node* R) const{
   if( R != nil ){
      inOrderString(s, R->left);
      s += R->key + " : " + std::to_string(R->val) + "\n";
      inOrderString(s,R->right);
   }
}

void Dictionary::preOrderString(std::string &s, Node *R) const{
   if( R != nil){
      s += R->key;
      preOrderString(s, R->left);
      preOrderString(s, R->right);
   }
}

void Dictionary::preOrderCopy(Node *R, Node *N){
   if(R != nil && R != N){
      setValue(R->key, R->val);
      preOrderCopy(R->left, N);
      preOrderCopy(R->right, N);
   }
}

void Dictionary::postOrderDelete(Node *R){
   std::cout << R->key << std::endl;
   if( R != nil ){
      postOrderDelete(R->left);
      postOrderDelete(R->right);
      R->parent = nullptr;
      R->left = nullptr;
      R->left = nullptr;
      delete R;
   }
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
   if(R == nil || R->key == k){
      return R;
   } else if(k < R->key){
      return search(R->left, k);
   } else {
      return search(R->right, k);
   }
}

Dictionary::Node* Dictionary::findMin(Node *R){
   if(num_pairs <=0){
      throw std::range_error("Dictionary: findMin(): empty tree");
   }
   Node* x = R;
   while(x->left != nil){
      x = x->left;
   }
   return x;
}

Dictionary::Node* Dictionary::findMax(Node *R){
   if(num_pairs <=0){
      throw std::range_error("Dictionary: findMin(): empty tree");
   }
   Node* x = R;
   while(x->right != nil){
      x = x->right;
   }
   return x;
}

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

/*** ACCESS FUNCTIONS ***/

int Dictionary::size() const{
   return num_pairs;
}

bool Dictionary::contains(keyType k) const{
   Node *x = search(root, k);
   if( x == nil ){
      return false;
   }
   return true;
}

valType& Dictionary::getValue(keyType k) const{
   if(contains(k)){
      Node* x = search(root, k);
      return x->val;
   } else {
      throw std::logic_error("Dictionary: getValue(): key "+ k +" does not exist");
   }
}

bool Dictionary::hasCurrent() const{
   if(current != nil){
      return true;
   }
   return false;
}

keyType Dictionary::currentKey() const{
   if(hasCurrent()){
      return current->key;
   } else {
      throw std::logic_error("Dictionary: currentKey(): current undefined");
   }
}

valType& Dictionary::currentVal() const{
   if(hasCurrent()){
      return current->val;
   } else {
      throw std::logic_error("Dictionary: currentVal(): current undefined");
   }
}

/*** Manipulation procedures ***/

void Dictionary::clear(){
   postOrderDelete(root);
   current = nil;
   num_pairs = 0;
   root = nil;
}

void Dictionary::setValue(keyType k, valType v){
   Node *n = search(root, k);

   if(n != nil){
      n->val = v;
   } else {
      Node *z = new Node(k,v);
      Node *y = nil;
      Node *x = root;

      while(x != nil){
         y = x;
         if(z->key < x->key){
            x = x->left;
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
}

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

void Dictionary::remove(keyType k){
   if(!contains(k)){
      throw std::logic_error("Dictionary: remove(): key "+ k +" does not exist");
   }
   Node *z = search(root, k);

   if(z->left == nil){ //case 1 or 2.1 (right only)
      transplant(z,z->right);
   } else if (z->right == nil){ //case 2.2 (left only)
      transplant(z,z->left);
   } else {
      Node *y = findNext(z->right);
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

void Dictionary::begin(){
   current = findMin(root);
}

void Dictionary::end(){
   current = findMax(root);
}

void Dictionary::next(){
   if(!hasCurrent()){
      throw std::logic_error("Dictionary: next(): current not defined");
   }
   current = findNext(current);
}

void Dictionary::prev(){
   if(!hasCurrent()){
      throw std::logic_error("Dictionary: prev(): current not defined");
   }
   current = findPrev(current);
}

/*** OTHER FUNCTIONS ***/

std::string Dictionary::to_string() const{
   std::string s = "";
   inOrderString(s,root);
   return s;
}

std::string Dictionary::pre_string() const{
   std::string s = "";
   preOrderString(s,root);
   return s;
}

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

std::ostream& operator<<( std::ostream& stream, Dictionary& D){
   return stream<< D.Dictionary::to_string();
}

bool operator==( const Dictionary& A, const Dictionary& B ){
   return A.Dictionary::equals(B);
}

Dictionary& Dictionary::operator=(const Dictionary& D){
   if(this != &D){
      Dictionary temp = D;
      std::swap(num_pairs, temp.num_pairs);
      std::swap(nil,temp.nil);
      std::swap(root,temp.root);
      std::swap(current,temp.current);
   }

   return *this;
}