#pragma warning( disable : 6386 )
#pragma warning( disable : 6385 )
#include <stdio.h>
#include <stdlib.h>

#include "DiagonalMatrix.h"
#include "BaseMatrix.h"
#include "RLSMatrix.h"
#include "BaseData.h"
#include "BaseFlag.h"
#include "flush.h"


DiagonalMatrix CreateDiagonalMatrix(int isIdentity)  // Create a diagonal matrix
{
	int retval = 0;

	DiagonalMatrix matrix = {
		.data = NULL,
		.t = 0
	};

	int t = 0;
	while (TRUE)
	{
		printf_s("\nPlease enter the number of elements(eg: 4): ");
		retval = scanf_s("%d", &t);
		flush();

		if (retval < 1)
		{
			printf_s("\033[41;33m\nInput error,"
				"please enter again\n\033[0m");
			continue;
		}

		if (t <= 1)
		{
			printf_s("\033[41;33m\nInput data is illegal,"
				"please enter again\n\033[0m");
			continue;
		}

		if (t > MATRIX_SIDE_MAX)
		{

			printf_s("\033[41;33m\nOut of range,"
				"please enter again\n\033[0m");
			continue;
		}

		break;
	}

	matrix.t = t;
	matrix.data = (ElemType*)malloc(sizeof(ElemType) * (t + 1));
	matrix.data[0] = 0;

	int i = 0;
	if (isIdentity)
	{
		for (i = 0; i <= t; i++)
		{
			matrix.data[i] = 1;
		}

		return matrix;
	}

	ElemType data = 0;

	for (i = 1; i <= t; i++)
	{
		while (TRUE)
		{
			printf_s("\nPlease enter the \033[31m%dth\033[0m element(eg: 2): ", i);
			retval = scanf_s("%lf", &data);
			flush();

			if (retval < 1)
			{
				printf_s("\033[41;33m\nInput error,"
					"please enter again\n\033[0m");
				continue;
			}

			break;
		}
		matrix.data[i] = data;
	}

	printf_s("\033[42m\nDiagonal matrix input completed\n\033[0m");
	return matrix;
}


void FreeDiagonalMatrix(DiagonalMatrix* matrix)  // Free a diagonal matrix
{
	free(matrix->data);
}


RLSMatrix DiagonalMatrix2RLSMatrix(DiagonalMatrix matrix)  // Diagonal matrix to RLSMatrix
{
	RLSMatrix res = {
		.data = NULL,
		.rpos = NULL,
		.c = 0,
		.r = 0,
		.t = 0
	};

	res.r = res.c = matrix.t;
	res.rpos = (int*)malloc(sizeof(int) * (matrix.t + 1));
	res.rpos[0] = 0;

	int t = 0;
	int tmp = 0;
	int zeroNum = 0;
	for (t = 1; t <= matrix.t; t++)
	{
		if (!matrix.data[t])
		{
			zeroNum++;
		}
	}

	res.t = matrix.t - zeroNum;
	res.data = (Triple*)malloc(sizeof(Triple) * (res.t + 1));
	res.data[0].i = 0;
	res.data[0].j = 0;
	res.data[0].e = 0;

	for (t = 1; t <= matrix.t; t++)
	{
		if (!matrix.data[t])
		{
			res.rpos[t] = 0;
			continue;
		}
		res.data[++tmp].e = matrix.data[t];  // Filter zero elements
		res.data[tmp].i = t;
		res.data[tmp].j = t;
		
		res.rpos[t] = tmp;
	}

	return res;
}


BaseMatrix DiagonalMatrix2BaseMatrix(DiagonalMatrix matrix)  // Diagonal matrix 2 base matrix
{
	BaseMatrix res = InitBaseMatrix(matrix.t, matrix.t);

	int i = 0,
		j = 0;

	for (i = 1; i <= matrix.t; i++)
	{
		for (j = 1; j <= matrix.t; j++)
		{
			if (i == j)
			{
				PutBaseMatrixElem(&res, i, j, matrix.data[i]);
				continue;
			}
			PutBaseMatrixElem(&res, i, j, 0);
		}
	}

	return res;
}
