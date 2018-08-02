#include "measure.h"

Measure::Measure(double time, double meas)
{
    this->meas = meas;
    this->time = time;
}

Measure::~Measure()
{
}

double Measure::getTime()
{
    return this->time;
}

double Measure::getMeas()
{
    return this->meas;
}

