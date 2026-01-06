#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <cuda.h>
#include <string.h>
#include <time.h>

#define CALL(x) { CUresult r = x; if(r!=CUDA_SUCCESS){ const char* p; cuGetErrorName(r,&p); fprintf(stderr,"%s returned %d (%s)\n", #x, r, p); exit(1); } }
#define N 100000

struct WIERZCHOLEK {
    float x, y;
};

int main(void) {
    float alfa = 0.123;
    size_t size_bytes = N * sizeof(struct WIERZCHOLEK);

    struct WIERZCHOLEK* FiguraCPU = (struct WIERZCHOLEK*)malloc(size_bytes);
    struct WIERZCHOLEK* FiguraGPU = (struct WIERZCHOLEK*)malloc(size_bytes);

    for (int i = 0; i < N; i++) {
        FiguraCPU[i].x = (float)rand() / RAND_MAX * 200.0f - 100.0f;
        FiguraCPU[i].y = (float)rand() / RAND_MAX * 200.0f - 100.0f;
    }

    memcpy(FiguraGPU, FiguraCPU, size_bytes);

    clock_t start_cpu = clock();
    for (int i = 0; i < N; i++) {
        float x = FiguraCPU[i].x * cosf(alfa) - FiguraCPU[i].y * sinf(alfa);
        float y = FiguraCPU[i].x * sinf(alfa) + FiguraCPU[i].y * cosf(alfa);
        FiguraCPU[i].x = x;
        FiguraCPU[i].y = y;
    }
    clock_t stop_cpu = clock();

    double cpu_ms = ((double)(stop_cpu - start_cpu)) / CLOCKS_PER_SEC * 1000.0;

    CALL(cuInit(0));

    CUdevice dev;
    CALL(cuDeviceGet(&dev, 0));

    CUcontext ctx;
    CUctxCreateParams params = {0};
    CALL(cuCtxCreate(&ctx, &params, 0, dev));

    CUmodule mod;
    CALL(cuModuleLoad(&mod, "kernel.cubin"));

    CUfunction func;
    CALL(cuModuleGetFunction(&func, mod, "obracanie"));

    CUdeviceptr d_W;
    CALL(cuMemAlloc(&d_W, size_bytes));
    CALL(cuMemcpyHtoD(d_W, FiguraGPU, size_bytes));

    int threadsPerBlock = 1024;
    int blocks = (N + threadsPerBlock - 1) / threadsPerBlock;

    int n = N;
    void* args[] = { &d_W, &alfa, &n };

    CUevent start, stop;
    CALL(cuEventCreate(&start, 0));
    CALL(cuEventCreate(&stop, 0));
    CALL(cuEventRecord(start, 0));

    CALL(cuLaunchKernel(
        func,
        blocks, 1, 1,
        threadsPerBlock, 1, 1,
        0, 0,
        args, 0
    ));

    CALL(cuCtxSynchronize());
    CALL(cuEventRecord(stop, 0));
    CALL(cuEventSynchronize(stop));

    float gpu_ms;
    CALL(cuEventElapsedTime(&gpu_ms, start, stop));

    CALL(cuMemcpyDtoH(FiguraGPU, d_W, size_bytes));
    CALL(cuMemFree(d_W));
    cuCtxDestroy(ctx);

    printf("%-12s: %.3f ms\n", "CPU", cpu_ms);
    printf("%-12s: %.3f ms\n", "GPU kernel", gpu_ms);

    free(FiguraCPU);
    free(FiguraGPU);

    return 0;
}
