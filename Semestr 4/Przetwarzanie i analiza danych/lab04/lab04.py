# %%
import matplotlib.pyplot as plt
import numpy as np
import pylab as py
from skimage import data
from skimage import filters
from skimage import exposure
from PIL import Image
import matplotlib.image

# %% [markdown]
# # 2 Dyskretyzacja

# %% [markdown]
# # 2.1

# %%
def sin(f = 1, T = 1, Fs = 128):
    dt = 1.0 / Fs
    t = np.arange(0, T, dt)
    s = np.sin(2 * np.pi * f * t)
    return t,s

# %% [markdown]
# # 2.2

# %%
(t, s) = sin(f = 10, Fs = 20)

plt.plot(t, s)
plt.show()

# %%
(t, s) = sin(f = 10, Fs = 21)

plt.plot(t, s)
plt.show()

# %%
(t, s) = sin(f = 10, Fs = 30)

plt.plot(t, s)
plt.show()

# %%
(t, s) = sin(f = 10, Fs = 45)

plt.plot(t, s)
plt.show()

# %%
(t, s) = sin(f = 10, Fs = 50)

plt.plot(t, s)
plt.show()

# %%
(t, s) = sin(f = 10, Fs = 100)

plt.plot(t, s)
plt.show()

# %%
(t, s) = sin(f = 10, Fs = 150)

plt.plot(t, s)
plt.show()

# %%
(t, s) = sin(f = 10, Fs = 200)

plt.plot(t, s)
plt.show()

# %%
(t, s) = sin(f = 10, Fs = 250)

plt.plot(t, s)
plt.show()

# %%
(t, s) = sin(f = 10, Fs = 1000)

plt.plot(t, s)
plt.show()

# %% [markdown]
# # 2.4

# %% [markdown]
# Czy istnieje twierdzenie, które określa z jaką częstotliwością należy
# próbkować, aby móc wiernie odtworzyć sygnał? Jak się nazywa? <br><br>
# Istnieje i nazywa się twierdzeniem Nyquista–Shannona

# %% [markdown]
# # 2.5

# %% [markdown]
# Jak nazywa się zjawisko, które z powodu błędnie dobranej częstotliwości próbkowania powoduje błędną interpretację sygnału? <br><br>
# Nazywa się ono aliasingiem

# %% [markdown]
# # Kwantyzacja

# %% [markdown]
# # 3.1

# %%
image = Image.open("lab04_zdjecie.png")

display(image)

# %% [markdown]
# # 3.2

# %%
image_array = np.array(image)

dimensions = image_array.shape

print("Liczba wymiarów macierzy obrazu:", len(dimensions))

# %% [markdown]
# # 3.3

# %%
depth = dimensions[-1]

print("Liczba wartości opisujących pojedynczy piksel:", depth)

# %% [markdown]
# # 3.4

# %%
R = image_array[:,:,0]
G = image_array[:,:,1]
B = image_array[:,:,2]

pixel_brightness_method = (np.maximum(R, G, B) + np.maximum(R, G, B)) / 2

display(Image.fromarray(pixel_brightness_method.astype(np.uint8)))

# %%
pixel_average_method = (R + G + B) / 3

display(Image.fromarray(pixel_average_method.astype(np.uint8)))

# %%
pixel_lumination_method = 0.21 * R + 0.72 * G + 0.07 * B

display(Image.fromarray(pixel_lumination_method.astype(np.uint8)))

# %% [markdown]
# # 3.5

# %%
flat_pixel_brightness_method = pixel_brightness_method.ravel()
histogram, bins = np.histogram(flat_pixel_brightness_method, bins=256, range=(0, 255))

plt.figure(figsize=(10, 5))
plt.hist(flat_pixel_brightness_method, bins=256, range=(0, 255), color='blue', alpha=0.7)
plt.xlabel('Pixel Intensity')
plt.ylabel('Frequency')
plt.title('Image Histogram')
plt.show()

# %%
flat_pixel_average_method = pixel_average_method.ravel()
histogram, bins = np.histogram(flat_pixel_average_method, bins=256, range=(0, 255))

