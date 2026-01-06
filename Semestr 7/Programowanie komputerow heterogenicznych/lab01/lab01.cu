#include <stdio.h>
#include <math.h>
#include <assert.h>

#include <stdlib.h>
#include <chrono>
using namespace std::chrono;

#define N 10000000

struct WIERZCHOLEK {
	float x,y;
};

__global__ void obracanie(WIERZCHOLEK *W, float alfa) {
	int i = blockDim.x * blockIdx.x + threadIdx.x;

	if (i < N) {
		float x = W[i].x * cos(alfa) - W[i].y * sin(alfa);
		float y = W[i].x * sin(alfa) + W[i].y * cos(alfa);
		W[i].x = x;
		W[i].y = y;
	}
}

int main(void) {
	float alfa = 0.123;
	int ile_cudow;
	size_t size_bytes = N * sizeof(WIERZCHOLEK);

	WIERZCHOLEK* FiguraCPU = (WIERZCHOLEK*)malloc(size_bytes);
	WIERZCHOLEK* FiguraGPU = (WIERZCHOLEK*)malloc(size_bytes);
	WIERZCHOLEK *d_W;

    for (int i = 0; i < N; i++) {
        FiguraCPU[i].x = (float)rand() / RAND_MAX * 200.0f - 100.0f;
        FiguraCPU[i].y = (float)rand() / RAND_MAX * 200.0f - 100.0f;
    }

	memcpy(FiguraGPU, FiguraCPU, size_bytes);

	puts("--- CPU ---");

	auto start_cpu = high_resolution_clock::now();

    for (int i = 0; i < N; i++) {
        float x = FiguraCPU[i].x * cosf(alfa) - FiguraCPU[i].y * sinf(alfa);
        float y = FiguraCPU[i].x * sinf(alfa) + FiguraCPU[i].y * cosf(alfa);
        FiguraCPU[i].x = x;
        FiguraCPU[i].y = y;
    }

    auto stop_cpu = high_resolution_clock::now();
    auto cpu_duration = duration_cast<microseconds>(stop_cpu - start_cpu);

	cudaGetDeviceCount(&ile_cudow);
	if(ile_cudow == 0) {
		perror("Nie ściemniaj – nie masz CUDY");
		return 1;
	}

	puts("--- GPU ---");

	cudaMalloc(&d_W, size_bytes);

	int watki_na_blok = 1024;
  	int bloki_na_siatke = (N + watki_na_blok - 1) / watki_na_blok;

	cudaEvent_t total_start, total_stop;
	cudaEvent_t kernel_start, kernel_stop;
	cudaEventCreate(&total_start);
	cudaEventCreate(&total_stop);
	cudaEventCreate(&kernel_start);
	cudaEventCreate(&kernel_stop);

    cudaEventRecord(total_start);
	cudaMemcpy(d_W, FiguraGPU, size_bytes, cudaMemcpyHostToDevice);

	cudaEventRecord(kernel_start);
  	obracanie<<<bloki_na_siatke, watki_na_blok>>>(d_W, alfa);
	cudaEventRecord(kernel_stop);
	cudaEventSynchronize(kernel_stop);

  	cudaError_t err = cudaGetLastError();
  	assert(err == cudaSuccess);
  	cudaDeviceSynchronize();

  	cudaMemcpy(FiguraGPU, d_W, N * size_bytes, cudaMemcpyDeviceToHost);

	cudaEventRecord(total_stop);
	cudaEventSynchronize(total_stop);

	float total_ms = 0.0f;
	float kernel_ms = 0.0f;
	cudaEventElapsedTime(&total_ms, total_start, total_stop);
	cudaEventElapsedTime(&kernel_ms, kernel_start, kernel_stop);

	cudaEventDestroy(total_start);
    cudaEventDestroy(total_stop);
    cudaEventDestroy(kernel_start);
    cudaEventDestroy(kernel_stop);

	cudaFree(d_W);

	// print differences to terminal
	// for (int i = 0; i < N; i++) {
	// 	if (FiguraCPU[i].x != FiguraGPU[i].x) {
	// 		printf("Index %d, x: %f -- %f\n", i, FiguraCPU[i].x, FiguraGPU[i].x);
	// 	}
	// 	if (FiguraCPU[i].y != FiguraGPU[i].y) {
	// 		printf("Index %d, y: %f -- %f\n", i, FiguraCPU[i].y, FiguraGPU[i].y);
	// 	}
	// }

	free(FiguraCPU);
	free(FiguraGPU);

	printf("%-12s: %.3f ms\n", "CPU", cpu_duration.count() / 1000.0);
	printf("%-12s: %.3f ms\n", "GPU kernel", kernel_ms);
	printf("%-12s: %.3f ms\n", "GPU total", total_ms);

	return 0;
}
