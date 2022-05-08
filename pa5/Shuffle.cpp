/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA5
* Shuffle.c 
* Main client file for the modified C++ List ADT 
*********************************************************************************/
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>

#include "List.h"

using namespace std;

/**
 * shuffle()
 * Shuffles a deck using the perfect shuffle
 * 
 * NOTE: This will mainpulate the referenced list
 */
void shuffle(List &D){
   int length_D = D.length();
   int half_D = length_D/2;

   List first_half, second_half;
   first_half.moveFront(); second_half.moveFront();
   for(D.moveFront(); D.position() < length_D; D.moveNext()){
      if(D.position() < half_D){ //we need to split the List D into 2 halves
         first_half.insertBefore(D.peekNext());
      } else {
         second_half.insertBefore(D.peekNext());
      }
   }

   first_half.moveFront(); second_half.moveFront(); D.moveFront();
   D.clear();
   while(D.length() < length_D){ //alternates & merges lists into List D
      
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
   if(deck_size < 0){
      cerr << "ERROR: Deck Size cannot be less than 0" << endl;
      return EXIT_FAILURE;
   }

   /*** SHUFFLING SEQUENCE ***/
   cout<< "deck size       shuffle count" << endl;
   cout<< "------------------------------" << endl;
   for(int i = 1; i <= deck_size; ++i){
      List Deck;
      Deck.moveFront();
      for(int j = 1; j <= i; ++j){
         Deck.insertBefore(j);
      }
      int shuffles = 1;
      List cpy_deck = Deck; //we will use this to determine when to stop shuffling
      shuffle(Deck);
      while( !(Deck == cpy_deck) ){
         shuffle(Deck);
         shuffles++;
      }
      cout<< i << "\t\t\t" << shuffles <<endl;
   }  

   return EXIT_SUCCESS;
}