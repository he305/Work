#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

using namespace std;

class Matrix
{
public:
    Matrix(int, int, double ** matrix = nullptr);
    Matrix(int, double* matrix = nullptr);
    ~Matrix();

    void inputMatrix();
    int getRow();
    int getCol();

    bool isSizeEqual(Matrix*);

    /*For MNK*/
    double getMiddle_(Matrix*);
    double getMiddle2_(Matrix*);
    double getXY_(Matrix*, Matrix*);
    /*=======*/

    Matrix* getTransp();

    void add(Matrix*);
    Matrix* addResult(Matrix *);

    double getSr();
    /*=========*/
    void printMatrix();
    /*=========*/
private:
    double** clone(double **);
    double** clone(double *);

    int _nRow = 0;
    int _nCol = 0;

    double** _matrix;
};

#endif // MATRIX_H
