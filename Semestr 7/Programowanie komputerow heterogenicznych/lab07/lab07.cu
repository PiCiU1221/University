#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <chrono>

typedef unsigned char uchar;

using namespace std;

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

void cpuMedian(unsigned char* in, unsigned char* out, int w, int h, int ch) {
    for (int y = 1; y < h - 1; y++) {
        for (int x = 1; x < w - 1; x++) {
            for (int c = 0; c < ch; c++) {
                unsigned char window[9];
                int index = 0;

                for (int dy = -1; dy <= 1; dy++) {
                        for (int dx = -1; dx <= 1; dx++) {
                        int pixelPos = (y + dy) * w + (x + dx);
                        int pixelIndex = pixelPos * ch + c;

                        window[index] = in[pixelIndex];
                        index++;
                    }
                }

                sort(window, window + 9);

                int outPos = (y * w + x) * ch + c;
                out[outPos] = window[4];
            }
        }
    }
}

__global__ void gpuMedian(unsigned char* in, unsigned char* out, int w, int h, int ch) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < 1 || x >= w - 1 || y < 1 || y >= h - 1)
        return;

    for (int c = 0; c < ch; c++) {
        unsigned char window[9];
        int index = 0;

        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                int pixelPos = (y + dy) * w + (x + dx);
                int pixelIndex = pixelPos * ch + c;

                window[index] = in[pixelIndex];
                index++;
            }
        }

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 8; j++) {
                if (window[j] > window[j + 1]) {
                    unsigned char temp = window[j];
                    window[j] = window[j + 1];
                    window[j + 1] = temp;
                }
            }
        }

        int outPos = (y * w + x) * ch + c;
        out[outPos] = window[4];
    }
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

    int channels = 3;
    size_t imgSize = width * height * channels;
    uchar *cpuOut = (uchar*)malloc(imgSize);
    uchar *gpuOut = (uchar*)malloc(imgSize);

    auto cpuStart = chrono::high_resolution_clock::now();
    cpuMedian(pixels, cpuOut, width, height, channels);
    auto cpuEnd = chrono::high_resolution_clock::now();
    auto cpuTime = chrono::duration_cast<chrono::milliseconds>(cpuEnd - cpuStart).count();
    printf("CPU median time: %ld ms\n", cpuTime);

    uchar *d_in, *d_out;
    cudaMalloc(&d_in, imgSize);
    cudaMalloc(&d_out, imgSize);
    cudaMemcpy(d_in, pixels, imgSize, cudaMemcpyHostToDevice);

    dim3 block(32, 32);
    dim3 grid((width + 31) / 32, (height + 31) / 32);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start);

    gpuMedian<<<grid, block>>>(d_in, d_out, width, height, channels);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float gpuTime;
    cudaEventElapsedTime(&gpuTime, start, stop);
    printf("GPU median kernel time: %.3f ms\n", gpuTime);

    cudaMemcpy(gpuOut, d_out, imgSize, cudaMemcpyDeviceToHost);

    int diffs = 0;
    for (size_t i=0; i < imgSize; i++){
        if (cpuOut[i] != gpuOut[i]) {
            diffs++;
        }
    }
    if (diffs==0) {
        printf("CPU i GPU wyniki sa IDENTYCZNE!\n");
    } else {
        printf("CPU i GPU roznia sie w %d bajtach\n", diffs);
    }

    stbi_write_jpg("cpu_output.jpg", width, height, channels, cpuOut, 100);
    stbi_write_jpg("gpu_output.jpg", width, height, channels, gpuOut, 100);

    free(cpuOut);
    free(gpuOut);
    stbi_image_free(pixels);

    cudaFree(d_in);
    cudaFree(d_out);

    return 0;
}
