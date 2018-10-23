#include <string.h>
#include "matrix.hpp"

Vector initVector(int size)
{
	Vector vector;
	memset(&vector, 0, sizeof(Vector));
	vector.size = size;

	return vector;
}
