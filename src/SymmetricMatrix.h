#include "BaseData.h"
#include "RLSMatrix.h"

#ifndef SYMMETRIC_MATRIX_H
#define SYMMETRIC_MATRIX_H

typedef struct SymmetricMatrix  // Symmetric matrix storage structure
{
    ElemType* data;
    int r, c;
} SymmetricMatrix;


int GetSymmetricMatrixElemPos(int i, int j);  // Get the position of a matrix element in a one-dimensional array
SymmetricMatrix CreateSymmetricMatrix();  // Create a symmetric matrix
RLSMatrix SymmetricMatrix2RLSMatrix(SymmetricMatrix matrix);  // Symmetric matrix to RLSMatrix

#endif // !DiagonalMatrix
