#ifndef MEASURE_H
#define MEASURE_H

class Measure
{

private:

    double time;
    double measure;
public:
    Measure();
    Measure(double, double);
    ~Measure();
    double getTime();
    double getMeasure();
};

#endif // MEASURE_H
