/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA4 
* Matrix.c 
* Implementation for the Matrix ADT
*********************************************************************************/
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

// newEntry()
// Creates a new entry struct
Entry newEntry(int column, double value){
   Entry E = malloc(sizeof(EntryObj));
   if(E == NULL){
      free(E);
      E = NULL;
      printf("ERROR: Cannot allocate enough memory to create an Entry\n");
      exit(EXIT_FAILURE);
   }
   E->col = column;
   E->val = value;
   return E;
}

// freeEntry()
// Frees heap memory that's pointing to *pE, also sets *pE to NULL
void freeEntry(Entry *pE){
   if(pE != NULL && (*pE) != NULL){
      free(*pE);
      *pE=NULL;
   }
   return;
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
   Matrix M = malloc(sizeof(MatrixObj));
   if(M == NULL){
      free(M);
      M = NULL;
      printf("ERROR: Cannot allocate enough memory to create a Matrix\n");
      exit(EXIT_FAILURE);
   }

   M->m_body = calloc(n+1, sizeof(List));
   for(int i = 1; i < n+1; ++i){
      M->m_body[i] = newList();
   }
   M->size = n;
   M->NNZ = 0;
   return M;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
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

// size()
// Return the size of square Matrix M.
int size(Matrix M){
   if(M == NULL){
      printf("MATRIX ERROR: Calling size() on a NULL Matrix\n");
      exit(EXIT_FAILURE);
   }
   return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
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
   if( length(P) != length(Q) ){
      return false;
   }

   for(moveFront(P), moveFront(Q); index(P) >= 0; moveNext(P), moveNext(Q)){
      Entry ent_p = (Entry)get(P);
      Entry ent_q = (Entry)get(Q);
      if(!(ent_p->col == ent_q->col && ent_p->val == ent_q->val)){
         return false;
      }
   }
   return true;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
   if(A == NULL || B == NULL){
      printf("MATRIX ERROR: Either A or B is NULL when calling equals()\n");
      exit(EXIT_FAILURE);
   }
   if(size(A) != size(B)){
      return 0;
   }

   if( A == B ){
      return 1;
   }

   for(int i = 1; i < size(A) + 1; ++i){
      if(length(A->m_body[i]) == 0 || length(B->m_body[i]) == 0){
         continue;
      }

      if(!(vectorEquals(A->m_body[i], B->m_body[i]))){
         return 0;
      }
   }
   return 1;
}

/***  MANIPULATION PROCEDURES ***/

// makeZero()
// Re-sets M to the zero Matrix state.
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

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
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
         if(curr_ent->col > j && x != 0){ //is the curreny column is bigger than the target, then insert before
            insertBefore(row, newEntry(j, x));
            M->NNZ++;
            return;
         } else if(curr_ent->col == j && x != 0){ //replace value of current index if we find a target
            curr_ent->val = x;
            return;
         } else if(curr_ent->col == j && x == 0){ //delete an already existing node
            freeEntry(&curr_ent);
            curr_ent = NULL;
            delete(row);
            M->NNZ--;
            return;
         }
      }
      int new_len = length(row);
      if(new_len == prev_len && x != 0){ //if by chance the target is supposed to be at the end, then append it
         append(row, newEntry(j, x));
         M->NNZ++;
      }
   }
   return;
}

/*** ARITHMETIC OPERATIONS ***/

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
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

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
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

      for(moveFront(row); index(row) >= 0; moveNext(row)){ //same as copy but reverse the order
         Entry curr_ent = (Entry)get(row);
         List new_row = M->m_body[curr_ent->col];
         append(new_row, newEntry(i, curr_ent->val));
         M->NNZ++;
      }
   }

   return M;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
   if(A == NULL){
      printf("MATRIX ERROR: Calling scalarMult() on a NULL list\n");
      exit(EXIT_FAILURE);
   }

   Matrix M = newMatrix(size(A));
   M->size = size(A);

   for(int i = 1; i < size(A) + 1; ++i){
      List A_row = A->m_body[i];
      if(length(A_row) == 0){
         continue;
      }

      List M_row = M->m_body[i];
      for(moveFront(A_row); index(A_row) >= 0; moveNext(A_row)){ //same as copy and transpose but multiply all entries
         Entry curr_ent = (Entry)get(A_row);
         append(M_row, newEntry(curr_ent->col, (curr_ent->val * x)));
         M->NNZ++;
      }
   }
   return M;
} 

/**
 * vectorSum()
 * Returns the sum of 2 vectors that are the same size
 */
