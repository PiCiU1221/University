import numpy as np
import matplotlib.pyplot as plt
import os
import soundfile as sf

A = 87.6

def kwant(data, bit):
    d = (1 << bit) - 1
    DataF = data.astype(float)

    if np.issubdtype(data.dtype, np.floating):
        m = -1
        n = 1
    else:
        m = np.iinfo(data.dtype).min
        n = np.iinfo(data.dtype).max

    data_minus_m = DataF - m
    data_normalized = data_minus_m / (n - m)

    data_scaled = data_normalized * d
    data_quantized = np.round(data_scaled)
    data_divided_by_d = data_quantized / d

    data_rescaled = data_divided_by_d * (n - m)
    DataF = data_rescaled + m

    return DataF.astype(data.dtype)

def a_law_encode(data):
    compressed = np.zeros_like(data)

    idx_small = np.abs(data) < (1 / A)
    compressed[idx_small] = (A * np.abs(data[idx_small])) / (1 + np.log(A))

    idx_big = (np.abs(data) >= (1 / A)) & (np.abs(data) <= 1)
    compressed[idx_big] = (1 + np.log(A * np.abs(data[idx_big]))) / (1 + np.log(A))

    compressed = np.sign(data) * compressed

    return compressed

def a_law_decode(compressed):
    decompressed = np.zeros_like(compressed)

    idx_small = np.abs(compressed) < (1 / (1 + np.log(A)))
    decompressed[idx_small] = (np.abs(compressed[idx_small]) * (1 + np.log(A))) / A

    idx_big = (np.abs(compressed) >= (1 / (1 + np.log(A)))) & (np.abs(compressed) <= 1)
    decompressed[idx_big] = (np.exp(np.abs(compressed[idx_big]) * (1 + np.log(A)) - 1)) / A

    decompressed = np.sign(compressed) * decompressed

    return decompressed

mu = 255

def mu_law_encode(data):
    compressed = np.zeros_like(data)

    idx = (-1 <= data) & (data <= 1)
    compressed[idx] = (np.log(1 + (mu * np.abs(data)))) / (np.log(1 + mu))

    compressed = np.sign(data) * compressed

    return compressed

def mu_law_decode(compressed):
    decompressed = np.zeros_like(compressed)

    idx = (-1 <= compressed) & (compressed <= 1)
    decompressed[idx] = (1 / mu) * (np.power((1 + mu), np.abs(compressed[idx])) - 1)

    decompressed = np.sign(compressed) * decompressed

    return decompressed

def DPCM_compress_no_pred(x,bit):
    y=np.zeros(x.shape)
    e=0
    for i in range(0,x.shape[0]):
        y[i]=kwant(x[i]-e,bit)
        e+=y[i]
    return y

def DPCM_decompress_no_pred(y):
    xp = np.zeros_like(y)
    e = 0
    for i in range(len(y)):
        xp[i] = y[i] + e
        e += y[i]
    return xp

def DPCM_compress(x,bit,predictor,n):
    y=np.zeros(x.shape)
    xp=np.zeros(x.shape)
    e=0
    for i in range(0,x.shape[0]):
        y[i]=kwant(x[i]-e,bit)
        xp[i]=y[i]+e
        idx = (np.arange(i - n, i, 1, dtype=int) + 1)
        idx = np.delete(idx, idx < 0)
        e=predictor(xp[idx], n)
    return y

def DPCM_decompress(y, predictor, n):
    xp = np.zeros_like(y, dtype=float)
    for i in range(len(y)):
        start_idx = max(0, i - n)
        idx = np.arange(start_idx, i)

        if i == 0:
            e = 0
        else:
            e = predictor(xp[idx], n)

        xp[i] = y[i] + e
    return xp

def no_pred(X, n):
    return X[-1]

def median_pred(X, n):
    if len(X) == 0:
        return 0.0
    return np.median(X)

