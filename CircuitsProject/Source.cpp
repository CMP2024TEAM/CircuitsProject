#include<Eigen/Dense>
#include<Eigen/sparse>
#include<complex>
#include<iostream>
#include"Global.h"
using namespace std;
using namespace Eigen;
using namespace std::complex_literals;

int main()
{
	UI.Omega = 0;

	MatrixXcd m3(2, 2);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			m3(i, j) = 2.0 + 3i;

	int n = 2;

	MatrixXcd m1(n, 2);
	MatrixXcd m2(2, 1);
	complex<double> c = 1. / (0.0005 * 1i * 1000.);

	m1 << 8. - 2i, -8.,
		-8., 14. + 1i;

	m1(0, 0) = 8. - 2i;

	m2 << 10. + 6i, -24. - 35i;

	// m*X=B--->X=m.inverse()*B

	cout << m1.inverse() * m2;

	return 0;
}