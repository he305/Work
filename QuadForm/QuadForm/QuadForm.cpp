// QuadForm.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include "RealQuadForm.h"


int main()
{
	int size = 2;
	double** matrix = new double*[size];

	for (int i = 0; i < size; i++) {
		matrix[i] = new double[size];
	}

	matrix[0][0] = 17;
	matrix[1][1] = 8;
	matrix[0][1] = 6;
	matrix[1][0] = 6;

	RealQuadForm* form = new RealQuadForm(size, matrix);
	double* coorf = form->getCoof();
	for (int i = size - 1; i >= 0; i--) {
		std::cout << coorf[i] << std::endl;
	}
    return 0;
}

