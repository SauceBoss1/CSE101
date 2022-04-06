/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA1 
* List.c 
* Implementation for the List ADT 
*********************************************************************************/


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

/*
newNode(int data)
creates a new Node and returns the new node
*/
Node newNode(int data){
  Node N = malloc(sizeof(NodeObj));
  N->data = data;
  N->next = NULL;
  N->prev = NULL;
  return(N);
}

/*
freeNode(Node* pN)
"deletes" and free a given node
*/
void freeNode(Node* pN){
  if( pN != NULL && *pN != NULL){
    free(*pN);
    *pN=NULL;
  }
}

/*
newList()
Creates a new list and returns it
*/
List newList(void){
  List L = malloc(sizeof(ListObj));
  L->cursor = L->front = L->back = NULL;
  L->length = 0;
  L->index = -1;
  return L;
}

/*
freeList(List* pL)
"Deletes" and frees a list

The implementation is similar to that of the Queue example
given to us by prof. Tantalo
*/
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

/*
length(List l)
Returns the length of a list

Pre: l == NULL
*/
int length(List l){
  if(l == NULL){
    printf("ERROR: Checking the length of a NULL list.\n");
    exit(EXIT_FAILURE);
  }
  return l->length;
}

/*
index(List l)
Returns the index of the list

index = -1 if undefined
Pre: l == NULL
*/
int index(List l){
  if(l == NULL){
    printf("ERROR: Checking the index of a NULL list.\n");
    exit(EXIT_FAILURE);
  }
  return l->index;
}

/*
front(list l)
Returns the front element

Pre: l == NULL & length < 0
*/
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

/*
back(List l)
Returns the back element

Pre: l == NULL & length < 0
*/
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

/*
get(List l)
Returns the element that is currently at the cursor

Pre: l == NULL & length < 0
*/
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

/*
equals(List A, List B)
Deteremines where or not two lists are equal or not

Pre: A == NULL or B == NULL
*/
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

/*
clear(List l)
Resets the list to its empty state

Pre: l == NULL
*/
void clear(List l){
  if(l == NULL){
    printf("ERROR: Clearing a NULL list.\n");
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

/*
set(List l, int x)
Replaces the cursors data with x

Pre: l == NULL & length < 0
*/
void set(List l, int x){
  if(l == NULL){
    printf("ERROR: Setting an element of a NULL list\n");
    exit(EXIT_FAILURE);
  }
  if (length(l) < 0 ){ 
    printf("ERROR: Setting an element to an empty list.\n");
    exit(EXIT_FAILURE);
  }

  if(index(l) != -1){
    l->cursor->data = x;
  }
  return;
}

/*
moveFront(List l)
Moves the cursor to the front

Pre: l == NULL
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

/*
moveBack(List l)
Moves the cursor to the front

Pre: l == NULL
*/
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

/*
movePrev(List l)
Moves the cursor to the previous element

Pre: l == NULL
*/
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

/*
moveNext(List l)
Moves the cursor to the next element

Pre: l == NULL
*/
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

/*
prepend(List l, int x)
Adds a new element to the beginning of the list

Pre: l == NULL
*/
void prepend(List l, int x){
  if(l==NULL){
    printf("ERROR: Trying to prepend to a NULL list\n");
    exit(EXIT_FAILURE);
  }
  
  Node n = newNode(x);
  if(l->front == NULL && l->back==NULL && length(l) == 0){ //if we are adding to an empty list
    l->front = n;
    l->back = n;
    l->length++;
  } else {
    l->front->prev = n;
    n->next = l->front;
    l->front = n;
    l->length++;
  }
  if(index(l) >= 0 ){
    l->index++;
  }
  return;
}

/*
append(List l, int x)
Adds a new element to the end of the list

Pre: l == NULL
*/
void append(List l, int x){
  if(l==NULL){
    printf("ERROR: Trying to append to a NULL list\n");
    exit(EXIT_FAILURE);
  }

  Node n = newNode(x);
  if(l->front == NULL && l->back == NULL && length(l) == 0){ //if the list is empty
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

/*
insertBefore(List l, int x)
Inserts a new element before the cursor

Pre: l == NULL & length < 0 & index == -1
*/
void insertBefore(List l, int x){
  if(l==NULL){
    printf("ERROR: Trying to insert before cursor on a NULL list\n");
    exit(EXIT_FAILURE);
  }

  if(length(l) < 0){
    printf("ERROR: Inserting to an empty list\n");
    exit(EXIT_FAILURE);
  }

  if(index(l) == -1){
    printf("ERROR: Inserting to an undefined cursor\n");
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

/*
insertAfter(List l, int x)
Inserts a new element after the cursor

Pre: l == NULL & length < 0 & index == -1
*/
void insertAfter(List l, int x){
  if(l==NULL){
    printf("ERROR: Trying to insert after cursor on a NULL list\n");
    exit(EXIT_FAILURE);
  }

  if(length(l) < 0){
    printf("ERROR: Inserting to an empty list\n");
    exit(EXIT_FAILURE);
  }

  if(index(l) == -1){
    printf("ERROR: Inserting to an undefined cursor\n");
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

/*
deleteFront(List l)
deletes the front element

Pre: l==NULL & length < 0
*/
void deleteFront(List l){
  if(l==NULL){
    printf("ERROR: Trying to delete front on a NULL list\n");
    exit(EXIT_FAILURE);
  }
  if(length(l) < 0){
    printf("ERROR: Deleting the front element of an empty list\n");
    exit(EXIT_FAILURE);
  }

  if(index(l) == 0){
    l->cursor = NULL;
    l->index = -1;
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
    l->front->prev = NULL;
    freeNode(&tempNode);
    l->length--;
    if(index(l) != -1){
      l->index--;
    }
  }
  return;
}

/*
deleteBack(List l)
deletes the back element

Pre: l==NULL & length < 0
*/
void deleteBack(List l){
  if(l==NULL){
    printf("ERROR: Trying to delete back on a NULL list\n");
    exit(EXIT_FAILURE);
  }
  if(length(l) < 0){
    printf("ERROR: Deleting the back element of an empty list\n");
    exit(EXIT_FAILURE);
  }

  if(index(l) == length(l) - 1){
    l->cursor = NULL;
    l->index = -1;
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
    l->back->next = NULL;
    freeNode(&tempNode);
    l->length--;
  }
  return;
}

/*
delete(List l)
Deletes the element at the cursor

Pre: l==NULL & length < 0 & index < 0
*/
void delete(List l){
  if(l==NULL){
    printf("ERROR: Trying to delete cursor element on a NULL list\n");
    exit(EXIT_FAILURE);
  }
  if(length(l) < 0){
    printf("ERROR: Deleting the back element of an empty list\n");
    exit(EXIT_FAILURE);
  }
  
  if(l->cursor == NULL){
    fprintf(stderr, "ERROR: Can't delete a null cursor\n");
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
    l->cursor = NULL;
    l->index = -1;
  } else if (l->cursor->prev == NULL && length(l) > 0 && index(l) >= 0){
    deleteFront(l);
    l->cursor = NULL;
    l->index = -1;
  } else if(length(l) > 0 && l->cursor != NULL){
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

/*
printList(FILE* out, List l)
Prints the List to out

Pre: l==NULL
*/
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

/*
copyList(List l)
Copys the items of List l and returns a new list

Pre: l == NULL
*/
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