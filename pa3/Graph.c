#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"
#include "Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

/*** Structs ***/

// private GraphObj type
typedef struct GraphObj{
   List* adj;
   int* color; //colors: WHITE, GRAY, BLACK
   int* parent;
   int* discover;
   int* finish;

   int order;
   int size;
} GraphObj;


/*** Constructor-Deconstructor Functions ***/

/**
 * Graph newGraph(int n)
 * Creates a new instance of the Graph ADT and returns it
 */
Graph newGraph(int n){
   Graph G = malloc(sizeof(Graph));

   G->adj = calloc(n+1, sizeof(List));
   G->color = calloc(n+1, sizeof(int));
   G->parent = calloc(n+1, sizeof(int));
   G->discover = calloc(n+1, sizeof(int));
   G->finish = calloc(n+1,sizeof(int));

   G->order = n;
   G->size = 0;

   for(int i = 1; i < n+1; ++i){
      G->adj[i] = newList();
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->discover[i] = UNDEF;
      G->finish[i] = UNDEF;
   }

   return G;
}

/**
 * void freeGraph(Graph* pG)
 * Frees a Graph ADT from the heap
 */
void freeGraph(Graph* pG){
   Graph G = (*pG);
   for(int i = 1; i < G->order + 1; ++i){
      freeList(&(G->adj[i]));
   }
   free(G->adj);
   free(G->color);
   free(G->parent);
   free(G->discover);
   free(G->finish);

   G->adj = NULL;
   G->color = G->parent = G->discover = G->finish = NULL;

   free(G);
   G = NULL;
   return;
}

/*** Access Function **/

/**
 * int getOrder(Graph G)
 * Returns the order of the graph G
 */
int getOrder(Graph G){
   if(G == NULL){
      fprintf(stderr, "GRAPH ERROR: Getting the order of a NULL Graph\n");
      exit(EXIT_FAILURE);
   }
   return G->order;
}

/**
 * int getSize(Graph G)
 * Returns the size of the Graph T
 */
int getSize(Graph G){
   if(G == NULL){
      fprintf(stderr, "GRAPH ERROR: Getting the order of a NULL Graph\n");
      exit(EXIT_FAILURE);
   }
   return G->size;
}

/**
 * int getParent(Graph G, int u)
 * Returns the parent of vertex u in Graph G
 */
int getParent(Graph G, int u){
   if(G == NULL){
      fprintf(stderr, "GRAPH ERROR: Getting the parent of a NULL Graph\n");
      exit(EXIT_FAILURE);
   }
   if(u < 1 || u > getOrder(G)){
      fprintf(stderr, "GRAPH ERROR: parent of u needs to be between 1 and getOrder(G)\n");
      exit(EXIT_FAILURE);
   }
   return G->parent[u];
}

/**
 * int getDiscover(Graph G, int u)
 * Returns the discover time of Graph G at vertex u
 */
int getDiscover(Graph G, int u){
   if(G == NULL){
      fprintf(stderr, "GRAPH ERROR: Getting the discover time of a NULL Graph\n");
      exit(EXIT_FAILURE);
   }
   if(u < 1 || u > getOrder(G)){
      fprintf(stderr, "GRAPH ERROR: discover time of u needs to be between 1 and getOrder(G)\n");
      exit(EXIT_FAILURE);
   }
   return G->discover[u];
}

/**
 * int getFinish(Graph G, int u)
 * Returns the finish time of Graph G at vertex u
 */
int getFinish(Graph G, int u){
   if(G == NULL){
      fprintf(stderr, "GRAPH ERROR: Getting the finish time of a NULL Graph\n");
      exit(EXIT_FAILURE);
   }
   if(u < 1 || u > getOrder(G)){
      fprintf(stderr, "GRAPH ERROR: finish time of u needs to be between 1 and getOrder(G)\n");
      exit(EXIT_FAILURE);
   }
   return G->finish[u];
}

