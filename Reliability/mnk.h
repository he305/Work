#ifndef MNK_H
#define MNK_H

#include <vector>
#include <math.h>
#include <ludecompose.h>

class MNK
{
public:
    MNK(std::vector<double> xVector,
        std::vector<double> yVector,
        std::vector<double> weightVector,
        int size);
    MNK(std::vector<double> xVector,
        std::vector<double> yVector,
        int size);

    std::vector<double> Calculate();
private:
    std::vector<double> xVector;
    std::vector<double> yVector;
    std::vector<double> weightVector;
    int size;
};

#endif // MNK_H
