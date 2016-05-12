#include <iostream>
#include <math.h>

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
    int polynomePower;
};

#endif // CONSOLETEST_H
