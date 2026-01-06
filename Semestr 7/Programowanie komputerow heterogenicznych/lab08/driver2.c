#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <string.h>
#include <time.h>

#define N 2000000
#define BLK_SZ 1024
#define CALL(x) { CUresult r = x; if(r!=CUDA_SUCCESS){ const char* p; cuGetErrorName(r,&p); fprintf(stderr,"%s returned %d (%s)\n", #x, r, p); exit(1); } }

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <kernel_name>\n", argv[0]);
        return 1;
    }

    const char* kernel_name = argv[1];

    float *HostVect = (float*)malloc(N * sizeof(float));
    float *HostOut  = (float*)malloc(N * sizeof(float));

    for (int i = 0; i < N; i++) {
        HostVect[i] = i * 0.5f;
    }

    int n = N;
    float in2 = 2.0f;
    float scale = 3.0f;

    int blocks = N / BLK_SZ;
    if (N % BLK_SZ) blocks++;

    CUdevice hDevice;
    CUcontext hContext;
    CUmodule hModule;
    CUfunction hFunction;

    CALL(cuInit(0));
    CALL(cuDeviceGet(&hDevice, 0));
    CUctxCreateParams params = {0};
    CALL(cuCtxCreate(&hContext, &params, 0, hDevice));
    CALL(cuModuleLoad(&hModule, "kernel.cubin"));

    if (cuModuleGetFunction(&hFunction, hModule, kernel_name) != CUDA_SUCCESS) {
        fprintf(stderr, "Kernel '%s' not found!\n", kernel_name);
        cuCtxDestroy(hContext);
        free(HostVect);
        free(HostOut);
        return 1;
    }

    size_t size_bytes = N * sizeof(float);
    CUdeviceptr DevVectIn, DevVectOut;
    CALL(cuMemAlloc(&DevVectIn, size_bytes));
    CALL(cuMemAlloc(&DevVectOut, size_bytes));
    CALL(cuMemcpyHtoD(DevVectIn, HostVect, size_bytes));

    void* args_add[] = { &DevVectIn, &in2, &DevVectOut, &n };
    void* args_dot[] = { &DevVectIn, &in2, &DevVectOut, &n };
    void* args_scale[] = { &DevVectIn, &DevVectOut, &scale, &n };

    void **args;

    if (strcmp(kernel_name, "add_vectors") == 0) {
        args = args_add;
    } else if (strcmp(kernel_name, "dot_product") == 0) {
        args = args_dot;
    } else if (strcmp(kernel_name, "scale_vectors") == 0) {
        args = args_scale;
    } else {
        fprintf(stderr, "Unknown kernel name!\n");
        cuMemFree(DevVectIn);
        cuMemFree(DevVectOut);
        cuCtxDestroy(hContext);
        free(HostVect);
        free(HostOut);
        return 1;
    }

    CUevent start, stop;
    CALL(cuEventCreate(&start, 0));
    CALL(cuEventCreate(&stop, 0));
    CALL(cuEventRecord(start, 0));

    CALL(cuLaunchKernel(hFunction,
                        blocks, 1, 1,
                        BLK_SZ, 1, 1,
                        0, 0,
                        args, 0));

    CALL(cuCtxSynchronize());
    CALL(cuEventRecord(stop, 0));
    CALL(cuEventSynchronize(stop));

    float gpu_ms;
    CALL(cuEventElapsedTime(&gpu_ms, start, stop));
    printf("GPU kernel '%s' time: %.3f ms\n", kernel_name, gpu_ms);

    CALL(cuMemcpyDtoH(HostOut, DevVectOut, size_bytes));

    printf("First 10 results:\n");
    for (int i = 0; i < 10; i++) {
        printf("%f ", HostOut[i]);
    }
    printf("\n");

    CALL(cuMemFree(DevVectIn));
    CALL(cuMemFree(DevVectOut));
    cuCtxDestroy(hContext);

    free(HostVect);
    free(HostOut);

    return 0;
}
