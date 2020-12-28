#include "BaseData.h"
#include "RLSMatrix.h"

#ifndef SYMMETRIC_MATRIX_H
#define SYMMETRIC_MATRIX_H

typedef struct SymmetricMatrix  // Symmetric matrix storage structure
{
    ElemType* data;
    int r, c, t;
} SymmetricMatrix;

SymmetricMatrix CreateSymmetricMatrix();  // Create a symmetric matrix
RLSMatrix SymmetricMatrix2RLSMatrix(SymmetricMatrix matrix);  // Symmetric matrix to RLSMatrix

#endif // !DiagonalMatrix
