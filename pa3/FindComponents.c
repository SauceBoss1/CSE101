#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"
#include "Graph.h"

int main(int argc, char * argv[]){
   FILE *in, *out;
   int vertices;

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

   /*** GET NUMBER OF VERTICES ***/

   fscanf(in, "%d\n", &vertices);


   fclose(in);
   fclose(out);
   return EXIT_SUCCESS;
}