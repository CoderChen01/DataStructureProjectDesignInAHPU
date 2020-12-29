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
	DiagonalMatrix matrix1 = CreateDiagonalMatrix(FALSE);
	DiagonalMatrix matrix2 = CreateDiagonalMatrix(TRUE);

	RLSMatrix matrix3 = DiagonalMatrix2RLSMatrix(matrix1);
	RLSMatrix matrix4 = DiagonalMatrix2RLSMatrix(matrix2);

	DisplayRLSMatrix(matrix3);
	DisplayRLSMatrix(matrix4);


	RLSMatrix matrix5 = MultiRLSMatrix(matrix3, matrix4);

	//BaseMatrix matrix2 = DiagonalMatrix2BaseMatrix(matrix1);

	DisplayRLSMatrix(matrix5);
	//BaseMatrix res = MatrixInverse(matrix2);

	//DisplayBaseMatrix(res);

	return 0;
}