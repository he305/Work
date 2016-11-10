#include <iostream>
#include "matrix.h"
#include <math.h>

template class Matrix<double>;

template<class TYPE>
Matrix<TYPE>::Matrix()
{

}

template<class TYPE>
Matrix<TYPE>::~Matrix()
{
  for (int i = 0; i < size[0]; i++)
  {
    delete mat[i];
  }
  delete mat;

  delete size;
}

template<class TYPE>
Matrix<TYPE>::Matrix(TYPE** a, int row, int col)
{
  this->mat = new TYPE*[row];
  for (int i = 0; i < row; i++)
  {
    this->mat[i] = new TYPE[col];
    for (int j = 0; j < col; j++)
    {
      this->mat[i][j] = a[i][j];
    }
  }
  this->size = new int(2);
  size[0] = row;
  size[1] = col;
}

template<class TYPE>
Matrix<TYPE>::Matrix(TYPE *a, int size)
{
    this->mat = new TYPE*[1];
    for (int i = 0; i < 1; i++)
    {
        this->mat[i] = new TYPE[size];
        for (int j = 0; j < size; j++)
        {
            this->mat[i][j] = a[j];
        }
    }
    this->size = new int[2];
    this->size[0] = 1;
    this->size[1] = size;
}

template<class TYPE>
void Matrix<TYPE>::printMatrix() const
{
  for (int i = 0; i < size[0]; i++)
  {
    for (int j = 0; j < size[1]; j++)
    {
      std::cout<< mat[i][j]<< "\t";
    }
    std::cout << '\n';
  }
}

template<class TYPE>
void Matrix<TYPE>::printRow(int num) const
{
  if (num >= size[0] || num < 0)
  {
    std::cout << "Out of bounds";
    return;
  }

  for (int i = 0; i < size[1]; i++)
  {
    std::cout << mat[num][i] << '\t';
  }
  std::cout << '\n';
}

template<class TYPE>
Matrix<TYPE>* Matrix<TYPE>::sum(Matrix* b)
{
  if (this->size[0] != b->getSize()[0] || this->size[1] != b->getSize()[1])
    return 0;

  TYPE** newMatrix = new TYPE*[this->size[0]];
  for (int i = 0; i < this->size[0]; i++)
  {
    newMatrix[i] = new TYPE[this->size[1]];
    for (int j = 0; j < this->size[1]; j++)
    {
      newMatrix[i][j] = this->getMatrix()[i][j] + b->getMatrix()[i][j];
    }
  }

  return new Matrix<TYPE>(newMatrix, this->size[0], this->size[1]);
}

template<class TYPE>
Matrix<TYPE>* Matrix<TYPE>::product(Matrix* b)
{
  int* newSize = new int(2);
  newSize[0] = this->getSize()[0];
  newSize[1] = b->getSize()[1];

  TYPE** newMatrix = new TYPE*[newSize[0]];
  for(int i = 0; i < newSize[0]; i++)
  {
    newMatrix[i] = new TYPE[newSize[1]];
    for(int j = 0; j < newSize[1]; j++)
    {
      TYPE sum = 0;
      for (int k = 0; k < b->getSize()[0]; k++)
      {
        sum += this->getMatrix()[i][k] * b->getMatrix()[k][j];
      }
      newMatrix[i][j] = sum;
      std::cout << newMatrix[i][j] << '\t';
    }
    std::cout << '\n';
  }

  return new Matrix(newMatrix, newSize[0], newSize[1]);
}

//TODO: доработай эту дрисню
//      я знаю тебе хочется это стереть, но чувак, ты должен её доделать,
//      проблема только с блоками ссаными

//UPD: done! проверка для 2 одинаковых матриц 2х2 и
//     для матриц 2х2 и 3х3
//TODO: проверка для неквадратных матриц:
//UPD: не работает для неквадратных (скорее всего и не надо)
template<class TYPE>
Matrix<TYPE>* Matrix<TYPE>::kroneckerProduct(Matrix* b)
{
  int* newSize = new int[2];
  newSize[0] = this->getSize()[0] * b->getSize()[0];
  newSize[1] = this->getSize()[1] * b->getSize()[1];

  int nBlockMatrix = this->getSize()[0] * this->getSize()[1];

  TYPE*** blockMatrix = new TYPE**[nBlockMatrix];
  for (int i = 0; i < nBlockMatrix; i++)
  {
    blockMatrix[i] = new TYPE*[b->getSize()[0]];
    for (int j = 0; j < b->getSize()[0]; j++)
    {
      blockMatrix[i][j] = new TYPE[b->getSize()[1]];
    }
  }


  int block = 0;
  for (int l = 0; l < nBlockMatrix/this->getSize()[0]; l++)
  {
    for (int k = 0; k < nBlockMatrix/this->getSize()[0]; k++)
    {
      for (int i = 0; i < b->getSize()[0]; i++)
      {
        for (int j = 0; j < b->getSize()[1]; j++)
        {
          blockMatrix[block][i][j] = this->getMatrix()[l][k] * b->getMatrix()[i][j];
        }
      }
      block++;
    }
  }

  std::cout << "\nNow matrixes go\n";

  for (int k = 0; k < nBlockMatrix; k++)
  {
      for (int i = 0; i < b->getSize()[0]; i++)
      {
          for (int j = 0; j < b->getSize()[1]; j++)
          {
              std::cout << blockMatrix[k][i][j] << "\t";
          }
          std::cout << '\n';
      }
      std::cout << "\n\n";
  }

  TYPE** newMatrix = new TYPE*[newSize[0]];
  for (int i = 0; i < newSize[0]; i++)
  {
    newMatrix[i] = new TYPE[newSize[1]];
  }



  int l = 0;
  int k = 0;
  block = 0;


  for (int i = 0; i < newSize[0]; i++)
  {
      if (k >= b->getSize()[0] && i != newSize[0] - 1)
      {
          k = 0;
          block += 2;
      }

      l = 0;
      for (int j = 0; j < newSize[1]; j++)
      {
          if (l >= b->getSize()[1] && j != newSize[1] - 1)
          {
              l = 0;
              block++;
          }
          newMatrix[i][j] = blockMatrix[block][k][l];
          l++;
      }
      block--;
      k++;
  }



  return new Matrix(newMatrix, newSize[0], newSize[1]);
}

