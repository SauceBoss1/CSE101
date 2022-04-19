#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"
#include "Graph.h"

int main(int argc, char * argv[]){
   FILE *in, *out;
   int vertices = -1;

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

   /*** ADT INITALIZATION ***/

   List S = newList();
   Graph G = newGraph(vertices);
   Graph T = NULL;

   int u,v,input;

   /*** GRAPH & LIST INITIALIZATION ***/

   u = v = -1;

   // Adding Arcs
   while(u != 0 && v != 0){
      if( (input = fscanf(in, "%d %d\n", &u, &v)) != EOF ){
         if(input == 0){
            fprintf(stderr, "Malformed read!\n");
            return EXIT_FAILURE;
         }

         if(u != 0 && v != 0){
            addArc(G, u, v);
         }
      }
   }

   //Adding vertices to S
   for(int i = 1; i <= vertices; ++i) append(S,i);

   /*** ADJACENCY LIST OUTPUT ***/

   fprintf(out, "Adjacency list representation of G:\n");
   printGraph(out, G);
   fprintf(out,"\n");

   /*** DFS ***/

   DFS(G,S);
   T = transpose(G);
   DFS(T,S);

   /*** SCC OUTPUT ***/

   List output = newList();

   //Get the number of components
   int components = 0;
   for(moveBack(S); index(S) >= 0; movePrev(S)){
      int i = get(S);
      //fprintf(stdout,"Vertex parent of %d is %d\n",i, getParent(T,i));
      if(getParent(T, i) == NIL){
         ++components;
      }
   }

   fprintf(out, "G contains %d strongly connected components:\n",components);
   
   components = 0;
   for(moveBack(S); index(S) >= 0; movePrev(S)){
      int i = get(S);

      prepend(output, i);
      if(getParent(T, i) == NIL){
         fprintf(out,"Component %d: ", ++components);
         printList(out, output);
         fprintf(out,"\n");

         clear(output);
      }
   }

   freeList(&output);
   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   fclose(in);
   fclose(out);
   return EXIT_SUCCESS;
}