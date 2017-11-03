#pragma once
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

