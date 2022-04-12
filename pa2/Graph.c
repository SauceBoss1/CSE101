/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA2 
* Graph.c 
* Implementation for the Graph ADT 
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"
#include "Graph.h"


#define NIL -1
#define INF -2

#define WHITE 0
#define GRAY 1
#define BLACK 2
/*** Structs ***/

// private GraphObj type
typedef struct GraphObj{
   List* adj_vertices;
   int* color;
   int* p;
   int* distance;

   int order;
   int size;
   int source;
} GraphObj;

/*** Constructor-Deconstructor Functions ***/

/*
* newGraph(int n)
* Creates a new instance of the Graph ADT and returns is
*/
Graph newGraph (int n){
   Graph G = malloc(sizeof(GraphObj));

   G->adj_vertices = calloc(1+n, sizeof(List));
   for(int i = 0; i < n+1; ++i){ //make sure the adj list all have new lists
      G->adj_vertices[i] = newList();
   }

   G->color = calloc(n+1, sizeof(int));
   G->p = calloc(n+1, sizeof(int));
   G->distance = calloc(n+1, sizeof(int));

   for(int i = 1; i < n+1; ++i){ //initialize the array fields
      G->p[i] = NIL;
      G->distance[i] = INF;
   }

   G->order = n;
   G->size = 0;
   G->source = NIL;
   return G;
}

/*
* freeGraph(Graph *pG)
* Frees a graph from the heap
*/
void freeGraph(Graph *pG){
   for(int i = 0; i < (*pG)->order + 1; ++i){ //make sure to free each List in array
      freeList(&((*pG)->adj_vertices[i]));
   }
   free((*pG)->adj_vertices);
   free((*pG)->color);
   free((*pG)->p);
   free((*pG)->distance);
   (*pG)->adj_vertices = NULL;
   (*pG)->color = (*pG)->p = (*pG)->distance = NULL;
   free(*pG);
   *pG = NULL;
   return;
}

/*** Access functions ***/

/*
* getOrder(Graph G)
* Returns the order/number of vertices in the graph
* 
* Pre: G != NULL
*/
int getOrder(Graph G){
   if(G == NULL){
      printf("GRAPH ERROR: Getting the order of a NULL Graph\n");
      exit(EXIT_FAILURE);
   }
   return G->order;
}

/**
 * getSize(Graph G)
 * Returns the suze of the graph
 * 
 * Pre: G != NULL
 */
int getSize(Graph G){
   if(G == NULL){
      printf("GRAPH ERROR: Getting the size of a NULL Graph\n");
      exit(EXIT_FAILURE);
   }
   return G->size;
}

/**
 * getSource(Graph G)
 * Returns the recently source of the BFS algorithm
 * 
 * NIL means that BFS has not been called
 * 
 * Pre: G != NULL
 */
int getSource(Graph G){
   if(G==NULL){
      printf("GRAPH ERROR: Getting the source of a NULL Graph\n");
      exit(EXIT_FAILURE);
   }
   return G->source;
}

/**
 * getParent(Graph G, int u)
 * Returns the parent of vertex u
 * 
 * Pre: G != NULL && u must be 1 <= u <= getOrder(G)
 */
int getParent(Graph G, int u){
   if(G==NULL){
      printf("GRAPH ERROR: Getting the parent of a NULL Graph\n");
      exit(EXIT_FAILURE);
   }
   if( u < 1 || u > getOrder(G)){
      printf("GRAPH ERROR: getParent() requires u to be between 1 and %d\n",getOrder(G));
      exit(EXIT_FAILURE);
   }
   return G->p[u];
}


/**
 * getDist(Graph G, int u)
 * Returns the Distance of vertex u
 * 
 * Pre: G != NULL && u must be 1 <= u <= getOrder(G)
 */
int getDist(Graph G, int u){
   if(G==NULL){
      printf("GRAPH ERROR: Getting the distance of a NULL Graph\n");
      exit(EXIT_FAILURE);
   }
   if( u < 1 || u > getOrder(G)){
      printf("GRAPH ERROR: getDistance() requires u to be between 1 and %d\n",getOrder(G));
      exit(EXIT_FAILURE);
   }
   return G->distance[u];
}

/**
 * getPath(List L, Graph G, int u)
 * Appends to List L the Shortest path from getSource(G) to vertex u
 * 
 * Taken from Prof. Tantalo's pseudocode
 * 
 * Pre: G != NULL && u must be 1 <= u <= getOrder(G) && BFS was already called
 */
void getPath(List L, Graph G, int u){
   if(G==NULL){
      printf("GRAPH ERROR: Getting the path of a NULL Graph\n");
      exit(EXIT_FAILURE);
   }
   if( u < 1 || u > getOrder(G)){
      printf("GRAPH ERROR: getPath() requires u to be between 1 and %d\n",getOrder(G));
      exit(EXIT_FAILURE);
   }

   if(getSource(G) != NIL){
      if(G->source == u){
         append(L,G->source);
      } else if (G->p[u] == NIL){
         append(L,NIL);
      } else {
         getPath(L,G,G->p[u]);
         append(L,u);
      }
   } else{
      printf("GRAPH ERROR: BFS must be ran first before obtaining the path\n");
      exit(EXIT_FAILURE);
   }
   return;
}

