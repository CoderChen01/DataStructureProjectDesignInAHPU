#pragma warning( disable : 6386 )
#pragma warning( disable : 6385 )
#include <stdio.h>
#include <stdlib.h>

#include "RLSMatrix.h"
#include "BaseMatrix.h"
#include "BaseFlag.h"
#include "BaseData.h"
#include "flush.h"


int FindNextLine(int* rpos, int rtmp, int r, int t)
{
	int end = 0;
	int flag = FALSE;

	if (rtmp == r)
	{
		end = t + 1;
	}
	else
	{
		/*
		Look for non-zero elements behind the rpos array
		to get the traversal range
		*/
		flag = TRUE;
		while (!rpos[++rtmp])
		{
			if (rtmp + 1 > r)
			{
				flag = FALSE;
				break;
			}
		}

		if (!flag)
		{
			end = t + 1;
		}
		else
		{
			end = rpos[rtmp];
		}
	}

	return end;
}


RLSMatrix CreateRLSMatrix()  // Create a row logical link matrix
{
	int retval = 0;
	int tmp = 0;

	RLSMatrix matrix = {
		.data = NULL,
		.rpos = NULL,
		.r = 0,
		.c = 0,
		.t = 0
	};

	int rowNum = 0;
	int colNum = 0;
	int nonZeroNum = 0;

	while (TRUE)
	{
		printf_s("\nPlease enter the number of rows,"
			"columns and non-zero elements of the matrix (eg: 4,4,4): ");
		retval = scanf_s("%d,%d,%d", &rowNum, &colNum, &nonZeroNum);
		flush();

		if (retval < 3 || nonZeroNum <= 0
			|| rowNum <= 0 || colNum <= 0)
		{
			printf_s("\n\033[41;33mInput error, please enter it again\033[0m");
			continue;
		}

		if (nonZeroNum > MAXSIZE)
		{
			printf_s("\n\033[41;33mThe number of non-zero elements"
				"you entered exceeds the maximum range\033[0m");
			continue;
		}

		break;
	}

	matrix.r = rowNum;
	matrix.c = colNum;
	matrix.t = nonZeroNum;
	matrix.data = (Triple*)malloc(sizeof(Triple) * (nonZeroNum + 1));
	matrix.rpos = (int*)malloc(sizeof(int) * (rowNum + 1));

	for (tmp = 0; tmp <= rowNum; tmp++)
	{
		matrix.rpos[tmp] = 0;
	}

	matrix.rpos[1] = 1;
	matrix.data[0].e = 0;
	matrix.data[0].i = 0;
	matrix.data[0].j = 0;

	Triple triple = {
		.i = 0,
		.j = 0,
		.e = 0
	};
	int i = 1;
	int j = 1;
	ElemType e = 0;

	int k = 1;
	int currentRowNum = 0;
	while (TRUE)
	{
		if (i > rowNum)
		{
			/*
			After all lines are entered,
			the specified number of non-zero elements is not reached,
			enter again
			*/
			if (k <= nonZeroNum)
			{
				i = 1;
				j = 1;
				e = 0;
				k = 1;
				currentRowNum = 0;

				for (tmp = 0; tmp <= rowNum; tmp++)
				{
					matrix.rpos[tmp] = 0;
				}
				matrix.rpos[1] = 1;

				printf_s("\n\033[41;33mIncomplete non-zero input, please re-enter all\n\033[0m");
			}
			else
			{
				break;
			}
		}

		/*
		If the number of input non-zero elements
		exceeds the specified size,
		stop input
		*/
		if (k > nonZeroNum)
		{
			printf_s("\n\033[42mThe entry of non - zero elements of all rows"
				"is completed\n\033[0m");
			break;
		}

		printf_s("\nPlease enter the column and value of the non-zero element"
			"in row \033[31;5m%d\033[0m of the matrix (such as: 2,3),"
			"\033[43;37menter 0 to indicate the end of the row\033[0m: ", i);
		retval = scanf_s("%d,%lf", &j, &e);
		flush();

		if (retval == 1 && j == 0)
		{
			printf_s("\033[42mLine %d data input completed\n\033[0m", i);

			if (matrix.rpos[i] == k)
			{
				matrix.rpos[i] = 0;
			}
			matrix.rpos[++i] = k;

			currentRowNum = 0;
			continue;
		}

		if (retval <= 1 || e == 0)
		{
			printf_s("\n\033[41;33mInput error, please enter it again\033[0m");
			continue;
		}

		if (j <= 0 || j > colNum)
		{
			printf_s("\n\033[41;33mInput column is out of range, please enter it again\033[0m");
			continue;
		}

		int flag = FALSE;
		for (int tmp = matrix.rpos[i];
			tmp < currentRowNum + matrix.rpos[i]; tmp++)
		{
			if (matrix.data[tmp].j == j)
			{
				if (abs(matrix.data[tmp].e - e) < INFINITESIMAL)
				{
					printf_s("\n\033[41;33mInput element already exists,"
						"please enter again\033[0m");
					flag = TRUE;
				}
				else
				{
					printf_s("\nWhether to update the corresponding value?(y/N): ");
					while (TRUE)
					{
						char update = getchar();
						flush();

						if (update == 'y' || update == '\n')
						{
							matrix.data[tmp].e = e;
							flag = TRUE;
							break;
						}
						else if (update == 'N')
						{
							flag = TRUE;
							break;
						}
						else
						{
							printf_s("\n\033[41;33mInput error, please enter again(y/N):\033[0m ");
						}
					}
				}
				break;
			}
		}

		if (flag)
		{
			continue;
		}

		triple.i = i;
		triple.j = j;
		triple.e = e;

		matrix.data[k++] = triple;
		currentRowNum++;
	}

	return matrix;
}


