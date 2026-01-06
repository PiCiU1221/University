import numpy as np
from tqdm import tqdm
import cv2

def rle_encode(data):
    data = data.astype(int)

    x = np.array([len(data.shape)])
    x = np.concatenate([x, data.shape])

    flat_data = data.flatten()

    compressed = []
    i = 0
    with tqdm(total=len(flat_data)) as pbar:
        while i < len(flat_data):
            count = 1
            while i + count < len(flat_data) and flat_data[i] == flat_data[i + count]:
                count += 1
            compressed.append(count)
            compressed.append(flat_data[i])
            i += count
            pbar.update(count)

    compressed_array = np.array(compressed, dtype=int)
    result = np.concatenate([x, compressed_array])
    return result

def rle_decode(encoded):
    OG_Shape = encoded[1:int(encoded[0] + 1)]
    compressed = encoded[int(encoded[0] + 1):]

    decompressed = []
    for i in tqdm(range(0, len(compressed), 2)):
        count = compressed[i]
        value = compressed[i + 1]
        decompressed.extend([value] * count)

    Array1D = np.array(decompressed, dtype=int)
    ArrayND = Array1D.reshape(OG_Shape)
    return ArrayND

def count_same(data, start):
    count = 1
    while start + count < len(data) and data[start] == data[start + count] and count < 128:
        count += 1
    return count

def count_different(data, start):
    count = 1
    while start + count < len(data) and data[start + count] != data[start + count - 1]:
        if start + count + 1 < len(data) and data[start + count] == data[start + count + 1]:
            break
        count += 1
        if count >= 128:
            break
    return count

from tqdm import tqdm
import numpy as np

def byterun_encode(data):
    data = data.astype(int)

    x = np.array([len(data.shape)])
    x = np.concatenate([x, data.shape])

    flat = data.flatten()
    encoded = []

    i = 0
    with tqdm(total=len(flat)) as pbar:
        while i < len(flat):
            if i + 1 < len(flat) and flat[i] == flat[i + 1]:
                count = count_same(flat, i)
                while count > 128:
                    encoded.append(-128)
                    encoded.append(flat[i])
                    i += 128
                    count -= 128
                    pbar.update(128)
                encoded.append(-count)
                encoded.append(flat[i])
                i += count
                pbar.update(count)
            else:
                count = count_different(flat, i)
                while count > 128:
                    encoded.append(128)
                    encoded.extend(flat[i:i + 128])
                    i += 128
                    count -= 128
                    pbar.update(128)
                encoded.append(count)
                encoded.extend(flat[i:i + count])
                i += count
                pbar.update(count)

    compressed_array = np.array(encoded, dtype=int)
    result = np.concatenate([x, compressed_array])
    return result

def byterun_decode(encoded):
    OG_Shape = encoded[1:int(encoded[0] + 1)]
    compressed = encoded[int(encoded[0] + 1):]

    decoded = []
    i = 0
    with tqdm(total=len(compressed)) as pbar:
        while i < len(compressed):
            count = int(compressed[i])
            i += 1
            pbar.update(1)
            if count < 0:
                decoded.extend([compressed[i]] * (-count))
                i += 1
                pbar.update(1)
            else:
                decoded.extend(compressed[i:i + count])
                i += count
                pbar.update(count)

    Array1D = np.array(decoded, dtype=int)
    ArrayND = Array1D.reshape(OG_Shape)
    return ArrayND

def calculate_compression_efficiency(original_image, compressed_image):
    original_size = original_image.nbytes
    compressed_size = compressed_image.nbytes
    compression_ratio = original_size / compressed_size
    compression_percentage = (compressed_size / original_size) * 100
    return compression_ratio, compression_percentage


def compress_and_calculate_efficiency(filename):
    img = cv2.imread(filename)
    img = img.astype(int)

    compressed_rle = rle_encode(img)
    ratio_rle, percentage_rle = calculate_compression_efficiency(img, compressed_rle)
    decompressed_rle = rle_decode(compressed_rle)

    compressed_byterun = byterun_encode(img)
    ratio_byterun, percentage_byterun = calculate_compression_efficiency(img, compressed_byterun)
    decompressed_byterun = byterun_decode(compressed_byterun)

    rle_identical = np.array_equal(img, decompressed_rle)
    byterun_identical = np.array_equal(img, decompressed_byterun)

    print(f"{filename}:")
    print(f"RLE: stopien kompresji: {ratio_rle:.4f}, czyli {percentage_rle:.2f}%")
    print(f"ByteRun: stopien kompresji: {ratio_byterun:.4f}, czyli {percentage_byterun:.2f}%")
    print(f"Obraz po RLE taki sam jak oryginal: {rle_identical}")
    print(f"Obraz po ByteRun taki sam jak oryginal: {byterun_identical}")

compress_and_calculate_efficiency("rysunek_techniczny.jpg")
compress_and_calculate_efficiency("diagramy.png")
compress_and_calculate_efficiency("kolorowy.jpg")