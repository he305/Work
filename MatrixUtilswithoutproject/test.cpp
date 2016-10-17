#include <iostream>
#include <math.h>
#include "Matrix.h"

using namespace std;

double** product(double** a, double** b);


int main()
{
  int row = 2;
  int col = 2;
  double** a = new double*[row];
  for (int i = 0; i < row; i++)
  {
      a[i] = new double[col];
      for (int j = 0; j < col; j++)
      {
        cin >> a[i][j];
      }
  }
  Matrix<double>* mat1 = new Matrix<double>(a, row, col);


  double** b = new double*[row];
  for (int i = 0; i < row; i++)
  {
      b[i] = new double[col];
      for (int j = 0; j < col; j++)
      {
        cin >> b[i][j];
      }
  }
  Matrix<double>* mat2 = new Matrix<double>(b, row, col);

  mat1->printMatrix();
  cout << '\n';
  mat2->printMatrix();
  cout << '\n';
  Matrix<double>* mat3 = mat1->kroneckerProduct(mat2);
  mat3->printMatrix();

  return 0;
}
