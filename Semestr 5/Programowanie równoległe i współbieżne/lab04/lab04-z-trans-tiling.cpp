#include <iostream>
#include <vector>
#include <omp.h>

int** A;
int** B;
int** BT;
int** C;
int*** _C;

int main(int argc, char* argv[]) {
    int num_threads = atoi(argv[1]);
    int N = atoi(argv[2]);
    int tile_size = atoi(argv[3]);

    omp_set_num_threads(num_threads);

    A = new int*[N];
    B = new int*[N];
    BT = new int*[N];
    C = new int*[N];

    for (int i = 0; i < N; i++) {
        A[i] = new int[N];
        B[i] = new int[N];
        BT[i] = new int[N];
        C[i] = new int[N];
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            BT[i][j] = B[j][i];
        }
    }

    _C = new int**[num_threads];
    for (int t = 0; t < num_threads; t++) {
        _C[t] = new int*[tile_size];
        for (int i = 0; i < tile_size; i++) {
            _C[t][i] = new int[tile_size];
        }
    }

    double start_time = omp_get_wtime();

#pragma omp parallel num_threads(num_threads)
    {
        int tid = omp_get_thread_num();

#pragma omp for
        for (int jj = 0; jj < N / tile_size; jj++)
            for (int ii = 0; ii < N / tile_size; ii++) {

                for (int j = jj * tile_size; j < (jj + 1) * tile_size; j++)
                    for (int i = ii * tile_size; i < (ii + 1) * tile_size; i++)
                        //_C[tid][j % tile_size][i % tile_size] = tid + (ii + 1) * 10;
                        for (int k = 0; k < N; k++) {
                            _C[tid][j % tile_size][i % tile_size] += A[j][k] * BT[i][k];
                        }

                for (int j = jj * tile_size; j < (jj + 1) * tile_size; j++)
                    for (int i = ii * tile_size; i < (ii + 1) * tile_size; i++)
                        C[j][i] = _C[tid][j % tile_size][i % tile_size];
            }
    }

//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//            std::cout << C[i][j] << " ";
//        }
//        std::cout << "\n";
//    }

    double end_time = omp_get_wtime();
    auto duration = end_time - start_time;
    std::cout << duration << " s" << std::endl;

    for (int i = 0; i < N; i++) {
        delete[] A[i];
        delete[] B[i];
        delete[] BT[i];
        delete[] C[i];
    }

    delete[] A;
    delete[] B;
    delete[] BT;
    delete[] C;

    for (int t = 0; t < num_threads; t++) {
        for (int i = 0; i < tile_size; i++) {
            delete[] _C[t][i];
        }
        delete[] _C[t];
    }
    delete[] _C;

    return 0;
}
