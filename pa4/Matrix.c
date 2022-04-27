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

      for(int i = 1; i < size(M) + 1; ++i){
         List row = M->m_body[i];
         for(moveFront(row); index(row) >= 0; moveNext(row)){
            Entry curr_entry = (Entry)get(row);
            freeEntry(&curr_entry);
            curr_entry = NULL;
         }
         freeList(&row);
         row = NULL;
      }
      free(M->m_body);
      M->m_body = NULL;
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
      Entry ent_p = (Entry)get(P);
      Entry ent_q = (Entry)get(Q);
      if(!(ent_p->col == ent_q->col && ent_p->val == ent_q->val)){
         return false;
      }
      return true;
   }
   return true;
}

int equals(Matrix A, Matrix B){
   if(A == NULL || B == NULL){
      printf("MATRIX ERROR: Either A or B is NULL when calling equals()\n");
      exit(EXIT_FAILURE);
   }
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

/***  MANIPULATION PROCEDURES ***/

void makeZero(Matrix M){
   if(M == NULL){
      printf("MATRIX ERROR: Calling makeZero on a NULL matrix\n");
      exit(EXIT_FAILURE);
   }

   for(int i = 1; i < size(M) + 1; ++i){
      List row = M->m_body[i];
      for(moveFront(row); index(row) >= 0; moveNext(row)){
         Entry curr_entry = (Entry)get(row);
         freeEntry(&curr_entry);
         curr_entry = NULL;
      }
      clear(row);
   }
   M->NNZ = 0;
   return;
}

void changeEntry(Matrix M, int i, int j, double x){
   if(M == NULL){
      printf("MATRIX ERROR: Calling changeEntry() on a NULL Matrix");
      exit(EXIT_FAILURE);
   }
   if( i < 1 || i > size(M) || j < 1 || j > size(M)){
      printf("MATRIX ERROR: Calling changeEntry() when i or j is less that 1 or greater than %d\n",size(M));
      exit(EXIT_FAILURE);
   }
   List row = M->m_body[i];

   if(length(row) == 0 && x != 0){
      append(row, newEntry(j, x));
      M->NNZ++;
   } else {
      int prev_len = length(row);
      for(moveFront(row); index(row) >= 0; moveNext(row)){
         Entry curr_ent = (Entry)get(row);
         if(curr_ent->col > j && x != 0){
            insertBefore(row, newEntry(j, x));
            M->NNZ++;
            return;
         } else if(curr_ent->col == j && x != 0){
            curr_ent->val = x;
            return;
         } else if(curr_ent->col == j && x == 0){
            freeEntry(&curr_ent);
            curr_ent = NULL;
            delete(row);
            M->NNZ--;
            return;
         }
      }
      int new_len = length(row);
      if(new_len == prev_len && x != 0){
         append(row, newEntry(j, x));
         M->NNZ++;
      }
   }
   return;
}

/*** ARITHMETIC OPERATIONS ***/

Matrix copy(Matrix A){
   if(A == NULL){
      printf("MATRIX ERROR: Calling copy() on a NULL matrix\n");
      exit(EXIT_FAILURE);
   }
   Matrix M = newMatrix(size(A));
   M->size = size(A);
   
   for(int i = 1; i < size(A) + 1; ++i){
      List row = A->m_body[i];
      if(length(row) == 0){
         continue;
      }

      List new_row = M->m_body[i];
      for(moveFront(row); index(row) >= 0; moveNext(row)){
         Entry curr_ent = (Entry)get(row);
         append(new_row, newEntry(curr_ent->col, curr_ent->val));
         M->NNZ++;
      }
   }

   return M;
}

Matrix transpose(Matrix A){
   if(A == NULL){
      printf("MATRIX ERROR: Calling transpose() on a NULL list\n");
      exit(EXIT_FAILURE);
   }
   Matrix M = newMatrix(size(A));
   M->size = size(A);

   for(int i = 1; i < size(A) + 1; ++i){
      List row = A->m_body[i];
      if(length(row) == 0){
         continue;
      }

      for(moveFront(row); index(row) >= 0; moveNext(row)){
         Entry curr_ent = (Entry)get(row);
         List new_row = M->m_body[curr_ent->col];
         append(new_row, newEntry(i, curr_ent->val));
         M->NNZ++;
      }
   }

   return M;
}

/*** DEBUG FUNCTIONS ***/

void printMatrix(FILE* out, Matrix M){
   if(M == NULL){
      printf("MATRIX ERROR: calling printMatrix on a NULL matrix\n");
      exit(EXIT_FAILURE);
   }
   for(int i = 1; i < size(M) + 1; ++i){
      List row = M->m_body[i];
      if(length(row) == 0){
         continue;
      }
      fprintf(out,"%d: ", i);
      for(moveFront(row); index(row) >= 0; moveNext(row)){
         Entry curr_ent = (Entry)get(row);
         fprintf(out, "(%d, %0.1lf) ", curr_ent->col, curr_ent->val);
      }
      fprintf(out,"\n");
   }
   return;
}