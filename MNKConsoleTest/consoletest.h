#include <iostream>
#include <math.h>
#include "ludecompose.h"
#include <QString>

#ifndef CONSOLETEST_H
#define CONSOLETEST_H


class ConsoleTest
{
public:
    ConsoleTest();
    ~ConsoleTest();
private:
    void solve();
    void initialize();
    int size;
    double* x;
    double* y;
    double* w;
    int polynomePower;
};

#endif // CONSOLETEST_H
