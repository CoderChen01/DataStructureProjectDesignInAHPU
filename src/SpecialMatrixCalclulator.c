#include <stdio.h>
#include <stdlib.h>

#include "BaseData.h"
#include "BaseFlag.h"
#include "RLSMatrix.h"
#include "BaseMatrix.h"
#include "DiagonalMatrix.h"
#include "TriangularMatrix.h"
#include "SymmetricMatrix.h"


int main()
{
	DiagonalMatrix matrix1 = CreateDiagonalMatrix();

	BaseMatrix matrix2 = RLSMatrix2BaseMatrix(matrix1);


	BaseMatrix res = MatrixInverse(matrix2);

	DisplayBaseMatrix(res);

	return 0;
}