#include "funcmaker.h"

FuncMaker::FuncMaker(double x, double t0, double interval)
{
    this->x = x;
    this->t0 = t0;
    this->interval = interval;

    y = getY();
    y1 = getY1();
    y2 = getY2();
}

double FuncMaker::make()
{
    return y + y1*interval + y2/2*pow(interval, 2);
}

void FuncMaker::db(double velocity, double R)
{
    double* xMass = new double[(int)interval];
    double* yMass = new double[(int)interval];

    for (int i = t0, j = 0; i < interval, j < interval; i++, j++)
    {
        double x = velocity*i/R;
        xMass[j] = i;

        double y = getY(x);
        double y1 = getY1(x)*(i-t0);
        double y2 = getY2(x)/2*pow(i-t0, 2);

        qDebug () << y;
        qDebug () << y1;
        qDebug () << y2;
        qDebug() << "";

        double yFin = 0;

        double eps = 100;
        int n = 0;
        for (int k = 0; k < 3; k++)
        {
            double yProm = pow(-1, n)/(2*n+1)*pow(x, 2*n+1);
            if (fabs(yProm) < 1 && k != 0)
            {
                break;
            }

            yFin += yProm;
            n++;
        }

        yMass[j] = yFin*-1;

        /*

        if (fabs(y1) < 0.04)
        {
            yFin = y;
        }
        else if (fabs(y2) < 0.04)
        {
            yFin = y + y1;
        }
        else
        {
            yFin = y + y1 + y2;
        }

        yMass[j] = yFin;

        */
    }

    std::ofstream dataBase;
    dataBase.open("C:\\Dropbox\\data.csv");
    dataBase << "X;Y" << std::endl;

    for (int i = 0; i < interval; i++)
    {
        dataBase << xMass[i] << ";" << yMass[i];

        dataBase << std::endl;
    }

    dataBase.close();
}

double FuncMaker::getY()
{
    return atan(x);
}

double FuncMaker::getY1()
{
    return 1/(pow(x, 2) + 1);
}

double FuncMaker::getY2()
{
    return -2*x/(pow((pow(x, 2) + 1), 2));
}

double FuncMaker::getY(double x)
{
    return atan(x);
}

double FuncMaker::getY1(double x)
{
    return 1/(pow(x, 2) + 1);
}

double FuncMaker::getY2(double x)
{
    return -2*x/(pow((pow(x, 2) + 1), 2));
}

void FuncMaker::refresh(double x, double t0, double interval)
{
    this->x = x;
    this->t0 = t0;
    this->interval = interval;

    y = getY();
    y1 = getY1();
    y2 = getY2();
}
