#pragma once
#include <stdio.h>
#include <stdlib.h>

int** MakeMatrix(int m, int n);

void FillRandMatrix(int** matrix, int m, int n, int rate, int diff);

int* MakeVector(int m);

void FillVector(int* vector, int m, int what);

void FillRandVector(int * vector, int m, int diff);

void PrintMatrix(int** matrix, int m, int n);

void PrintVector(int* matrix, int m);

int GetX(int i, int cols);

int GetY(int i, int cols);
