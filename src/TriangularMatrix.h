#include "BaseData.h"
#include "RLSMatrix.h"

#ifndef TRIANGULAR_MATRIX_H
#define TRIANGULAR_MATRIX_H

typedef struct TriangularMatrix  // Triangular matrix storage structure
{
    ElemType* data;
    int r, c, isTop;
} TriangularMatrix;

int GetTrianglularMatrixElemPos(int i, int j, int isTop);  // Get the position of a matrix element in a one-dimensional array
TriangularMatrix CreateTriangularMatrix();  // Create a triangular matrix
void FreeTriangularMatrix(TriangularMatrix* matrix);  // Free a Triangular matrix
RLSMatrix TriangularMatrix2RLSMatrix(TriangularMatrix matrix);  // Triangular matrix to RLSMatrix
BaseMatrix TriangularMatrix2BaseMatrix(TriangularMatrix matrix);  // Triangular matrix to base matrix


#endif // !TRIANGULAR_MATRIX_H

