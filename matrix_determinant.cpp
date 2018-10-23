#include <stdio.h>
#include <math.h>
#include "matrix.hpp"

// determinant
double det(Matrix matrix)
{
	double det_a = 0;

	if (matrix.size == 1)
		det_a = matrix.data[0][0];
	else if (matrix.size == 2)
		det_a =
		+(matrix.data[0][0] * matrix.data[1][1])
		- matrix.data[0][1] * matrix.data[1][0];
	else if (matrix.size == 3) // sarrus
		det_a =
		+(matrix.data[0][0] * matrix.data[1][1] * matrix.data[2][2])
		+ matrix.data[0][1] * matrix.data[1][2] * matrix.data[2][0]
		+ matrix.data[0][2] * matrix.data[1][0] * matrix.data[2][1]
		- matrix.data[0][0] * matrix.data[1][2] * matrix.data[2][1]
		- matrix.data[0][1] * matrix.data[1][0] * matrix.data[2][2]
		- matrix.data[0][2] * matrix.data[1][1] * matrix.data[2][0];
	else // minor -> cofactor -> det
	{
		const int row = 0;

		// get det_a
		for (int col = 0; col < matrix.size; col++)
		{
			// minorMatrix
			Matrix minor = minorMatrix(matrix, row, col);

			double sign = pow(-1, col);
			double coef = matrix.data[0][col];
			double det_m = det(minor);
			double result = sign * coef * det_m;
			det_a += result;

			if (MATRIX_LOG_ENABLE) fprintf(stdout, "%c" FMT "*" FMT " = " FMT " \n\n", (sign > 0 ? '+' : '-'), coef, det_m, result);
		}
	}

	return det_a;
}

// minor matrix
Matrix minorMatrix(Matrix matrix, int row, int col)
{
	Matrix minor = initMatrix(matrix.size - 1);
	int t_y = 0;

	// init temp
	for (int a_y = 0; a_y < matrix.size; a_y++)
	{
		if (a_y == row) // A 특정 행 제외
			continue;

		int t_x = 0;

		for (int a_x = 0; a_x < matrix.size; a_x++)
		{
			if (a_x == col) // A 특정 열 제외
				continue;

			minor.data[t_y][t_x] = matrix.data[a_y][a_x];
			t_x++;
		}

		t_y++;
	}

	if (MATRIX_LOG_ENABLE)
	{
		fprintf(stdout, "M[%d,%d] \n", row + 1, col + 1);
		printMatrix(minor);
	}
	return minor;
}
