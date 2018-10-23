#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "matrix.hpp"

Matrix initMatrix(int size)
{
	Matrix matrix;
	memset(&matrix, 0, sizeof(Matrix));
	matrix.size = size;

	return matrix;
}

// input from stdin
Matrix inputMatrix(Matrix matrix)
{
	if (MATRIX_LOG_ENABLE) fprintf(stdout, "matrix A : \n");
	for (int y = 0; y < matrix.size; y++)
	{
		for (int x = 0; x < matrix.size; x++)
		{
			scanf("%lf", &matrix.data[y][x]);
		}
	}

	return matrix;
}

// print to stdout
void printMatrix(Matrix matrix)
{
	for (int y = 0; y < matrix.size; y++)
	{
		for (int x = 0; x < matrix.size; x++)
			printf(FMT, matrix.data[y][x]);
		printf("\n");
	}
}

// square only
Matrix mul_matrix(Matrix a, Matrix b)
{
	Matrix c = initMatrix(a.size);

	for (int y = 0; y < a.size; y++)
	{
		for (int x = 0; x < a.size; x++)
		{
			double sum = 0;
			for (int m = 0; m < a.size; m++)
				sum += a.data[y][m] * b.data[m][x];
			c.data[y][x] = sum;
		}
	}

	return c;
}
