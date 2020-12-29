#include "BaseData.h"
#include "BaseMatrix.h"

#ifndef RTSMATRIX_H
#define RTSMATRIX_H

#define MAXSIZE 100

typedef struct Triple  // Triples for storing sparse matrix elements
{
	int i, j;
	ElemType e;
} Triple;

typedef struct RLSMatrix  // Row logical link matrix
{
	Triple* data;
	int* rpos;
	int r, c, t;
} RLSMatrix;

RLSMatrix CreateRLSMatrix();  // Create a row logical link matrix
void DisplayRLSMatrix(RLSMatrix matrix);  // Format sparse matrix output
void FreeRLSMatrix(RLSMatrix* matrix);  // Free a RLSMatrix
RLSMatrix FastTransposeRLSMatrix(RLSMatrix matrix);  // Use fast transpose algorithm
RLSMatrix MultiRLSMatrix(RLSMatrix A, RLSMatrix B);  // A and B matrix multiplication
RLSMatrix AddRLSMatrix(RLSMatrix A, RLSMatrix B);  // Add A and B
RLSMatrix SubRLSMatrix(RLSMatrix A, RLSMatrix B);  // Subtract A and B
BaseMatrix RLSMatrix2BaseMatrix(RLSMatrix matrix);  // Convert row logical link matrix to normal matrix

#endif // !RTSMATRIX_H

