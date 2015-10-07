#include "matrix.h"

Matrix::Matrix(int nRow, int nCol, double **matrix)
{
    _nRow = nRow;
    _nCol = nCol;

    if (matrix != nullptr)
    {
        _matrix = clone(matrix);
    }
    else
    {
        _matrix = new double *[_nRow];
        for (int i = 0; i < _nRow; i++)
        {
            _matrix[i] = new double[_nCol];
            for (int j = 0; j < _nCol; j++)
            {
                _matrix[i][j] = 0;
            }
        }
    }
}

Matrix::Matrix(int col, double *matrix)
{
    _nRow = 1;
    _nCol = col;

    if (matrix != nullptr)
    {
        _matrix = clone(matrix);
    }
    else
    {
        _matrix = new double *[_nRow];
        for (int i = 0; i < _nRow; i++)
        {
            _matrix[i] = new double[_nCol];
            for (int j = 0; j < _nCol; j++)
            {
                _matrix[i][j] = 1;
            }
        }
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < _nCol; i++)
    {
        delete[] _matrix[i];
    }

    delete[] _matrix;
}

double** Matrix::clone(double *a)
{
    double **temp = new double *[_nRow];
    for (int i = 0; i < _nRow; i++)
    {
        temp[i] = new double[_nCol];
        for (int j = 0; j < _nCol; j++)
        {
            temp[i][j] = a[j];
        }
    }

    return temp;
}

double** Matrix::clone(double **a)
{
    double **temp = new double *[_nRow];
    for (int i = 0; i < _nRow; i++)
    {
        temp[i] = new double[_nCol];
        for (int j = 0; j < _nCol; j++)
        {
            temp[i][j] = a[i][j];
        }
    }

    return temp;
}

void Matrix::printMatrix()
{
    for (int i = 0; i < _nRow; i++)
    {
        for (int j = 0; j < _nCol; j++)
        {
            cout << _matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

Matrix* Matrix::getTransp()
{
    Matrix* temp = new Matrix(this->getCol(), this->getRow());

    for (int i = 0; i < _nCol; i++)
    {
        for (int j = 0; j < _nRow; j++)
        {
            temp->_matrix[i][j] = this->_matrix[j][i];
        }
    }

    return temp;
}

double Matrix::getSr()
{
    double sr = 0;
    for (int i = 0; i < this->getRow(); i++)
    {
        for (int j = 0; j < this->getCol(); j++)
        {
            sr += this->_matrix[i][j];
        }
    }

    return sr;
}

void Matrix::inputMatrix()
{
    cout << "Input matrix: " << _nRow << " x " << _nCol << endl;
    for (int i = 0; i < _nRow; i++)
    {
        for (int j = 0; j < _nCol; j++)
        {
            cin >> _matrix[i][j];
        }
    }
}

void Matrix::add(Matrix* a)
{
    for (int i = 0; i < this->getRow(); i++)
    {
        for (int j = 0; j < this->getCol(); j++)
        {
            this->_matrix[i][j] += a->_matrix[i][j];
        }
    }
}

Matrix* Matrix::addResult(Matrix* a)
{
    Matrix *temp = new Matrix(this->getRow(), this->getCol());
    for (int i = 0; i < this->getRow(); i++)
    {
        for (int j = 0; j < this->getCol(); j++)
        {
            temp->_matrix[i][j] = this->_matrix[i][j] + a->_matrix[i][j];
        }
    }
    return temp;
}

int Matrix::getRow()
{
    return _nRow;
}

int Matrix::getCol()
{
    return _nCol;
}

double Matrix::getMiddle_(Matrix* w)
{
    double x_ = 0;

    for (int i = 0; i < _nRow; i++)
    {
        for (int j = 0; j < _nCol; j++)
        {
            x_ += w->_matrix[i][j] * _matrix[i][j];
        }
    }

    x_ /= w->getSr();
    return x_;
}

double Matrix::getXY_(Matrix* a, Matrix* w)
{
    if (!this->isSizeEqual(a))
        return 0;

    double xy_ = 0;
    for (int i = 0; i < _nRow; i++)
    {
        for (int j = 0; j < _nCol; j++)
        {
            xy_ += w->_matrix[i][j] * this->_matrix[i][j] * a->_matrix[i][j];
        }
    }
    xy_ /= w->getSr();
    return xy_;
}

double Matrix::getMiddle2_(Matrix* w)
{
    double xx_ = 0;
    for (int i = 0; i < _nRow; i++)
    {
        for (int j = 0; j < _nCol; j++)
        {
            xx_ += w->_matrix[i][j] * _matrix[i][j] * _matrix[i][j];
        }
    }

    xx_ /= w->getSr();
    return xx_;
}

bool Matrix::isSizeEqual(Matrix* a)
{
    if (this->getCol() == a->getCol() &&
        this->getRow() == a->getRow())
        return true;
    else
        return false;
}
