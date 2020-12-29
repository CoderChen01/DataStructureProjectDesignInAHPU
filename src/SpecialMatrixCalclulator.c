#pragma warning( disable : 6386 )
#pragma warning( disable : 6385 )
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
	SymmetricMatrix matrix1 = CreateSymmetricMatrix();
	SymmetricMatrix matrix2 = CreateSymmetricMatrix();

	//BaseMatrix matrix3 = TriangularMatrix2BaseMatrix(matrix1);
	//BaseMatrix matrix4 = TriangularMatrix2BaseMatrix(matrix2);

	//DisplayBaseMatrix(matrix3);
	//DisplayBaseMatrix(matrix4);
	RLSMatrix matrix3 = SymmetricMatrix2RLSMatrix(matrix1);
	RLSMatrix matrix4 = SymmetricMatrix2RLSMatrix(matrix2);
	//RLSMatrix matrix3 = CreateRLSMatrix();
	//RLSMatrix matrix4 = CreateRLSMatrix();

	DisplayRLSMatrix(matrix3);
	DisplayRLSMatrix(matrix4);

	RLSMatrix matrix5 = MultiRLSMatrix(matrix3, matrix4);
	DisplayRLSMatrix(matrix5);

	//FreeTriangularMatrix(&matrix1);
	//FreeTriangularMatrix(&matrix2);

	//RLSMatrix matrix3 = DiagonalMatrix2RLSMatrix(matrix1);
	//RLSMatrix matrix4 = DiagonalMatrix2RLSMatrix(matrix2);

	//DisplayRLSMatrix(matrix3);
	//DisplayRLSMatrix(matrix4);


	//RLSMatrix matrix5 = MultiRLSMatrix(matrix3, matrix4);

	//BaseMatrix matrix2 = DiagonalMatrix2BaseMatrix(matrix1);

	//DisplayRLSMatrix(matrix5);
	//BaseMatrix res = MatrixInverse(matrix2);

	//DisplayBaseMatrix(res);

	return 0;
}