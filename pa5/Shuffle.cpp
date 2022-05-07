#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>

#include "List.h"

using namespace std;

void shuffle(List &D){
   int length_D = D.length();
   int half_D = length_D/2;

   List first_half, second_half;
   first_half.moveFront(); second_half.moveFront();
   for(D.moveFront(); D.position() < length_D; D.moveNext()){
      if(D.position() < half_D){
         first_half.insertBefore(D.peekNext());
      } else {
         second_half.insertBefore(D.peekNext());
      }
   }

   first_half.moveFront(); second_half.moveFront(); D.moveFront();
   D.clear();
   while(D.length() < length_D){
      
      if(second_half.position() < second_half.length()){
         D.insertBefore(second_half.moveNext());
      }
      if(first_half.position() < first_half.length()){
         D.insertBefore(first_half.moveNext());
      }

   }

   
}

int main(int argc, char* argv[]){
   if(argc != 2){
      cerr << "Usage: " << argv[0] <<  " <Deck Size>" << endl;
      return EXIT_FAILURE;
   }

   int deck_size = stoi(argv[1]);

   List Deck;
   List cpy_deck = Deck; //we will use this to determine when to stop shuffling
   for(int i = 0; i < deck_size; ++i){
      Deck.insertBefore(i);
   }


   shuffle(Deck);
   Deck.moveFront();
   cout<< Deck << endl;
   return EXIT_SUCCESS;
}