#ifndef EPR_H
#define EPR_H

#include <vector>
#include "aviationclasses.h"


class EPRList
{
public:
    EPRList();
private:
    void init();
    std::vector<EPR> eprs;
};

class EPR
{
public:
    EPR(int& angle, double& avrEPR, double& variance, AviationClasses aviationClass);
private:
    static int delta = 20;
    int angle;
    std::vector<double> EPRvariance; //Среднее значение ЭПР и дисперсии
    AviationClasses aviationClass;
};

#endif // EPR_H
