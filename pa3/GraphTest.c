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
   int i, n=11;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL, C=NULL;
   
   for(i=1; i<=n; i++) append(S, i);

   addArc(G,1,4);
   addArc(G,2,3);
   addArc(G,3,5);
   addArc(G,4,1);
   addArc(G,5,4);
   addArc(G,6,5);
   addArc(G,6,3);
   addArc(G,6,9);
   addArc(G,6,10);
   addArc(G,7,3);
   addArc(G,7,6);
   addArc(G,8,4);
   addArc(G,9,4);
   addArc(G,9,8);
   addArc(G,9,5);
   addArc(G,10,9);
   addArc(G,10,11);
   addEdge(G,11,7);
   printf("Size: %d\n",getSize(G));

   addArc(G,11,7);
   addArc(G,11,7);
   addArc(G,11,7);
   addArc(G,11,7);
   printf("New Size: %d\n",getSize(G));
   printGraph(stdout,G);
   printf("\n");

   T = transpose(G);
   C = copyGraph(G);
   printf("TRANSPOSE: \n");
   printGraph(stdout, T);
   printf("\nCOPY:\n");
   printGraph(stdout, C);

   printf("\nOriginal G data: Order %d, Size%d\n", getOrder(G), getSize(G));
   printf("Transpose data: Order: %d, Size: %d\n",getOrder(T), getSize(T));
   printf("Copy data: Order: %d, Size: %d\n\n",getOrder(C),getOrder(C));

   DFS(G,S);
   DFS(T,S);

   for(moveBack(S); index(S) >= 0 ; movePrev(S)){
      int i = get(S);
      printf("Vertex %d:\n",i);
      printf("   Parent in T: %d, Discover Time: %d, Finish Time: %d\n",getParent(T, i), getDiscover(T, i), getFinish(T,i));
   }

   freeGraph(&T);
   freeGraph(&C);
   freeGraph(&G);
   freeList(&S);
   return EXIT_SUCCESS; 
}