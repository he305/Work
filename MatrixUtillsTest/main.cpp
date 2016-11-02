#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{
    int size_a[2];
    //int size_b[2];
    cout << "Input size of a";
    for (int i = 0; i < 2; i++)
    {
        cin >> size_a[i];
    }

    /*
    cout << "Input size of b";
    for (int i = 0; i < 2; i++)
    {
        cin >> size_b[i];
    }
    */

    cout << "Input matrix a\n";
    double** a = new double *[size_a[0]];
    for (int i = 0; i < size_a[0]; i++)
    {
        a[i] = new double[size_a[1]];
        for (int j = 0; j < size_a[1]; j++)
        {
            cin >> a[i][j];
        }
    }

    /*
    cout << "Input matrix b\n";
    double** b = new double *[size_b[0]];
    for (int i = 0; i < size_b[0]; i++)
    {
        b[i] = new double[size_b[1]];
        for (int j = 0; j < size_b[1]; j++)
        {
            cin >> b[i][j];
        }
    }
    */

    for (int i = 0; i < size_a[0]; i++)
    {
        for (int j = 0; j < size_a[1]; j++)
        {
            cout << a[i][j] << '\t';
        }
        cout << '\n';
    }

    cout << "\n\n";

    /*
    for (int i = 0; i < size_b[0]; i++)
    {
        for (int j = 0; j < size_b[1]; j++)
        {
            cout << b[i][j] << '\t';
        }
        cout << '\n';
    }

    cout << "\n\n";
    */

    Matrix<double>* mat1 = new Matrix<double>(a, size_a[0], size_a[1]);
    //Matrix<double>* mat2 = new Matrix<double>(b, size_b[0], size_b[1]);

    cout << "Обратная матрица\n";
    mat1->shultsReverse()->printMatrix();

    return 0;
}

