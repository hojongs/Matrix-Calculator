#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "matrix.hpp"

Vector backSubstitution(Matrix A, Vector b, int n);
void printEquation(double A[], double b, int n);

Vector gaussJordanEliminate(Matrix A, Vector b, int n)
{
	bool error = false;
	int pv = 0; // pivot

	while (pv < (n-1))
	{
		if (MATRIX_LOG_ENABLE) fprintf(stdout, "pivot=R%d \n", pv+1);
		// if pivot is 0, swap rows
		if (A.data[pv][pv] == 0)
		{
			for (int row = pv + 1; row < n; row++)
			{
				if (A.data[row][pv] != 0)
				{
					int t = row; // temp
					for (int j = pv; j < n; j++)
						swap(&A.data[pv][j], &A.data[t][j]);
					swap(&b.data[pv], &b.data[row]);

					if (MATRIX_LOG_ENABLE)
					{
						fprintf(stdout, "R%d <-> R%d (%.lf > %.lf) \n", pv + 1, row + 1, fabs(A.data[row][pv]), fabs(A.data[pv][pv]));
						printLinearSystem(A, b, n);
					}
					break;
				}
			}
		}

		// eliminates rows
		if (A.data[pv][pv] == 0)
		{
			// pivot row로 elimination 할 것이 없음
			fprintf(stdout, "\n");
			error = true;
		}
		else
		{
			for (int row = pv + 1; row < n; row++)
			{
				double coef = -1 * A.data[row][pv] / A.data[pv][pv];
				if (coef == 0)
					continue;

				for (int col = pv; col < n; col++)
					A.data[row][col] += coef * A.data[pv][col];
				b.data[row] += coef * b.data[pv];

				if (MATRIX_LOG_ENABLE)
				{
					fprintf(stdout, "%.1lfR%d + R%d -> R%d \n", coef, pv + 1, row + 1, row + 1);
					printLinearSystem(A, b, n);
				}
			}
		}

		pv++;
	}

	if (error)
	{
		if (MATRIX_LOG_ENABLE) fprintf(stdout, "Trap condition \n");
	}

	if (MATRIX_LOG_ENABLE)
	{
		fprintf(stdout, "Upper Triangular Matrix \n");
		printLinearSystem(A, b, n);
	}
	return backSubstitution(A, b, n);
}

// 포인터를 리턴하면, null return 가능
Vector backSubstitution(Matrix A, Vector b, int n)
{
	if (fabs(A.data[n - 1][n - 1]) < 1 / 1000000)
	{
		printf("Singular Matrix");
		return initVector(0);
	}

	Vector x = initVector(n);

	// get x_(n-1)
	if (A.data[n - 1][n - 1] == 0)
	{
		if (b.data[n - 1] == 0)
		{
			if (MATRIX_LOG_ENABLE)
			{
				fprintf(stdout, "x%d = random number \n", n);

				for (int i = n - 2; i >= 0; i--)
				{
					fprintf(stdout, "x%d = ", i + 1);

					for (int k = 0; k < i + 1; k++)
						fprintf(stdout, "          ");
					for (int k = i + 1; k < n; k++)
						fprintf(stdout, "+ %4.1lf*x%d ", -A.data[i][k] / A.data[i][i], k + 1);
					fprintf(stdout, "+ %4.1lf \n", b.data[i]);
				}
			}
		}
		else
			if (MATRIX_LOG_ENABLE) fprintf(stdout, "No solution \n");

		for (int i = n - 1; i >= 0; i--)
			x.data[i] = NAN;

		// return null
		return x;
	}
	else
	{
		x.data[n - 1] = b.data[n - 1] / A.data[n - 1][n - 1];

		// get x_(n-2) ~ x_1
		for (int i = n - 2; i >= 0; i--)
		{
			double sum = 0;

			for (int k = n - 1; k > i; k--)
			{
				sum += A.data[i][k] * x.data[k];
				A.data[i][k] = 0;
			}

			x.data[i] = (b.data[i] - sum) / A.data[i][i];
			b.data[i] -= -sum;
		}

		if (MATRIX_LOG_ENABLE)
		{
			fprintf(stdout, "Back substitution result (Diagonal Matrix) \n");
			printLinearSystem(A, b, n);
		}

		return x;
	}
}

void printLinearSystem(Matrix A, Vector b, int n)
{
	for (int i = 0; i < n; i++)
		printEquation(A.data[i], b.data[i], n);
	printf("\n");
}

void printEquation(double A[], double b, int n)
{
	printf("[ ");
	for (int i = 0; i < n; i++)
	{
		printf(" %+8.1lf ", A[i]);
	}
	printf(" | ");
	printf("%+8.1lf ] \n", b);
}