template<class TYPE>
Matrix<TYPE>* Matrix<TYPE>::shultsReverse()
{
    int* size = new int[2];
    size[0] = getSize()[0];
    size[1] = getSize()[1];
    double** edinMat = new double*[size[0]];
    for (int i = 0; i < size[0]; i++)
    {
        edinMat[i] = new double[size[1]];
        for (int j = 0; j < size[1]; j++)
        {
            edinMat[i][j] = 0;
        }

        edinMat[i][i] = 2;
    }

    Matrix<double>* edin = new Matrix<double>(edinMat, size[0], size[1]);

    double N1 = 0, Ninf = 0; //норма матрицы по столбцам и по строкам
    Matrix<double>* inv = clone(this);
    inv->printMatrix();
    /*
    for (int row = 0; row < size[0]; row++){
        double colsum = 0, rowsum = 0;
        for(int col = 0; col < size[1]; col++){
            rowsum += fabs(inv->getMatrix()[row][col]);
            colsum += fabs(inv->getMatrix()[col][row]);
        }
        N1 = std::max(colsum, N1);
        Ninf = std::max(rowsum, Ninf);
    }

    inv = inv->transpose()->productNumber(1/(N1*Ninf));
    double EPS = 0.001;

    while (fabs (this->product(inv)->getGaussDet() - 1) >= EPS)
    {
        Matrix* prev = clone(inv);
        inv = this->product(prev);
        inv = inv->productNumber(-1);
        inv = inv->sum(edin);
        inv = prev->product(inv);
        delete prev;
    }
    delete edinMat;
    */
    return inv;
}

template<class TYPE>
Matrix<TYPE>* Matrix<TYPE>::transpose()
{
    TYPE** trasposedMat = new TYPE *[this->getSize()[1]];
    for (int i = 0; i < this->getSize()[1]; i++)
    {
        trasposedMat[i] = new TYPE[this->getSize()[0]];
        for (int j = 0; j < this->getSize()[0]; j++)
        {
            trasposedMat[i][j] = this->getMatrix()[j][i];
        }
    }

    return new Matrix(trasposedMat, this->getSize()[0], this->getSize()[1]);
}

template<class TYPE>
Matrix<TYPE>* Matrix<TYPE>::productNumber(double num)
{
    for (int i = 0; i < this->getSize()[0]; i++)
    {
        for (int j = 0; j < this->getSize()[1]; j++)
        {
            this->getMatrix()[i][j] *= num;
        }
    }

    return new Matrix(this->getMatrix(), this->getSize()[0], this->getSize()[1]);
}

template<class TYPE>
Matrix<TYPE>* Matrix<TYPE>::minus()
{
    double** a = new double*[this->getSize()[0]];
    for (int i = 0; i < this->getSize()[0]; i++)
    {
        a[i] = new double[this->getSize()[1]];
        for (int j = 0; j < this->getSize()[1]; j++)
        {
            a[i][j] = -this->getMatrix()[i][j];
        }
    }

    return new Matrix(a, this->getSize()[0], this->getSize()[1]);
}


template<class TYPE>
Matrix<TYPE>* Matrix<TYPE>::clone(Matrix *a)
{
    TYPE** newMat = new TYPE*[a->getSize()[0]];
    for (int i = 0; i < a->getSize()[0]; i++)
    {
        newMat[i] = new TYPE[a->getSize()[1]];
        for (int j = 0; j < a->getSize()[1]; j++)
        {
            newMat[i][j] = a->getMatrix()[i][j];
        }
    }

    return new Matrix(newMat, a->getSize()[0], a->getSize()[1]);
}

template<class TYPE>
double Matrix<TYPE>::getGaussDet()
{
    double det = 1;
    for (int i = 0; i < this->getSize()[0]; i++)
    {
        det *= this->getMatrix()[i][i];
    }
    return det;
}

template<class TYPE>
int* Matrix<TYPE>::getSize()
{
  return size;
}

template<class TYPE>
TYPE** Matrix<TYPE>::getMatrix()
{
  return mat;
}
