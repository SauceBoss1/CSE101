/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA4
* ListTest.c 
* Main test harness for the modified List ADT
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"

typedef int ListEle;

/**
 * printList()
 * Custom printList function for test harness
 */
void printList(List L){
   for(moveFront(L); index(L) >=0; moveNext(L)){
      printf("%d ", *(ListEle *)get(L));
   }
   printf("\n");
   return;
}

int main(void){
   List A,B;
   A = newList(); B = newList();

   ListEle X[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

   for(int i = 1; i < 21; ++i){
      append(A,&X[i]);
      prepend(B,&X[i]);
   }
   printList(A);
   printList(B);
   printf("Length of A: %d\n", length(A));
   printf("Length of B: %d\n", length(B));

   for(moveFront(A); index(A) <= 10; moveNext(A)){
      printf("index(A) = %d, element: %d\n", index(A), *(ListEle *)get(A));
   }

   printf("Front of B: %d\n", *(ListEle *)front(B));
   printf("Front of B: %d\n", *(ListEle *)back(B));


   freeList(&A);
   freeList(&B);
   return EXIT_SUCCESS;
}
