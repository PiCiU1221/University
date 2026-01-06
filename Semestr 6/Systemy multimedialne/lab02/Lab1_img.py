import numpy as np
import matplotlib.pyplot as plt
import cv2
from io import BytesIO

def imgToUInt8(img):
    if np.issubdtype(img.dtype, np.unsignedinteger):
        return img
    elif np.issubdtype(img.dtype, np.floating):
        return (np.clip(img * 255, 0, 255)).astype('uint8')

def imgToFloat(img):
    if np.issubdtype(img.dtype, np.floating):
        return img
    elif np.issubdtype(img.dtype, np.unsignedinteger):
        return img / 255.0

# img1 = plt.imread('IMG_INTRO/B01.png')
#
# print(img1.dtype)
# print(img1.shape)
# print(np.min(img1),np.max(img1))
#
# img2 = cv2.imread('IMG_INTRO/B01.png')

# print(img2.dtype)
# print(img2.shape)
# print(np.min(img2),np.max(img2))

img = cv2.imread('IMG_INTRO/B01.png')
img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

def image_plot_maker(img):
    plt.figure(figsize=(9, 9))

    plt.subplot(3, 3, 1)
    plt.imshow(img)
    plt.axis('off')

    Y1 = 0.299 * img[:,:,0] + 0.587 * img[:,:,1] + 0.114 * img[:,:,2]
    plt.subplot(3, 3, 2)
    plt.imshow(Y1, cmap='gray')
    plt.axis('off')

    Y2 = 0.2126 * img[:,:,0] + 0.7152 * img[:,:,1] + 0.0722 * img[:,:,2]
    plt.subplot(3, 3, 3)
    plt.imshow(Y2, cmap='gray')
    plt.axis('off')

    R = img[:,:,0]
    plt.subplot(3, 3, 4)
    plt.imshow(R, cmap='gray')
    plt.axis('off')

    G = img[:,:,1]
    plt.subplot(3, 3, 5)
    plt.imshow(G, cmap='gray')
    plt.axis('off')

    B = img[:,:,2]
    plt.subplot(3, 3, 6)
    plt.imshow(B, cmap='gray')
    plt.axis('off')

    CR = img.copy()
    CR[:,:,1] = 0
    CR[:,:,2] = 0
    plt.subplot(3, 3, 7)
    plt.imshow(CR)
    plt.axis('off')

    CG = img.copy()
    CG[:,:,0] = 0
    CG[:,:,2] = 0
    plt.subplot(3, 3, 8)
    plt.imshow(CG)
    plt.axis('off')

    CB = img.copy()
    CB[:,:,0] = 0
    CB[:,:,1] = 0
    plt.subplot(3, 3, 9)
    plt.imshow(CB)
    plt.axis('off')

    plt.tight_layout()
    # plt.show()

    memfile = BytesIO()
    plt.savefig(memfile, format='png')
    memfile.seek(0)
    plt.close()

    return memfile

# image_plot_maker(img)
