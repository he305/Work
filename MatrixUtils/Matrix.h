#ifndef MATRIX
#define MATRIX

template<typename TYPE>
class Matrix
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

#endif