/*** Manipulation procedures ***/

/**
 * makeNull(Graph G)
 * Resets the Graph G to its inital state (Null graph)
 * while maintaining its order
 * 
 * Pre: G != NULL
 */
void makeNull(Graph G){
   if(G==NULL){
      printf("GRAPH ERROR: Making G NULL of an already NULL Graph\n");
      exit(EXIT_FAILURE);
   }

   int i;

   for(i = 0; i < G->order + 1; ++i){ //make sure to empty out each list in adjacency list
      clear(G->adj_vertices[i]);
   }
   free(G->color);
   free(G->p);
   free(G->distance);
   G->color = G->p = G->distance = NULL;
   G->size = 0;
   G->source = NIL;

   int n = G->order;
   G->color = calloc(n+1, sizeof(int));
   G->p = calloc(n+1, sizeof(int));
   G->distance = calloc(n+1, sizeof(int));
   return;
}

/*
Private function
addArcHelper(Graph G, int u, int v)
Adds an arc to a graph without increasing its size
This is done so the function can be used in other functions as well
such as addEdge()

Insertion Sort algorithm was taken from Derfel's pa1 Lex.c file

Pre: None -> public functions that use this function should handle the preconditions
*/
void addArcHelper(Graph G, int u, int v){
   List curr_list = G->adj_vertices[u];

   int prev_len = length(curr_list);

   if(prev_len == 0){
      prepend(curr_list, v);
   } else {
      for(moveFront(curr_list); index(curr_list) >=0 && prev_len == length(curr_list); moveNext(curr_list)){
         if(v < get(curr_list) && v != u){ //we need to make sure we don't add the same vertex twice
            insertBefore(curr_list, v);
         }
      }

      int new_len = length(curr_list);
      if (new_len == prev_len && v > back(curr_list) && v != u){
         append(curr_list, v);
      }
   }
   return;
}

/**
 * addArc(Graph G, int u, int v)
 * Adds an arc to Graph G
 * 
 * Pre: G != NULL && u must be 1 <= u <= getOrder(G)
 */
void addArc(Graph G, int u, int v){
   if(G==NULL){
      printf("GRAPH ERROR: Adding an Arc to a NULL Graph\n");
      exit(EXIT_FAILURE);
   }

   if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
      printf("GRAPH ERROR: addArc(): u or v is not between 1 and %d\n", getOrder(G));
      exit(EXIT_FAILURE);
   }

   addArcHelper(G,u,v);
   G->size++;
   return;
}

/**
 * addEdge(Graph G, int u, int v)
 * adds an Edge to graph G
 * 
 * Pre: G != NULL && u must be 1 <= u <= getOrder(G)
 */
void addEdge(Graph G, int u, int v){
   if(G==NULL){
      printf("GRAPH ERROR: Adding an Edge to a NULL Graph\n");
      exit(EXIT_FAILURE);
   }
   if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
      printf("GRAPH ERROR: addEdge(): u or v is not between 1 and %d\n", getOrder(G));
      exit(EXIT_FAILURE);
   }
   addArcHelper(G,u,v);
   addArcHelper(G,v,u);
   G->size++;
   return;
}

/**
 * BFS(Graph G, int s)
 * Finds the shortest path from source s to all its destinations
 * The algorithm updates all the Fields of the Graph ADT
 * 
 * Pseudo code taken from Prof. Tantalo
 * 
 * Pre: G != NULL && u must be 1 <= u <= getOrder(G)
 */
void BFS(Graph G, int s){
   if(G==NULL){
      printf("GRAPH ERROR: cannot call BFS() on a NULL graph\n");
      exit(EXIT_FAILURE);
   }
   if( s < 1 || s > getOrder(G)){
      printf("GRAPH ERROR: source vertex must be between 1 and %d\n",getOrder(G));
      exit(EXIT_FAILURE);
   }

   G->source = s;

   for(int i = 1; i < G->order + 1; ++i){ //Initialize Graph G fields except for the source
      if(i != s){
      G->color[i] = WHITE;
      G->distance[i] = INF;
      G->p[i] = NIL;
      }
   }

   G->color[s] = GRAY;
   G->distance[s] = 0;
   G->p[s] = NIL;
   List Q = newList();

   append(Q,s);
   while(length(Q) > 0){
      int x = front(Q);
      deleteFront(Q);

      List adj_list = G->adj_vertices[x];

      for(moveFront(adj_list);index(adj_list) >= 0; moveNext(adj_list)){
         int y = get(adj_list);

         if (G->color[y] == WHITE){
            G->color[y] = GRAY;
            G->distance[y] = G->distance[x] + 1;
            G->p[y] = x;
            append(Q, y);
         }
      }
      G->color[x] = BLACK;
   }

   freeList(&Q);
   return;
}

/*** Other operations ***/

/**
 * printGraph(FILE* out, Graph G)
 * Print's the adjacency list of Graph G
 */
void printGraph(FILE* out, Graph G){
   for(int i = 1; i < G->order + 1; ++i){
      fprintf(out,"%d: ",i);
      printList(out, G->adj_vertices[i]);
      fprintf(out,"\n");
   }
   return;
}