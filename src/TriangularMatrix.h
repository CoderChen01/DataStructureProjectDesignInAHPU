#include "BaseData.h"
#include "RLSMatrix.h"

#ifndef TRIANGULAR_MATRIX_H
#define TRIANGULAR_MATRIX_H

typedef struct TriangularMatrix  // Triangular matrix storage structure
{
    ElemType* data;
    int r, c, t, isTop;
} TriangularMatrix;

TriangularMatrix CreateTriangularMatrix();  // Create a triangular matrix
RLSMatrix TriangularMatrix2RLSMatrix(TriangularMatrix matrix);  // Triangular matrix to RLSMatrix

#endif // !TRIANGULAR_MATRIX_H

