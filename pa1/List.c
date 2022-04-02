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
} ListObj;

// Constructors-Deconstructors --------------------------------

Node newNode(int data){
  Node N = malloc(sizeof(NodeObj));
  N->data = data;
  N->next = NULL;
  N->prev = NULL;
  return(N);
}

void freeNode(Node* pN){
  if( pN != NULL && *pN != NULL){
    free(*pN);
    *pN=NULL;
  }
}

List newList(void){
  List L = malloc(sizeof(ListObj));
  L->cursor = L->front = L->back = NULL;
  L->length = 0;
  L->index = -1;
  return L;
}

void freeList(List* pL){
  if(pL != NULL && *pL!=NULL){
    while( length(*pL) > 0){
      deleteBack(*pL);
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
    printf("ERROR: The length of the list is 0\n");
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
    printf("ERROR: The length of the list is 0\n");
    exit(EXIT_FAILURE);
  }
  return l->back->data;
}

int get(List l){
  if(l == NULL){
    printf("ERROR: Getting the element of a NULL list.\n");
    exit(EXIT_FAILURE);
  }
  if(length(l) < 0){
    printf("ERROR: The length of the list is 0\n");
    exit(EXIT_FAILURE);
  }
  return l->cursor->data;
}

bool equals(List A, List B){
  bool eq = false;
  Node N = NULL;
  Node M = NULL;

  if(A == NULL || B == NULL){
    printf("ERROR: Either List A or List B is NULL\n");
  }

  eq = (length(A) == length(B));
  N = A->front;
  M = B->front;
  while ( eq && N != NULL){
    eq = (N->data == M->data);
    N = N->next;
    M = M->next;
  }

  return eq;
}

// Manipulation procedures ----------------------------------------------------

void clear(List l){
  if(l == NULL){
    printf("ERROR: Clearing a NULL list.\n");
    exit(EXIT_FAILURE);
  }

  if(length(l) == 0){
    printf("ERROR: Clearing an already empty list.\n");
    exit(EXIT_FAILURE);
  }
  
  while( length(l) > 0){
    deleteBack(l);
  }
  l->front = l->cursor = l->back = NULL;
  l->index = -1;
  l->length = 0;
  return;
}

void set(List l, int x){
  if(l == NULL){
    printf("ERROR: Setting an element of a NULL list\n");
    exit(EXIT_FAILURE);
  }
  if (length(l) < 0 ){ //You may need to just use prepend or append instead but check later
    printf("ERROR: Setting an element to an empty list.\n");
    exit(EXIT_FAILURE);
  }

  l->cursor->data = x;

  return;
}

/*
  REMEMBER: Chec for the length just in case someone tries to move cursor on an empty List.
*/
void moveFront(List l){
  if(l == NULL){
    printf("ERROR: Trying to move cursor to the front of a NULL list\n");
    exit(EXIT_FAILURE);
  }
  if (length(l) > 0){
    l->cursor = l->front;
    l->index = 0;
  }

  return;
}

void moveBack(List l){
  if(l == NULL){
    printf("ERROR: Trying to move cursor to the back of a NULL list\n");
    exit(EXIT_FAILURE);
  }
  if (length(l) > 0){
    l->cursor = l->back;
    l->index = length(l) - 1;
  }
}

void movePrev(List l){
  if(l == NULL){
    printf("ERROR: Trying to move cursor one step to the front of a NULL list\n");
    exit(EXIT_FAILURE);
  }

  if(l->cursor != NULL && l->cursor->prev == NULL){
    l->cursor = NULL;
    l->index = -1;
  } else if(l->cursor != NULL && l->cursor->prev != NULL){
    l->cursor = l->cursor->prev;
    l->index--;
  } 
  return;
}

void moveNext(List l){
  if(l == NULL){
    printf("ERROR: Trying to move cursor one step to the back of a NULL list\n");
    exit(EXIT_FAILURE);
  }

  if(l->cursor != NULL && l->cursor->next == NULL){
    l->cursor = NULL;
    l->index = -1;
  } else if(l->cursor->next != NULL && l->cursor != NULL){
    l->cursor = l->cursor->next;
    l->index++;
  }
  return;
}

void prepend(List l, int x){
  if(l==NULL){
    printf("ERROR: Trying to prepend to a NULL list\n");
    exit(EXIT_FAILURE);
  }
  
  Node n = newNode(x);
  if(l->front == NULL && l->back==NULL && length(l) == 0){
    l->front = n;
    l->back = n;
    l->length++;
  } else {
    l->front->prev = n;
    n->next = l->front;
    l->front = n;
    l->length++;
  }
  return;
}

void append(List l, int x){
  if(l==NULL){
    printf("ERROR: Trying to append to a NULL list\n");
    exit(EXIT_FAILURE);
  }

  Node n = newNode(x);
  if(l->front == NULL && l->back == NULL && length(l) == 0){
    l->front = l->back = n;
    l->length++;
  } else {
    l->back->next = n;
    n->prev = l->back;
    l->back = n;
    l->length++;
  }
  return;
}

void insertBefore(List l, int x){
  if(l==NULL){
    printf("ERROR: Trying to insert before cursor on a NULL list\n");
    exit(EXIT_FAILURE);
  }

  if(l->cursor->prev == NULL && length(l) > 0 && index(l) >=0){
    prepend(l,x);
  } else if(length(l) > 0 && index(l) >=0){
    Node n = newNode(x);

    n->next = l->cursor;
    n->prev = l->cursor->prev;
    l->cursor->prev = n;
    n->prev->next = n;
    l->index++;
    l->length++;
  }
  return;
}

void insertAfter(List l, int x){
  if(l==NULL){
    printf("ERROR: Trying to insert after cursor on a NULL list\n");
    exit(EXIT_FAILURE);
  }

  if(l->cursor->next == NULL && length(l) > 0 && index(l) >= 0){
    append(l,x);
  } else if(length(l) > 0 && index(l) >=0){
    Node n = newNode(x);

    n->prev = l->cursor;
    n->next = l->cursor->next;
    l->cursor->next = n;
    n->next->prev = n;
    l->length++;
  }
  return;
}


//TODO: CHECK IF CURSOR IS FRONT OR BACK
void deleteFront(List l){
  if(l==NULL){
    printf("ERROR: Trying to delete front on a NULL list\n");
    exit(EXIT_FAILURE);
  }

  if(length(l) > 0 && l->front->next == NULL){
    freeNode(&(l->front));
    l->front = NULL;
    l->back = NULL;
    l->cursor = NULL;
    l->index = -1;
    l->length--;
    return;
  }

  if(length(l) > 0){
    Node tempNode = l->front;
    l->front = l->front->next;
    freeNode(&tempNode);
    l->length--;
  }
  return;
}

void deleteBack(List l){
  if(l==NULL){
    printf("ERROR: Trying to delete back on a NULL list\n");
    exit(EXIT_FAILURE);
  }

  if(length(l) > 0 && l->back->prev == NULL){
    freeNode(&(l->back));
    l->front = NULL;
    l->back = NULL;
    l->cursor = NULL;
    l->index = -1;
    l->length--;
    return;
  }

  if(length(l) > 0){
    Node tempNode = l->back;
    l->back = l->back->prev;
    freeNode(&tempNode);
    l->length--;
  }
  return;
}

void delete(List l){
  if(l==NULL){
    printf("ERROR: Trying to delete cursor element on a NULL list\n");
    exit(EXIT_FAILURE);
  }

  if(l->cursor->next == NULL && l->cursor->prev == NULL && length(l) > 0 && index(l) >= 0){
    freeNode(&(l->cursor));
    l->front = NULL;
    l->back = NULL;
    l->cursor = NULL;
    l->index = -1;
    l->length--;
  } else if(l->cursor->next == NULL && length(l) > 0 && index(l) >= 0){
    deleteBack(l);
  } else if (l->cursor->prev == NULL && length(l) > 0 && index(l) >= 0){
    deleteFront(l);
  } else if(length(l) > 0){
    Node temp = l->cursor;
    l->cursor->next->prev = l->cursor->prev;
    l->cursor->prev->next = l->cursor->next;
    freeNode(&temp);
    l->cursor = NULL;
    l->index = -1;
    l->length--;
  }
  return;
}

// Other operations -----------------------------------------------------------

void printList(FILE* out, List l){
  if(l==NULL){
    printf("ERROR: Trying to print a NULL list\n");
    exit(EXIT_FAILURE);
  }

  for(Node curr = l->front; curr != NULL; curr = curr->next){
    fprintf(out, "%d ",curr->data);
  }
  return;
}

//FIX THIS (use pre-existing functions)
List copyList(List l){
  if(l == NULL){
    printf("ERROR: Trying to copy a NULL list\n");
    exit(EXIT_FAILURE);
  }
  List newL = newList();
  for(Node curr = l->front; curr != NULL; curr = curr->next){
    append(newL, curr->data);
  }

  return newL;
}