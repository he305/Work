#ifndef MNK_H
#define MNK_H

#include <iostream>
#include <vector>
#include "ludecompose.h"

#include <math.h>

class MNK
{
public:
    MNK(double *, double *, double *, double *, int, int*);
    ~MNK();

    double *calculate();
private:
    std::vector<double>* x;
    std::vector<double>* y;
    std::vector<double>* z;
    std::vector<double>* w;

    int* polynomeSize;

    int size;
};

#endif // MNK_H
