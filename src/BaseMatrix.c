#include <stdio.h>
#include <stdlib.h>

#include "BaseMatrix.h"
#include "BaseData.h"
#include "BaseFlag.h"


BaseMatrix InitBaseMatrix(int r, int c)  // Initialize an ordinary matrix
{
	int k = 0;
	int j = 0;

	BaseMatrix matrix = {
		.data = (ElemType**)malloc(sizeof(ElemType*) * r),
		.r = r,
		.c = c
	};

	for (k = 0; k < r; k++)
	{
		matrix.data[k] = (ElemType*)malloc(sizeof(ElemType) * c);
		
		for (j = 0; j < c; j++)
		{
			matrix.data[k][j] = 0;
		}
	}

	return matrix;
}


ElemType GetBaseMatrixElem(BaseMatrix matrix, int i, int j)  // Get matrix elements
{
	return matrix.data[i-1][j-1];
}


void PutBaseMatrixElem(BaseMatrix* matrix, int i, int j, int value)  // Store elements into matrices
{
	matrix->data[i-1][j-1] = value;
}


void DisplayBaseMatrix(BaseMatrix matrix)  // Display base matrix
{
	int i = 0;
	int j = 0;
	
	printf_s("\n");

	for (i = 1; i <= matrix.r; i++)
	{
		printf_s("\033[44;37m");

		for (j = 1; j <= matrix.c; j++)
		{
			printf_s("%lf ", GetBaseMatrixElem(matrix, i, j));
		}
		printf_s("\n");
		printf_s("\033[0m");
	}
}


void FreeBaseMatrix(BaseMatrix* matrix)  // Free base matrix
{
	int i = 0;

	for (i = 0; i < matrix->r; i++)
	{
		free(matrix->data[i]);
	}

	free(matrix->data);
}


ElemType DeterminantMatrix(BaseMatrix matrix, int n)  // Recursively find the value of the matrix corresponding to the determinant
{
	int z = 0,
		j = 0,
		k = 0,
		r = 0,
		total = 0;
	int tmp = 0;
	int ctmp = 0;
	BaseMatrix b = {
		.data = NULL,
		.r = 0,
		.c = 0
	};

	if (matrix.r != matrix.c)
	{
		printf_s("\033[41;33m\nDoes not meet the determinant calculation conditions\n\033[0m");
		return 0;
	}

	if (n > 2)
	{
		for (z = 0; z < n; z++)
		{
			// Construct co-form
			b = InitBaseMatrix(n - 1, n - 1);

			for (j = 0; j < n - 1; j++)
			{
				for (k = 0; k < n - 1; k++)
				{
					if (k >= z)
					{
						b.data[j][k] = matrix.data[j + 1][k + 1];
					}
					else
					{
						b.data[j][k] = matrix.data[j + 1][k];
					}
				}
			}

			// The determinant is expanded in the first column
			if (z % 2 == 0)
			{
				r = matrix.data[0][z] * DeterminantMatrix(b, n - 1);
				FreeBaseMatrix(&b);
			}
			else
			{
				r = (-1) * matrix.data[0][z] * DeterminantMatrix(b, n - 1);
				FreeBaseMatrix(&b);
			}
			total = total + r;
		}
	}
	else if (n == 2)
	{
		total = matrix.data[0][0] * matrix.data[1][1]
			- matrix.data[0][1] * matrix.data[1][0];
	}

	return total;
}


BaseMatrix CofactorMatrix(BaseMatrix matrix, int n)  // Find the remainder formula corresponding to each element of the matrix
{
	int z = 0,
		j = 0,
		k = 0,
		m = 0,
		l = 0,
		g = 0;

	BaseMatrix tmp = {
		.data = NULL,
		.r = 0,
		.c = 0
	};

	BaseMatrix cofactorMatrix = InitBaseMatrix(n, n);

	for (z = 0; z < n; z++)
	{
		l = z;
		for (j = 0; j < n; j++)
		{
			m = j;

			tmp = InitBaseMatrix(n - 1, n - 1);

			for (k = 0; k < n - 1; k++)
			{
				for (g = 0; g < n - 1; g++)
				{
					if (g >= m && k < l)
					{
						tmp.data[k][g] = matrix.data[k][g + 1];
					}
					else if (k >= l && g < m)
					{
						tmp.data[k][g] = matrix.data[k + 1][g];
					}
					else if (k >= l && g >= m)
					{
						tmp.data[k][g] = matrix.data[k + 1][g + 1];
					}
					else
					{
						tmp.data[k][g] = matrix.data[k][g];
					}
				}
			}
			cofactorMatrix.data[z][j] = DeterminantMatrix(tmp, n - 1);
			FreeBaseMatrix(&tmp);
		}
	}

	return cofactorMatrix;
}


BaseMatrix MatrixInverse(BaseMatrix matrix)  // Find the inverse of a matrix
{
	int i = 0,
		j = 0,
		n = matrix.r;

	BaseMatrix InverseMatrix = {
		.data = NULL,
		.r = 0,
		.c = 0
	};

	ElemType determinant = DeterminantMatrix(matrix, matrix.r);

	if (!determinant)
	{
		printf_s("\033[41;33m\nThe determinant is zero"
			"and the matrix is irreversible\n\033[0m");
		return InverseMatrix;
	}

	BaseMatrix cofactorMatrix = CofactorMatrix(matrix, matrix.r);

	for (i = 0; i < n; i++)  // The algebraic cofactor is obtained from the cofactor
	{
		for (j = 0; j < n; j++)
		{
			if ((i + j) % 2 != 0
				&& cofactorMatrix.data[i][j] != 0)
			{
				cofactorMatrix.data[i][j] = -cofactorMatrix.data[i][j];
			}
		}
	}

	/*
	The adjoint matrix is obtained by
	transposing the matrix of algebraic cofactor
	*/
	ElemType temp = 0;
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			temp = cofactorMatrix.data[i][j];
			cofactorMatrix.data[i][j] = cofactorMatrix.data[j][i];
			cofactorMatrix.data[j][i] = temp;
		}
	}

	/*
	The adjoint matrix is divided by the value of the determinant
	to get the inverse matrix
	*/
	InverseMatrix = InitBaseMatrix(n, n);

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			InverseMatrix.data[i][j] = cofactorMatrix.data[i][j] / determinant;
		}
	}

	return InverseMatrix;
}
