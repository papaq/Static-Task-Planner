#include "Planner.h"

bool AllZerosInRow(int ** matrix, int m, int n, int row)
{
	for (int i = 0; i < m; i++)
	{
		if (matrix[GetY(row * m + i, m)][GetX(row * m + i, m)] != 0)
		{
			return false;
		}
	}
	return true;
}

bool AllZerosInColumn(int** matrix, int m, int n, int column)
{
	for (int i = 0; i < n; i++)
	{
		if (matrix[GetY(column + i * m, m)][GetX(column + i * m, m)] != 0)
		{
			return false;
		}
	}
	return true;
}

int SingleOneInRow(int** matrix, int* taskVect, int m, int n, int row)
{
	int one = -1;

	for (int i = 0; i < m; i++)
	{
		if (taskVect[i] == 1)
		{
			continue;
		}

		if (matrix[GetY(row * m + i, m)][GetX(row * m + i, m)] != 0)
		{
			if (one == -1)
			{
				one = i;
			}
			else
			{
				return -1;
			}
		}
	}
	return one;
}

int SingleOneInColumn(int** matrix, int* resVect, int m, int n, int column)
{
	int one = -1;

	for (int i = 0; i < n; i++)
	{
		if (resVect[i] == 1)
		{
			continue;
		}

		if (matrix[GetY(column + i * m, m)][GetX(column + i * m, m)] != 0)
		{
			if (one == -1)
			{
				one = i;
			}
			else
			{
				return -1;
			}
		}
	}
	return one;
}

int FindFirstSingleRow(int** matrix, int* taskVect, int* resVect, int m, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (resVect[i] == 1)
		{
			continue;
		}

		if (SingleOneInRow(matrix, taskVect, m, n, i) != -1)
		{
			return i;
		}
	}

	return -1;
}

int FindFirstSingleColumn(int** matrix, int* taskVect, int* resVect, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		if (taskVect[i] == 1)
		{
			continue;
		}

		if (SingleOneInColumn(matrix, resVect, m, n, i) != -1)
		{
			return i;
		}
	}

	return -1;
}

void AttachTaskToRes(int** matrix, int** arrayOfResourcesQ, int* taskVector, int xCoord, int yCoord, int resPow, int taskDiff)
{
	int qOnResource = arrayOfResourcesQ[yCoord][0];
	qOnResource++;

	/*
	arrayOfResourcesQ[yCoord] = (int*)realloc(
		arrayOfResourcesQ[yCoord],
		(qOnResource + 1) * sizeof(int)
	);
	*/

	arrayOfResourcesQ[yCoord][0] = qOnResource;
	arrayOfResourcesQ[yCoord][qOnResource] = resPow * taskDiff;
	taskVector[xCoord] = 1;
	matrix[yCoord][xCoord] = 0;
}

int CountTasksInArray(int** arrayOfResourcesQ, int resNum)
{
	int counter = 0;
	for (int i = 0; i < resNum; i++)
	{
		counter += arrayOfResourcesQ[i][0];
	}

	return counter;
}

int** BuildResourceArray(int resNum)
{
	int** resources = (int**)calloc(resNum, sizeof(int*));
	int* values = (int*)calloc(resNum*100, sizeof(int));

	for (int i = 0; i < resNum; i++)
	{
		resources[i] = values + i*100;
	}

	for (int i = 0; i < resNum; i++)
	{
		resources[i][0] = 0;
	}

	return resources;
}

int** PlanTasks(int** matrix, int* tasks, int* ress, int m, int n)
{
	/* set the seed */
	srand((unsigned)time(NULL));

	int** arrayOfResourcesQ = BuildResourceArray(n);

	int* resVector = (int*)malloc(n * sizeof(int));
	int* taskVector = (int*)malloc(m * sizeof(int));

	int tasksLeft = m;

	FillVector(resVector, n, 0);
	FillVector(taskVector, m, 0);

	// Reduce all zero rows
	for (int i = 0; i < n; i++)
	{
		if (AllZerosInRow(matrix, m, n, i))
		{
			resVector[i] = 1;
		}
	}

	// Reduce all zero cols
	for (int i = 0; i < m; i++)
	{
		if (AllZerosInColumn(matrix, m, n, i))
		{
			taskVector[i] = 1;
			tasksLeft--;
		}
	}

	while (tasksLeft > 0)
	{

		// Check One in resources. If there is such - attach task and reduce matrix
		int singleInRow = FindFirstSingleRow(matrix, taskVector, resVector, m, n);
		if (singleInRow != -1)
		{
			int singleXcoord = SingleOneInRow(matrix, taskVector, m, n, singleInRow);
			
			AttachTaskToRes(
				matrix, 
				arrayOfResourcesQ, 
				taskVector, 
				singleXcoord, 
				singleInRow, 
				ress[singleInRow], 
				tasks[singleXcoord]
			);
			
			resVector[singleInRow] = 1;

			tasksLeft--;
			continue;
		}

		// Check One in tasks. If there is such - attach task and reduce matrix
		int singleInColumn = FindFirstSingleColumn(matrix, taskVector, resVector, m, n);
		if (singleInColumn != -1)
		{
			int singleYcoord = SingleOneInColumn(matrix, resVector, m, n, singleInColumn);
			
			AttachTaskToRes(
				matrix, 
				arrayOfResourcesQ, 
				taskVector, 
				singleInColumn, 
				singleYcoord, 
				ress[singleYcoord], 
				tasks[singleInColumn]
			);

			tasksLeft--;
			continue;
		}

		// We could not reduce matrix, therefore, random variant left
		int xCoord;
		do
		{
			xCoord = rand() % m;
		} while (taskVector[xCoord] == 1);

		int yCoord;
		do
		{
			yCoord = rand() % n;
		} while (matrix[yCoord][xCoord] != 1 || resVector[yCoord] == 1);

		AttachTaskToRes(
			matrix, 
			arrayOfResourcesQ, 
			taskVector, 
			xCoord, 
			yCoord, 
			ress[yCoord], 
			tasks[xCoord]);

		tasksLeft--;
	}

	return arrayOfResourcesQ;
}

double AvarageWaitTime(int** planArray, int resourcesNum)
{
	int sumTime = 0;
	int tasksSum = 0;

	for (int i = 0; i < resourcesNum; i++)
	{
		tasksSum += planArray[i][0];
		int currentSum = 0;
		for (int j = 0; j < planArray[i][0] - 1; j++)
		{
			currentSum += planArray[i][j + 1];
			sumTime += currentSum;
		}
	}
	return (double)sumTime / tasksSum;
}
