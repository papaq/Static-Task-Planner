// ConsoleApplication1.c : Defines the entry point for the console application.
//

#include "Matrix.h"
#include "Planner.h"

int main()
{
	int tasksNum = 80;
	int resourcesNum = 20;
	int percent = 80;
	int procRate = 20;
	int difficulty = 20;

	
	printf("Number of tasks ....................... %d\n", tasksNum);
	printf("Number of resources ................... %d\n", resourcesNum);
	printf("Upper bound of task difficulty ........ %d\n", difficulty);
	printf("Upper bound of resource performance ... %d\n", procRate);
	printf("Percentage of busy cells in matrix .... %d\n\n", percent);

	// Check algorythm once
	int** matrix = MakeMatrix(tasksNum, resourcesNum);
	FillRandMatrix(matrix, tasksNum, resourcesNum, percent, difficulty);
	PrintMatrix(matrix, tasksNum, resourcesNum);

	int* tasksVector = MakeVector(tasksNum);
	int* resourcesVector = MakeVector(resourcesNum);

	FillRandVector(tasksVector, tasksNum, difficulty);
	FillRandVector(resourcesVector, resourcesNum, procRate);

	int** planArray = PlanTasks(matrix, tasksVector, resourcesVector, tasksNum, resourcesNum);
	
	double avarageWaitTime = AvarageWaitTime(planArray, resourcesNum);
	printf("Average wait time ....................... %.2f\n", avarageWaitTime);
	

	/*
	// Calculate average numbers
	for (int i = 1; i < 100; i+=5)
	{
		double sumTime = 0;

		for (int j = 0; j < 100; j++)
		{
			int** matrix = MakeMatrix(tasksNum, resourcesNum);
			int* tasksVector = MakeVector(tasksNum);
			int* resourcesVector = MakeVector(resourcesNum);

			FillRandMatrix(matrix, tasksNum, resourcesNum, i, difficulty);
			FillRandVector(tasksVector, tasksNum, difficulty);
			FillRandVector(resourcesVector, resourcesNum, procRate);

			int** planArray = PlanTasks(matrix, tasksVector, resourcesVector, tasksNum, resourcesNum);

			sumTime += AvarageWaitTime(planArray, resourcesNum);
		}
		
		printf("%.2f\n", sumTime/10);
	}
	*/

	scanf("");
    return 0;
}