plt.figure(figsize=(10, 5))
plt.hist(flat_pixel_average_method, bins=256, range=(0, 255), color='blue', alpha=0.7)
plt.xlabel('Pixel Intensity')
plt.ylabel('Frequency')
plt.title('Image Histogram')
plt.show()

# %%
flat_pixel_lumination_method = pixel_lumination_method.ravel()
histogram, bins = np.histogram(flat_pixel_lumination_method, bins=256, range=(0, 255))

plt.figure(figsize=(10, 5))
plt.hist(flat_pixel_lumination_method, bins=256, range=(0, 255), color='blue', alpha=0.7)
plt.xlabel('Pixel Intensity')
plt.ylabel('Frequency')
plt.title('Image Histogram')
plt.show()

# %% [markdown]
# # 3.6

# %%
histogram, bins = np.histogram(flat_pixel_lumination_method, bins=16, range=(0, 255))

plt.figure(figsize=(10, 5))
plt.hist(flat_pixel_lumination_method, bins=16, range=(0, 255), color='blue', alpha=0.7)
plt.xlabel('Pixel Intensity')
plt.ylabel('Frequency')
plt.title('Image Histogram')
plt.show()

print("Zakresy nowych kolorów:")
for i in range(len(bins) - 1):
    print(f"Bin {i+1}: {bins[i]} - {bins[i+1]}")

# %% [markdown]
# # 3.7

# %%
flat_image_array = image_array.ravel()

histogram, bins = np.histogram(flat_image_array, bins=16, range=(0, 255))

midpoints = [(bins[i] + bins[i+1]) // 2 for i in range(len(bins) - 1)]

reduced_image_array = np.digitize(image_array, bins) - 1
reduced_image_array = np.clip(reduced_image_array, 0, 15)
reduced_image_array = np.array(midpoints)[reduced_image_array]

reduced_image = Image.fromarray(reduced_image_array.astype(np.uint8))

plt.imshow(reduced_image)
plt.axis('off')
plt.title('Image with Reduced Colors')
plt.show()

# %%
reduced_flat_image_array = reduced_image_array.ravel()
reduced_histogram, reduced_bins = np.histogram(reduced_flat_image_array, bins=16, range=(0, 255))

plt.figure(figsize=(10, 5))
plt.hist(reduced_flat_image_array, bins=16, range=(0, 255), color='blue', alpha=0.7)
plt.xlabel('Pixel Intensity')
plt.ylabel('Frequency')
plt.title('Histogram of Image with Reduced Colors')
plt.show()

# %% [markdown]
# # Binaryzacja

# %% [markdown]
# # 4.2

# %%
image = Image.open("lab04_zdjecie2.png")

image_array = np.array(image)

R = image_array[:,:,0]
G = image_array[:,:,1]
B = image_array[:,:,2]

image_array = 0.21 * R + 0.72 * G + 0.07 * B

flat_image_array = image_array.ravel()

histogram, bins = np.histogram(flat_image_array, bins=256, range=(0, 255))

plt.figure(figsize=(10, 5))
plt.hist(flat_image_array, bins=256, range=(0, 255), color='blue', alpha=0.7)
plt.xlabel('Pixel Intensity')
plt.ylabel('Frequency')
plt.title('Histogram of Grayscale Image')
plt.show()


# %% [markdown]
# # 4.3

# %%
def find_threshold(hist):
    smoothed_hist = np.convolve(hist, np.ones(3)/3, mode='valid')
    
    minima_indices = np.where((smoothed_hist[:-2] > smoothed_hist[1:-1]) & (smoothed_hist[1:-1] < smoothed_hist[2:]))[0] + 1
    
    if len(minima_indices) > 0:
        threshold_index = minima_indices[0]
        threshold = threshold_index
    else:
        threshold = len(hist) // 2
    
    return threshold

threshold = find_threshold(histogram)
print("Threshold value:", threshold)

# %% [markdown]
# # 4.4

# %%
camera = np.array(image_array)

val = filters.threshold_otsu(camera)

def binarize_image(image_array, threshold):
    binary_image_array = np.where(image_array > threshold, 1, 0)
    return binary_image_array

binary_image_array = binarize_image(image_array, val)

binary_image = Image.fromarray(binary_image_array.astype(np.uint8) * 255)
display(binary_image)


