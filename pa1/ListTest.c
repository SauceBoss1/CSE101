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
  printList(stdout, B);
  printf("\n");
  printf("----------------------------------------------\n");

  freeList(&A);
  freeList(&B);
  freeList(&C);
  return 0;
}