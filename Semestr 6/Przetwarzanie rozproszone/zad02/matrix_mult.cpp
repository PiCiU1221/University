#include <iostream>
#include <fstream>
#include <omp.h>
#include <vector>
#include <string>

using namespace std;

int* loadMatrixFromFile(const string filename, int& rows, int& cols) {
    ifstream file(filename);
    
    file >> rows >> cols;

    int* matrix = new int[rows * cols];

    for (int i = 0; i < rows * cols; i++) {
        file >> matrix[i];
    }

    file.close();
    return matrix;
}

void multiplyMatrices1For(const int* matrix_a, const int* matrix_b, long* matrix_c, const int rows, const int cols) {
    #pragma omp parallel for
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (int k = 0; k < cols; k++) {
                matrix_c[i * cols + j] += matrix_a[i * cols + k] * matrix_b[k * cols + j];
            }
        }
    }
}

void multiplyMatrices2For(const int* matrix_a, const int* matrix_b, long* matrix_c, const int rows, const int cols) {
    for (int i = 0; i < rows; i++) {
        #pragma omp parallel for
        for (int j = 0; j < cols; j++) {
            for (int k = 0; k < cols; k++) {
                matrix_c[i * cols + j] += matrix_a[i * cols + k] * matrix_b[k * cols + j];
            }
        }
    }
}

void writeMatrixToFile(const long* matrix_c, const char* filename, const int rows, const int cols) {
    ofstream file(filename);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            file << matrix_c[i * cols + j] << " ";
        }
        file << endl;
    }

    file.close();
}

int main(int argc, char* argv[]) {
    // FIRST PART - matrix load
    vector<string> matrix_filenames = {"100_100.txt", "500_500.txt", "1000_1000.txt", "2000_2000.txt"};
    vector<int> thread_counts = {1, 2, 4, 8, 16};

    string matrices_path = "../matrices/";

    int rows, cols;
    int* matrix_a = nullptr;
    int* matrix_b = nullptr;
    long* matrix_c = nullptr;
    string full_path;

    for (const string& filename : matrix_filenames) {
        full_path = matrices_path + filename;
        
        matrix_a = nullptr;
        matrix_b = nullptr;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                matrix_a = loadMatrixFromFile(full_path, rows, cols);
            }
            #pragma omp section
            {
                matrix_b = loadMatrixFromFile(full_path, rows, cols);
            }
        }

        // SECOND PART - matrix multiplication
        matrix_c = new long[rows * cols];

        for (int t : thread_counts) {
            omp_set_num_threads(t);
            
            fill(matrix_c, matrix_c + (rows * cols), 0);

            double start = omp_get_wtime();
            multiplyMatrices1For(matrix_a, matrix_b, matrix_c, rows, cols);
            double end = omp_get_wtime();

            cout << "File: " << filename << " | Threads: " << t << " | Time: " << (end - start) << " seconds\n";
        }
    }

    // THIRD PART - result matrix write to file
    writeMatrixToFile(matrix_c, "matrix_c.txt", rows, cols);

    delete[] matrix_a;
    delete[] matrix_b;
    delete[] matrix_c;

    return 0;
}