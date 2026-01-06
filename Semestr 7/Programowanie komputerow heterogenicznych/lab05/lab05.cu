//
// LISTA ZADAN NR 5S
//

#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

//
// ZADANIE 3
//

__global__ void wallis(int from, int to, double *vector, double *product) {
    int idx = threadIdx.x + from;
    vector[idx - from] = (4.0 * idx * idx) / (4.0 * idx * idx - 1.0);

    __syncthreads();

    if (threadIdx.x == 0) {
        double prod = 1.0;
        for (int i = 0; i < to - from; i++) {
            prod *= vector[i];
        }
        *product = prod;
    }
}

void zad03(int n, int streamsNum) {
    const int maxThreads = 1024;
    const int batchSize = n / streamsNum;

    double *d_vectors[streamsNum];
    double *d_products[streamsNum];
    double h_products[streamsNum];

    cudaStream_t streams[streamsNum];

    for (int i = 0; i < streamsNum; i++) {
        cudaStreamCreate(&streams[i]);
        cudaMalloc(&d_vectors[i], batchSize * sizeof(double));
        cudaMalloc(&d_products[i], sizeof(double));
    }

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);

    for (int i = 0; i < streamsNum; i++) {
        int from = i * batchSize + 1;

        int to;
        if (i == streamsNum - 1) {
            to = n + 1;
        } else {
            to = (i + 1) * batchSize + 1;
        }

        int threads = to - from;

        if (threads > maxThreads) {
            threads = maxThreads;
        }

        wallis<<<1, threads, 0, streams[i]>>>(from, to, d_vectors[i], d_products[i]);
    }

    for (int i = 0; i < streamsNum; i++) {
        cudaMemcpyAsync(&h_products[i], d_products[i], sizeof(double), cudaMemcpyDeviceToHost, streams[i]);
    }

    cudaDeviceSynchronize();

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    double h_product = 1.0;
    for (int i = 0; i < streamsNum; i++) {
        h_product *= h_products[i];
    }

    double pi = 2.0 * h_product;

    float time_ms = 0.0f;
    cudaEventElapsedTime(&time_ms, start, stop);

    cout << "pi = " << pi << "\n";
    cout << "GPU time: " << time_ms << " ms\n";

    for (int i = 0; i < streamsNum; i++) {
        cudaFree(d_vectors[i]);
        cudaFree(d_products[i]);
        cudaStreamDestroy(streams[i]);
    }
}

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "you have to pass two arguments\n";
        return 1;
    }

    int n = atoi(argv[1]);
    int streamsNum = atoi(argv[2]);

    zad03(n, streamsNum);

    return 0;
}
