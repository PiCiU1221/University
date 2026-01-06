import numpy as np
import cv2
import scipy.fftpack
from tqdm import tqdm
import matplotlib.pyplot as plt

QY= np.array([
        [16, 11, 10, 16, 24,  40,  51,  61],
        [12, 12, 14, 19, 26,  58,  60,  55],
        [14, 13, 16, 24, 40,  57,  69,  56],
        [14, 17, 22, 29, 51,  87,  80,  62],
        [18, 22, 37, 56, 68,  109, 103, 77],
        [24, 36, 55, 64, 81,  104, 113, 92],
        [49, 64, 78, 87, 103, 121, 120, 101],
        [72, 92, 95, 98, 112, 100, 103, 99],
        ])

QC= np.array([
        [17, 18, 24, 47, 99, 99, 99, 99],
        [18, 21, 26, 66, 99, 99, 99, 99],
        [24, 26, 56, 99, 99, 99, 99, 99],
        [47, 66, 99, 99, 99, 99, 99, 99],
        [99, 99, 99, 99, 99, 99, 99, 99],
        [99, 99, 99, 99, 99, 99, 99, 99],
        [99, 99, 99, 99, 99, 99, 99, 99],
        [99, 99, 99, 99, 99, 99, 99, 99],
        ])

class container:
    Y=np.array([])
    Cb=np.array([])
    Cr=np.array([])
    ChromaRatio="4:4:4"
    QY=np.ones((8,8))
    QC=np.ones((8,8))
    shape=(0,0,3)


def CompressJPEG(RGB,Ratio="4:4:4",QY=np.ones((8,8)),QC=np.ones((8,8))):
    # RGB -> YCrCb
    YCrCb = cv2.cvtColor(RGB, cv2.COLOR_RGB2YCrCb).astype(int)
    Y, Cr, Cb = cv2.split(YCrCb)

    # zapisać dane z wejścia do klasy
    JPEG = container()
    JPEG.Y = Y
    JPEG.Cb = Cb
    JPEG.Cr = Cr
    JPEG.ChromaRatio = Ratio
    JPEG.QY = QY
    JPEG.QC = QC
    JPEG.shape = RGB.shape

    if Ratio == "4:2:2":
        JPEG.Cr = JPEG.Cr[:, ::2]
        JPEG.Cb = JPEG.Cb[:, ::2]
    elif Ratio == "4:4:4":
        pass

    JPEG.Y=CompressLayer(JPEG.Y,JPEG.QY)
    JPEG.Cr=CompressLayer(JPEG.Cr,JPEG.QC)
    JPEG.Cb=CompressLayer(JPEG.Cb,JPEG.QC)

    return JPEG

