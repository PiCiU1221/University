import cv2
import numpy as np
import matplotlib.pyplot as plt
import os

def rle_encode(data):
    data = data.astype(int)

    x = np.array([len(data.shape)])
    x = np.concatenate([x, data.shape])

    flat_data = data.flatten()

    compressed = []
    i = 0
    while i < len(flat_data):
        count = 1
        while i + count < len(flat_data) and flat_data[i] == flat_data[i + count]:
            count += 1
        compressed.append(count)
        compressed.append(flat_data[i])
        i += count

    compressed_array = np.array(compressed, dtype=int)
    result = np.concatenate([x, compressed_array])
    return result


def rle_decode(encoded):
    OG_Shape = encoded[1:int(encoded[0] + 1)]
    compressed = encoded[int(encoded[0] + 1):]

    decompressed = []
    for i in range(0, len(compressed), 2):
        count = compressed[i]
        value = compressed[i + 1]
        decompressed.extend([value] * count)

    Array1D = np.array(decompressed, dtype=int)
    ArrayND = Array1D.reshape(OG_Shape)
    return ArrayND

##############################################################################
######   Konfiguracja       ##################################################
##############################################################################

kat = './video'  # katalog z plikami wide`o
plik = "clip_2.mp4"  # nazwa pliku
ile = 20  # ile klatek odtworzyć? <0 - całość
key_frame_counter = 5  # co która klatka ma być kluczowa i nie podlegać kompresji
plot_frames = np.array([14])  # automatycznie wyrysuj wykresy
auto_pause_frames = np.array([101])  # automatycznie za pauzuj dla klatki
subsampling = "4:2:0"  # parametry dla chroma subsampling
dzielnik = 4  # dzielnik przy zapisie różnicy
wyswietlaj_kaltki = False  # czy program ma wyświetlać klatki
ROI = [[100, 500, 500, 1000], [100, 200, 500, 700]]  # wyświetlane fragmenty (można podać kilka )


##############################################################################
####     Kompresja i dekompresja    ##########################################
##############################################################################
class data:
    def init(self):
        self.Y = None
        self.Cb = None
        self.Cr = None


def Chroma_subsampling(L, subsampling):
    if subsampling == "4:2:2":
        L = L[:, ::2]

    elif subsampling == "4:4:0":
        L = L[::2, :]

    elif subsampling == "4:2:0":
        L = L[::2, ::2]

    elif subsampling == "4:1:1":
        L = L[:, ::4]

    elif subsampling == "4:1:0":
        L = L[::2, ::4]

    return L


def Chroma_resampling(L, subsampling):
    if subsampling == "4:2:2":
        L = np.repeat(L, 2, axis=1)

    elif subsampling == "4:4:0":
        L = np.repeat(L, 2, axis=0)

    elif subsampling == "4:2:0":
        L = np.repeat(np.repeat(L, 2, axis=0), 2, axis=1)

    elif subsampling == "4:1:1":
        L = np.repeat(L, 4, axis=1)

    elif subsampling == "4:1:0":
        L = np.repeat(np.repeat(L, 2, axis=0), 4, axis=1)

    return L


def frame_image_to_class(frame, subsampling):
    Frame_class = data()
    Frame_class.Y = frame[:, :, 0].astype(int)
    Frame_class.Cb = Chroma_subsampling(frame[:, :, 2].astype(int), subsampling)
    Frame_class.Cr = Chroma_subsampling(frame[:, :, 1].astype(int), subsampling)
    return Frame_class


def frame_layers_to_image(Y, Cr, Cb, subsampling):
    Cb = Chroma_resampling(Cb, subsampling)
    Cr = Chroma_resampling(Cr, subsampling)
    return np.dstack([Y, Cr, Cb]).clip(0, 255).astype(np.uint8)


def compress_KeyFrame(Frame_class):
    KeyFrame = data()
    KeyFrame.Y = rle_encode(Frame_class.Y)
    KeyFrame.Cb = rle_encode(Frame_class.Cb)
    KeyFrame.Cr = rle_encode(Frame_class.Cr)
    return KeyFrame


def decompress_KeyFrame(KeyFrame):
    Y = rle_decode(KeyFrame.Y)
    Cb = rle_decode(KeyFrame.Cb)
    Cr = rle_decode(KeyFrame.Cr)
    frame_image = frame_layers_to_image(Y, Cr, Cb, subsampling)
    return frame_image


def compress_not_KeyFrame(Frame_class, KeyFrame, inne_paramerty_do_dopisania=None):
    Compress_data = data()
    diff_Y = (Frame_class.Y - rle_decode(KeyFrame.Y)) // dzielnik
    diff_Cb = (Frame_class.Cb - rle_decode(KeyFrame.Cb)) // dzielnik
    diff_Cr = (Frame_class.Cr - rle_decode(KeyFrame.Cr)) // dzielnik
    Compress_data.Y = rle_encode(diff_Y)
    Compress_data.Cb = rle_encode(diff_Cb)
    Compress_data.Cr = rle_encode(diff_Cr)
    return Compress_data


