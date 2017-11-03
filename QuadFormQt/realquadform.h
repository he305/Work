#ifndef REALQUADFORM_H
#define REALQUADFORM_H


class RealQuadForm
{
public:
    RealQuadForm(int size, double** matrix);
    ~RealQuadForm();
    double* getCoof();

private:
    int size;
    double** matrix;
};

#endif // REALQUADFORM_H
