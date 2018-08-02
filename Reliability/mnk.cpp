#include "mnk.h"

MNK::MNK(std::vector<double> xVector,
         std::vector<double> yVector,
         std::vector<double> weightVector,
         int size)
{
    this->xVector = std::vector<double>(size);
    this->yVector = std::vector<double>(size);
    this->weightVector = std::vector<double>(size);

    this->xVector = xVector;
    this->yVector = yVector;
    this->weightVector = weightVector;
    this->size = size;
}

MNK::MNK(std::vector<double> xVector,
         std::vector<double> yVector,
         int size)
{
    this->xVector = std::vector<double>(size);
    this->yVector = std::vector<double>(size);

    this->xVector = xVector;
    this->yVector = yVector;
    this->size = size;

    this->weightVector = std::vector<double>(size);

    for (int i = 0; i < size; i++)
    {
        this->weightVector[i] = 1;
    }
}

std::vector MNK::Calculate()
{
    size_t polynomeSize = 2;
    //Assuming it's always 2 for polynome size
    double a[polynomeSize][polynomeSize];
    for (size_t i = 0; i < polynomeSize; i++)
    {
        for (size_t j = 0; j < polynomeSize; j++)
        {
            double sum = 0;
            for (size_t k = 0; k < this->size; k++)
            {
                sum += pow(this->xVector[k], i+j) * this->weightVector[k];
            }
            a[i][j] = sum;
        }
    }

    std::vector<double> z(polynomeSize);
    for (size_t i = 0; i < polynomeSize; i++)
    {
        double sum = 0;
        for (size_t j = 0; j < polynomeSize; j++)
        {
            sum += pow(xVector[j], i) * yVector[j] * weightVector[j];
        }
        z[i] = sum;
    }

}
