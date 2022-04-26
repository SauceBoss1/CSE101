#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"
#include "Matrix.h"

/*** STRUCTS ***/

//Private Entry type
typedef struct EntryObj* Entry;

//Private EntryObj struct
typedef struct EntryObj{
   int col;
   double val;
} EntryObj;

//Private MatrixObj struct
typedef struct MatrixObj{
   List* m_body;
   int size;
   int NNZ;
} MatrixObj;

/*** CONSTRUCTOR-DESTRUCTORS ***/

Entry newEntry(int column, double value){
   Entry E = malloc(sizeof(EntryObj));
   //TODO: add the if null part
   E->col = column;
   E->val = value;
   return E;
}

void freeEntry(Entry *pE){
   if(pE != NULL && (*pE) != NULL){
      free(*pE);
      *pE=NULL;
   }
   return;
}

Matrix newMatrix(int n){
   Matrix M = malloc(sizeof(MatrixObj));
   //TODO: Add if null check

   M->m_body = calloc(n+1, sizeof(List));
   for(int i = 1; i < n+1; ++i){
      M->m_body[i] = newList();
   }
   M->size = n;
   M->NNZ = 0;
   return M;
}

void freeMatrix(Matrix* pM){
   if(pM != NULL && *pM != NULL){
      Matrix M = (*pM);

      for(int i = 1; i < size(M)+1; ++i){
         List curr = M->m_body[i];
         for(moveFront(curr); index(curr) <= 0; moveNext(curr)){
            Entry ent = *(Entry*)get(curr);
            freeEntry(ent);
         }
         freeList(&curr);
         curr = NULL;
      }

      free(M);
      M = NULL;
   }
   return;
}

/*** ACCESS FUNCTIONS ***/

int size(Matrix M){
   if(M == NULL){
      printf("MATRIX ERROR: Calling size() on a NULL Matrix\n");
      exit(EXIT_FAILURE);
   }
   return M->size;
}