#ifndef INVERT_H
#define INVERT_H

#include <QString>

/*!
 * \brief The Invert class, use to get inverted matrix.
 *
 */


class Invert
{
public:
    Invert(int);
    ~Invert();
    double **getInvertedMatrix();
    double **invertMatrix(double**);
    double getDet(double **, int);
    double **invert(double **);
    QString getMatrixType();

private:
    QString str;
    int N;
    double getNorma(double**);
    double **inverted;
    long double EPS;
    double getGaussDet(double **);
    double **shultsMethod(double**);
    double **clone(double**);
    double **numOnMatrix(double**, double);
    void addMatrix(double **, double**);
    double **getMult(double**, double**);
    double** getTransp(double**);
    double getMinor(double **, int, int, int);
    double** pseudoInverse(double**);
    double getTr(double **);
    void printMatrix(double**);
};


#endif // INVERT_H
