#pragma warning( disable : 6386 )
#pragma warning( disable : 6385 )
#include <stdio.h>
#include <stdlib.h>

#include "ConsoleStyle.h"
#include "BaseData.h"
#include "BaseFlag.h"
#include "RLSMatrix.h"
#include "BaseMatrix.h"
#include "DiagonalMatrix.h"
#include "TriangularMatrix.h"
#include "SymmetricMatrix.h"


typedef enum OperationChooseMap
{
	EXIT,
	ADDITION,
	SUBTRACTION,
	MULTIPLICATION,
	INVERSE,
	TRANSPOSE,
	DETERMINANT
} OperationChooseMap;


typedef enum TypeChooseMap
{
	RETURN,
	DIAGONAL,
	SYMMETRIC,
	IDENTITY,
	TRIANGLUAR,
	SPARSE
} TypeChooseMap;


int GetUserChoose(int isTypeChoose)
{
	int retval = 0;
	int choose = 0;

	while (TRUE)
	{
		retval = scanf_s("%d", &choose);
		flush();

		if (retval < 1)
		{
			system("cls");
			printf_s("\033[41;33m\nInput error,"
				"please enter again\n\033[0m");
			Pause();
			system("cls");
			Menu(isTypeChoose, FALSE);
			continue;
		}

		if (choose < 0 || choose > 6 && !isTypeChoose
			|| choose > 5 && isTypeChoose)
		{
			system("cls");
			printf_s("\033[41;33m\nInput data is illegal,"
				"please enter again\n\033[0m");
			Pause();
			system("cls");
			Menu(isTypeChoose, FALSE);
			continue;
		}

		break;
	}

	return choose;
}


RLSMatrix MapCreateRLSMatrix(int type)
{
	switch (type)
	{
		case DIAGONAL:
		{
			DiagonalMatrix diagonalMatrix = CreateDiagonalMatrix(FALSE);
			RLSMatrix rlsMatrix = DiagonalMatrix2RLSMatrix(diagonalMatrix);
			FreeDiagonalMatrix(&diagonalMatrix);
			return rlsMatrix;
		}
		case SYMMETRIC:
		{
			SymmetricMatrix symmetricMatrix = CreateSymmetricMatrix();
			RLSMatrix rlsMatrix = SymmetricMatrix2RLSMatrix(symmetricMatrix);
			FreeSymmetricMatrix(&symmetricMatrix);
			return rlsMatrix;
		}
		case IDENTITY:
		{
			DiagonalMatrix diagonalMatrix = CreateDiagonalMatrix(TRUE);
			RLSMatrix rlsMatrix = DiagonalMatrix2RLSMatrix(diagonalMatrix);
			FreeDiagonalMatrix(&diagonalMatrix);
			return rlsMatrix;
		}
		case TRIANGLUAR:
		{
			TriangularMatrix triangularMatrix = CreateTriangularMatrix();
			RLSMatrix rlsMatrix = TriangularMatrix2RLSMatrix(triangularMatrix);
			FreeTriangularMatrix(&triangularMatrix);
			return rlsMatrix;
		}
		case SPARSE:
		{
			RLSMatrix rlsMatrix = CreateRLSMatrix();
			return rlsMatrix;
		}
		default: break;
	}
}


BaseMatrix MapCreateBaseMatrix(int type)
{
	switch (type)
	{
		case DIAGONAL:
		{
			DiagonalMatrix diagonalMatrix = CreateDiagonalMatrix(FALSE);
			BaseMatrix baseMatrix = DiagonalMatrix2BaseMatrix(diagonalMatrix);
			FreeDiagonalMatrix(&diagonalMatrix);
			return baseMatrix;
		}
		case SYMMETRIC:
		{
			SymmetricMatrix symmetricMatrix = CreateSymmetricMatrix();
			BaseMatrix baseMatrix = SymmetricMatrix2BaseMatrix(symmetricMatrix);
			FreeSymmetricMatrix(&symmetricMatrix);
			return baseMatrix;
		}
		case IDENTITY:
		{
			DiagonalMatrix diagonalMatrix = CreateDiagonalMatrix(TRUE);
			BaseMatrix baseMatrix = DiagonalMatrix2BaseMatrix(diagonalMatrix);
			FreeDiagonalMatrix(&diagonalMatrix);
			return baseMatrix;
		}
		case TRIANGLUAR:
		{
			TriangularMatrix triangularMatrix = CreateTriangularMatrix();
			BaseMatrix baseMatrix = TriangularMatrix2BaseMatrix(triangularMatrix);
			FreeTriangularMatrix(&triangularMatrix);
			return baseMatrix;
		}
		case SPARSE:
		{
			RLSMatrix rlsMatrix = CreateRLSMatrix();
			BaseMatrix baseMatrix = RLSMatrix2BaseMatrix(rlsMatrix);
			return baseMatrix;
		}
		default: break;
	}
}