void DisplayRLSMatrix(RLSMatrix matrix)  // Format sparse matrix output
{
	printf_s("\n");

	int tmp = 0;
	int end = 0;
	int flag = FALSE;

	for (int i = 1; i <= matrix.r; i++)
	{
		int j = 1;

		printf_s("\033[44;37m");

		/*
		If the rpos array element is zero,
		it means that the current row has no non-zero elements
		*/
		if (!matrix.rpos[i])
		{
			for (j = 1; j <= matrix.c; j++)
			{
				printf_s("0.000000 ");
			}
		}
		else
		{
			end = 0;
			tmp = i;

			if (tmp == matrix.r)
			{
				end = matrix.t + 1;
			}
			else
			{
				/*
				Look for non-zero elements behind the rpos array
				to get the traversal range
				*/
				flag = TRUE;
				while (!matrix.rpos[++tmp])
				{
					if (tmp + 1 > matrix.r)
					{
						flag = FALSE;
						break;
					}
				}

				if (!flag)
				{
					end = matrix.t + 1;
				}
				else
				{
					end = matrix.rpos[tmp];
				}
			}


			for (j = 1; j <= matrix.c; j++)  // Traverse the elements to format the output matrix
			{
				flag = FALSE;
				for (int k = matrix.rpos[i]; k < end; k++)
				{
					if (i == matrix.data[k].i && j == matrix.data[k].j)
					{
						printf_s("%lf ", matrix.data[k].e);
						flag = TRUE;
						break;
					}
					flag = FALSE;
				}
				if (!flag)
				{
					printf_s("0.000000 ");
				}
			}
		}

		printf_s("\n");
		printf_s("\033[0m");
	}
}


void FreeRLSMatrix(RLSMatrix* matrix)  // Free a RLSMatrix
{
	free(matrix->data);
	free(matrix->rpos);
}


RLSMatrix FastTransposeRLSMatrix(RLSMatrix M)  // Use fast transpose algorithm
{
	int tmp = 0;

	RLSMatrix T = {
		.data = NULL,
		.rpos = NULL,
		.c = 0,
		.r = 0,
		.t = 0
	};

	// Swap rows and columns
	T.r = M.c;
	T.c = M.r;
	T.t = M.t;
	T.rpos = (int*)malloc(sizeof(int) * (T.r+1));
	T.data = (Triple*) malloc(sizeof(Triple)*(T.t+1));
	
	for (tmp = 1; tmp <= T.r; tmp++)
	{
		T.rpos[tmp] = 0;
	}
	T.rpos[1] = 1;

	if (T.t)
	{
		// Calculate array
		int* array = (int*) malloc(sizeof(int)*M.r);
		for (int col = 1; col <= M.r; col++) {
			array[col] = 0;
		}

		for (int t = 1; t <= M.t; t++) {
			int j = M.data[t].j;
			array[j]++;
		}

		// Create and initialize the cpot array
		int* cpot = (int*) malloc(sizeof(int)*(T.r + 1));

		// The position of the first non-zero element in the first column is 1 by default
		cpot[1] = 1;

		for (int col = 2; col <= M.r; col++)
		{
			cpot[col] = cpot[col - 1] + array[col - 1];

			// Calculate the rpos array
			T.rpos[col] = cpot[col];
		}

		// Transpose the triple table by traversing once
		for (int p = 1; p <= M.t; p++) {
			// Extract the number of columns of the current triple
			int col = M.data[p].j;

			/*
			According to the number of columns and the cpot array, 
			find the location where the current element needs to be stored
			*/
			int q = cpot[col];
			
			/*
			By default, the triples of the transposed matrix start from the array index 0,
			and the obtained q value is a simple position,
			so it needs to be reduced by 1
			*/
			T.data[q].i = M.data[p].j;
			T.data[q].j = M.data[p].i;
			T.data[q].e = M.data[p].e;
			
			/*
			After the storage is complete,
			the position corresponding to the cpot array must be +1,
			so that next time the column stores the next triplet
			*/
			cpot[col]++;
		}
		free(array);
		free(cpot);
	}
	return T;
}


