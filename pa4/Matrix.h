#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"

/***  EXPORTED DATA TYPES ***/

typedef struct MatrixObj* Matrix;

/***  CONSTRUCTOR-DESTRUCTORS ***/

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n);

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM);

/***  ACCESS FUNCTIONS ***/

// size()
// Return the size of square Matrix M.
int size(Matrix M);
// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M);
// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B);