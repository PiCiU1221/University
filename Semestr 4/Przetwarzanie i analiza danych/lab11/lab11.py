# Zadanie 1.2

import sounddevice as sd
import soundfile as sf

s, fs = sf.read("jestem_studentem_informatyki.wav", dtype = "float32")

sd.play(s, fs)
status = sd.wait()

# Zadanie 1.3

import numpy as np
import matplotlib.pyplot as plt

# normalizacja
s_min = np.min(s)
s_max = np.max(s)

s = 2 * (s - s_min) / (s_max - s_min) - 1

# zmienna czasowa
time_ms = np.linspace(0, len(s) / fs * 1000, len(s))

plt.plot(time_ms, s)
plt.title('Signal')
plt.xlabel('Time in ms (' + str(len(s)) + ') samples')
plt.ylabel('Signal V value')
plt.grid(True)
plt.show()

# Zadanie 2.1

def oblicz_energie_i_przejscia_przez_zero(s, ramka_ms, fs):

    # Ilosc probek w ramce
    n = int(ramka_ms / 1000 * fs)

    ilosc_ramek = int(len(s) / n)

    E = np.zeros(ilosc_ramek)
    Z = np.zeros(ilosc_ramek)

    for j in range(ilosc_ramek):
        for i in range(n):
            E[j] += s[j * n + i] ** 2

            if i < n - 1:
                if s[j * n + i] * s[j * n + i + 1] < 0:
                    Z[j] += 1

    return E, Z, ilosc_ramek

# Zadanie 2.2

def normalizacja_0_1(arr):
    arr_min = np.min(arr)
    arr_max = np.max(arr)
    
    normalized_arr = (arr - arr_min) / (arr_max - arr_min)
    
    return normalized_arr

E, Z, ilosc_ramek = oblicz_energie_i_przejscia_przez_zero(s, 10, fs)

# Normalizacja energii
E = normalizacja_0_1(E)

# Normalizacja przejść przez zero
Z = normalizacja_0_1(Z)

# Inicjalizacja tablicy czasu dla E i Z
time_ms_frame = np.linspace(0, len(s) / fs * 1000, ilosc_ramek)

plt.figure(figsize=(15, 3))
plt.plot(time_ms, s, color='lightgreen', linewidth=0.7)
plt.plot(time_ms_frame, E, color='red', linewidth=0.7)
plt.plot(time_ms_frame, Z, color='blue', linewidth=0.7)
plt.title('Signal')
plt.xlabel('Time in ms (' + str(len(s)) + ') samples')
plt.ylabel('Signal V value')
plt.grid(True)
plt.show()

# Zadanie 2.4

E5, Z5, ilosc_ramek1 = oblicz_energie_i_przejscia_przez_zero(s, 5, fs)
E20, Z20, ilosc_ramek2 = oblicz_energie_i_przejscia_przez_zero(s, 20, fs)
E50, Z50, ilosc_ramek3 = oblicz_energie_i_przejscia_przez_zero(s, 50, fs)

# Normalize the energy and zero crossings arrays
E5_normalized = normalizacja_0_1(E5)
Z5_normalized = normalizacja_0_1(Z5)
E20_normalized = normalizacja_0_1(E20)
Z20_normalized = normalizacja_0_1(Z20)
E50_normalized = normalizacja_0_1(E50)
Z50_normalized = normalizacja_0_1(Z50)

time_ms_frame5 = np.linspace(0, len(s) / fs * 1000, ilosc_ramek1)
time_ms_frame20 = np.linspace(0, len(s) / fs * 1000, ilosc_ramek2)
time_ms_frame50 = np.linspace(0, len(s) / fs * 1000, ilosc_ramek3)

plt.figure(figsize=(15, 9))

plt.subplot(3, 1, 1)
plt.plot(time_ms, s, color='lightgreen', linewidth=0.7, label='Signal')
plt.plot(time_ms_frame5, E5_normalized, color='red', linewidth=0.7)
plt.plot(time_ms_frame5, Z5_normalized, color='blue', linewidth=0.7)
plt.xlabel('Time in ms')
plt.ylabel('Signal V value')
plt.grid(True)
plt.legend()

plt.subplot(3, 1, 2)
plt.plot(time_ms, s, color='lightgreen', linewidth=0.7, label='Signal')
plt.plot(time_ms_frame20, E20_normalized, color='red', linewidth=0.7)
plt.plot(time_ms_frame20, Z20_normalized, color='blue', linewidth=0.7)
plt.xlabel('Time in ms')
plt.ylabel('Signal V value')
plt.grid(True)
plt.legend()

