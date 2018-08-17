#include "measure.h"

Measure::Measure(double time, double meas)
{
    this->meas = meas;
    this->time = time;
}

Measure::~Measure()
{
}

double Measure::getTime() const
{
    return this->time;
}

double Measure::getMeas() const
{
    return this->meas;
}

