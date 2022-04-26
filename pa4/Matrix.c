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

int NNZ(Matrix M){
   if(M ==  NULL){
      printf("MATRIX ERROR: Calling NNS() on a NULL Matrix\n");
      exit(EXIT_FAILURE);
   }
   return M->NNZ;
}

/**
 * Private helper fucntion
 * bool vectorEquals(List P, List Q)
 * Checks whether or two vectors are equal or not
 */
bool vectorEquals(List P, List Q){
   if(P == NULL || Q == NULL){
      printf("vectorEquals ERROR: List P or Q is NULL!\n");
      exit(EXIT_FAILURE);
   }
   if( length(P) != length(Q)){
      return false;
   }

   for(moveFront(P), moveFront(Q); index(P) >= 0 && index(Q) >=0; moveNext(P), moveNext(Q)){
      Entry ent_p = *(Entry*)get(P);
      Entry ent_q = *(Entry*)get(Q);
      if(!(ent_p->col == ent_q->col && ent_p->val == ent_q->val)){
         return false;
      }
      return true;
   }
   return true;
}

int equals(Matrix A, Matrix B){
   if(size(A) != size(B)){
      return 0;
   }

   for(int i = 1; i < size(A) + 1; ++i){
      if(!(vectorEquals(A->m_body[i], B->m_body[i]))){
         return 0;
      }
   }
   return 1;
}