List vectorSum(Matrix M, List A, List B){
   if(A == NULL || B == NULL){
      printf("VECTORSUM ERROR: Calling vectorSum() when A or B is NULL\n");
      exit(EXIT_FAILURE);
   }

   List final = newList();

   moveFront(A);
   moveFront(B);
   while(index(A) >= 0 && index(B) >= 0){
      Entry ent_A = (Entry)get(A);
      Entry ent_B = (Entry)get(B);
      int i = ent_A->col; double i_val = ent_A->val;
      int j = ent_B->col; double j_val = ent_B->val;

      if(i < j){
         append(final, newEntry(i, i_val));
         M->NNZ++;
         moveNext(A);
         continue;
      } else if(j < i){
         append(final, newEntry(j, j_val));
         M->NNZ++;
         moveNext(B);
         continue;
      } else if(j == i){
         if(j_val + i_val != 0){
            append(final, newEntry(j, j_val + i_val));
            M->NNZ++;
         }
         moveNext(A);
         moveNext(B);
         continue;
      }
   }

   while(index(A) >= 0){ //if there are still entries left, append the to the vector
      Entry ent_A = (Entry)get(A);
      append(final, newEntry(ent_A->col, ent_A->val));
      M->NNZ++;
      moveNext(A);
   }

   while(index(B) >= 0){ //if there are still entries left, append the to the vector
      Entry ent_B = (Entry)get(B);
      append(final, newEntry(ent_B->col, ent_B->val));
      M->NNZ++;
      moveNext(B);
   }

   return final;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
   if(A == NULL || B == NULL){
      printf("MATRIX ERROR: Calling sum() when A or B is NULL\n");
      exit(EXIT_FAILURE);
   }
   if(size(A) != size(B)){
      printf("MATRIX ERROR: sum(): size(A) != size(B)\n");
      exit(EXIT_FAILURE);
   }

   Matrix final_M = newMatrix(size(A));
   
   if( A == B){
      freeMatrix(&final_M);
      return scalarMult(2, A);
   }

   for(int i = 1; i < size(B) + 1; ++i){
      List row_A = A->m_body[i];
      List row_B = B->m_body[i];
      if(length(row_A) == 0 && length(row_B) == 0){
         continue;
      }
      freeList(&(final_M->m_body[i]));
      final_M->m_body[i] = NULL;
      final_M->m_body[i] = vectorSum(final_M, row_A, row_B);
   }
   return final_M;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
   if(A == NULL || B == NULL){
      printf("MATRIX ERROR: Calling diff() when A or B is NULL\n");
      exit(EXIT_FAILURE);
   }
   if(size(A) != size(B)){
      printf("MATRIX ERROR: diff(): size(A) != size(B)\n");
      exit(EXIT_FAILURE);
   }
   Matrix S = scalarMult(-1, B);
   Matrix M = sum(A,S);

   freeMatrix(&S);
   return M;
}

/**
 * vectorDot()
 * Returns the dot product of two vectors that are the same size
 */
double vectorDot(List A, List B){
   if(A == NULL || B == NULL){
      printf("VECTOR DOT ERROR: List A or List B is NULL\n");
      exit(EXIT_FAILURE);
   }
   double sum = 0;

   moveFront(A);
   moveFront(B);
   while(index(A) >= 0 && index(B) >= 0){
      Entry ent_A = (Entry)get(A);
      Entry ent_B = (Entry)get(B);
      int i = ent_A->col; double i_val = ent_A->val;
      int j = ent_B->col; double j_val = ent_B->val;

      if(i < j){
         moveNext(A);
         continue;
      } else if(j < i){
         moveNext(B);
         continue;
      } else if(i == j){
         sum += (i_val * j_val);
         moveNext(A);
         moveNext(B);
         continue;
      }
   }
   return sum;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
   if(A == NULL || B == NULL){
      printf("MATRIX ERROR: Calling product() when A or B is NULL\n");
      exit(EXIT_FAILURE);
   }

   if(size(A) != size(B)){
      printf("MATRIX ERROR: product(): size(A) != size(B)\n");
      exit(EXIT_FAILURE);
   }

   Matrix T = transpose(B);
   Matrix M = newMatrix(size(A));

   for(int i = 1; i <= size(A); ++i){
      List A_row = A->m_body[i];
      List new_row = M->m_body[i];

      if(length(A_row) == 0){
         continue;
      }

      for(int j = 1; j <= size(B); ++j){
         List B_row = T->m_body[j];
         if(length(B_row) == 0){
            continue;
         }
         double dot_prod = vectorDot(A_row, B_row);
         
         if (dot_prod != 0){
            append(new_row, newEntry(j, dot_prod));
            M->NNZ++;
         }
      }
   }

   freeMatrix(&T);
   return M;
}

/*** DEBUG FUNCTIONS ***/

/*
printMatrix()
Prints a string representation of Matrix M to filestream out. Zero rows
are not printed. Each non-zero row is represented as one line consisting
of the row number, followed by a colon, a space, then a space separated
list of pairs "(col, val)" giving the column numbers and non-zero values
in that row. The double val will be rounded to 1 decimal point.
*/
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