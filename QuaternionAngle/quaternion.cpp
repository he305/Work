#include "quaternion.h"
#include "math.h"
#include <iostream>

using namespace std;

/*!
 * \brief Quaternion::Quaternion
 * \param w - rotate angle
 * \param x - x coord
 * \param y - y coord
 * \param z - z coord
 */
Quaternion::Quaternion(double x, double y, double z)
{
    this->w = 0;
    this->x = x;
    this->y = y;
    this->z = z;
}

Quaternion::Quaternion(double w, double x, double y, double z)
{
    this->w = w;
    this->x = x;
    this->y = y;
    this->z = z;
}

Quaternion* Quaternion::createQuat(double rotateAngle, double x, double y, double z)
{
    double rotateAngleRad = rotateAngle*180/M_PI;
    Quaternion* q = normal(x, y, z);
    q->w = cos(rotateAngleRad/2);
    q->x *= sin(rotateAngleRad/2);
    q->y *= sin(rotateAngleRad/2);
    q->z *= sin(rotateAngleRad/2);
    return q;
}

Quaternion* Quaternion::createQuat(double rotateAngle, Quaternion* quat)
{
    Quaternion* q = new Quaternion(cos(rotateAngle*180/M_PI), quat->x, quat->y, quat->z);
    return q;
}

Quaternion* Quaternion::normal(double x, double y, double z)
{
    Quaternion* q = new Quaternion(x, y, z);
    double length = sqrt(pow(q->x, 2) + pow(q->y, 2) + pow(q->z, 2));
    if (length == 0)
    {
        cout << "Вектор равен 0";
        return q;
    }
    q->x /= length;
    q->y /= length;
    q->z /= length;
    return q;
}

void Quaternion::toString()
{
    cout << "x: " << this->x << "\ny: " << this->y << "\nz: " << this->z << "\nw: " << this->w << '\n';
}
