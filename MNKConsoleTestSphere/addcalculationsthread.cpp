#include "addcalculationsthread.h"
#include <iostream>

using namespace std;

void AddCalculationsThread::run()
{
    srand(time(0));
    cout << "Введите количество вычислений: ";
    int size;
    cin >> size;
    cout << "Введите степень полинома: ";

    int* polynomePower = new int(2);
    for (int i = 0; i < 2; i++)
    {
        cin >> polynomePower[i];
    }

    cout << "Метод ввода\n0-ручной\n1-авто\n";
    int choose;
    cin >> choose;
    ConsoleTest* solver = new ConsoleTest(size, polynomePower, choose);
    while(1)
    {
        solver->run();
        solver->setFlag(true);

        if (choose)
        {
            x = solver->getX();
            y = solver->getY();
            z = solver->getZ();

            x->erase(x->begin());
            y->erase(y->begin());
            z->erase(z->begin());

            cout << "\n";
            for (int i = 0; i < x->size(); i++)
            {
                cout << x->at(i) << "\t";
            }
            cout << "\nX: " << x->at(x->size()-1) << "\n";
            x->push_back((rand() % 3 + 1) + x->at(x->size()-1));
            y->push_back(x->at(x->size()-1) * (rand() % 4 - 2));
            z->push_back(x->at(x->size()-1) * (rand() % 4 - 2));
        }
        sleep(100000);
    }
}

void AddCalculationsThread::sleep(unsigned long s)
{
    QThread::msleep(s);
}
