#pragma warning( disable : 6386 )
#include <stdio.h>
#include <stdlib.h>

#include "TriangularMatrix.h"
#include "BaseMatrix.h"
#include "RLSMatrix.h"
#include "BaseData.h"
#include "BaseFlag.h"
#include "flush.h"


int GetTrianglularMatrixElemPos(int i, int j, int isTop)  // Get the position of a matrix element in a one-dimensional array
{
	if (isTop)
	{
		return j * (j - 1) / 2 + i;
	}

	return i * (i - 1) / 2 + j;
}


TriangularMatrix CreateTriangularMatrix()  // Create a triangular matrix
{
	int retval = 0;
	TriangularMatrix res = {
		.data = NULL,
		.c = 0,
		.r = 0,
		.isTop = 0
	};

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

	int isTop = 0;
	while (TRUE)
	{
		printf_s("\nWhether it is an upper triangular matrix (y/N): ");
		char input = getchar();
		flush();

		if ('y' == input || '\n' == input)
		{
			isTop = 1;
		}
		else if ('N' == input)
		{
			isTop = 0;
		}
		else
		{
			printf_s("\033[41;33m\nInput error,"
				"please enter again\n\033[0m");
			continue;
		}

		break;
	}
	res.isTop = isTop;

	int pos = 0;
	ElemType data = 0;
	int i = 0;
	int j = 0;

	if (isTop)
	{
		for (i = 1; i <= r; i++)
		{
			for (j = i; j <= r; j++)
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

					if (!data)
					{
						printf_s("\033[41;33m\nInput data is illegal,"
							"please enter again\n\033[0m");
						continue;
					}
					
					break;
				}

				pos = GetTrianglularMatrixElemPos(i, j, isTop);
				res.data[pos] = data;
			}
		}
	}
	else
	{
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

					if (!data)
					{
						printf_s("\033[41;33m\nInput data is illegal,"
							"please enter again\n\033[0m");
						continue;
					}

					break;
				}

				pos = GetTrianglularMatrixElemPos(i, j, isTop);
				res.data[pos] = data;
			}
		}
	}

	printf_s("\033[42m\nTriangular matrix input completed\n\033[0m");
	return res;
}


void FreeTriangularMatrix(TriangularMatrix* matrix)  // Free a Triangular matrix
{
	free(matrix->data);
}


RLSMatrix TriangularMatrix2RLSMatrix(TriangularMatrix matrix)  // Triangular matrix to RLSMatrix
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
	res.t = ((matrix.r * matrix.c) + matrix.r) / 2;
	res.data = (Triple*)malloc(sizeof(Triple) * (res.t + 1));
	res.rpos = (int*)malloc(sizeof(int) * (res.r + 1));

	int i = 0,
		j = 0,
		t = 0,
		pos = 0;
	if (matrix.isTop)
	{
		for (i = 1; i <= matrix.r; i++)
		{
			res.rpos[i] = t + 1;
			for (j = i; j <= matrix.c; j++)
			{
				pos = GetTrianglularMatrixElemPos(i, j, TRUE);
				res.data[++t].e = matrix.data[pos];
				res.data[t].i = i;
				res.data[t].j = j;
			}
		}
	}
	else
	{
		for (i = 1; i <= matrix.r; i++)
		{
			res.rpos[i] = t + 1;
			for (j = 1; j <= i; j++)
			{
				pos = GetTrianglularMatrixElemPos(i, j, TRUE);
				res.data[++t].e = matrix.data[pos];
				res.data[t].i = i;
				res.data[t].j = j;
			}
		}
	}

	return res;
}


BaseMatrix TriangularMatrix2BaseMatrix(TriangularMatrix matrix)  // Triangular matrix to base matrix
{
	BaseMatrix res = InitBaseMatrix(matrix.r, matrix.c);

	int i = 0,
		j = 0,
		pos = 0;

	if (matrix.isTop)
	{
		for (i = 1; i <= matrix.r; i++)
		{
			for (j = i; j <= matrix.c; j++)
			{
				pos = GetTrianglularMatrixElemPos(i, j, TRUE);
				PutBaseMatrixElem(&res, i, j, matrix.data[pos]);
			}
		}
	}
	else
	{
		for (i = 1; i <= matrix.r; i++)
		{
			for (j = 1; j <= i; j++)
			{
				pos = GetTrianglularMatrixElemPos(i, j, FALSE);
				PutBaseMatrixElem(&res, i, j, matrix.data[pos]);
			}
		}
	}

	return res;
}