int main()
{
	FullScreen();  // full screen

	while (TRUE)
	{
		system("cls");
		Menu(FALSE, TRUE);  // draw menu style

		switch (GetUserChoose(FALSE))
		{
			case ADDITION:
			{
				system("cls");
				Menu(TRUE, FALSE);
				int type = GetUserChoose(TRUE);
				if (!type)
				{
					continue;
				}
				system("cls");
				RLSMatrix matrix1 = MapCreateRLSMatrix(type);
				Pause();


				system("cls");
				Menu(TRUE, FALSE);
				type = GetUserChoose(TRUE);
				if (!type)
				{
					continue;
				}
				system("cls");
				RLSMatrix matrix2 = MapCreateRLSMatrix(type);

				RLSMatrix res = AddRLSMatrix(matrix1, matrix2);

				if (res.data)
				{
					DisplayRLSMatrix(matrix1);
					printf_s("\033[31m\nADD\n\033[0m");
					DisplayRLSMatrix(matrix2);
					printf_s("\033[32m\nEQUAL\n\033[0m");
					DisplayRLSMatrix(res);
				}

				FreeRLSMatrix(&matrix1);
				FreeRLSMatrix(&matrix2);
				FreeRLSMatrix(&res);
				Pause();

				break;
			}
			case SUBTRACTION:
			{
				system("cls");
				Menu(TRUE, FALSE);
				int type = GetUserChoose(TRUE);
				if (!type)
				{
					continue;
				}
				system("cls");
				RLSMatrix matrix1 = MapCreateRLSMatrix(type);
				Pause();


				system("cls");
				Menu(TRUE, FALSE);
				type = GetUserChoose(TRUE);
				if (!type)
				{
					continue;
				}
				system("cls");
				RLSMatrix matrix2 = MapCreateRLSMatrix(type);

				RLSMatrix res = SubRLSMatrix(matrix1, matrix2);

				if (res.data)
				{
					DisplayRLSMatrix(matrix1);
					printf_s("\033[31m\nSUB\n\033[0m");
					DisplayRLSMatrix(matrix2);
					printf_s("\033[32m\nEQUAL\n\033[0m");
					DisplayRLSMatrix(res);
				}

				FreeRLSMatrix(&matrix1);
				FreeRLSMatrix(&matrix2);
				FreeRLSMatrix(&res);
				Pause();

				break;
			}
			case MULTIPLICATION:
			{
				system("cls");
				Menu(TRUE, FALSE);
				int type = GetUserChoose(TRUE);
				if (!type)
				{
					continue;
				}
				system("cls");
				RLSMatrix matrix1 = MapCreateRLSMatrix(type);
				Pause();


				system("cls");
				Menu(TRUE, FALSE);
				type = GetUserChoose(TRUE);
				if (!type)
				{
					continue;
				}
				system("cls");
				RLSMatrix matrix2 = MapCreateRLSMatrix(type);

				RLSMatrix res = MultiRLSMatrix(matrix1, matrix2);

				if (res.t)
				{
					DisplayRLSMatrix(matrix1);
					printf_s("\033[31m\nMULTI\n\033[0m");
					DisplayRLSMatrix(matrix2);
					printf_s("\033[32m\nEQUAL\n\033[0m");
					DisplayRLSMatrix(res);
				}

				FreeRLSMatrix(&matrix1);
				FreeRLSMatrix(&matrix2);
				FreeRLSMatrix(&res);
				Pause();

				break;
			}
			case INVERSE:
			{
				system("cls");
				Menu(TRUE, FALSE);
				int type = GetUserChoose(TRUE);
				if (!type)
				{
					continue;
				}
				system("cls");
				BaseMatrix matrix = MapCreateBaseMatrix(type);

				BaseMatrix res = MatrixInverse(matrix);

				if (res.data)
				{
					DisplayBaseMatrix(matrix);
					printf_s("\033[31m\nINVERSE\n\033[0m");
					DisplayBaseMatrix(res);
				}

				FreeBaseMatrix(&matrix);
				FreeBaseMatrix(&res);
				Pause();

				break;
			}
			case TRANSPOSE:
			{
				system("cls");
				Menu(TRUE, FALSE);
				int type = GetUserChoose(TRUE);
				if (!type)
				{
					continue;
				}
				system("cls");
				RLSMatrix matrix = MapCreateRLSMatrix(type);
				Pause();

				RLSMatrix res = FastTransposeRLSMatrix(matrix);

				if (res.data)
				{
					DisplayRLSMatrix(matrix);
					printf_s("\033[31m\nTRANSPOSE\n\033[0m");
					DisplayRLSMatrix(res);
				}

				FreeRLSMatrix(&matrix);
				FreeRLSMatrix(&res);
				Pause();

				break;
			}
			case DETERMINANT:
			{
				system("cls");
				Menu(TRUE, FALSE);
				int type = GetUserChoose(TRUE);
				if (!type)
				{
					continue;
				}
				system("cls");
				BaseMatrix matrix = MapCreateBaseMatrix(type);

				ElemType res = DeterminantMatrix(matrix, matrix.r);

				if (res)
				{
					DisplayBaseMatrix(matrix);
					printf_s("\033[31m\nDETERMINANT\n\033[0m");
					printf_s("%lf", res);
				}

				FreeBaseMatrix(&matrix);
				Pause();

				break;
			}
			case EXIT:
			{
				system("cls");
				_DrawLogo(37, 10, 2, TRUE);
				SetFontColor(7);
				printf_s("Thank you for your use...\n");
				SetFontColor(2);
				Pause();
				exit(0);
			}
			default: break;
		}
	}
}
