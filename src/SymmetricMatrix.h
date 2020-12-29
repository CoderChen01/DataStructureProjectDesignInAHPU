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
void FreeSymmetricMatrix(SymmetricMatrix* matrix);  // Free a symmetric matrix
SymmetricMatrix CreateSymmetricMatrix();  // Create a symmetric matrix
RLSMatrix SymmetricMatrix2RLSMatrix(SymmetricMatrix matrix);  // Symmetric matrix to RLSMatrix
BaseMatrix SymmetricMatrix2BaseMatrix(SymmetricMatrix matrix);  // Symmetric matrix to base matrix

#endif // !DiagonalMatrix
