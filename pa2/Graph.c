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

Graph newGraph (int n){
  Graph G = malloc(sizeof(GraphObj));

  G->adj_vertices = calloc(1+n, sizeof(List));
  for(int i = 0; i < n+1; ++i){
    G->adj_vertices[i] = newList();
  }

  G->color = calloc(n+1, sizeof(int));
  G->p = calloc(n+1, sizeof(int));
  G->distance = calloc(n+1, sizeof(int));

  G->order = n;
  G->size = 0;
  G->source = NIL;
}

void freeGraph(Graph *pG){
  for(int i = 0; i < (*pG)->order; ++i){
    freeList(&((*pG)->adj_vertices[i]));
  }
  free((*pG)->color);
  free((*pG)->p);
  free((*pG)->distance);
  free(*pG);
  *pG = NULL;
  return;
}

/*** Access functions ***/