RLSMatrix MultiRLSMatrix(RLSMatrix A, RLSMatrix B)  // A and B matrix multiplication
{
	int tmp = 0;
	int flag = FALSE;

	RLSMatrix C = {
		.data = NULL,
		.rpos = NULL,
		.c = 0,
		.r = 0,
		.t = 0
	};

	/*
	If the number of columns of matrix A
	is not equal to the number of rows of matrix B,
	you cannot do matrix multiplication
	*/
	if (A.c != B.r)
	{
		printf_s("\n\033[41;33mDoes not meet the "
			"matrix multiplication rule\n\033[0m");
		return C;
	}
	
	C.r = A.r;
	C.c = B.c;
	C.t = 0;
	C.rpos = (int*)malloc(sizeof(int) * (C.r+1));

	for (tmp = 0; tmp < C.r + 1; tmp++)
	{
		C.rpos[tmp] = 0;
	}

	C.data = (Triple*)malloc(sizeof(Triple) * (MAXSIZE + 1));
	//C.data = (Triple*)malloc(sizeof(Triple));

	/*
	If the number of elements in any matrix is zero,
	it is meaningless to do multiplication elements, all are 0
	*/
	if (A.t * B.t == 0)
	{
		printf_s("\n\033[41;33mMultiplying with zero matrix "
			"must be zero matrix\n\033[0m"); 
		return C;
	}

	int arow = 0;
	int ccol = 0;

	/*
	Create an array to temporarily store the result of the product
	*/
	ElemType* ctemp = (ElemType*)malloc(sizeof(ElemType) * (C.c + 1));

	// Traverse each row of matrix A
	for (arow = 1; arow <= A.r; arow++)
	{
		if (!A.rpos[arow])
		{
			continue;
		}

		/*
		initialize it to 0 and it needs to be cleared every time you traverse
		*/
		for (tmp = 0; tmp <= C.c; tmp++)
		{
			ctemp[tmp] = 0.0;
		}

		C.rpos[arow] = C.t + 1;
		
		/*
		According to the number of rows,
		find the positions of all non-zero elements
		in the row in the triple table
		*/
		int tp = 0;
		tmp = arow;

		if (tmp == A.r)
		{
			/*
			If the current line is the last line,
			take the last element + 1
			*/
			tp = A.t + 1;
		}
		else
		{
			/*
			Look for non-zero elements behind the rpos array
			to get the traversal range
			*/
			flag = TRUE;
			while (!A.rpos[++tmp])
			{
				if (tmp + 1 > A.r)
				{
					flag = FALSE;
					break;
				}
			}
			if (!flag)
			{
				tp = A.t + 1;
			}
			else
			{
				tp = A.rpos[tmp];
			}
		}


		int p = 0;
		int brow = 0;
		int q = 0;

		// Traverse all non-zero elements in the current row
		for (p = A.rpos[arow]; p < tp; p++)
		{
			/*
			Take the number of columns
			of the non-zero element
			to find the corresponding non-zero element in B
			*/
			brow = A.data[p].j;
			
			if (!B.rpos[brow])
			{
				continue;
			}

			/*
			Determine if for the non-zero elements in A,
			find all the non-zero elements
			in the row of matrix B that are multiplied
			*/
			int t = 0;
			tmp = brow;
			if (tmp == B.r)
			{
				t = B.t + 1;
			}
			else
			{
				flag = TRUE;
				while (!B.rpos[++tmp])
				{
					if (tmp + 1 > B.r)
					{
						flag = FALSE;
						break;
					}
				}
				if (!flag)
				{
					t = B.t + 1;
				}
				else
				{
					t = B.rpos[tmp];
				}
			}

			/*
			Traverse the corresponding non-zero elements found
			and start the product operation
			*/
			for (q = B.rpos[brow]; q < t; q++)
			{
				/*
				The result of the product is added to the value
				at the corresponding position in the ctemp array each time
				*/
				ccol = B.data[q].j;
				ctemp[ccol] += A.data[p].e * B.data[q].e;
			}
		}

		/*
		The number of rows of matrix C is equal to the number of rows of matrix A,
		and the number of columns is equal to the number of columns of matrix B. 
		Therefore, the result stored in ctemp
		will also be within the range of the number of columns of C
		*/
		for (ccol = 1; ccol <= C.c; ccol++)
		{
			/*
			Since the result can be 0,
			and 0 does not need to be stored,
			we need to judge here
			*/
			if (ctemp[ccol])
			{
				/*
				If it is not 0,
				the variable tu that records the number of non-zero elements
				in the matrix must be +1;
				and the value cannot exceed the space size of the three-element array
				*/
				if (++C.t > MAXSIZE)
				{
					printf_s("\033[43;37m\nThe number of non-zero elements exceeds the maximum\n\033[0m");
					return C;
				}

				//Triple* data = (Triple*)malloc(sizeof(C.data) + sizeof(Triple));
				//if (!data)
				//{
				//	printf_s("\n\033[41;33mNot enough storage\n\033[0m");
				//	return C;
				//}

				//data[C.t].e = ctemp[ccol];
				//data[C.t].i = arow;
				//data[C.t].j = ccol;
				//free(C.data);
				//C.data = data;

				//if (C.data = (Triple*)realloc(C.data, sizeof(Triple)))
				//{
				//	C.data[C.t].e = ctemp[ccol];
				//	C.data[C.t].i = arow;
				//	C.data[C.t].j = ccol;
				//}
				//else
				//{
				//	printf_s("\n\033[41;33mNot enough storage\n\033[0m");
				//	return C;
				//}


				C.data[C.t].e = ctemp[ccol];
				C.data[C.t].i = arow;
				C.data[C.t].j = ccol;
			}
		}
	}
	//free(ctemp);
	return C;
}


