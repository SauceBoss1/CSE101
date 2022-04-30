/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA4 
* Sparse.c 
* Main client file to use the Matrix ADT
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"
#include "Matrix.h"

int main(int argc, char * argv[]){
   FILE *in, *out;

   /*** ARGUMENT PARSER ***/

   if(argc != 3){
      fprintf(stderr, "Usage: %s <input file> <output file>\n",argv[0]);
      return EXIT_FAILURE;
   }

   in = fopen(argv[1], "r");
   if(in == NULL){
      fprintf(stderr, "ERROR: Unable to open file: %s for reading\n",argv[1]);
      return EXIT_FAILURE;
   }

   out = fopen(argv[2], "w");
   if(out == NULL){
      fprintf(stderr,"ERROR: Unable to open file: %s for writing\n",argv[2]);
      return EXIT_FAILURE;
   }

   /*** INPUT PARSING ***/

   int input_size, mat_a, mat_b;

   fscanf(in, "%d %d %d\n", &input_size, &mat_a, &mat_b);

   Matrix A = newMatrix(input_size);
   Matrix B = newMatrix(input_size);

   int i,j;
   double val;

   for(int x = 0; x < mat_a; ++x){
      if(fscanf(in, "%d %d %lf\n",&i, &j, &val) == 0){
         fprintf(stderr,"ERROR: Bad Read on input\n");
         return EXIT_FAILURE;
      }
      changeEntry(A,i,j,val);
   }

   for(int x = 0; x < mat_b; ++x){
      if(fscanf(in, "%d %d %lf\n",&i, &j, &val) == 0){
         fprintf(stderr,"ERROR: Bad Read on input\n");
         return EXIT_FAILURE;
      }
      changeEntry(B,i,j,val);
   }

   /*** MATRIX CALCULATIONS ***/   

   fprintf(out,"A has %d non-zero entries:\n",NNZ(A));
   printMatrix(out, A);
   fprintf(out,"\n");

   fprintf(out,"B has %d non-zero entries:\n",NNZ(B));
   printMatrix(out, B);
   fprintf(out,"\n");

   fprintf(out,"(1.5)*A =\n");
   Matrix scalar = scalarMult(1.5,A);
   printMatrix(out, scalar);
   fprintf(out,"\n");

   fprintf(out,"A+B =\n");
   Matrix sumA_B = sum(A,B);
   printMatrix(out, sumA_B);
   fprintf(out,"\n");

   fprintf(out,"A+A =\n");
   Matrix sumA_A = sum(A,A);
   printMatrix(out,sumA_A);
   fprintf(out,"\n");

   fprintf(out,"B-A =\n");
   Matrix diffB_A = diff(B,A);
   printMatrix(out,diffB_A);
   fprintf(out,"\n");

   fprintf(out,"A-A =\n");
   Matrix diffA_A = diff(A,A);
   printMatrix(out,diffA_A);
   fprintf(out,"\n");

   fprintf(out,"Transpose(A) =\n");
   Matrix T = transpose(A);
   printMatrix(out,T);
   fprintf(out,"\n");

   fprintf(out,"A*B =\n");
   Matrix prodA_B = product(A,B);
   printMatrix(out,prodA_B);
   fprintf(out,"\n");

   fprintf(out,"B*B =\n");
   Matrix prodB_B = product(B,B);
   printMatrix(out,prodB_B);
   fprintf(out,"\n");

   /*** EXIT PROCEDURES ***/

   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&scalar);
   freeMatrix(&sumA_B);
   freeMatrix(&sumA_A);
   freeMatrix(&diffB_A);
   freeMatrix(&diffA_A);
   freeMatrix(&T);
   freeMatrix(&prodA_B);
   freeMatrix(&prodB_B);

   fclose(in);
   fclose(out);
   return EXIT_SUCCESS;
}