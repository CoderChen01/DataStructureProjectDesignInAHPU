#include <stdio.h>
#include <stdlib.h>

#include "TriangularMatrix.h"
#include "RLSMatrix.h"
#include "BaseData.h"
#include "BaseFlag.h"

TriangularMatrix CreateTriangularMatrix()  // Create a triangular matrix
{
	TriangularMatrix a = {
		.data = NULL,
		.c = 0,
		.r = 0,
		.t = 0,
		.isTop = 0
	};
	return a;
}


RLSMatrix TriangularMatrix2RLSMatrix(TriangularMatrix matrix)  // Triangular matrix to RLSMatrix
{
	RLSMatrix a = {
		.data = NULL,
		.rpos = NULL,
		.c = 0,
		.r = 0,
		.t = 0
	};
	return a;
}
