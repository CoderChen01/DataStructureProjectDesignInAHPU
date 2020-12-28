#include "BaseData.h"
#include "RLSMatrix.h"

#ifndef DIAGONAL_MATRIX_H
#define DIAGONAL_MATRIX_H

typedef struct DiagonalMatrix  // Diagonal matrix storage structure
{
    ElemType* data;
    int r, c, t;
} DiagonalMatrix;


DiagonalMatrix CreateDiagonalMatrix();  // Create a diagonal matrix
DiagonalMatrix CreateIdentityMatrix();  // Create an identity matrix
RLSMatrix DiagonalMatrix2RLSMatrix(DiagonalMatrix matrix);  // Diagonal matrix to RLSMatrix

#endif // !DiagonalMatrix

