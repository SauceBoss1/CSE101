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
  
  // INPUT ARRAY ---------------------------------------------------
  fseek(in, 0, SEEK_SET);

  //TODO
  //remember to free all the elements and then free the array
  char **file_lines = malloc(line_count * sizeof(char *));
  if (file_lines == NULL){
    printf("ERROR: Unable to create an array for the input file\n");
    return EXIT_FAILURE;
  }

  for(int i = 0; i < line_count; ++i){
    char buffer[MAX_LEN];
    char* line;

    if(fgets(buffer, MAX_LEN, in) == NULL){
      printf("ERROR: null at fgets()\n");
      return EXIT_FAILURE;
    }

    if((line = strtok(buffer, "\n")) == NULL){
      line = "";
    }
    file_lines[i] = malloc(strlen(line) + 1);
    strcpy(file_lines[i], line); //there are some valgrind errors here
    //printf("%s\n",file_lines[i]);
  }
  

  // List Sorting ---------------------------------------------------
  List final_list = newList();
  prepend(final_list, 0);

  for(int i = 1; i < line_count; ++i){
    int prev_list_len = length(final_list);
    for(moveFront(final_list); index(final_list) >= 0 && prev_list_len == length(final_list); moveNext(final_list)){
      if (strcmp(file_lines[i], file_lines[get(final_list)]) < 0){
        insertBefore(final_list, i);
      }
    }

    int updated_list_len = length(final_list);

    //check if the current index is bigger than the last element of the list
    if(prev_list_len == updated_list_len && strcmp(file_lines[i], file_lines[back(final_list)]) > 0){
      append(final_list, i);
    }
  }

  // OUTPUTTING RESULTS --------------------------------------------

  for(moveFront(final_list); index(final_list) >=0; moveNext(final_list)){
    fprintf(out, "%s\n", file_lines[get(final_list)]);
  }


  // CLOSING PROCEDURES --------------------------------------------

  for(int i = 0; i < line_count; i++){
    free(file_lines[i]);
    file_lines[i] = NULL;
  }

  free(file_lines);
  file_lines = NULL;

  freeList(&final_list);

  fclose(in);
  fclose(out);

  return EXIT_SUCCESS;
}