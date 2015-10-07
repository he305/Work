#ifndef RADSPEED_H
#define RADSPEED_H


class RadSpeed
{
public:
    RadSpeed(int*, int*, int*, int*);
    RadSpeed(int&, int&, int&, int&);
    ~RadSpeed();
    int* t;
    int* r;
    int* angle;
    int* rTEMP;
};

#endif // RADSPEED_H
