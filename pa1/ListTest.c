/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA1 
* List.c 
* Testing harness for List ADT
*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"

int main(void){

  List A = newList();
  List B = newList();
  List C = NULL;

  int i;

  for (i = 0; i <= 50; ++i){
    append(A, i);
  }
  for (i = 0; i <= 50; ++i){
    prepend(B, i);
  }

  C = copyList(A);
  printf("-----------------LISTS A & B-----------------\n");
  printList(stdout, A);
  printf("\n");
  printf("length A: %d\n\n",length(A));

  printList(stdout, B);
  printf("\n");
  printf("length B: %d\n", length(B));
  printf("----------------------------------------------\n");

  printf("-----------------GET A & B--------------------\n");
  for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", get(A));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", get(B));
   }
   printf("\n");
  printf("----------------------------------------------\n");

  printf("-----------------COMPARE A, B & C-------------\n");
  printf("%s\n", equals(A,B)?"true":"false");
  printf("%s\n", equals(B,C)?"true":"false");
  printf("%s\n", equals(C,A)?"true":"false");
  printf("----------------------------------------------\n");

  printf("-----------------MOVING A---------------------\n");
  moveFront(A);
  for(i=0; i<5; i++) moveNext(A); // at index 5
  insertBefore(A, -1);            // at index 6
  for(i=0; i<9; i++) moveNext(A); // at index 15
  insertAfter(A, -2);
  for(i=0; i<5; i++) movePrev(A); // at index 10
  delete(A);
  printList(stdout,A);
  printf("\n");
  printf("%d\n", length(A));
  clear(A);
  printf("%d\n", length(A));
  printf("----------------------------------------------\n");

  printf("-----------------DELETING B-------------------\n");

  deleteBack(B);
  printList(stdout, B);
  printf("\n");

  deleteFront(B);
  printList(stdout, B);
  printf("\n");

  moveFront(B);
  for(i = 0; i <= 10; ++i){
    moveNext(B);
  }
  delete(B);
  printList(stdout, B);
  printf("\n");

  clear(B);
  printList(stdout, B);
  printf("\n");

  /*
  Things to look out for:
    check delete functions and their outputs to an empty list
  */

  printf("----------------------------------------------\n");
  freeList(&A);
  freeList(&B);
  freeList(&C);
  return 0;
}