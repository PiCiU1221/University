import numpy as np
import cv2
from skimage.metrics import peak_signal_noise_ratio as psnr, structural_similarity as ssim
import matplotlib.pyplot as plt

def water_mark(img,mask,alpha=0.25):
    assert (img.shape[0]==mask.shape[0]) and (img.shape[1]==mask.shape[1]), "Wrong size"
    if len(img.shape)<3:
        flag=True
        t_img=cv2.cvtColor(img,cv2.COLOR_GRAY2RGBA)
    else:
        flag=False
        t_img=cv2.cvtColor(img,cv2.COLOR_RGB2RGBA)
    if (mask.dtype==bool):
        t_mask=cv2.cvtColor((mask*255).astype(np.uint8),cv2.COLOR_GRAY2RGBA)
    elif (mask.dtype==np.uint8):
        if len(mask.shape)<3:
            t_mask=cv2.cvtColor((mask).astype(np.uint8),cv2.COLOR_GRAY2RGBA)
        else:
            t_mask=cv2.cvtColor((mask).astype(np.uint8),cv2.COLOR_RGB2RGBA)
    else:
        if len(mask.shape)<3:
            t_mask=cv2.cvtColor((mask*255).astype(np.uint8),cv2.COLOR_GRAY2RGBA)
        else:
            t_mask=cv2.cvtColor((mask*255).astype(np.uint8),cv2.COLOR_RGB2RGBA)
    t_out=cv2.addWeighted(t_img,1,t_mask,alpha,0)
    if flag:
        out=cv2.cvtColor(t_out,cv2.COLOR_RGBA2GRAY)
    else:
        out=cv2.cvtColor(t_out,cv2.COLOR_RGBA2RGB)
    return out

def put_data(img,data,binary_mask=np.uint8(1)):
    assert img.dtype==np.uint8 , "img wrong data type"
    assert binary_mask.dtype==np.uint8, "binary_mask wrong data type"
    un_binary_mask=np.unpackbits(binary_mask)
    if data.dtype!=bool:
        unpacked_data=np.unpackbits(data)
    else:
        unpacked_data=data

    dataspace=img.shape[0]*img.shape[1]*np.sum(un_binary_mask)
    assert (dataspace>=unpacked_data.size) , "too much data"
    if dataspace==unpacked_data.size:
        prepered_data=unpacked_data.reshape(img.shape[0],img.shape[1],np.sum(un_binary_mask)).astype(np.uint8)
    else:
        prepered_data=np.resize(unpacked_data,(img.shape[0],img.shape[1],np.sum(un_binary_mask))).astype(np.uint8)
    mask=np.full((img.shape[0],img.shape[1]),binary_mask)
    img=np.bitwise_and(img,np.invert(mask))
    bv=0
    for i,b in enumerate(un_binary_mask[::-1]):
        if b:
            temp=prepered_data[:,:,bv]
            temp=np.left_shift(temp,i)
            img=np.bitwise_or(img,temp)
            bv+=1
    return img

def pop_data(img,binary_mask=np.uint8(1),out_shape=None):
    un_binary_mask=np.unpackbits(binary_mask)
    data=np.zeros((img.shape[0],img.shape[1],np.sum(un_binary_mask))).astype(np.uint8)
    bv=0
    for i,b in enumerate(un_binary_mask[::-1]):
        if b:
            mask=np.full((img.shape[0],img.shape[1]),2**i)
            temp=np.bitwise_and(img,mask)
            data[:,:,bv]=temp[:,:].astype(np.uint8)
            bv+=1
    if out_shape!=None:
        tmp=np.packbits(data.flatten())
        tmp=tmp[:np.prod(out_shape)]
        data=tmp.reshape(out_shape)
    return data


# Zadanie 2

binary_mask = np.uint8(1)
with open("test_data/cytat.txt", "rb") as f:
    secret_data = np.frombuffer(f.read(), dtype=np.uint8)

img_bgr = cv2.imread('test_data/zdjecie1.png')
img = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2RGB)

original_blue = img[:,:,2].copy()

carrier_img_encoded = img.copy()
carrier_img_encoded[:,:,2] = put_data(carrier_img_encoded[:,:,2], secret_data, binary_mask)

recovered_data = pop_data(carrier_img_encoded[:,:,2], binary_mask, out_shape=secret_data.shape)

encoded_blue = carrier_img_encoded[:,:,2]
psnr_value = psnr(original_blue, encoded_blue)
ssim_value = ssim(original_blue, encoded_blue)

print(f"PSNR: {psnr_value:.2f} dB")
print(f"SSIM: {ssim_value:.4f}")
print("Data match:", np.array_equal(secret_data, recovered_data))

# Zadanie 3

def get_bit_stream(image_channel_msb, num_bits):
    bit_array = np.zeros((image_channel_msb.shape[0], image_channel_msb.shape[1], num_bits), dtype=bool)
    for i in range(num_bits):
        bit_array[:, :, i] = (image_channel_msb >> (num_bits - 1 - i)) & 1
    return bit_array.flatten()