RLSMatrix AddRLSMatrix(RLSMatrix A, RLSMatrix B)  // Add A and B
{
	int r = 0;
	int c = 0;
	int k = 0;
	int ka = 0;
	int kb = 0;
	int ct = 0;

	int end = 0;
	int flag = FALSE;

	ElemType tmp = 0;
	RLSMatrix C = {
		.data = NULL,
		.rpos = NULL,
		.r = 0,
		.c = 0,
		.t = 0
	};

	if (A.r != B.r || A.c != B.c)
	{
		printf_s("\033[41;33m\nDoes not meet the matrix addition condition\033[0m");
		printf_s("\033[43;37m\nThe number of rows and columns"
			" of the two matrices must be equal"
			"in order to perform the addition operation\n\033[0m");
		return C;
	}

	C.r = A.r;
	C.c = A.c;
	C.data = (Triple*)malloc(sizeof(Triple) * (MAXSIZE + 1));
	C.rpos = (int*)malloc(sizeof(int) * (A.r + 1));
	
	for (k = 0; k < A.r + 1; k++)
	{
		C.rpos[k] = 0;
	}

	for (r = 1; r <= C.r; r++)
	{
		C.rpos[r] = ct + 1;

		if ((ct + 1) == C.rpos[r - 1])
		{
			C.rpos[r - 1] = 0;
		}

		if (!A.rpos[r] && !B.rpos[r])
		{
			continue;
		}

		if (!A.rpos[r] && B.rpos[r])
		{
			end = FindNextLine(B.rpos, r, B.r, B.t);

			for (k = B.rpos[r]; k < end; k++)
			{
				if (++ct > MAXSIZE)
				{
					printf_s("\033[43;37m\nThe number of non-zero elements exceeds the maximum\n\033[0m");
					return C;
				}
				C.data[ct].e = B.data[k].e;
				C.data[ct].i = B.data[k].i;
				C.data[ct].j = B.data[k].j;
			}
			continue;
		}

		if (!B.rpos[r] && A.rpos[r])
		{
			for (k = A.rpos[r]; k < FindNextLine(A.rpos, r, A.r, A.t); k++)
			{

				if (++ct > MAXSIZE)
				{
					printf_s("\033[43;37m\nThe number of non-zero elements exceeds the maximum\n\033[0m");
					return C;
				}
				C.data[ct].e = A.data[k].e;
				C.data[ct].i = A.data[k].i;
				C.data[ct].j = A.data[k].j;
			}
			continue;
		}

		for (c = 1; c <= C.c; c++)
		{
			end = FindNextLine(A.rpos, r, A.r, A.t);
			for (ka = A.rpos[r]; ka < end; ka++)
			{
				flag = FALSE;
				if (A.data[ka].j == c)
				{
					end = FindNextLine(B.rpos, r, A.r, B.t);
					for (kb = B.rpos[r]; kb < end; kb++)
					{
						if (B.data[kb].j == c)
						{
							flag = TRUE;
							if (tmp = A.data[ka].e + B.data[kb].e)
							{
								if (++ct > MAXSIZE)
								{
									printf_s("\033[43;37m\nThe number of non-zero elements exceeds the maximum\n\033[0m");
									return C;
								}
								C.data[ct].e = tmp;
								C.data[ct].i = r;
								C.data[ct].j = c;
							}
							break;
						}
					}

					if (!flag)
					{
						if (++ct > MAXSIZE)
						{
							printf_s("\033[43;37m\nThe number of non-zero elements exceeds the maximum\n\033[0m");
							return C;
						}
						C.data[ct].e = A.data[ka].e;
						C.data[ct].i = r;
						C.data[ct].j = c;
					}

					flag = TRUE;
					break;
				}
			}

			if (!flag)
			{
				end = FindNextLine(B.rpos, r, B.r, B.t);
				for (kb = B.rpos[r]; kb < end; kb++)
				{
					if (B.data[kb].j == c)
					{
						if (++ct > MAXSIZE)
						{
							printf_s("\033[43;37m\nThe number of non-zero elements exceeds the maximum\n\033[0m");
							return C;
						}
						C.data[ct].e = B.data[kb].e;
						C.data[ct].i = r;
						C.data[ct].j = c;
						break;
					}
				}
			}

		}
	}
	C.t = ct;
	return C;
}


