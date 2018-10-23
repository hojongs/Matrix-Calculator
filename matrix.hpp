#ifndef MATRIX_H
#define MATRIX_H
#include <varargs.h>
#define MAX_SIZE 8
#define FMT "%8.3lf "
#define AND &&
#define OR ||
#define NOT !

extern bool MATRIX_LOG_ENABLE;

// square only
typedef struct _Matrix
{
	double data[MAX_SIZE][MAX_SIZE];
	int size;
}Matrix;

typedef struct _Vector
{
	double data[MAX_SIZE];
	int size;
}Vector;

Matrix initMatrix(int size);
Matrix inputMatrix(Matrix matrix);
void printMatrix(Matrix matrix);
double det(Matrix matrix);
Matrix minorMatrix(Matrix matrix, int row, int col);
Matrix inverseMatrix(Matrix matrix);

Vector initVector(int size);

Vector gaussJordanEliminate(Matrix A, Vector b, int n);
void printLinearSystem(Matrix A, Vector b, int n);

template<typename T>
void swap(T* a, T* b)
{
	T c = *a;
	*a = *b;
	*b = c;
}
#endif
