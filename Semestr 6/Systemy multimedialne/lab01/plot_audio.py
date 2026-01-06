import numpy as np
import matplotlib.pyplot as plt
import soundfile as sf
import scipy.fftpack

def plotAudio(Signal, Fs, TimeMargin=[0, 0.02]):
    plt.figure(figsize=(12, 8))

    plt.subplot(2, 1, 1)
    plt.plot(np.arange(0,Signal.shape[0])/Fs,Signal)
    plt.xlim(TimeMargin)
    plt.title("Signal in Time Domain")
    plt.xlabel("Time (s)")
    plt.ylabel("Amplitude")

    fsize = 2 ** 8
    plt.subplot(2, 1, 2)
    yf = scipy.fftpack.fft(Signal, fsize)
    plt.plot(np.arange(0, Fs / 2, Fs / fsize), 20 * np.log10(np.abs(yf[:fsize // 2])))
    plt.title("Frequency Spectrum")
    plt.xlabel("Frequency (Hz)")
    plt.ylabel("Magnitude (dB)")

    plt.tight_layout()
    plt.show()

data, fs = sf.read('SIN/sin_440Hz.wav', dtype=np.int32)
plotAudio(data, fs, TimeMargin=[0, 1])