plt.subplot(3, 1, 3)
plt.plot(time_ms, s, color='lightgreen', linewidth=0.7, label='Signal')
plt.plot(time_ms_frame50, E50_normalized, color='red', linewidth=0.7)
plt.plot(time_ms_frame50, Z50_normalized, color='blue', linewidth=0.7)
plt.xlabel('Time in ms')
plt.ylabel('Signal V value')
plt.grid(True)

plt.suptitle('5ms, 20ms, 50ms')
plt.tight_layout()
plt.show()

# Zadanie 2.5

def oblicz_energie_i_przejscia_przez_zero_z_nakladaniem(s, ramka_ms, fs, overlap=0.5):
    n = int(ramka_ms / 1000 * fs)
    overlap_samples = int(n * overlap)
    step = n - overlap_samples
    ilosc_ramek = 1 + (len(s) - n) // step
    
    E = np.zeros(ilosc_ramek)
    Z = np.zeros(ilosc_ramek)

    for j in range(ilosc_ramek):
        start = j * step
        end = start + n
        ramka = s[start:end]
        for i in range(1, len(ramka)):
            E[j] += ramka[i] ** 2
            if i != len(ramka) - 1:
                if ramka[i] * ramka[i + 1] < 0:
                    Z[j] += 1
                    
    return E, Z, ilosc_ramek

E5, Z5, ilosc_ramek1 = oblicz_energie_i_przejscia_przez_zero_z_nakladaniem(s, 5, fs, 0.5)
E20, Z20, ilosc_ramek2 = oblicz_energie_i_przejscia_przez_zero_z_nakladaniem(s, 20, fs, 0.5)
E50, Z50, ilosc_ramek3 = oblicz_energie_i_przejscia_przez_zero_z_nakladaniem(s, 50, fs, 0.5)

E5_normalized = normalizacja_0_1(E5)
Z5_normalized = normalizacja_0_1(Z5)
E20_normalized = normalizacja_0_1(E20)
Z20_normalized = normalizacja_0_1(Z20)
E50_normalized = normalizacja_0_1(E50)
Z50_normalized = normalizacja_0_1(Z50)

time_ms_frame5 = np.linspace(0, len(s) / fs * 1000, ilosc_ramek1)
time_ms_frame20 = np.linspace(0, len(s) / fs * 1000, ilosc_ramek2)
time_ms_frame50 = np.linspace(0, len(s) / fs * 1000, ilosc_ramek3)

plt.figure(figsize=(15, 9))

plt.subplot(3, 1, 1)
plt.plot(time_ms, s, color='lightgreen', linewidth=0.7, label='Signal')
plt.plot(time_ms_frame5, E5_normalized, color='red', linewidth=0.7)
plt.plot(time_ms_frame5, Z5_normalized, color='blue', linewidth=0.7)
plt.xlabel('Time in ms')
plt.ylabel('Signal V value')
plt.grid(True)

plt.subplot(3, 1, 2)
plt.plot(time_ms, s, color='lightgreen', linewidth=0.7, label='Signal')
plt.plot(time_ms_frame20, E20_normalized, color='red', linewidth=0.7)
plt.plot(time_ms_frame20, Z20_normalized, color='blue', linewidth=0.7)
plt.xlabel('Time in ms')
plt.ylabel('Signal V value')
plt.grid(True)

plt.subplot(3, 1, 3)
plt.plot(time_ms, s, color='lightgreen', linewidth=0.7, label='Signal')
plt.plot(time_ms_frame50, E50_normalized, color='red', linewidth=0.7)
plt.plot(time_ms_frame50, Z50_normalized, color='blue', linewidth=0.7)
plt.xlabel('Time in ms')
plt.ylabel('Signal V value')
plt.grid(True)

plt.suptitle('5ms, 20ms, 50ms')
plt.tight_layout()
plt.show()

E5, Z5, ilosc_ramek1 = oblicz_energie_i_przejscia_przez_zero(s, 5, fs)

E5_normalized = normalizacja_0_1(E5)
Z5_normalized = normalizacja_0_1(Z5)

time_ms_frame5 = np.linspace(0, len(s) / fs * 1000, ilosc_ramek1)

plt.figure(figsize=(15, 9))

plt.subplot(2, 1, 1)
plt.plot(time_ms, s, color='lightgreen', linewidth=0.7, label='Signal')
plt.plot(time_ms_frame5, E5_normalized, color='red', linewidth=0.7)
plt.plot(time_ms_frame5, Z5_normalized, color='blue', linewidth=0.7)
plt.xlabel('Time in ms')
plt.ylabel('Signal V value')
plt.grid(True)

E5, Z5, ilosc_ramek1 = oblicz_energie_i_przejscia_przez_zero_z_nakladaniem(s, 5, fs, 0.5)

