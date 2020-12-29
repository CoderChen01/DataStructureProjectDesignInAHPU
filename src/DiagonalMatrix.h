#include "BaseData.h"
#include "RLSMatrix.h"

#ifndef DIAGONAL_MATRIX_H
#define DIAGONAL_MATRIX_H

typedef struct DiagonalMatrix  // Diagonal matrix storage structure
{
    ElemType* data;
    int t;
} DiagonalMatrix;


DiagonalMatrix CreateDiagonalMatrix();  // Create a diagonal matrix
void FreeDiagonalMatrix(DiagonalMatrix* matrix);  // Free a diagonal matrix
RLSMatrix DiagonalMatrix2RLSMatrix(DiagonalMatrix matrix);  // Diagonal matrix to RLSMatrix
BaseMatrix DiagonalMatrix2BaseMatrix(DiagonalMatrix matrix);  // Diagonal matrix 2 base matrix

#endif // !DiagonalMatrix

