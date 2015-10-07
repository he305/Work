#include "radspeed.h"

RadSpeed::RadSpeed(int* t, int* r, int* angle, int* rTEMP)
{
    this->t = t;
    this->r = r;
    this->angle = angle;
    this->rTEMP = rTEMP;
}

RadSpeed::RadSpeed(int& t, int& r, int& angle, int& rTEMP)
{
    this->t = &t;
    this->r = &r;
    this->angle = &angle;
    this->rTEMP = &rTEMP;
}


RadSpeed::~RadSpeed()
{
    delete t;
    delete r;
    delete angle;
    delete rTEMP;
}

