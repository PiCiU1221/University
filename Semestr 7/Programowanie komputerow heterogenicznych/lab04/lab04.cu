//
// LISTA ZADAN NR 4S
//

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cuda_runtime.h>
#include <cstring>

using namespace std;

// 
// ZAD 1
//

unsigned long ulps_between(float a, float b) {
    a = fabs(a);
    b = fabs(b);

    int ia, ib;
    memcpy(&ia, &a, sizeof(float));
    memcpy(&ib, &b, sizeof(float));

    return (unsigned long)abs(ia - ib);
}

void test_ulps() {
    float a, b;
    unsigned long ulp;

    cout << fixed << setprecision(7);

    a = 1.0f; b = nextafterf(a, 2.f);
    ulp = ulps_between(a, b);
    cout << "ULP distance between | " << a << "| and | " << b << "| = " << ulp << endl;

    a = -1.0f; b = -1.0000010f;
    ulp = ulps_between(a, b);
    cout << "ULP distance between |" << a << "| and |" << b << "| = " << ulp << endl;

    a = 1.0f; b = 2.0f;
    ulp = ulps_between(a, b);
    cout << "ULP distance between | " << a << "| and | " << b << "| = " << ulp << endl;
}

//
// ZAD 3
//

__global__ void poly(float a[], float x, float products[]) {
    int i = threadIdx.x;
    float exponent = 1.f / (i + 0.6180339887f);
    products[i] = a[i] * powf(x, exponent);
}

float poly_cpu(float a[], int N, float x) {
    float result = 0.0f;
    for (int i = 0; i < N; i++) {
        float exponent = 1.f / (i + 0.6180339887f);
        result += a[i] * powf(x, exponent);
    }
    return result;
}

void poly_experiment(void) {
    const int N = 1024;

    float *a = new float[N];
    float *products = new float[N];

    for (int i = 0; i < N; i++) {
        a[i] = 1.0f / (1000.0f + i * 0.12345f); 
    }

    float x = 1.0000001f;

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

    printf("Polynomial value (GPU): %.10f\n", result_gpu);
    printf("Polynomial value (CPU): %.10f\n", result_cpu);

    unsigned long ulp_diff = ulps_between(result_cpu, result_gpu);
    printf("Difference in ULP between CPU and GPU: %lu\n", ulp_diff);

    cudaFree(d_a);
    cudaFree(d_products);

    delete[] a;
    delete[] products;
}

int main() {
    test_ulps();

    poly_experiment();

    return 0;
}