E5_normalized = normalizacja_0_1(E5)
Z5_normalized = normalizacja_0_1(Z5)

time_ms_frame5 = np.linspace(0, len(s) / fs * 1000, ilosc_ramek1)

plt.subplot(2, 1, 2)
plt.plot(time_ms, s, color='lightgreen', linewidth=0.7, label='Signal')
plt.plot(time_ms_frame5, E5_normalized, color='red', linewidth=0.7)
plt.plot(time_ms_frame5, Z5_normalized, color='blue', linewidth=0.7)
plt.xlabel('Time in ms')
plt.ylabel('Signal V value')
plt.grid(True)

plt.suptitle('5ms bez nakladania i z nakladaniem')
plt.tight_layout()
plt.show()

# Zadanie 3.1

# dla litery 'e'

start_sample = 23000

# dla litery 'i'

start_sample = 35000

# dla litery 'o'

start_sample = 42000

# dla litery 't'

start_sample = 8000

# do testowania

start_sample = 8000

tested_sample = s[start_sample:start_sample + 20048]

sd.play(tested_sample, fs)
status = sd.wait()

# Zadanie 3.2

tested_sample = s[start_sample:start_sample + 2048]

hamming_window = np.hamming(len(tested_sample))

windowed_segment = tested_sample * hamming_window

# Zadanie 3.3

import scipy.fftpack

yf = scipy.fftpack.fft(windowed_segment)

widmo_amplitudowe = np.abs(yf)

widmo_amplitudowe_log = np.log(widmo_amplitudowe + 1e-10)

# Zadanie 3.4

xf = np.linspace(0, fs, len(widmo_amplitudowe_log))

plt.figure(figsize=(12, 5))
plt.plot(xf[:len(xf)//2], widmo_amplitudowe_log[:len(widmo_amplitudowe_log)//2])
plt.xlim(0, 10000)
plt.title('Amplitude spectrum: log(abs(fft(W * H)))')
plt.xlabel('Frequency')
plt.ylabel('Values')
plt.grid(True)
plt.show()

# Zadanie 4.1

okno = s[start_sample:start_sample + 2048]

# Zadanie 4.2

import librosa

p = 20
a = librosa.lpc(okno, order=p)

print("Współczynniki LPC:", a)

# Zadanie 4.4

a = np.pad(a, (0, 2048 - len(a)))

# Zadanie 4.5

# Wyznaczenie wygładzonego widma amplitudowego na bazie wektora a
fft_a = np.fft.fft(a)
widmoLPC = np.log(np.abs(fft_a))

# Odbicie wygładzonego widma w poziomie
widmoLPC *= -1

# Wygenerowanie prawidłowej osi częstotliwości w Hz
f_axis_hz = np.fft.fftfreq(len(a), d=1/fs)

plt.figure(figsize=(10, 6))

# Właściwe widmo amplitudowe
plt.plot(xf[:len(xf)//2], widmo_amplitudowe_log[:len(widmo_amplitudowe_log)//2])

widmoLPC_shifted = widmoLPC - 2

# Wygładzone widmo amplitudowe
plt.plot(f_axis_hz[:len(f_axis_hz)//2], widmoLPC_shifted[:len(f_axis_hz)//2], color='red')

plt.xlim(0, 12000)

plt.xlabel('Częstotliwość [Hz]')
plt.ylabel('Amplituda [dB]')
plt.grid()
plt.show()

def widmo_dla_gloski(start_sample, s, fs, xf, widmo_amplitudowe_log):
    okno = s[start_sample:start_sample + 2048]

    p = 20
    a = librosa.lpc(okno, order=p)
    a = np.pad(a, (0, 2048 - len(a)))

    fft_a = np.fft.fft(a)

    widmoLPC = np.log(np.abs(fft_a))
    widmoLPC *= -1

    f_axis_hz = np.fft.fftfreq(len(a), d=1/fs)

    widmoLPC_shifted = widmoLPC - 2

    plt.figure(figsize=(8, 5))
    plt.plot(xf[:len(xf)//2], widmo_amplitudowe_log[:len(widmo_amplitudowe_log)//2])
    plt.plot(f_axis_hz[:len(f_axis_hz)//2], widmoLPC_shifted[:len(f_axis_hz)//2], color='red')
    plt.xlim(0, 3000)
    plt.xlabel('Częstotliwość [Hz]')
    plt.ylabel('Amplituda [dB]')
    plt.grid()
    plt.show()

    widmo_dla_gloski(42000, s, fs, xf, widmo_amplitudowe_log)

    widmo_dla_gloski(35000, s, fs, xf, widmo_amplitudowe_log)

    widmo_dla_gloski(22500, s, fs, xf, widmo_amplitudowe_log)