#include "ludecompose.h"

LUDecompose::LUDecompose(std::vector<std::vector<double> > matrix, std::vector<double> vector, int size)
{
    this->size = size;
    this->vector = std::vector<double>(vector);
    this->matrix = std::vector<std::vector<double> >(matrix);
}

std::vector<double> LUDecompose::lupSolve()
{
    std::vector<std::vector<double> > a1(this->matrix);
    std::vector<double> x(this->size), y(this->size);

    std::vector<int> p(this->size);


    p = lupDecompose(a1);
    y = forwardSub(a1, this->vector, p);
    for (int i = 0; i < y.size(); i++)
    {
        std::cout << this->vector[i] << std::endl;
    }
    x = backSub(a1, y);

    return x;
}

std::vector<int> LUDecompose::lupDecompose(std::vector<std::vector<double>> &mat)
{
    int j, k;
    std::vector<int> p(this->size);
    for (int i = 0; i < this->size; i++)
    {
        p[i] = i;
    }
    for (int i = 0; i < this->size; i++)
    {
        j = MaxInColumn(mat, i);
        if (i != j)
        {
            swapRow(mat, i, j);
            k = p[i];
            p[i] = p[j];
            p[j] = k;
        }
        for (int j = i+1; j < this->size; j++)
        {
            mat[j][i] /= mat[i][i];
        }
        for (int j = i+1; j < this->size; j++)
        {
            for (int k = i+1; k < this->size; k++)
            {
                mat[j][k] -= (mat[i][k]*mat[j][i]);
            }
        }
    }

    return p;
}

void LUDecompose::swapRow(std::vector<std::vector<double> > &mat, int size1, int size2)
{
    auto temp = mat[size1];
    mat[size1] = mat[size2];
    mat[size2] = temp;
}

int LUDecompose::MaxInColumn(std::vector<std::vector<double> > mat, int i) const
{
    int j = i + 1, k = i;

    double max = fabs(mat[i][i]);
    for(; j < this->size; j++)
    {
        if (fabs(mat[j][i]) > max)
        {
            max = fabs(mat[j][i]);
            k = j;
        }
    }

    return k;
}

std::vector<double> LUDecompose::forwardSub(std::vector<std::vector<double> > mat, std::vector<double> vec, std::vector<int> p)
{
    std::vector<double> y(this->size);
    for (int i = 0; i < this->size; i++)
    {
        y[i] = vec[p[i]];
        for (int j = 0; j < i; j++)
        {
            y[i] -= mat[i][j]*y[j];
        }
    }

    return y;
}

std::vector<double> LUDecompose::backSub(std::vector<std::vector<double> > mat, std::vector<double> y)
{
    std::vector<double> x(this->size);

    for (int i = 0; i < this->size; i++)
    {
        x[this->size-i-1] = y[this->size-1-i];
        for (int j = 0; j < i; j++)
        {
            x[this->size-1-i] -= (mat[this->size-1-i][this->size-1-j]*x[this->size-1-j]);
        }
        x[this->size-1-i] /= mat[this->size-1-i][this->size-1-i];
    }

    return x;
}
