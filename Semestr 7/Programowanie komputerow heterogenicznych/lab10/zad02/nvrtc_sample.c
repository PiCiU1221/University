#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <cuda.h>
#include <nvrtc.h>

#define CUDA_CHECK(err) \
    if (err != CUDA_SUCCESS) { \
        const char *errStr; \
        cuGetErrorString(err, &errStr); \
        fprintf(stderr, "CUDA Error: %s\n", errStr); \
        exit(1); \
    }

#define NVRTC_CHECK(err) \
    if (err != NVRTC_SUCCESS) { \
        fprintf(stderr, "NVRTC Error: %s\n", nvrtcGetErrorString(err)); \
        exit(1); \
    }

int main(int argc, char *argv[]) {
    int N_SAMPLES = 1000;
    int N_POINTS = 1000000;

    if (argc < 4) {
        fprintf(stderr, "Usage: %s \"y=f(x)\" xd xg\n", argv[0]);
        fprintf(stderr, "Example: %s \"y = sin(x) + cos(x)\" 0.0 1.5707\n", argv[0]);
        exit(1);
    }

    char *input_func = argv[1];
    char *formula = strchr(input_func, '=');
    
    if (formula != NULL) {
        formula++;
    } else {
        formula = input_func;
    }

    float xd = strtof(argv[2], NULL);
    float xg = strtof(argv[3], NULL);

    if (xg <= xd) {
        fprintf(stderr, "Error: Upper bound (xg) must be greater than lower bound (xd)!\n");
        exit(1);
    }

    printf("Funkcja: %s\n", formula);
    printf("Przedzial: [%.4f, %.4f]\n", xd, xg);

    const char *code_template_part1 = 
        "extern \"C\" __device__ float f(float x) {\n"
        "  return ";
    
    const char *code_template_part2 = 
        ";\n"
        "}\n"
        "\n"
        "extern \"C\" __global__ void findExtremes(float *samples, float xd, float xg, int n) {\n"
        "  int i = blockIdx.x * blockDim.x + threadIdx.x;\n"
        "  if (i < n) {\n"
        "    float step = (xg - xd) / (float)n;\n"
        "    float x = xd + i * step;\n"
        "    samples[i] = f(x);\n"
        "  }\n"
        "}\n"
        "\n"
        "extern \"C\" __global__ void monteCarlo(float *x_rand, float *y_rand, int *m, float xd, float xg, float ymin, float ymax, int n) {\n"
        "  int i = blockIdx.x * blockDim.x + threadIdx.x;\n"
        "  if (i < n) {\n"
        "    float width = xg - xd;\n"
        "    float height = (ymax + 1.0f) - (ymin - 1.0f);\n"
        "\n"
        "    float x = xd + x_rand[i] * width;\n"
        "    float y = (ymin - 1.0f) + y_rand[i] * height;\n"
        "\n"
        "    float val = f(x);\n"
        "\n"
        "    if (val > 0.0f) {\n"
        "      if (y > 0.0f && y < val) {\n"
        "        atomicAdd(m, 1);\n"
        "      }\n"
        "    } else if (val < 0.0f) {\n"
        "      if (y < 0.0f && y > val) {\n"
        "        atomicAdd(m, -1);\n"
        "      }\n"
        "    }\n"
        "  }\n"
        "}\n";

    size_t code_len = strlen(code_template_part1) + strlen(formula) + strlen(code_template_part2) + 100;
    char *cuda_code = (char *)malloc(code_len);
    
    sprintf(cuda_code, "%s%s%s", code_template_part1, formula, code_template_part2);

    nvrtcProgram prog;
    NVRTC_CHECK(nvrtcCreateProgram(&prog, cuda_code, "monte_carlo.cu", 0, NULL, NULL));

    const char *opts[] = {"--gpu-architecture=compute_80"};
    nvrtcResult compileRes = nvrtcCompileProgram(prog, 1, opts);

    if (compileRes != NVRTC_SUCCESS) {
        size_t logSize;
        nvrtcGetProgramLogSize(prog, &logSize);
        char *log = (char *)malloc(logSize);
        nvrtcGetProgramLog(prog, log);
        fprintf(stderr, "NVRTC compilation error:\n%s\n", log);
        free(log);
        exit(1);
    }

    size_t ptxSize;
    NVRTC_CHECK(nvrtcGetPTXSize(prog, &ptxSize));
    char *ptx = (char *)malloc(ptxSize);
    NVRTC_CHECK(nvrtcGetPTX(prog, ptx));
    NVRTC_CHECK(nvrtcDestroyProgram(&prog));

    CUDA_CHECK(cuInit(0));
    CUdevice dev;
    CUDA_CHECK(cuDeviceGet(&dev, 0));
    CUcontext ctx;
    CUDA_CHECK(cuCtxCreate(&ctx, 0, dev, 0));

    CUmodule module;
    CUDA_CHECK(cuModuleLoadData(&module, ptx));
    
    CUfunction kernel_findExtremes, kernel_monteCarlo;
    CUDA_CHECK(cuModuleGetFunction(&kernel_findExtremes, module, "findExtremes"));
    CUDA_CHECK(cuModuleGetFunction(&kernel_monteCarlo, module, "monteCarlo"));

    srand(time(NULL));

    size_t size_samples = N_SAMPLES * sizeof(float);
    size_t size_points = N_POINTS * sizeof(float);

    float *h_samples = (float*)malloc(size_samples);
    float *h_x_rand = (float*)malloc(size_points);
    float *h_y_rand = (float*)malloc(size_points);
    int h_M = 0;

    for(int i=0; i<N_POINTS; i++) {
        h_x_rand[i] = (float)rand() / (float)RAND_MAX;
        h_y_rand[i] = (float)rand() / (float)RAND_MAX;
    }

    CUdeviceptr d_samples, d_x_rand, d_y_rand, d_M;
    
    CUDA_CHECK(cuMemAlloc(&d_samples, size_samples));
    CUDA_CHECK(cuMemAlloc(&d_x_rand, size_points));
    CUDA_CHECK(cuMemAlloc(&d_y_rand, size_points));
    CUDA_CHECK(cuMemAlloc(&d_M, sizeof(int)));

    CUDA_CHECK(cuMemcpyHtoD(d_x_rand, h_x_rand, size_points));
    CUDA_CHECK(cuMemcpyHtoD(d_y_rand, h_y_rand, size_points));
    CUDA_CHECK(cuMemsetD32(d_M, 0, 1)); 

    int blockSize = 1024;
    int gridSizeSamples = (N_SAMPLES + blockSize - 1) / blockSize;

    void *argsExtremes[] = { &d_samples, &xd, &xg, &N_SAMPLES };

    CUDA_CHECK(cuLaunchKernel(kernel_findExtremes,
                              gridSizeSamples, 1, 1,
                              blockSize, 1, 1,
                              0, 0, argsExtremes, 0));
    
    CUDA_CHECK(cuCtxSynchronize());

    CUDA_CHECK(cuMemcpyDtoH(h_samples, d_samples, size_samples));

    float ymin = h_samples[0];
    float ymax = h_samples[0];
    for(int i=1; i<N_SAMPLES; i++) {
        if(h_samples[i] < ymin) ymin = h_samples[i];
        if(h_samples[i] > ymax) ymax = h_samples[i];
    }

    int gridSizePoints = (N_POINTS + blockSize - 1) / blockSize;
    void *argsMonte[] = { &d_x_rand, &d_y_rand, &d_M, &xd, &xg, &ymin, &ymax, &N_POINTS };

    CUDA_CHECK(cuLaunchKernel(kernel_monteCarlo,
                              gridSizePoints, 1, 1,
                              blockSize, 1, 1,
                              0, 0, argsMonte, 0));
    
    CUDA_CHECK(cuCtxSynchronize());

    CUDA_CHECK(cuMemcpyDtoH(&h_M, d_M, sizeof(int)));

    float integral_result = (xg - xd) * (ymax - ymin + 2.0f) * (float)h_M / (float)N_POINTS;

    printf("--- WYNIKI ---\n");
    printf("Liczba trafien (M): %d\n", h_M);
    printf("WYNIK CALKI:        %.6f\n", integral_result);

    cuMemFree(d_samples);
    cuMemFree(d_x_rand);
    cuMemFree(d_y_rand);
    cuMemFree(d_M);
    
    cuModuleUnload(module);
    cuCtxDestroy(ctx);
    free(ptx);
    free(h_samples);
    free(h_x_rand);
    free(h_y_rand);

    return 0;
}