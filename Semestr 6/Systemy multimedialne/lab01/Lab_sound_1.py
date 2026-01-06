import numpy as np
import matplotlib.pyplot as plt
import sounddevice as sd
import soundfile as sf
import scipy.fftpack

data, fs = sf.read('SOUND_INTRO/sound1.wav', dtype='float32')

print(data.dtype)
print(data.shape)

# sd.play(data, fs)
# status = sd.wait()

left_channel = data[:, 0]
right_channel = data[:, 1]

mono_channel = np.mean(data, axis=1)

sf.write('SOUND_INTRO/sound_L.wav', left_channel, fs)
sf.write('SOUND_INTRO/sound_R.wav', right_channel, fs)
sf.write('SOUND_INTRO/sound_mix.wav', mono_channel, fs)

yf_left = scipy.fftpack.fft(left_channel)
yf_right = scipy.fftpack.fft(right_channel)
yf_mono = scipy.fftpack.fft(mono_channel)

fsize=2**8
plt.figure(figsize=(12, 10))

plt.subplot(3, 2, 1)
plt.plot(np.arange(0, left_channel.shape[0]) / fs, left_channel)
plt.title("Left Channel")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")

plt.subplot(3, 2, 2)
frequencies = np.linspace(0, fs / 2, fsize // 2)
plt.plot(frequencies, 20 * np.log10(np.abs(yf_left[:fsize // 2])))
plt.title("Left Channel")
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude (dB)")

plt.subplot(3, 2, 3)
plt.plot(np.arange(0, right_channel.shape[0]) / fs, right_channel)
plt.title("Right Channel")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")

plt.subplot(3, 2, 4)
plt.plot(frequencies, 20 * np.log10(np.abs(yf_right[:fsize // 2])))
plt.title("Right Channel")
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude (dB)")

plt.subplot(3, 2, 5)
plt.plot(np.arange(0, mono_channel.shape[0]) / fs, mono_channel)
plt.title("Mono Channel")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")

plt.subplot(3, 2, 6)
plt.plot(frequencies, 20 * np.log10(np.abs(yf_mono[:fsize // 2])))
plt.title("Mono Channel")
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude (dB)")

plt.tight_layout()
plt.show()
