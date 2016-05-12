#include "consoletest.h"

using namespace std;

void ConsoleTest::initialize()
{
    cout << "Введите общее количество точек: ";
    cin >> size;
    x = new double[size];
    y = new double[size];

    cout << "Введите значения X\n";
    for (int i = 0; i < size; i++)
    {
        cout << "X[" << i << "] = ";
        cin >> x[i];
    }

    cout << "Введите значения Y\n";
    for (int i = 0; i < size; i++)
    {
        cout << "Y[" << i << "] = ";
        cin >> y[i];
    }

    system("clear");
    cout << "Полученные данные:\n";
    for (int i = 0; i < size; i++)
    {
        cout << x[i] << "\t" << y[i] << "\n";
    }

    cout << "Введите степень полинома: ";
    cin >> polynomePower;
}

void ConsoleTest::solve()
{
    double** a;
    a = new double *[polynomePower+1];
    for (int i = 0; i < polynomePower+1; i++)
    {
        a[i] = new double[polynomePower+1];
    }

    //a(i,j) = sum(k->size)(xi^(polynomePower-i+1)*xi^(polynomePower-j+1))
    for (int i = 0; i < polynomePower+1; i++)
    {
        for (int j = 0; j < polynomePower+1; j++)
        {
            int sum = 0;
            for (int k = 0; k < size; k++)
            {
                sum += pow(x[k], polynomePower-i+1) * pow(x[k], polynomePower-j+1);
            }
            a[i][j] = sum;
        }
    }
    cout << "\nМатрица А:\n";
    for (int i = 0; i < polynomePower+1; i++)
    {
        for (int j = 0; j < polynomePower+1; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }

    //zi = sum(j->size)(xj^(polynomePower-i+1)*yj)
    double* z = new double[polynomePower+1];
    for (int i = 0; i < polynomePower+1; i++)
    {
        int sum = 0;
        for (int j = 0; j < size; j++)
        {
            sum += pow(x[j], polynomePower-i+1) * y[j];
        }
        z[i] = sum;
    }

    cout << "Правый вектор:\n";
    for (int i = 0; i < polynomePower+1; i++)
    {
        cout << z[i] << "\n";
    }
}

ConsoleTest::ConsoleTest()
{
    cout << "Консольная версия программы апроксимации функции методом наименьших "
            "квадратов полиномом\n";
    initialize();
    solve();
}

ConsoleTest::~ConsoleTest()
{
    delete x;
    delete y;
}
