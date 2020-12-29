#pragma warning( disable : 6386 )
#include <stdio.h>
#include <stdlib.h>

#include "SymmetricMatrix.h"
#include "RLSMatrix.h"
#include "BaseData.h"
#include "BaseFlag.h"


SymmetricMatrix CreateSymmetricMatrix()  // Create a symmetric matrix;
{
	SymmetricMatrix a = {
		.data = NULL,
		.c = 0,
		.r = 0,
		.t = 0
	};
	return a;
}


RLSMatrix SymmetricMatrix2RLSMatrix(SymmetricMatrix matrix)  // Symmetric matrix to RLSMatrix
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

