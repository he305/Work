#include <math.h>
#include <iostream>

#ifndef LUDECOMPOSE_H
#define LUDECOMPOSE_H


class LUDecompose
{
public:
    LUDecompose(double**, double*, int);
    ~LUDecompose();

    double* lupSolve();
private:
    int MaxInColumn(double** mat, int i, int size);
    int* lupDecompose(double** matrix, int size);
    void swapRow(double** mat, int size1, int size2);
    double* forwardSub(double** mat, double* vec, int* p, int size);
    double* backSub(double** mat, double* y, int size);

    double** createMatrix(int size);
    double* createVector(int size);
    void freeMatrix(double** matrix, int size);
    void freeVector(double* vector, int size);
    double** copyMatrix(double**, int);
    double* copyVector(double*, int);
    double** matrix;
    double* vector;
    int size;
};

#endif // LUDECOMPOSE_H
