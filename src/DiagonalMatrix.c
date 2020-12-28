#include <stdio.h>
#include <stdlib.h>

#include "DiagonalMatrix.h"
#include "RLSMatrix.h"
#include "BaseData.h"
#include "BaseFlag.h"



DiagonalMatrix CreateDiagonalMatrix()  // Create a diagonal matrix
{
	DiagonalMatrix matrix = {
		.data = NULL,
		.c = 0,
		.r = 0,
		.t = 0
	};
	return matrix;
}


DiagonalMatrix CreateIdentityMatrix()  // Create an identity matrix
{
	DiagonalMatrix a = {
		.data = NULL,
		.c = 0,
		.r = 0,
		.t = 0
	};
	return a;
}


RLSMatrix DiagonalMatrix2RLSMatrix(DiagonalMatrix matrix)  // Diagonal matrix to RLSMatrix
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