RLSMatrix SubRLSMatrix(RLSMatrix A, RLSMatrix B)  // Subtract A and B
{
	int k = 0;
	RLSMatrix C = {
		.data = NULL,
		.rpos = NULL,
		.r = 0,
		.c = 0,
		.t = 0
	};

	if (A.r != B.r || A.c != B.c)
	{
		printf_s("\033[41;33m\nDoes not meet the matrix substract condition\033[0m");
		printf_s("\033[43;37m\nThe number of rows and columns"
			"of the two matrices must be equal"
			"in order to perform the substract operation\n\033[0m");
		return C;
	}

	for (k = 1; k <= B.t; k++)
	{
		B.data[k].e = -1 * B.data[k].e;
	}

	C = AddRLSMatrix(A, B);

	for (k = 1; k <= B.t; k++)
	{
		B.data[k].e = -1 * B.data[k].e;
	}

	return C;
}


BaseMatrix RLSMatrix2BaseMatrix(RLSMatrix matrix)  // Convert row logical link matrix to normal matrix
{
	int tmp = 0;
	int end = 0;
	int flag = FALSE;
	
	BaseMatrix newMatrix = InitBaseMatrix(matrix.r, matrix.c);

	if (matrix.r > MATRIX_SIDE_MAX || matrix.c > MATRIX_SIDE_MAX)
	{
		printf_s("\033[41;33m\nOut of conversion range\n\033[0m");
		return newMatrix;
	}

	for (int i = 1; i <= matrix.r; i++)
	{
		int j = 1;

		/*
		If the rpos array element is zero,
		it means that the current row has no non-zero elements
		*/
		if (!matrix.rpos[i])
		{
			for (j = 1; j <= matrix.c; j++)
			{
				PutBaseMatrixElem(&newMatrix, i, j, 0);
			}
		}
		else
		{
			end = FindNextLine(matrix.rpos, i, matrix.r, matrix.t);

			for (j = 1; j <= matrix.c; j++)  // Traverse the elements to format the output matrix
			{
				flag = FALSE;
				for (int k = matrix.rpos[i]; k < end; k++)
				{
					if (i == matrix.data[k].i && j == matrix.data[k].j)
					{
						PutBaseMatrixElem(&newMatrix, i, j, matrix.data[k].e);
						flag = TRUE;
						break;
					}
				}

				if (!flag)
				{
					PutBaseMatrixElem(&newMatrix, i, j, 0);
				}
			}
		}
	}

	return newMatrix;
}
