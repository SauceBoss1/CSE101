/*
Derfel Terciano
Created: 2022
v1

CSE 101 - Tantalo
*/


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "List.h"

// structs ----------------------------------------------------

//private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj {

  int data;
  Node next;
  Node prev;

} NodeObj;

// private ListObj type
typedef struct ListObj{
  Node front, cursor, back;
  int index;
  int length;
}

// Constructors-Deconstructors --------------------------------

Node newNode(int data){
  Node N = malloc(sizeof(NodeObj));
  N->data = data;
  N->next = NULL;
  N->prev = NULL;
  return(N);
}

void freeNode(Node* pN){
  if( pN != NULL && pN* != NULL){
    free(*pN);
    *pN=NULL;
  }
}

List newList(void){
  List L = malloc(sizeof(ListObj));
  L->cursor = L->front = L->back = NULL;
  L->length = 0;
  L->index = -1;
}

