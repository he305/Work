#ifndef MNK_H
#define MNK_H

#include "matrix.h"

#include <math.h>

class MNK
{
public:
    MNK(double *, double *, double *, int);
    MNK(double *, double *, int);
    ~MNK();

    double getXSr();
    double getA();
    double getB();
    double getWeightA();
    double getWeightB();
private:
    Matrix *x;
    Matrix *y;
    Matrix *w;
};

#endif // MNK_H
