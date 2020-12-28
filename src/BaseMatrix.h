#include "BaseData.h"

#ifndef BASE_MATRIX_H
#define BASE_MATRIX_H

#define MATRIX_SIDE_MAX 100

typedef struct BaseMatrix
{
	ElemType** data;
	int r, c;
} BaseMatrix;

BaseMatrix InitBaseMatrix(int r, int c);  // Initialize an ordinary matrix
ElemType GetBaseMatrixElem(BaseMatrix matrix, int i, int j);  // Get matrix elements
void PutBaseMatrixElem(BaseMatrix* matrix, int i, int j, int value);  // Store elements into matrices
void DisplayBaseMatrix(BaseMatrix matrix); // Display base matrix
void FreeBaseMatrix(BaseMatrix* matrix);  // Free base matrix

ElemType DeterminantMatrix(BaseMatrix matrix, int n);  // Recursively find the value of the matrix corresponding to the determinant
BaseMatrix CofactorMatrix(BaseMatrix matrix, int n);  // Find the remainder formula corresponding to each element of the matrix
BaseMatrix MatrixInverse(BaseMatrix matrix);  // Find the inverse of a matrixs

#endif // !BASE_MATRIX_H
