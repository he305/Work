#include <QCoreApplication>
#include "quaternion.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{

    Quaternion* q = new Quaternion(0, 0, 0);
    Quaternion* q2 = Quaternion::createQuat(90, 90, 0, 0);

    q2->toString();
    return 0;
}
