#include "measure.h"

Measure::Measure()
{

}

Measure::Measure(double time, double measure)
{
    this->measure = measure;
    this->time = time;
}

double Measure::getTime()
{
    return this->time;
}

double Measure::getMeasure()
{
    return this->measure;
}
