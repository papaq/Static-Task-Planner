#include "Matrix.h"

int GetX(int i, int cols)
{
	return i % cols;
}

int GetY(int i, int cols)
{
	return i / cols;
}

int ** MakeMatrix(int m, int n)
{
	int** rows = (int**)calloc(n, sizeof(int*));
	int* values = (int*)calloc(n*m, sizeof(int));

	for (int i = 0; i < n; i++)
	{
		rows[i] = values + i*m;
	}

	return rows;
}

void FillRandMatrix(int ** matrix, int m, int n, int rate, int diff)
{
	int cells = m * n * rate / 100;

	/* set the seed */
	srand((unsigned)time(NULL));

	while(cells > 0)
	{
		int rnd = rand() % (m*n);
		if (matrix[GetY(rnd, m)][GetX(rnd, m)] == 0)
		{
			matrix[GetY(rnd, m)][GetX(rnd, m)] = 1;
			cells--;
		}
	}
}

int * MakeVector(int m)
{
	int* vector = (int*)malloc(m * sizeof(int));
	return vector;
}

void FillVector(int * vector, int m, int what)
{
	for (int i = 0; i < m; i++)
	{
		vector[i] = what;
	}
}

void FillRandVector(int * vector, int m, int upper)
{
	/* set the seed */
	srand((unsigned)time(NULL));

	for (int i = 0; i < m; i++)
	{
		int random = rand() % upper;
		vector[i] = random + 1;
	}
}

void PrintMatrix(int ** matrix, int m, int n)
{
	for (int i = 0; i < m*n; i++)
	{
		if (i % m == 0 && i / m > 0)
		{
			printf("\n");
		}
		printf("%2d ", matrix[GetY(i, m)][GetX(i, m)]);
	}

	printf("\n");
}

void PrintVector(int * matrix, int m)
{
	for (int i = 0; i < m; i++)
	{
		printf("%3d ", matrix[i]);
	}

	printf("\n");
}
