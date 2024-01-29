#include "err.h"

using namespace std;

double err(complex<double>* cDFT, complex<double>* cFFT, int N) {
	double result = 0.0;
	double Re, Im;

	for (int k = 0; k < N; k++) {
		double Re = real(cDFT[k]) - real(cFFT[k]);
		double Im = imag(cDFT[k]) - imag(cFFT[k]);

		result += abs(Re) + abs(Im);
	}

	return result / N;
}