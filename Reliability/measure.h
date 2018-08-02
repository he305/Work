#ifndef MEASURE_H
#define MEASURE_H

class Measure
{
public:
    Measure(double time, double meas);
    ~Measure();
    double getTime();
    double getMeas();

private:
    double time;
    double meas;
};

#endif // MEASURE_H
