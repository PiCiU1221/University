#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uchar;

uchar *load_jpeg_as_rgb(char *filename, int *width, int *height)
{
    int channels;
    uchar *data = stbi_load(filename, width, height, &channels, 3);
    if (!data) {
        fprintf(stderr, "stbi_load failed: %s\n", stbi_failure_reason());
        return NULL;
    }
    return data;
}

__global__ void histogram(uchar *pixels, int width, int height, int *histR, int *histG, int *histB) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= width * height) {
        return;
    }

    int pixelIndex = idx * 3;
    uchar r = pixels[pixelIndex + 0];
    uchar g = pixels[pixelIndex + 1];
    uchar b = pixels[pixelIndex + 2];

    atomicAdd(&histR[r], 1);
    atomicAdd(&histG[g], 1);
    atomicAdd(&histB[b], 1);
}

int main(int argc, char *argv[]){
    if(argc != 2) { 
        fprintf(stderr, "usage: %s jpg_file\n", argv[0]); 
        return 1; 
    }
    int width, height;
    uchar *pixels = load_jpeg_as_rgb(argv[1], &width, &height);
    if(!pixels) 
        return 1;
    printf("Dimensions: %d x %d\n", width, height);

    uchar *d_pixels;
    int *d_histR, *d_histG, *d_histB;
    int histSize = 256 * sizeof(int);

    cudaMalloc(&d_pixels, width * height * 3);
    cudaMalloc(&d_histR, histSize);
    cudaMalloc(&d_histG, histSize);
    cudaMalloc(&d_histB, histSize);

    cudaMemcpy(d_pixels, pixels, width * height * 3, cudaMemcpyHostToDevice);
    cudaMemset(d_histR, 0, histSize);
    cudaMemset(d_histG, 0, histSize);
    cudaMemset(d_histB, 0, histSize);

    int threadsPerBlock = 1024;
    int numBlocks = (width * height + threadsPerBlock - 1) / threadsPerBlock;
    histogram<<<numBlocks, threadsPerBlock>>>(d_pixels, width, height, d_histR, d_histG, d_histB);

    int histR[256], histG[256], histB[256];
    cudaMemcpy(histR, d_histR, histSize, cudaMemcpyDeviceToHost);
    cudaMemcpy(histG, d_histG, histSize, cudaMemcpyDeviceToHost);
    cudaMemcpy(histB, d_histB, histSize, cudaMemcpyDeviceToHost);

    FILE *f = fopen("histogram.csv", "w");
    if(f){
        fprintf(f, "LVL,R,G,B\n");
        int totalPixels = width * height;
        for (int i = 0; i < 256; i++){
            float percentR = 100.0f * histR[i] / totalPixels;
            float percentG = 100.0f * histG[i] / totalPixels;
            float percentB = 100.0f * histB[i] / totalPixels;
            fprintf(f, "%d,%.5f,%.5f,%.5f\n", i, percentR, percentG, percentB);
        }
        fclose(f);
        printf("Histogram saved to histogram.csv\n");
    } else {
        fprintf(stderr, "Failed to open histogram.csv\n");
    }

    stbi_image_free(pixels);
    cudaFree(d_pixels);
    cudaFree(d_histR);
    cudaFree(d_histG);
    cudaFree(d_histB);

    return 0;
}
