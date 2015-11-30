#ifndef FUNCMAKER_H
#define FUNCMAKER_H

#include <QDebug>
#include <math.h>
#include <fstream>

class FuncMaker
{
public:
    FuncMaker(double, double, double);
    double make();
    double getY();
    double getY1();
    double getY2();

    double getY(double);
    double getY1(double);
    double getY2(double);

    void db(double, double);

    void refresh(double, double, double);
private:
    double t0;
    double interval;
    double x;

    double y;
    double y1;
    double y2;
};

#endif // FUNCMAKER_H