def reconstruct_from_bits_lsb_first(bitplanes, bits_per_pixel):
    val = np.zeros_like(bitplanes[:, :, 0], dtype=np.uint8)
    for b in range(bits_per_pixel):
        val += bitplanes[:, :, b] << b
    levels = (1 << bits_per_pixel) - 1
    if levels == 0:
        return val
    val = (val.astype(np.float32) / levels * 255).astype(np.uint8)
    return val

def pack_bits_from_mask(data, binary_mask):
    bits_per_pixel = np.sum(np.unpackbits(np.array([binary_mask], dtype=np.uint8)))
    data_uint8 = data.astype(np.uint8) if data.dtype != np.uint8 else data
    bits = np.unpackbits(data_uint8[:, :, None], axis=2, bitorder='little')[:, :, :bits_per_pixel]
    return bits.reshape(-1)

def reconstruct_from_bits(bitplanes, bits_per_pixel):
    val = np.zeros_like(bitplanes[:, :, 0], dtype=np.uint8)
    for b in range(bits_per_pixel):
        val += bitplanes[:, :, b] << (bits_per_pixel - 1 - b)
    levels = (1 << bits_per_pixel) - 1
    if levels == 0:
        return val
    val = (val.astype(np.float32) / levels * 255).astype(np.uint8)
    return val

carrier_bgr = cv2.imread('test_data/zdjecie1.png')
carrier = cv2.cvtColor(carrier_bgr, cv2.COLOR_BGR2RGB)

hidden_bgr = cv2.imread('test_data/zdjecie2.png')
hidden = cv2.cvtColor(hidden_bgr, cv2.COLOR_BGR2RGB)
hidden = cv2.resize(hidden, (carrier.shape[1], carrier.shape[0]))

original = carrier.copy()

hidden_r_msb = (hidden[:, :, 0] >> 6).astype(np.uint8)
hidden_g_msb = (hidden[:, :, 1] >> 6).astype(np.uint8)
hidden_b_msb = (hidden[:, :, 2] >> 5).astype(np.uint8)

bits_to_hide_r = get_bit_stream(hidden_r_msb, 2)
bits_to_hide_g = get_bit_stream(hidden_g_msb, 2)
bits_to_hide_b = get_bit_stream(hidden_b_msb, 3)

encoded = carrier.copy()
encoded[:, :, 0] = put_data(encoded[:, :, 0], bits_to_hide_r, binary_mask=np.uint8(3))
encoded[:, :, 1] = put_data(encoded[:, :, 1], bits_to_hide_g, binary_mask=np.uint8(3))
encoded[:, :, 2] = put_data(encoded[:, :, 2], bits_to_hide_b, binary_mask=np.uint8(7))

bits_r_channel = np.sum(np.unpackbits(np.array([3], dtype=np.uint8)))
bits_g_channel = bits_r_channel
bits_b_channel = np.sum(np.unpackbits(np.array([7], dtype=np.uint8)))

recovered_r_bitplanes = pop_data(encoded[:, :, 0], binary_mask=np.uint8(3))
recovered_g_bitplanes = pop_data(encoded[:, :, 1], binary_mask=np.uint8(3))
recovered_b_bitplanes = pop_data(encoded[:, :, 2], binary_mask=np.uint8(7))

rec_img_r = reconstruct_from_bits_lsb_first(recovered_r_bitplanes, bits_r_channel)
rec_img_g = reconstruct_from_bits_lsb_first(recovered_g_bitplanes, bits_g_channel)
rec_img_b = reconstruct_from_bits_lsb_first(recovered_b_bitplanes, bits_b_channel)

recovered_img = np.stack([rec_img_r, rec_img_g, rec_img_b], axis=2)

plt.figure(figsize=(15, 5))
plt.subplot(1, 3, 1)
plt.title("Original Carrier Image")
plt.imshow(original)
plt.axis('off')

plt.subplot(1, 3, 2)
plt.title("Carrier with Hidden Image")
plt.imshow(encoded)
plt.axis('off')

plt.subplot(1, 3, 3)
plt.title("Recovered Hidden Image")
plt.imshow(recovered_img)
plt.axis('off')

plt.tight_layout()
plt.show()

orig_r = original[:, :, 0]
orig_g = original[:, :, 1]
orig_b = original[:, :, 2]

enc_r = encoded[:, :, 0]
enc_g = encoded[:, :, 1]
enc_b = encoded[:, :, 2]

psnr_r = psnr(orig_r, enc_r, data_range=255)
ssim_r = ssim(orig_r, enc_r, data_range=255)

psnr_g = psnr(orig_g, enc_g, data_range=255)
ssim_g = ssim(orig_g, enc_g, data_range=255)

