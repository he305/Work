#include "consoletest.h"
#include <fstream>

using namespace std;

void ConsoleTest::initialize()
{
    system("clear");
    cout << "Полученные данные:\n";
    for (int i = 0; i < size; i++)
    {
        cout << x->at(i) << "\t" << y->at(i) << "\t" << w->at(i) << "\n";
    }

    cout << "Введите степень полинома: ";
    //cin >> polynomePower;
}

void ConsoleTest::handInput()
{
    x->clear();
    y->clear();
    w->clear();

    double znach;
    cout << "Введите значения X\n";
    for (int i = 0; i < size; i++)
    {
        cout << "X[" << i << "] = ";
        cin >> znach;
        x->push_back(znach);
    }

    cout << "Введите значения Y\n";
    for (int i = 0; i < size; i++)
    {
        cout << "Y[" << i << "] = ";
        cin >> znach;
        y->push_back(znach);
    }

    cout << "Введите веса W\n";
    for (int i = 0; i < size; i++)
    {
        cout << "w[" << i << "] = ";
        cin >> znach;
        w->push_back(znach);
    }
}

void ConsoleTest::autoInput()
{
    srand(time(0));
    for (int i = 0; i < size; i++)
    {
        if (i == 0)
        {
            x->at(i) = rand() % 30 - 15;
        }
        else
        {
            x->at(i) = (rand() % 3 + 1) + x->at(i-1);
        }

        y->at(i) = x->at(i) * (rand() % 4 - 2);
    }

    double h = 1/double(size); //Шаг вычисления весов
    cout << "Шаг: " << h << "\n";

    for (int i = 0; i < size; i++)
    {
        w->at(i)= 1;
    }
}

void ConsoleTest::solve()
{
    double** a;
    a = new double *[polynomePower+1];
    for (int i = 0; i < polynomePower+1; i++)
    {
        a[i] = new double[polynomePower+1];
    }

    //Old version: a(i,j) = sum(k->size)(xi^(polynomePower-i+1)*xi^(polynomePower-j+1))
    //New version: a(i,j) = sum(k->size)(xk^(i+j))
    //Weight version a(i, j) = sum(k->size)(xk^(i+j) * wk)
    for (int i = 0; i < polynomePower+1; i++)
    {
        for (int j = 0; j < polynomePower+1; j++)
        {
            double sum = 0;
            for (int k = 0; k < size; k++)
            {
                sum += pow(x->at(k), i+j) * w->at(k);
                cout << i << ":" << j << ":" << k << ":" <<sum << "\n";
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

    //Old version: zi = sum(j->size)(xj^(polynomePower-i+1)*yj)
    //New version: zi = sum(j->size)(xj^i*yj)
    //Weight verison zi = sum(j->size)(xj^i * yj * wj)
    double* z = new double[polynomePower+1];
    for (int i = 0; i < polynomePower+1; i++)
    {
        double sum = 0;
        for (int j = 0; j < size; j++)
        {
            sum += pow(x->at(j), i) * y->at(j) * w->at(j);
        }
        z[i] = sum;
    }

    cout << "Правый вектор:\n";
    for (int i = 0; i < polynomePower+1; i++)
    {
        cout << z[i] << "\n";
    }

    LUDecompose* lu = new LUDecompose(a, z, polynomePower+1);
    double* answer = lu->lupSolve();

    cout << "\n\nРешение: ";
    for (int i = polynomePower; i >= 0; i--)
    {
        if (fabs(answer[i]) < 0.0000001)
            answer[i] = 0;

        if (i == 0)
        {
            if (answer[i] >= 0)
                cout << " + " << answer[i];
            else
                cout << answer[i];
            cout << "\n";
        }
        else if (i == polynomePower)
        {
            cout << answer[i] << "x^" << i;
        }
        else
        {
            if (answer[i] >= 0)
                cout << " + " << answer[i] << "x^" << i;
            else
                cout << answer[i] << "x^" << i;
        }
    }

    ofstream dataBase;

    if (flag)
    {
        dataBase.open("data.csv", ios_base::app);
        dataBase << x->at(x->size()-1) << ";" << y->at(y->size()-1) << endl;
    }
    else
    {
        dataBase.open("data.csv");
        for (int i = 0; i < x->size(); i++)
        {
            dataBase << x->at(i) << ";" << y->at(i) << endl;
        }
    }

    dataBase.close();

    dataBase.open("koff.csv");
    for (int i = 0; i < polynomePower+1; i++)
    {
        dataBase << answer[i] << std::endl;
    }
}

void ConsoleTest::run()
{
    if (inputType)
    {
        autoInput();
    }
    else
    {
        handInput();
    }

    initialize();

    solve();
}

std::vector<double>* ConsoleTest::getX()
{
    return x;
}

std::vector<double>* ConsoleTest::getY()
{
    return y;
}

ConsoleTest::ConsoleTest(int size, int polynomePower, bool inputType)
{
    this->size = size;
    this->polynomePower = polynomePower;
    flag = false;
    x = new vector<double>(size);
    y = new vector<double>(size);
    w = new vector<double>(size);
    this->inputType = inputType;
}

ConsoleTest::~ConsoleTest()
{
    delete x;
    delete y;
    delete w;
}

void ConsoleTest::setFlag(bool flag)
{
    this->flag = flag;
}
