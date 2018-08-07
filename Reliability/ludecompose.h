#ifndef LUDECOMPOSE_H
#define LUDECOMPOSE_H

#include <math.h>
#include <iostream>
#include <vector>
#include <iostream>

class LUDecompose
{
public:
    LUDecompose(std::vector<std::vector<double> > matrix, std::vector<double> vector, int size);

    std::vector<double> lupSolve();
private:
    int MaxInColumn(std::vector<std::vector<double>> mat, int i);
    std::vector<int> lupDecompose(std::vector<std::vector<double> > &matrix);
    void swapRow(std::vector<std::vector<double> > &mat, int size1, int size2);
    std::vector<double> forwardSub(std::vector<std::vector<double> > mat, std::vector<double> vec, std::vector<int> p);
    std::vector<double> backSub(std::vector<std::vector<double> > mat, std::vector<double> y);


    std::vector<std::vector<double> > matrix;
    std::vector<double> vector;
    int size;
};

#endif // LUDECOMPOSE_H
