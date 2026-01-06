#include <iostream>
#include <cmath>
#include <chrono>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

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

void zad01(double eps) {
    auto start = chrono::high_resolution_clock::now();

    double product = 1.0;
    double pi_prev = 0.0, pi_curr = 0.0;
    int n = 0;

    while (true) {
        n++;
        product *= (4.0 * n * n) / (4.0 * n * n - 1.0);
        pi_curr = 2.0 * product;

        if (fabsl(pi_curr - pi_prev) < eps)
            break;

        pi_prev = pi_curr;
    }

    auto end = chrono::high_resolution_clock::now();
    double time_ms = chrono::duration<double, milli>(end - start).count();

    cout << "pi = " << pi_curr << "\n";
    cout << "iterations: " << n << "\n";
    cout << "CPU time: " << time_ms << " ms\n";

    if (fabs(pi_curr - M_PI) < 1e-4) {
        cout << "PI matches to at least 4 decimal places\n";
    }
}

void zad02(int i) {
    int maxThreads = 1024;

    double *d_vector, *d_product;
    double h_product = 1.0;

    cudaMalloc(&d_vector, i * sizeof(double));
    cudaMalloc(&d_product, sizeof(double));

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);

    int remaining = i;
    int offset = 0;

    while (remaining > 0) {
        int currentBatch = 0;
        if (remaining > maxThreads) {
            currentBatch = maxThreads;
        } else {
            currentBatch = remaining;
        }

        wallis<<<1, currentBatch>>>(offset + 1, offset + currentBatch + 1, d_vector, d_product);
        cudaDeviceSynchronize();

        double h_partial = 0.0;
        cudaMemcpy(&h_partial, d_product, sizeof(double), cudaMemcpyDeviceToHost);

        h_product *= h_partial;

        offset += currentBatch;
        remaining -= currentBatch;
    }

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    double pi = 2.0 * h_product;

    float time_ms = 0.0f;
    cudaEventElapsedTime(&time_ms, start, stop);

    cout << "pi = " << pi << "\n";
    cout << "GPU time: " << time_ms << " ms\n";

    cudaFree(d_vector);
    cudaFree(d_product);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "you have to pass two arguments\n";
        return 1;
    }

    double eps = atof(argv[1]);
    if (eps <= 0) {
        cout << "eps must be > 0\n";
        return 1;
    }

    int i = atoi(argv[2]);

    zad01(eps);
    zad02(i);

    return 0;
}
