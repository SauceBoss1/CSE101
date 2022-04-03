/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA1 
* List.c 
* Implementation for the Lex program 
*********************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"

#define MAX_LEN 1024

int main(int argc, char * argv[]){
  FILE *in, *out;
  int line_count;
  char line[MAX_LEN];
  
  // ARGUMENT PARSER ------------------------------------------------

  if(argc != 3){
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  in = fopen(argv[1], "r");
  if(in == NULL){
    printf("ERROR: Unable to open file: %s for reading\n",argv[1]);
    return EXIT_FAILURE;
  }

  out = fopen(argv[2], "w");
  if(out == NULL){
    printf("ERROR: Unable to open file: %s for writing\n",argv[2]);
    return EXIT_FAILURE;
  }
  
  // LINE COUNTER --------------------------------------------------
  line_count = 0;
  while( fgets(line, MAX_LEN, in) != NULL){
    line_count++;
  }
  

  fclose(in);
  fclose(out);

  return EXIT_SUCCESS;
}