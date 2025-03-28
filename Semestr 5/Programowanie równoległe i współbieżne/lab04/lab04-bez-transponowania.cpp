#include <iostream>
#include <vector>
#include <omp.h>

int** A;
int** B;
int** C;

int main(int argc, char* argv[]) {
    int num_threads = atoi(argv[1]);
    int N = atoi(argv[2]);

    omp_set_num_threads(num_threads);

    A = new int*[N];
    B = new int*[N];
    C = new int*[N];

    for (int i = 0; i < N; i++) {
        A[i] = new int[N];
        B[i] = new int[N];
        C[i] = new int[N];
    }

    double start_time = omp_get_wtime();

#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
                //C[i][j] = omp_get_thread_num();
            }
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
        delete[] C[i];
    }

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
