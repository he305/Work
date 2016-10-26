#include <iostream>
#include "matrix.h"
#include <math.h>

template class Matrix<double>;
template class Matrix<int>;

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
  if (this->getSize()[0] < b->getSize()[1])
    return 0;

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
      for (int k = 0; k <= newSize[1]+1; k++)
      {
        sum += this->getMatrix()[i][k] * b->getMatrix()[k][j];
      }
      newMatrix[i][j] = sum;
    }
  }

  return new Matrix(newMatrix, newSize[0], newSize[1]);
}

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



  //TODO: доработай эту дрисню
  //      я знаю тебе хочется это стереть, но чувак, ты должен её доделать,
  //      проблема только с блоками ссаными

  //UPD: done! проверка для 2 одинаковых матриц 2х2 и
  //     для матриц 2х2 и 3х3
  //TODO: проверка для неквадратных матриц
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
int* Matrix<TYPE>::getSize()
{
  return size;
}

template<class TYPE>
TYPE** Matrix<TYPE>::getMatrix()
{
  return mat;
}
