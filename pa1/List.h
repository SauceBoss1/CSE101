/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA1 
* List.h 
* Header file for the List ADT 
*********************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#pragma once

// Exported Types -------------------------------------------------------------

typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------

List newList(void);
void freeList(List* pL);

// Access functions -----------------------------------------------------------

int length(List l);
int index(List l);
int front(List l);
int back(List l);
int get(List l);
bool equals(List A, List B);

// Manipulation procedures ----------------------------------------------------

void clear(List l);
void set(List l, int x);
void moveFront(List l);
void moveBack(List l);
void movePrev(List l);
void moveNext(List l);
void prepend(List l, int x);
void append(List l, int x);
void insertBefore(List l, int x);
void insertAfter(List l, int x);

void deleteFront(List l);
void deleteBack(List l);
void delete(List l);

// Other operations -----------------------------------------------------------

void printList(FILE* out, List l);
List copyList(List l);