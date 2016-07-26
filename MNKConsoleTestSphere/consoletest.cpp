#include "consoletest.h"
#include <fstream>

using namespace std;

void ConsoleTest::initialize()
{
    system("clear");
    cout << "Полученные данные:\n";
    for (int i = 0; i < size; i++)
    {
        cout << x->at(i) << "\t" << y->at(i) << "\t" << z->at(i) << "\t" << w->at(i) << "\n";
    }
}

void ConsoleTest::handInput()
{
    x->clear();
    y->clear();
    z->clear();
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

    cout << "Введите значения Z\n";
    for (int i = 0; i < size; i++)
    {
        cout << "Z[" << i << "] = ";
        cin >> znach;
        z->push_back(znach);
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
            x->at(i) = rand() % 4;
        }
        else
        {
            x->at(i) = (rand() % 3 + 1) + x->at(i-1);
        }

        y->at(i) = x->at(i) * (rand() % 4 - 2);
        z->at(i) = x->at(i) * (rand() % 4 - 2);
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
    const int rows = 4;
    double** koords = new double*[rows];
    for (int i = 0; i < rows; i++)
    {
        koords[i] = new double[size+1];
        cout << koords[i][size];
        for (int j = 0; j < size; j++)
        {
            switch(i)
            {
                case 0:
                    koords[i][j] = x->at(j);
                    break;
                case 1:
                    koords[i][j] = y->at(j);
                    break;
                case 2:
                    koords[i][j] = 1;
                    break;
                case 3:
                    koords[i][j] = z->at(j);
                    break;
            }
        }
    }
    koords[0][size] = polynomeSize[0];
    koords[1][size] = polynomeSize[1];
    koords[2][size] = 1;
    koords[3][size] = 1;

    cout << "Сформированная матрица\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < size+1; j++)
        {
            cout << koords[i][j] << "\t";
        }
        cout << "\n";
    }

    double** a;
    const int matSize = 3;
    a = new double *[matSize];
    for (int i = 0; i < matSize; i++)
    {
        a[i] = new double[matSize];
    }


    int indexFromBehind = rows-2;
    //Old version: a(i,j) = sum(k->size)(xi^(polynomePower-i+1)*xi^(polynomePower-j+1))
    //New version: a(i,j) = sum(k->size)(xk^(i+j))
    //Weight version a(i, j) = sum(k->size)(xk^(i+j) * wk)
    //Sphere version a(i, j) = sum(k->size)(koords[j][k] * koords[i][k] * wk)
    for (int i = 0; i < matSize; i++)
    {
        for (int j = 0; j < matSize; j++)
        {
            double sum = 0;
            for (int k = 0; k < size; k++)
            {
                sum += pow(koords[j][k], koords[j][size])
                        * pow(koords[indexFromBehind][k], koords[indexFromBehind][size]) * w->at(k);
                cout << "sum[" << i << "][" << j << "] = " << sum << "\t" << koords[j][k] << "\n";
            }
            a[i][j] = sum;
        }
        indexFromBehind--;
    }

    cout << "Матрица А\n";
    for (int i = 0; i < matSize; i++)
    {
        for (int j = 0; j < matSize; j++)
        {
            cout << a[i][j] << "\t";
        }
        cout << "\n";
    }

    indexFromBehind = rows-2;
    //Old version: zi = sum(j->size)(xj^(polynomePower-i+1)*yj)
    //New version: zi = sum(j->size)(xj^i*yj)
    //Weight verison zi = sum(j->size)(xj^i * yj * wj)
    //Sphere version zi = sum(j->size)(koords[3][j] * koords[i][j])
    double* z = new double[matSize];
    for (int i = 0; i < matSize; i++)
    {
        double sum = 0;
        for (int j = 0; j < size; j++)
        {
            sum += koords[3][j] * pow(koords[indexFromBehind][j], koords[indexFromBehind][size]);
        }
        z[i] = sum;
        indexFromBehind--;
    }


    cout << "Правый вектор:\n";
    for (int i = 0; i < matSize; i++)
    {
        cout << z[i] << "\n";
    }

    LUDecompose* lu = new LUDecompose(a, z, matSize);
    double* answer = lu->lupSolve();

    cout << "\n\n";
    for (int i = 0; i < matSize; i++)
    {
        cout << answer[i] << "\n";
    }
    return;

    cout << "\n\nРешение: ";
    for (int i = matSize-1; i >= 0; i--)
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
        else if (i == size)
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
    for (int i = 0; i < matSize; i++)
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

std::vector<double>* ConsoleTest::getZ()
{
    return z;
}

ConsoleTest::ConsoleTest(int size, int* polynomeSize, bool inputType)
{
    this->size = size;
    this->polynomeSize = polynomeSize;
    flag = false;
    x = new vector<double>(size);
    y = new vector<double>(size);
    z = new vector<double>(size);
    w = new vector<double>(size);
    this->inputType = inputType;
}

ConsoleTest::~ConsoleTest()
{
    delete x;
    delete y;
    delete z;
    delete w;
}

void ConsoleTest::setFlag(bool flag)
{
    this->flag = flag;
}
