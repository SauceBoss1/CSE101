/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA1 
* FindPath.c 
* Finds the shortest possible Path 
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Graph.h"
#include "List.h"

#define MAX_LEN 1024

int main(int argc, char * argv[]){
   FILE *in, *out;
   int vertices;
   // ARGUMENT PARSER -------------------------------------------------------

   if(argc != 3){
      fprintf(stderr, "Usage: %s <input file> <outputfile>\n",argv[0]);
      return EXIT_FAILURE;
   }

   in = fopen(argv[1], "r");
   if(in == NULL){
      fprintf(stderr, "ERROR: Unable to open file: %s for reading\n",argv[1]);
      return EXIT_FAILURE;
   }

   out = fopen(argv[2], "w");
   if(out == NULL){
      fprintf(stderr, "ERROR: Unable to open file: %s for writing\n",argv[2]);
      return EXIT_FAILURE;
   }

   // GET NUMBER OF VERTICES ------------------------------------------------
   char buffer[MAX_LEN];
   if ((fgets(buf, MAX_LEN, infile)) == NULL){
      fprintf(stderr,"ERROR: Bad Read of the number of vertices\n");
      return EXIT_FAILURE;
   }
   buffer[strlen(buffer) - 1] = '\0';
   vertices = strtol(buffer, MAX_LEN, 10);
   
   List L = newList;
   Graph G = newGraph(vertices);
   
   return EXIT_SUCCESS;
}