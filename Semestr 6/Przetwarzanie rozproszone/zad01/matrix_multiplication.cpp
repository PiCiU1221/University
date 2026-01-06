#include <iostream>
#include <fstream>

using namespace std;

int* loadMatrixFromFile(const char* filename, int& rows, int& cols) {
    ifstream file(filename);
    
    file >> rows >> cols;

    int* matrix = new int[rows * cols];

    for (int i = 0; i < rows * cols; i++) {
        file >> matrix[i];
    }

    file.close();
    return matrix;
}

void multiplyMatrices(const int* matrix_a, const int* matrix_b, long* matrix_c, const int rows, const int cols) {
    for (int i = 0; i < rows; i++) {
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
    int rows, cols;

    const char* matrix_a_filename = argv[1];
    const char* matrix_b_filename = argv[2];

    int* matrix_a = loadMatrixFromFile(matrix_a_filename, rows, cols);
    int* matrix_b = loadMatrixFromFile(matrix_b_filename, rows, cols);

    // SECOND PART - matrix multiplication
    long* matrix_c = new long[rows * cols];
    for (int i = 0; i < rows * cols; i++) {
        matrix_c[i] = 0;
    }

    multiplyMatrices(matrix_a, matrix_b, matrix_c, rows, cols);

    // THIRD PART - result matrix write to file
    writeMatrixToFile(matrix_c, "matrix_c.txt", rows, cols);

    delete[] matrix_a;
    delete[] matrix_b;
    delete[] matrix_c;

    return 0;
}