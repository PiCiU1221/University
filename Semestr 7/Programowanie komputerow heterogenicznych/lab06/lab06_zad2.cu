#include <stdio.h>
#include <cuda.h>

__global__ void loopNormal(int *result, unsigned int *cycles) {
    unsigned int start = clock();
    int sum = 0;

    #pragma unroll 1
    for (int i = 0; i < 1000000; i++) {
        sum += (i & 7);
    }

    unsigned int end = clock();
    cycles[0] = end - start;
    result[0] = sum;
}

__global__ void loopUnrolled(int *result, unsigned int *cycles) {
    unsigned int start = clock();
    int sum = 0;

    #pragma unroll 10000
    for (int i = 0; i < 1000000; i++) {
        sum += (i & 7);
    }

    unsigned int end = clock();
    cycles[0] = end - start;
    result[0] = sum;
}

int main() {
    int *d_result;
    unsigned int *d_cycles;
    int h_result;
    unsigned int h_cycles;

    cudaMalloc(&d_result, sizeof(int));
    cudaMalloc(&d_cycles, sizeof(unsigned int));

    loopNormal<<<1,1>>>(d_result, d_cycles);
    cudaDeviceSynchronize();
    cudaMemcpy(&h_result, d_result, sizeof(int), cudaMemcpyDeviceToHost);
    cudaMemcpy(&h_cycles, d_cycles, sizeof(unsigned int), cudaMemcpyDeviceToHost);
    printf("Normal loop cycles:   %u\n", h_cycles);

    loopUnrolled<<<1,1>>>(d_result, d_cycles);
    cudaDeviceSynchronize();
    cudaMemcpy(&h_cycles, d_cycles, sizeof(unsigned int), cudaMemcpyDeviceToHost);
    printf("Unrolled loop cycles: %u\n", h_cycles);

    cudaFree(d_result);
    cudaFree(d_cycles);

    return 0;
}
