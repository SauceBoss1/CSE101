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

void freeList(List* pL){
  if(pL != NULL && *pL!=NULL){
    for(Node curr = pL->front; curr->next != NULL; curr = curr->next){
      freeNode(*curr);
    }
    free(*pL);
    *pL = NULL;
  }
}

// Access functions -----------------------------------------------------------

int length(List l){
  if(l == NULL){
    printf("ERROR: Checking the length of a NULL list.\n");
    exit(EXIT_FAILURE);
  }
  return l->length;
}

int index(List l){
  if(l == NULL){
    printf("ERROR: Checking the index of a NULL list.\n");
    exit(EXIT_FAILURE);
  }
  return l->index;
}

int front(List l){
  if(l == NULL){
    printf("ERROR: Checking the front element of a NULL list.\n");
    exit(EXIT_FAILURE);
  }
  if(length(l) < 0){
    printf("ERROR: The length of the list is 0");
    exit(EXIT_FAILURE);
  }
  return l->front->data;
}

int back(List l){
  if(l == NULL){
    printf("ERROR: Checking the back element of a NULL list.\n");
    exit(EXIT_FAILURE);
  }
  if(length(l) < 0){
    printf("ERROR: The length of the list is 0");
    exit(EXIT_FAILURE);
  }
  return l->back->data;
}

int get(List L){
  if(l == NULL){
    printf("ERROR: Getting the element of a NULL list.\n");
    exit(EXIT_FAILURE);
  }
  if(length(l) < 0){
    printf("ERROR: The length of the list is 0");
    exit(EXIT_FAILURE);
  }
  return L->cursor->data;
}

//TODO bool equals()