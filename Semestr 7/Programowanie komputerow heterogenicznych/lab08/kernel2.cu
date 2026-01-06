extern "C" __global__ void add_vectors(float *in1, float in2, float *out, int N) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N) {
        out[i] = in1[i] + in2;
    }
}

extern "C" __global__ void dot_product(float *in1, float in2, float *out, int N) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N) {
        out[i] = in1[i] * in2;
    }
}

extern "C" __global__ void scale_vectors(float *in, float *out, float scale, int N) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N) {
        out[i] = in[i] * scale;
    }
}
