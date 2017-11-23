#ifndef QUATERNION_H
#define QUATERNION_H


/*!
  \class Quaternion
  \brief The QVector
*/
class Quaternion
{
public:
    Quaternion(double x, double y, double z);
    Quaternion(double w, double x, double y, double z);
    static Quaternion* createQuat(double rotateAngle, double x, double y, double z);
    static Quaternion* createQuat(double rotateAngle, Quaternion* quat);
    void toString();
private:
    double w;
    double x;
    double y;
    double z;
    static Quaternion* normal(double x, double y, double z);
};

#endif // QUATERNION_H
