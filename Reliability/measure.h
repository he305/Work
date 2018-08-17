#ifndef MEASURE_H
#define MEASURE_H

class Measure
{
public:
    Measure(double time, double meas);
    ~Measure();
    double getTime() const;
    double getMeas() const;

private:
    double time;
    double meas;
};

#endif // MEASURE_H
