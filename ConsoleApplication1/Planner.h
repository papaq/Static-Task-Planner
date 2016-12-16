#pragma once

#include "Matrix.h"

typedef enum { false, true } bool;

int** PlanTasks(int** matrix, int* tasks, int* ress, int m, int n);

double AvarageWaitTime(int** planArray, int resourcesNum);

