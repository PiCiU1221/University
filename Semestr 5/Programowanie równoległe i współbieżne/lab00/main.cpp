#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

int** A;
int** B;
int** BT;
int** C;

void func(int N, int tid, int num_threads) {
    int lb = (N / num_threads) * tid;
    int ub = lb + (N / num_threads) - 1;

    for (int i = lb; i <= ub; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * BT[j][k];
            }
        }
    }
}

int main(int argc, char* argv[]) {
    //int num_threads = atoi(argv[1]);
    //int N = atoi(argv[2]);
    int num_threads = 1;
    int N = 1000;

    A = new int*[N];

    for (int i = 0; i < N; i++) {
        A[i] = new int[N];
    }

    B = new int*[N];

    for (int i = 0; i < N; i++) {
        B[i] = new int[N];
    }

    BT = new int*[N];

    for (int i = 0; i < N; i++) {
        BT[i] = new int[N];
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            BT[i][j] = B[j][i];
        }
    }

    C = new int*[N];

    for (int i = 0; i < N; i++) {
        C[i] = new int[N];
    }

    std::vector<std::thread> th;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_threads; i++) {
        th.push_back(std::thread(func, N, i, num_threads));
    }

    for (auto &t : th) {
        t.join();
    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << duration.count() << " ms" << std::endl;

    for (int i = 0; i < N; i++) {
        delete[] A[i];
    }
    delete[] A;

    for (int i = 0; i < N; i++) {
        delete[] B[i];
    }
    delete[] B;

    for (int i = 0; i < N; i++) {
        delete[] C[i];
    }
    delete[] C;

    return 0;
}