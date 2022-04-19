/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA3 
* GraphTest.c 
* Main testing harness for DFS Graph ADT 
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"
#include "Graph.h"

int main(void){
   int i, n=8;
   List S = newList();
   Graph G = newGraph(n);
   //Graph T=NULL, C=NULL;
   
   for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 3,8);
   addArc(G, 6,5);
   addArc(G, 6,7);
   addArc(G, 8,4);
   addArc(G, 8,7);
   printf("Size: %d\n",getSize(G));

   addArc(G, 8,7);
   addArc(G, 8,7);
   addArc(G, 8,7);
   addArc(G, 8,7);
   addArc(G, 8,7);
   printf("New Size: %d\n",getSize(G));
   printGraph(stdout,G);
   printf("\n");
   return EXIT_SUCCESS; 
}