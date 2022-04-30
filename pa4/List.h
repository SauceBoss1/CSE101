/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA4 
* List.h 
* Header file for the List ADT 
*********************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#pragma once

// Exported Types -------------------------------------------------------------

typedef struct ListObj* List;
typedef void* ListElement;

// Constructors-Destructors ---------------------------------------------------

List newList(void);
void freeList(List* pL);

// Access functions -----------------------------------------------------------

int length(List l);
int index(List l);
ListElement front(List l);
ListElement back(List l);
ListElement get(List l);

// Manipulation procedures ----------------------------------------------------

void clear(List l);
void set(List l, ListElement x);
void moveFront(List l);
void moveBack(List l);
void movePrev(List l);
void moveNext(List l);
void prepend(List l, ListElement x);
void append(List l, ListElement x);
void insertBefore(List l, ListElement x);
void insertAfter(List l, ListElement x);

void deleteFront(List l);
void deleteBack(List l);
void delete(List l);

// Other operations -----------------------------------------------------------