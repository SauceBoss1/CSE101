#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"
#include "Matrix.h"

int main(){
   int n=100000;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   Matrix C, T;

   changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
   changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
   changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
   changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
   changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
   changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
   changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
   changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
   changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);
   changeEntry(A, 3,3,0); changeEntry(B, 3,3,0);

   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);
   printf("\n");
   
   printf("%d\n", NNZ(B));
   printMatrix(stdout, B);
   printf("\n");

   C = copy(A);
   T = transpose(A);

   printf("%d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\n");

   printf("%d\n", NNZ(T));
   printMatrix(stdout, T);
   printf("\n");

   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&T);

   return EXIT_SUCCESS;
}