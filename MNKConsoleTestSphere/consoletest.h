#include <iostream>
#include <math.h>
#include "ludecompose.h"
#include <QString>
#include <time.h>
#include <QThread>

#ifndef CONSOLETEST_H
#define CONSOLETEST_H


class ConsoleTest
{
public:
    void run();
    std::vector<double>* getX();
    std::vector<double>* getY();
    std::vector<double>* getZ();
    void setFlag(bool flag);
    ConsoleTest(int size, int polynomePower, bool inputType);
    ~ConsoleTest();
private:
    void solve();
    void initialize();
    void handInput();
    void autoInput();
    int size;
    std::vector<double>* x;
    std::vector<double>* y;
    std::vector<double>* z;
    std::vector<double>* w;
    int polynomePower;
    bool flag;
    bool inputType;
};

#endif // CONSOLETEST_H
