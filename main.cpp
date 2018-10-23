/* 2018-2 linear algebra hw */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "matrix.hpp"
#include "menu.hpp"

// TODO : change to log level
extern bool MATRIX_LOG_ENABLE = true;

void mainDet();
void mainInverse();
void mainGaussJordan();
void inputLinearSystem(Matrix* A, Vector* b, int n);
void inputEquation(double A[], double* b, int n);

int main()
{
	Menu menuArr[] = {
		initMenu(1, "det", mainDet),
		initMenu(2, "inverse", mainInverse),
		initMenu(3, "gauss-jordan", mainGaussJordan),
	};
	const int menuCnt = sizeof(menuArr) / sizeof(Menu);
	printMenu(menuArr, menuCnt);

	int selection = 0;
	scanf("%d", &selection);

	runMenu(menuArr, menuCnt, selection);

	return 0;
}

void mainDet()
{
	int n = MAX_SIZE;
	if (MATRIX_LOG_ENABLE) fprintf(stdout, "n : ");
	scanf("%d", &n);

	Matrix matrix = initMatrix(n);
	matrix = inputMatrix(matrix);

	printf("det(A)=" FMT "\n", det(matrix));
}

void mainInverse()
{
	int n = MAX_SIZE;
	if (MATRIX_LOG_ENABLE) fprintf(stdout, "n : ");
	scanf("%d", &n);

	Matrix matrix = initMatrix(n);
	matrix = inputMatrix(matrix);

	Matrix inverse = inverseMatrix(matrix);
	if (MATRIX_LOG_ENABLE) fprintf(stdout, "inverse \n");
	printMatrix(inverse);
}

void mainGaussJordan()
{
	int n = MAX_SIZE;
	if (MATRIX_LOG_ENABLE) fprintf(stdout, "n : ");
	scanf("%d", &n);

	Matrix A = initMatrix(n);
	Vector b = initVector(n);
	inputLinearSystem(&A, &b, n);

	if (MATRIX_LOG_ENABLE)
	{
		fprintf(stdout, "Matrix \n");
		printLinearSystem(A, b, n);
	}

	Vector x = gaussJordanEliminate(A, b, n);
	if (MATRIX_LOG_ENABLE) fprintf(stdout, "solution \n");
	for (int i = 0; i < n; i++)
	{
		if (MATRIX_LOG_ENABLE)
			fprintf(stdout, "x%d=", i + 1);
		fprintf(stdout, "%.lf \t", x.data[i]);
	}
}

// 방정식 수가 부족하면, 0으로 입력
void inputLinearSystem(Matrix* A, Vector* b, int n)
{
	if (MATRIX_LOG_ENABLE)
	{
		fprintf(stdout, "input equation form : ( )x1");
		for (int i = 2; i <= n; i++)
			fprintf(stdout, " + ( )x%d", i);
		fprintf(stdout, " = ( ) \n");
	}

	for (int i = 0; i < n; i++)
	{
		fprintf(stdout, "equation %d : ", i);
		inputEquation(A->data[i], &b->data[i], n);
	}
}

void inputEquation(double A[], double* b, int n)
{
	if (n <= 0)
		return;

	for (int i = 0; i < n; i++)
		scanf("%lf", &A[i]);
	scanf("%lf", b);
}