def DecompressJPEG(JPEG):
    height, width = JPEG.shape[:2]
    Y = DecompressLayer(JPEG.Y, JPEG.QY, (height, width))

    chroma_shape = (height, width)
    Ratio = JPEG.ChromaRatio
    if Ratio == "4:2:2":
        chroma_shape = (height, width // 2)
    elif Ratio == "4:2:0":
        chroma_shape = (height // 2, width // 2)

    Cr = DecompressLayer(JPEG.Cr, JPEG.QC, chroma_shape)
    Cb = DecompressLayer(JPEG.Cb, JPEG.QC, chroma_shape)

    if Ratio == "4:2:2":
        Cr = np.repeat(Cr, 2, axis=1)
        Cb = np.repeat(Cb, 2, axis=1)
    elif Ratio == "4:4:4":
        pass

    # tu rekonstrukcja obrazu
    YCrCb=np.dstack([Y,Cr,Cb]).clip(0,255).astype(np.uint8)

    # YCrCb -> RGB
    RGB = cv2.cvtColor(YCrCb.astype(np.uint8), cv2.COLOR_YCrCb2RGB)

    return RGB

def CompressBlock(block,Q):
    d = dct2(block)
    qd=np.round(d/Q).astype(int)
    vector = zigzag(qd)

    return vector

def DecompressBlock(vector,Q):
    qd = zigzag(vector)
    pd=qd*Q
    block = idct2(pd)

    return block

## podział na bloki
# L - warstwa kompresowana
# S - wektor wyjściowy
def CompressLayer(L,Q):
    S=np.array([])
    L = L - 128
    for w in range(0,L.shape[0],8):
        for k in range(0,L.shape[1],8):
            block=L[w:(w+8),k:(k+8)]
            S=np.append(S, CompressBlock(block,Q))

    size_before_rle = S.size
    S = rle_encode(S)
    size_after_rle = len(S)

    reduction = size_before_rle - size_after_rle
    reduction_percent = (reduction / size_before_rle) * 100

    print(f"RLE compression: {reduction_percent:.2f}%")
    return S

## wyodrębnianie bloków z wektora
# L - warstwa o oczekiwanym rozmiarze
# S - długi wektor zawierający skompresowane dane
def DecompressLayer(S,Q, expected_shape):
    S = rle_decode(S)

    height, width = expected_shape
    L = np.zeros((height, width))

    for idx,i in enumerate(range(0,S.shape[0],64)):
        vector=S[i:(i+64)]
        m=L.shape[1]/8
        k=int((idx%m)*8)
        w=int((idx//m)*8)
        L[w:(w+8),k:(k+8)]=DecompressBlock(vector,Q)

    L = L + 128
    return L

def dct2(a):
    return scipy.fftpack.dct( scipy.fftpack.dct( a.astype(float), axis=0, norm='ortho' ), axis=1, norm='ortho' )

def idct2(a):
    return scipy.fftpack.idct( scipy.fftpack.idct( a.astype(float), axis=0 , norm='ortho'), axis=1 , norm='ortho')

def zigzag(A):
    template= np.array([
            [0,  1,  5,  6,  14, 15, 27, 28],
            [2,  4,  7,  13, 16, 26, 29, 42],
            [3,  8,  12, 17, 25, 30, 41, 43],
            [9,  11, 18, 24, 31, 40, 44, 53],
            [10, 19, 23, 32, 39, 45, 52, 54],
            [20, 22, 33, 38, 46, 51, 55, 60],
            [21, 34, 37, 47, 50, 56, 59, 61],
            [35, 36, 48, 49, 57, 58, 62, 63],
            ])
    if len(A.shape)==1:
        B=np.zeros((8,8))
        for r in range(0,8):
            for c in range(0,8):
                B[r,c]=A[template[r,c]]
    else:
        B=np.zeros((64,))
        for r in range(0,8):
            for c in range(0,8):
                B[template[r,c]]=A[r,c]
    return B

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

def process_and_plot(fragment, title_prefix, save_path):
    jpeg = CompressJPEG(fragment, Ratio="4:2:2", QY=QY, QC=QC)
    decompressed = DecompressJPEG(jpeg)

    fig, axs = plt.subplots(4, 2, sharey=True)
    fig.set_size_inches(9, 13)

    axs[0, 0].imshow(fragment)
    axs[0, 0].set_title(f"{title_prefix} Original RGB")
    PRZED_YCrCb = cv2.cvtColor(fragment, cv2.COLOR_RGB2YCrCb)
    axs[1, 0].imshow(PRZED_YCrCb[:, :, 0], cmap=plt.cm.gray)
    axs[2, 0].imshow(PRZED_YCrCb[:, :, 1], cmap=plt.cm.gray)
    axs[3, 0].imshow(PRZED_YCrCb[:, :, 2], cmap=plt.cm.gray)

    axs[0, 1].imshow(decompressed)
    axs[0, 1].set_title(f"{title_prefix} Decompressed RGB")
    PO_YCrCb = cv2.cvtColor(decompressed, cv2.COLOR_RGB2YCrCb)
    axs[1, 1].imshow(PO_YCrCb[:, :, 0], cmap=plt.cm.gray)
    axs[2, 1].imshow(PO_YCrCb[:, :, 1], cmap=plt.cm.gray)
    axs[3, 1].imshow(PO_YCrCb[:, :, 2], cmap=plt.cm.gray)

    for ax in axs.flat:
        ax.axis("off")

    plt.tight_layout()
    plt.savefig(save_path)
    plt.close(fig)

def calculate_compression_efficiency(original_image, compressed_image):
    original_size = original_image.nbytes
    compressed_size = compressed_image.nbytes
    compression_ratio = original_size / compressed_size
    compression_percentage = (compressed_size / original_size) * 100
    return compression_ratio, compression_percentage

image = cv2.imread("IMG_BIG/BIG_0001.jpg")
# image = cv2.imread("IMG_BIG/BIG_0002.jpg")
# image = cv2.imread("IMG_BIG/BIG_0003.jpg")
# image = cv2.imread("IMG_BIG/BIG_0004.png")
image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

# fragment1 = image[0:256, 0:256]
# fragment2 = image[2000:2256, 1500:1756]
fragment1 = image[500:756, 500:756]
fragment2 = image[800:1056, 800:1056]

process_and_plot(fragment1, "Fragment 1", "output_fragment1.png")
process_and_plot(fragment2, "Fragment 2", "output_fragment2.png")