#pragma warning( disable : 6386 )
#pragma warning( disable : 6385 )
#include <stdio.h>
#include <stdlib.h>

#include "SymmetricMatrix.h"
#include "RLSMatrix.h"
#include "BaseData.h"
#include "BaseFlag.h"


int GetSymmetricMatrixElemPos(int i, int j)  // Get the position of a matrix element in a one-dimensional array
{
	/*
	If the column index is greater than the row index, 
	the element is an upper triangular element
	*/
	if (j >= i)
	{
		return j * (j - 1) / 2 + i;
	}

	return i * (i - 1) / 2 + j;
}


SymmetricMatrix CreateSymmetricMatrix()  // Create a symmetric matrix;
{
	SymmetricMatrix res = {
		.data = NULL,
		.c = 0,
		.r = 0
	};

	int retval = 0;

	int r = 0;
	while (TRUE)
	{
		printf_s("\nPlease enter the number of sides of the matrix(eg: 4): ");
		retval = scanf_s("%d", &r);
		flush();

		if (retval < 1)
		{
			printf_s("\033[41;33m\nInput error,"
				"please enter again\n\033[0m");
			continue;
		}

		if (r <= 1)
		{
			printf_s("\033[41;33m\nInput data is illegal,"
				"please enter again\n\033[0m");
			continue;
		}

		if (r > MATRIX_SIDE_MAX)
		{

			printf_s("\033[41;33m\nOut of range,"
				"please enter again\n\033[0m");
			continue;
		}

		break;
	}
	res.r = res.c = r;

	res.data = (ElemType*)malloc(sizeof(ElemType) * (r * (r + 1) / 2 + 1));
	res.data[0] = 0;

	int pos = 0;
	ElemType data = 0;
	int i = 0;
	int j = 0;
	
	for (i = 1; i <= r; i++)
	{
		for (j = 1; j <= i; j++)
		{
			while (TRUE)
			{
				printf_s("\nPlease enter the element with coordinates (%d,%d) (eg: 4): ", i, j);
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

			pos = GetSymmetricMatrixElemPos(i, j);
			res.data[pos] = data;
		}
	}
	

	printf_s("\033[42m\nSymmetric matrix input completed\n\033[0m");

	return res;
}


void FreeSymmetricMatrix(SymmetricMatrix* matrix)  // Free a symmetric matrix
{
	free(matrix->data);
}


RLSMatrix SymmetricMatrix2RLSMatrix(SymmetricMatrix matrix)  // Symmetric matrix to RLSMatrix
{
	RLSMatrix res = {
		.data = NULL,
		.rpos = NULL,
		.c = 0,
		.r = 0,
		.t = 0
	};

	res.r = matrix.r;
	res.c = matrix.c;
	res.rpos = (int*)malloc(sizeof(int) * (res.r + 1));
	res.rpos[0] = 0;

	int i = 0,
		j = 0,
		t = 0,
		tmp = 0,
		zeroNum = 0,
		pos = 0;

	tmp = matrix.r * matrix.c;
	/*
	Find the number of zero elements
	to facilitate the allocation of memory below
	*/
	for (i = 1; i <= matrix.r; i++)
	{
		for (j = 1; j <= matrix.c; j++)
		{
		    if (!matrix.data[GetSymmetricMatrixElemPos(i, j)])
			{
				zeroNum++;
			}
		}
	}

	res.t = tmp - zeroNum;
	res.data = (Triple*)malloc(sizeof(Triple) * (res.t + 1));

	for (i = 1; i <= matrix.r; i++)
	{
		/*
		If this condition is true,
		it means that the elements of row i-1 are all 0
		*/
		if (res.rpos[i - 1] == t + 1)
		{
			res.rpos[i - 1] = 0;
		}
		res.rpos[i] = t + 1;
		for (j = 1; j <= matrix.c; j++)
		{
			pos = GetSymmetricMatrixElemPos(i, j);
			if (!matrix.data[pos])
			{
				continue;
			}
			res.data[++t].e = matrix.data[pos];
			res.data[t].i = i;
			res.data[t].j = j;
		}
	}

	return res;
}


BaseMatrix SymmetricMatrix2BaseMatrix(SymmetricMatrix matrix)  // Symmetric matrix to base matrix
{
	BaseMatrix res = InitBaseMatrix(matrix.r, matrix.c);

	int i = 0,
		j = 0,
		pos = 0;

	for (i = 1; i <= matrix.r; i++)
	{
		for (j = 1; j <= matrix.c; j++)
		{
			pos = GetTrianglularMatrixElemPos(i, j);
			PutBaseMatrixElem(&res, i, j, matrix.data[pos]);
		}
	}
	
	return res;
}
