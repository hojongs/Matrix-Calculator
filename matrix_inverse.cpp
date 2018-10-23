#include <stdio.h>
#include <math.h>
#include "matrix.hpp"

// cofactor
Matrix cofactorMatrix(Matrix matrix)
{
	Matrix cofactor = initMatrix(matrix.size);

	for (int y = 0; y < cofactor.size; y++)
		for (int x = 0; x < cofactor.size; x++)
		{
			Matrix minor = minorMatrix(matrix, y, x);
			double det_m = det(minor);
			if (MATRIX_LOG_ENABLE) fprintf(stdout, "det(M[%d,%d](size=%d))=" FMT " \n\n", y+1, x+1, minor.size, det_m);

			cofactor.data[y][x] = pow(-1, y + x) * det_m;
		}

	if (MATRIX_LOG_ENABLE)
	{
		fprintf(stdout, "cofactor \n");
		printMatrix(cofactor);
		fprintf(stdout, "\n");
	}
	return cofactor;
}

// transposed matrix
Matrix transpose(Matrix matrix)
{
	Matrix transposed = initMatrix(matrix.size);

	for (int t_y = 0; t_y < matrix.size; t_y++)
		for (int t_x = 0; t_x < matrix.size; t_x++)
			transposed.data[t_y][t_x] = matrix.data[t_x][t_y];

	if (MATRIX_LOG_ENABLE)
	{
		fprintf(stdout, "transpose \n");
		printMatrix(transposed);
		fprintf(stdout, "\n");
	}
	return transposed;
}

// 수반 행렬
Matrix adjoint(Matrix matrix)
{
	Matrix cofactor = cofactorMatrix(matrix);
	Matrix adj = transpose(cofactor);

	if (MATRIX_LOG_ENABLE)
	{
		fprintf(stdout, "adj \n");
		printMatrix(adj);
		fprintf(stdout, "\n");
	}
	return adj;
}

// inverse matrix
Matrix inverseMatrix(Matrix matrix)
{
	Matrix adj = adjoint(matrix);

	Matrix inverse = initMatrix(matrix.size);
	double det_a = det(matrix);

	for (int y = 0; y < matrix.size; y++)
		for (int x = 0; x < matrix.size; x++)
			inverse.data[y][x] = 1 / det_a * adj.data[y][x];

	if (MATRIX_LOG_ENABLE)
	{
		fprintf(stdout, "inverse \n");
		fprintf(stdout, "(1/%.3lf) * \n", det_a);
		printMatrix(adj);
		fprintf(stdout, "\n");
	}
	return inverse;
}
