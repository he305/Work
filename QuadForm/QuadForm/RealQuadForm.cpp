#include "stdafx.h"
#include "RealQuadForm.h"
#include <iostream>
#include <math.h>


RealQuadForm::RealQuadForm(int size, double** matrix)
{
	this->size = size;
	this->matrix = matrix;
}

double* RealQuadForm::getCoof() {
	double* coof;

	double a = 1;
	double b = -matrix[0][0] + -matrix[1][1];
	double c = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
	std::cout << a << "x^2 + " << b << "x + " << c << std::endl;

	double disc = pow(b, 2) - 4 * a * c;
	
	if (disc > 0) {
		coof = new double[size];

		coof[0] = (-b + sqrt(disc)) / 2 * a;
		coof[1] = (-b - sqrt(disc)) / 2 * a;
	}
	else if (disc == 0) {
		coof = new double[1];
		coof[0] = -b / 2 * a;
	}
	else return 0;
	
	return coof;
}

RealQuadForm::~RealQuadForm()
{
	for (int i = 0; i < this->size; i++) {
		delete matrix[i];
	}

	delete matrix;
}
