// 10Fourier.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <complex>

#include "dft.h"
#include "fft.h"
#include "err.h"

using namespace std;

int main()
{
	const int MAX_ORDER = 13; // maksymalny rzad wielkosci danych ( w ramach bazy 2)
	const bool PRINT_COEFS = false; // przelacznik do ewentualnego wypisu na ekran rezultatow DFT , FFT
	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int N = 1 << o; // rozmiar problemu ( potega dwojki - przesuniecie bitowe w lewo )
		printf("N: %i\n", N);

		double* f = new double[N];
		for (int n = 0; n < N; n++)
			f[n] = (n / (double)N) * (n / (double)N); // przykladowe dane ( tu akurat : probki funkcji liniowej )

		clock_t t1 = clock();
		complex<double>* cDFT = dft(f, N);
		clock_t t2 = clock();
		double dft_time = (t2 - t1) / (double)CLOCKS_PER_SEC * 1000.0;
		printf("DFT time [ms]: %f\n", dft_time);

		t1 = clock();
		complex<double>* cFFT = fft(f, N);
		t2 = clock();
		double fft_time = (t2 - t1) / (double)CLOCKS_PER_SEC * 1000.0;
		printf("FFT time [ms]: %f\n\n", fft_time);

		printf("mean error: %le\n\n", err(cDFT, cFFT, N));

		if (PRINT_COEFS) {
			for (int k = 0; k < N; k++) {
				printf("DFT: %.6f + %.6fi\n", real(cDFT[k]), imag(cDFT[k]));
				printf("FFT: %.6f + %.6fi\n\n", real(cFFT[k]), imag(cFFT[k]));
			}

			printf("================================\n\n");
		}

		delete[] f;
		delete[] cDFT;
		delete[] cFFT;
	}
	return 0;
}