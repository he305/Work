#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{
    const int N = 6;
    double* a = new double[N];
    double* aIst = new double[N];
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
        aIst[i] = a[i] + 1;
    }
    for (int i = 0; i < N; i++)
    {
        cout << a[i] << '\t';
    }
    Matrix<double>* aMat = new Matrix<double>(a, N);
    Matrix<double>* aIstMat = new Matrix<double>(aIst, N);

    Matrix<double>* rx = new Matrix<double>();
    Matrix<double>* left = aMat->sum(aIstMat->minus());
    Matrix<double>* right = aMat->sum(aIstMat->minus())->transpose();
    rx = left->product(right);
    //aMat->sum(aIstMat->minus())->product(aMat->sum(aIstMat->minus())->transpose());

    cout << "\n\nHERE\n\n";
    for (int i = 0; i < rx->getSize()[0]; i++)
    {
        for (int j = 0; j < rx->getSize()[1]; j++)
        {
            cout << rx->getMatrix()[i][j] << '\t';
        }
        cout << '\n';
    }
    return 0;
}