def decompress_not_KeyFrame(Compress_data, KeyFrame, inne_paramerty_do_dopisania=None):
    Y = rle_decode(Compress_data.Y) * dzielnik + rle_decode(KeyFrame.Y)
    Cb = rle_decode(Compress_data.Cb) * dzielnik + rle_decode(KeyFrame.Cb)
    Cr = rle_decode(Compress_data.Cr) * dzielnik + rle_decode(KeyFrame.Cr)
    return frame_layers_to_image(Y, Cr, Cb, subsampling)


def plotDifference(ReferenceFrame_YCrCb, DecompressedFrame_YCrCb, ROI):
    ReferenceFrame_RGB = cv2.cvtColor(ReferenceFrame_YCrCb, cv2.COLOR_YCrCb2RGB)
    DecompressedFrame_RGB = cv2.cvtColor(DecompressedFrame_YCrCb, cv2.COLOR_YCrCb2RGB)

    ref_roi = ReferenceFrame_RGB[ROI[0]:ROI[1], ROI[2]:ROI[3]]
    dec_roi = DecompressedFrame_RGB[ROI[0]:ROI[1], ROI[2]:ROI[3]]

    diff = np.abs(ref_roi.astype(np.int16) - dec_roi.astype(np.int16)).astype(np.uint8)

    fig, axs = plt.subplots(1, 3, sharey=True)
    fig.set_size_inches(18, 6)

    axs[0].imshow(ref_roi)
    axs[0].set_title('Reference (RGB)')
    axs[0].axis('off')

    axs[1].imshow(diff)
    axs[1].set_title('Absolute Difference (RGB)')
    axs[1].axis('off')

    axs[2].imshow(dec_roi)
    axs[2].set_title('Decompressed (RGB)')
    axs[2].axis('off')

    plt.tight_layout()
    plt.show()


##############################################################################
####     Głowna pętla programu      ##########################################
##############################################################################

cap = cv2.VideoCapture(os.path.join(kat, plik))

if ile < 0:
    ile = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))

if wyswietlaj_kaltki:
    cv2.namedWindow('Normal Frame')
    cv2.namedWindow('Decompressed Frame')

compression_information = np.zeros((3, ile))


for i in range(ile):
    ret, frame = cap.read()
    if wyswietlaj_kaltki:
        cv2.imshow('Normal Frame', frame)
    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2YCrCb)
    Frame_class = frame_image_to_class(frame, subsampling)
    if (i % key_frame_counter) == 0:  # pobieranie klatek kluczowych
        KeyFrame = compress_KeyFrame(Frame_class)
        cY = KeyFrame.Y
        cCb = KeyFrame.Cb
        cCr = KeyFrame.Cr
        Decompresed_Frame = decompress_KeyFrame(KeyFrame)
    else:  # kompresja
        Compress_data = compress_not_KeyFrame(Frame_class, KeyFrame)
        cY = Compress_data.Y
        cCb = Compress_data.Cb
        cCr = Compress_data.Cr
        Decompresed_Frame = decompress_not_KeyFrame(Compress_data, KeyFrame)

    compression_information[0, i] = (frame[:, :, 0].size - cY.size) / frame[:, :, 0].size
    compression_information[1, i] = (frame[:, :, 0].size - cCb.size) / frame[:, :, 0].size
    compression_information[2, i] = (frame[:, :, 0].size - cCr.size) / frame[:, :, 0].size
    if wyswietlaj_kaltki:
        cv2.imshow('Decompressed Frame', cv2.cvtColor(Decompresed_Frame, cv2.COLOR_YCrCb2BGR))

    if np.any(plot_frames == i):  # rysuj wykresy
        for r in ROI:
            plotDifference(frame, Decompresed_Frame, r)

    if np.any(auto_pause_frames == i):
        cv2.waitKey(-1)  # wait until any key is pressed

    k = cv2.waitKey(1) & 0xff

    if k == ord('q'):
        break
    elif k == ord('p'):
        cv2.waitKey(-1)  # wait until any key is pressed

plt.figure()
plt.plot(np.arange(0, ile), compression_information[0, :] * 100)
plt.plot(np.arange(0, ile), compression_information[1, :] * 100)
plt.plot(np.arange(0, ile), compression_information[2, :] * 100)
plt.title("File:{}, subsampling={}, divider={}, KeyFrame={} ".format(plik, subsampling, dzielnik, key_frame_counter))
plt.show()