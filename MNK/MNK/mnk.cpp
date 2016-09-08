#include "mnk.h"
#include "QDebug"

MNK::MNK(double *xMatrix, double *yMatrix, double* zMatrix, double *sMatrix,
         int size, int* polynomeSize)
{
    x = new std::vector<double>(size);
    y = new std::vector<double>(size);
    z = new std::vector<double>(size);
    w = new std::vector<double>(size);

    x->clear();
    y->clear();
    z->clear();
    w->clear();
    for (int i = 0; i < size; i++)
    {
        x->push_back(xMatrix[i]);
        y->push_back(yMatrix[i]);
        z->push_back(zMatrix[i]);
        w->push_back(sMatrix[i]);
    }

    this->polynomeSize = polynomeSize;

    this->size = size;
}


MNK::~MNK()
{
    delete x;
    delete y;
    delete z;

    if (w != nullptr)
        delete w;
}

double* MNK::calculate()
{
    const int rows = 4;
    double** koords = new double*[rows];
    for (int i = 0; i < rows; i++)
    {
        koords[i] = new double[size+1];
        for (int j = 0; j < size; j++)
        {
            switch(i)
            {
                case 0:
                    koords[i][j] = x->at(j);
                    break;
                case 1:
                    koords[i][j] = y->at(j);
                    break;
                case 2:
                    koords[i][j] = 1;
                    break;
                case 3:
                    koords[i][j] = z->at(j);
                    break;
            }
        }
    }
    koords[0][size] = polynomeSize[0];
    koords[1][size] = polynomeSize[1];
    koords[2][size] = 1;
    koords[3][size] = 1;

    double** a;
    const int matSize = 3;
    a = new double *[matSize];
    for (int i = 0; i < matSize; i++)
    {
        a[i] = new double[matSize];
    }

    int indexFromBehind = rows-2;
    //Old version: a(i,j) = sum(k->size)(xi^(polynomePower-i+1)*xi^(polynomePower-j+1))
    //New version: a(i,j) = sum(k->size)(xk^(i+j))
    //Weight version a(i, j) = sum(k->size)(xk^(i+j) * wk)
    //Sphere version a(i, j) = sum(k->size)(koords[j][k] * koords[i][k] * wk)
    for (int i = 0; i < matSize; i++)
    {
        for (int j = 0; j < matSize; j++)
        {
            double sum = 0;
            for (int k = 0; k < size; k++)
            {
                sum += pow(koords[j][k], koords[j][size])
                       * pow(koords[indexFromBehind][k], koords[indexFromBehind][size])
                       * w->at(k);
            }
            a[i][j] = sum;
        }
        indexFromBehind--;
    }

    //Bug probably in index



    indexFromBehind = rows-2;
    //Old version: zi = sum(j->size)(xj^(polynomePower-i+1)*yj)
    //New version: zi = sum(j->size)(xj^i*yj)
    //Weight verison zi = sum(j->size)(xj^i * yj * wj)
    //Sphere version zi = sum(j->size)(koords[3][j] * koords[i][j])
    double* z = new double[matSize];
    for (int i = 0; i < matSize; i++)
    {
        double sum = 0;
        for (int j = 0; j < size; j++)
        {
            sum += koords[3][j] * pow(koords[indexFromBehind][j], koords[indexFromBehind][size]);
        }
        z[i] = sum;
        indexFromBehind--;
    }

    LUDecompose* lu = new LUDecompose(a, z, matSize);
    double* answer = lu->lupSolve();

    for (int i = 0; i < matSize; i++)
    {
        if (answer[i] <= 0.00001)
            answer[i] = 0;
    }

    return answer;
}