def test_and_plot(start, finish):
    x = np.linspace(start, finish, 1000)
    signal = 0.9 * np.sin(np.pi * x * 4)
    bit = 6

    a_law_compressed = a_law_encode(signal)
    mu_law_compressed = mu_law_encode(signal)

    a_law_quantized = kwant(a_law_compressed, bit)
    mu_law_quantized = kwant(mu_law_compressed, bit)

    a_law_decoded = a_law_decode(a_law_quantized)
    mu_law_decoded = mu_law_decode(mu_law_quantized)

    y_dpcm_no_pred = DPCM_compress_no_pred(signal, bit=bit)
    dpcm_no_pred_decoded = DPCM_decompress_no_pred(y_dpcm_no_pred)

    y_dpcm_pred = DPCM_compress(signal, bit=bit, predictor=median_pred, n=5)
    dpcm_pred_decoded = DPCM_decompress(y_dpcm_pred, predictor=median_pred, n=5)

    fig, axs = plt.subplots(nrows=5, ncols=1, figsize=(10, 10))

    axs[0].plot(x, signal)
    axs[0].set_title("Oryginalny sygnal")

    axs[1].plot(x, a_law_decoded)
    axs[1].set_title("Kompresja A-law")

    axs[2].plot(x, mu_law_decoded)
    axs[2].set_title("Kompresja mu-law")

    axs[3].plot(x, dpcm_no_pred_decoded)
    axs[3].set_title("Kompresja DPCM bez predykcji")

    axs[4].plot(x, dpcm_pred_decoded)
    axs[4].set_title("Kompresja DPCM z predykcja")

    axs[-1].set_xlabel("x")
    plt.tight_layout()
    plt.show()

def normalize_signal(signal):
    return signal / np.iinfo(np.int16).max

def scale_signal_back(decoded_signal):
    return decoded_signal * np.iinfo(np.int16).max

def process_and_save_files():
    bit = 8
    input_dir = "SING"
    output_dir = "2.2"
    file_names = ['sing_high1.wav', 'sing_low1.wav', 'sing_medium1.wav']

    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    for file_name in file_names:
        input_file_path = os.path.join(input_dir, file_name)
        signal, fs = sf.read(input_file_path)

        normalized_signal = normalize_signal(signal)

        a_law_compressed = a_law_encode(normalized_signal)
        mu_law_compressed = mu_law_encode(normalized_signal)

        a_law_quantized = kwant(a_law_compressed, bit)
        mu_law_quantized = kwant(mu_law_compressed, bit)

        a_law_decoded = a_law_decode(a_law_quantized)
        mu_law_decoded = mu_law_decode(mu_law_quantized)

        y_dpcm_no_pred = DPCM_compress_no_pred(normalized_signal, bit=bit)
        dpcm_no_pred_decoded = DPCM_decompress_no_pred(y_dpcm_no_pred)

        y_dpcm_pred = DPCM_compress(normalized_signal, bit=bit, predictor=median_pred, n=5)
        dpcm_pred_decoded = DPCM_decompress(y_dpcm_pred, predictor=median_pred, n=5)

        a_law_decoded = scale_signal_back(a_law_decoded)
        mu_law_decoded = scale_signal_back(mu_law_decoded)
        dpcm_no_pred_decoded = scale_signal_back(dpcm_no_pred_decoded)
        dpcm_pred_decoded = scale_signal_back(dpcm_pred_decoded)

        base_name = file_name.replace('.wav', '')

        sf.write(os.path.join(output_dir, f'{base_name}_a_law_decoded.wav'), a_law_decoded, fs)
        sf.write(os.path.join(output_dir, f'{base_name}_mu_law_decoded.wav'), mu_law_decoded, fs)
        sf.write(os.path.join(output_dir, f'{base_name}_dpcm_no_pred_decoded.wav'), dpcm_no_pred_decoded, fs)
        sf.write(os.path.join(output_dir, f'{base_name}_dpcm_pred_decoded.wav'), dpcm_pred_decoded, fs)

# test_and_plot(-1, 1)
# test_and_plot(-0.5, -0.25)

process_and_save_files()