psnr_b = psnr(orig_b, enc_b, data_range=255)
ssim_b = ssim(orig_b, enc_b, data_range=255)

print(f"R channel – PSNR: {psnr_r:.2f} dB, SSIM: {ssim_r:.4f}")
print(f"G channel – PSNR: {psnr_g:.2f} dB, SSIM: {ssim_g:.4f}")
print(f"B channel – PSNR: {psnr_b:.2f} dB, SSIM: {ssim_b:.4f}")


# Zadanie 4

bit_distributions = [
    (1, 1, 1),
    (2, 2, 2),
    (3, 3, 3),
    (4, 4, 4),
    (5, 5, 5)
]

for i, (bits_r, bits_g, bits_b) in enumerate(bit_distributions):
    print(f"\n### Test {i+1}: R={bits_r}, G={bits_g}, B={bits_b} (Total: {bits_r+bits_g+bits_b} bits)")

    hidden_r_msb = (hidden[:, :, 0] >> (8 - bits_r)).astype(np.uint8)
    hidden_g_msb = (hidden[:, :, 1] >> (8 - bits_g)).astype(np.uint8)
    hidden_b_msb = (hidden[:, :, 2] >> (8 - bits_b)).astype(np.uint8)

    bits_to_hide_r = get_bit_stream(hidden_r_msb, bits_r)
    bits_to_hide_g = get_bit_stream(hidden_g_msb, bits_g)
    bits_to_hide_b = get_bit_stream(hidden_b_msb, bits_b)

    mask_r = np.uint8((1 << bits_r) - 1)
    mask_g = np.uint8((1 << bits_g) - 1)
    mask_b = np.uint8((1 << bits_b) - 1)

    encoded = carrier.copy()
    encoded[:, :, 0] = put_data(encoded[:, :, 0], bits_to_hide_r, binary_mask=mask_r)
    encoded[:, :, 1] = put_data(encoded[:, :, 1], bits_to_hide_g, binary_mask=mask_g)
    encoded[:, :, 2] = put_data(encoded[:, :, 2], bits_to_hide_b, binary_mask=mask_b)

    psnr_r = psnr(original[:, :, 0], encoded[:, :, 0], data_range=255)
    psnr_g = psnr(original[:, :, 1], encoded[:, :, 1], data_range=255)
    psnr_b = psnr(original[:, :, 2], encoded[:, :, 2], data_range=255)

    ssim_r = ssim(original[:, :, 0], encoded[:, :, 0], data_range=255)
    ssim_g = ssim(original[:, :, 1], encoded[:, :, 1], data_range=255)
    ssim_b = ssim(original[:, :, 2], encoded[:, :, 2], data_range=255)

    print(f"R channel – PSNR: {psnr_r:.2f} dB, SSIM: {ssim_r:.4f}")
    print(f"G channel – PSNR: {psnr_g:.2f} dB, SSIM: {ssim_g:.4f}")
    print(f"B channel – PSNR: {psnr_b:.2f} dB, SSIM: {ssim_b:.4f}")

    plt.figure(figsize=(12, 4))
    plt.suptitle(f"Bit distribution R:{bits_r} G:{bits_g} B:{bits_b} – Total: {bits_r + bits_g + bits_b} bits", fontsize=12)
    plt.subplot(1, 2, 1)
    plt.imshow(original)
    plt.title("Original")
    plt.axis('off')

    plt.subplot(1, 2, 2)
    plt.imshow(encoded)
    plt.title("Encoded")
    plt.axis('off')

    plt.tight_layout()
    plt.show()

# Zadanie 5

mask = cv2.imread('test_data/zdjecie_binarne.png', cv2.IMREAD_GRAYSCALE)
mask = cv2.resize(mask, (carrier.shape[1], carrier.shape[0]))
mask_bin = (mask > 127).astype(np.uint8) * 255

alphas = [0.10, 0.25, 0.50]

for alpha in alphas:
    watermarked = water_mark(carrier, mask_bin, alpha=alpha)

    carrier_uint8 = carrier.astype(np.uint8)
    watermarked_uint8 = watermarked.astype(np.uint8)

    psnr_val = psnr(carrier_uint8, watermarked_uint8, data_range=255)
    ssim_val = ssim(carrier_uint8, watermarked_uint8, data_range=255, channel_axis=2)

    print(f"\nAlpha = {alpha}")
    print(f"PSNR: {psnr_val:.2f} dB")
    print(f"SSIM: {ssim_val:.4f}")

    plt.figure(figsize=(12, 4))
    plt.suptitle(f"Watermark alpha = {alpha}", fontsize=14)

    plt.subplot(1, 2, 1)
    plt.imshow(carrier)
    plt.title("Original Image")
    plt.axis('off')

    plt.subplot(1, 2, 2)
    plt.imshow(watermarked)
    plt.title("Image with Watermark")
    plt.axis('off')

    plt.tight_layout()
    plt.show()
