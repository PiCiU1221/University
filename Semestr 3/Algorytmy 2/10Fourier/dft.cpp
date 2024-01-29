#include "dft.h"

using namespace std;

const double pi = acos(-1);
const complex<double> i(0, 1);

complex<double>* dft(double* f, int N) {
	complex<double>* cVector = new complex<double>[N];
	double Re, Im;

	for (int k = 0; k < N; k++) {
		for (int n = 0; n < N; n++) {
			Re = f[n] * cos(2 * pi * k * n / N);
			Im = -f[n] * sin(2 * pi * k * n / N);
			cVector[k] += complex<double>(Re, Im);
		}
	}

	return cVector;
}