#include "mnk.h"

MNK::MNK(double *xMatrix, double *yMatrix, double *sMatrix, int size)
{
    x = new Matrix(size, xMatrix);
    y = new Matrix(size, yMatrix);
    w = new Matrix(size, sMatrix);
}

MNK::MNK(double *xMatrix, double *yMatrix, int size)
{
    x = new Matrix(size, xMatrix);
    y = new Matrix(size, yMatrix);
    w = nullptr;
}

MNK::~MNK()
{
    delete x;
    delete y;

    if (w != nullptr)
        delete w;
}

double MNK::getA()
{
    double a = x->getXY_(y, w) - y->getMiddle_(w)*x->getMiddle_(w);
    a /= x->getMiddle2_(w) - pow(x->getMiddle_(w), 2);
    return a;
}

double MNK::getB()
{
    double b = y->getMiddle_(w) - getA()*x->getMiddle_(w);
    return b;
}

double MNK::getWeightA()
{
    double a = x->getXY_(y, w);
    a /= x->getMiddle2_(w);
    return a;
}

double MNK::getWeightB()
{
    double b = y->getMiddle_(w) - getA()*x->getMiddle_(w);
    return b;
}
