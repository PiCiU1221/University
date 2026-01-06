#include <stdio.h>
#include <cuda_runtime.h>

#include <math.h>

__global__ void poly(float a[], float x, float products[]) {
    int i = threadIdx.x;
    products[i] = a[i] * powf(x, i);
}

float poly_cpu(float a[], int N, float x) {
    float result = 0.0f;
    for (int i = 0; i < N; i++) {
        result += a[i] * powf(x, i);
    }
    return result;
}

int get_max_threads_per_block(int devno) {
    int count;
    cudaGetDeviceCount(&count);
    if (count == 0 || devno < 0 || devno >= count) {
        return -1;
    }

    cudaDeviceProp prop;
    cudaGetDeviceProperties(&prop, devno);
    return prop.maxThreadsPerBlock;
}

int print_cuda_device_info(void) {
    int count;
    cudaGetDeviceCount(&count);

    if (count == 0) {
        printf("No CUDA devices found.\n");
        return 1;
    }

    printf("Number of CUDA devices: %d\n\n", count);

    for (int i = 0; i < count; i++) {
        cudaDeviceProp prop;
        cudaGetDeviceProperties(&prop, i);

        printf("Device %d:\n", i);
        printf("  Name: %s\n", prop.name);
        printf("  Global memory: %zu MB\n", prop.totalGlobalMem / (1024 * 1024));
        printf("  Multiprocessors: %d\n", prop.multiProcessorCount);
        printf("  Compute capability: %d.%d\n", prop.major, prop.minor);
        printf("  Max threads per block: %d\n", get_max_threads_per_block(i));
        printf("  Can map host memory: %s\n", prop.canMapHostMemory ? "YES" : "NO");
        printf("\n");
    }

    return 0;
}

void run_poly_demo(void) {
    const int N = 8;
    float a[N] = {1, 1, 1, 1, 1, 1, 1, 1};
    float x = 2.0f;
    float products[N];

    int byte_size = N * sizeof(float); 

    float *d_a = NULL;
    float *d_products = NULL;

    cudaMalloc(&d_a, byte_size);
    cudaMalloc(&d_products, byte_size);

    cudaMemcpy(d_a, a, byte_size, cudaMemcpyHostToDevice);

    poly<<<1, N>>>(d_a, x, d_products);

    cudaMemcpy(products, d_products, byte_size, cudaMemcpyDeviceToHost);

    float result_gpu = 0.0f;
    for (int i = 0; i < N; i++) {
        result_gpu += products[i];
    }

    float result_cpu = poly_cpu(a, N, x);

    printf("Polynomial value (GPU): %.1f\n", result_gpu);
    printf("Polynomial value (CPU): %.1f\n", result_cpu);

    cudaFree(d_a);
    cudaFree(d_products);
}

int main(void) {
    // ZAD 1
    int status = print_cuda_device_info();
    if (status != 0) {
        return status;
    }

    // ZAD 2
    run_poly_demo();

    return 0;
}
