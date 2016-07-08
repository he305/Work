#include "ludecompose.h"

void LUDecompose::freeMatrix(double** mat, int size)
{
    for (int i = 0; i < size; i++)
    {
        delete mat[i];
    }
    delete mat;
}

void LUDecompose::freeVector(double* vec, int size)
{
    delete vec;
}

double** LUDecompose::createMatrix(int size)
{
    double** mat = new double *[size];
    for (int i = 0; i < size; i++)
    {
        mat[i] = new double[size];
    }
    return mat;
}

double* LUDecompose::createVector(int size)
{
    double* vec = new double[size];
    return vec;
}

double* LUDecompose::copyVector(double* vector, int size)
{
    for (int i = 0; i < size; i++)
    {
        this->vector[i] = vector[i];
    }
    return vector;
}

double** LUDecompose::copyMatrix(double** matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            this->matrix[i][j] = matrix[i][j];
        }
    }

    return matrix;
}

LUDecompose::LUDecompose(double** matrix, double* vector, int size)
{
    this->size = size;
    this->vector = createVector(this->size);
    this->matrix = createMatrix(this->size);


    this->matrix = copyMatrix(matrix, this->size);
    this->vector = copyVector(vector, this->size);
}

double* LUDecompose::lupSolve()
{
    double** a1, *x, *y;
    int* p;

    a1 = createMatrix(size);
    a1 = copyMatrix(matrix, size);
    p = lupDecompose(a1, size);
    y = forwardSub(a1, vector, p, size);
    x = backSub(a1, y, size);

    return x;
}

int* LUDecompose::lupDecompose(double** mat, int size)
{
    int j, k;
    int* p = new int[size];
    for (int i = 0; i < size; i++)
    {
        p[i] = i;
    }
    for (int i = 0; i < size; i++)
    {
        j = MaxInColumn(mat, i, size);
        if (i != j)
        {
            swapRow(mat, i, j);
            k = p[i];
            p[i] = p[j];
            p[j] = k;
        }
        for (int j = i+1; j < size; j++)
        {
            mat[j][i] /= mat[i][i];
        }
        for (int j = i+1; j < size; j++)
        {
            for (int k = i+1; k < size; k++)
            {
                mat[j][k] -= (mat[i][k]*mat[j][i]);
            }
        }
    }

    return p;
}

void LUDecompose::swapRow(double** mat, int size1, int size2)
{
    double* temp = mat[size1];
    mat[size1] = mat[size2];
    mat[size2] = temp;
}

int LUDecompose::MaxInColumn(double** mat, int i, int size)
{
    int j = i + 1, k = i;

    double max = fabs(mat[i][i]);
    for(; j < size; j++)
    {
        if (fabs(mat[j][i]) > max)
        {
            max = fabs(mat[j][i]);
            k = j;
        }
    }

    return k;
}

double* LUDecompose::forwardSub(double** mat, double* vec, int* p, int size)
{
    double* y = new double[size];
    for (int i = 0; i < size; i++)
    {
        y[i] = vec[p[i]];
        for (int j = 0; j < i; j++)
        {
            y[i] -= mat[i][j]*y[j];
        }
    }

    return y;
}

double* LUDecompose::backSub(double** mat, double* y, int size)
{
    double* x = new double[size];

    for (int i = 0; i < size; i++)
    {
        x[size-i-1] = y[size-1-i];
        for (int j = 0; j < i; j++)
        {
            x[size-1-i] -= (mat[size-1-i][size-1-j]*x[size-1-j]);
        }
        x[size-1-i] /= mat[size-1-i][size-1-i];
    }

    return x;
}

LUDecompose::~LUDecompose()
{
    freeMatrix(matrix, size);
    freeVector(vector, size);
}
