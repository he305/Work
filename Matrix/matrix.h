#ifndef MATRIX_H
#define MATRIX_H

#include "matrix_global.h"

template <typename TYPE>
class MATRIXSHARED_EXPORT Matrix
{

public:
  Matrix(TYPE **a, int row, int col);
  Matrix(TYPE **a, int size);
  void printMatrix() const;
  void printRow(int num) const;
  ~Matrix();

  Matrix* sum(Matrix* b);
  Matrix* product(Matrix* b);
  Matrix* kroneckerProduct(Matrix* b);

  int* getSize();
  TYPE** getMatrix();
private:
  int* size;
  TYPE** mat;
};

#endif // MATRIX_H
