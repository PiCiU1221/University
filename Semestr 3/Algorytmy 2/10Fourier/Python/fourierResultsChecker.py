import numpy as np

def dft(f):
    N = len(f)
    n = np.arange(N)
    k = n.reshape((N, 1))
    e = np.exp(-2j * np.pi * k * n / N)
    return np.dot(e, f)

def fft(f):
    return np.fft.fft(f)

MAX_ORDER = 13
PRINT_COEFS = False

for o in range(1, MAX_ORDER + 1):
    N = 2 ** o
    print(f"N: {N}\n")

    f = np.arange(N) / N

    cDFT = dft(f)
    cFFT = fft(f)

    mean_error = np.mean(np.abs(cDFT - cFFT))
    print(f"Mean error: {mean_error}\n")

    if PRINT_COEFS:
        for k in range(N):
            print(f"DFT: {cDFT[k].real:.6f} + {cDFT[k].imag:.6f}i")
            print(f"FFT: {cFFT[k].real:.6f} + {cFFT[k].imag:.6f}i\n")

    print("================================\n")