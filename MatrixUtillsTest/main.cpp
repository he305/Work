#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{
    int N;
    cin >> N;
    int M;
    cin >> M;
    double** a = new double *[N];
    for (int i = 0; i < N; i++)
    {
        a[i] = new double[N];
        for (int j = 0; j < N; j++)
        {
            cin >> a[i][j];
        }
    }
    double** b = new double *[M];
    for (int i = 0; i < M; i++)
    {
        b[i] = new double[M];
        for (int j = 0; j < M; j++)
        {
            cin >> b[i][j];
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << a[i][j] << '\t';
        }
        cout << '\n';
    }

    cout << "\n\n";

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cout << b[i][j] << '\t';
        }
        cout << '\n';
    }

    cout << "\n\n";


    Matrix<double>* mat1 = new Matrix<double>(a, N, N);
    Matrix<double>* mat2 = new Matrix<double>(b, M, M);

    mat1->kroneckerProduct(mat2)->printMatrix();

    return 0;
}

