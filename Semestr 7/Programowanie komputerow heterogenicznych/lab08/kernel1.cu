#include <cuda.h>

struct WIERZCHOLEK {
    float x, y;
};

extern "C" __global__ void obracanie(WIERZCHOLEK *W, float alfa, int N) {
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < N) {
        float x = W[i].x * cosf(alfa) - W[i].y * sinf(alfa);
        float y = W[i].x * sinf(alfa) + W[i].y * cosf(alfa);
        W[i].x = x;
        W[i].y = y;
    }
}
