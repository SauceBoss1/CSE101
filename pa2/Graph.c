#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"
#include "Graph.h"

/*** Structs ***/

// private GraphObj type

typedef struct GraphObj{
  List* adj_vertices;
  int* color;
  int* p;
  int* distance;

  int vertices;
  int size;
  int dource;
} GraphObj;

/*** Access Functions ***/

