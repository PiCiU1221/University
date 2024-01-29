#include "fft.h"
#include <iostream>
#include <vector>

using namespace std;

const double pi = acos(-1);
const complex<double> i(0, 1);

complex<double>* fftRecursive(complex<double>* f, int N) {
	if (N == 1) {
		complex<double>* result = new complex<double>[1];
		result[0] = f[0];
		return result;
	}

	complex<double>* E = new complex<double>[N / 2];
	complex<double>* O = new complex<double>[N / 2];

	for (int i = 0; i < (N / 2); i++) {
		E[i] = f[2 * i];
		O[i] = f[2 * i + 1];
	}

	E = fftRecursive(E, N / 2);
	O = fftRecursive(O, N / 2);

	complex<double>* result = new complex<double>[N];

	double Re, Im, angle;

	for (int k = 0; k < (N / 2); k++) {
		angle = -2 * pi * k / N;
		Re = real(O[k]) * cos(angle) - imag(O[k]) * sin(angle);
		Im = real(O[k]) * sin(angle) + imag(O[k]) * cos(angle);

		result[k] = E[k] + complex<double>(Re, Im);
		result[k + (N / 2)] = E[k] - complex<double>(Re, Im);

		/*complex<double> t = polar(1.0, -2 * pi * k / N) * O[k];

		f[k] = E[k] + t;
		f[k + (N / 2)] = E[k] - t;*/
	}

	delete[] E;
	delete[] O;

	return result;
}

complex<double>* fft(double* f, int N) {
	complex<double>* fNew = new complex<double>[N];

	for (int i = 0; i < N; i++) {
		fNew[i] = f[i];
	}

	return fftRecursive(fNew, N);
}