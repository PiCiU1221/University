#include <iostream>
#include <omp.h>
#include <valarray>
#include <iomanip>
#include <random>

int ulam_get_map(int x, int y, int n) {
    x -= (n - 1) / 2;
    y -= n / 2;

    int mx = abs(x), my = abs(y);
    int l = 2 * std::max(mx, my);
    int d = y >= x ? l * 3 + x + y : l - x - y;

    return pow(l - 1, 2) + d;
}

int isprime(int n) {
    int p;
    for (p = 2; p * p <= n; p++)
        if (n % p == 0) return 0;
    return n > 2;
}

unsigned char*** colorArray;

const int MaxColorComponentValue=255;
FILE * fp;
char *filename="new1.ppm";
char *comment="# ";

int main(int argc, char* argv[]) {
    int num_threads = atoi(argv[1]);
    int n = atoi(argv[2]);
    int tile_size = atoi(argv[3]);

    colorArray = new unsigned char **[n];
    for (int i = 0; i < n; ++i) {
        colorArray[i] = new unsigned char *[n];
        for (int j = 0; j < n; ++j) {
            colorArray[i][j] = new unsigned char[3];
        }
    }

    double start_time = omp_get_wtime();

#pragma omp parallel num_threads(num_threads)
    {
        int tid = omp_get_thread_num();

        std::mt19937 rng(omp_get_thread_num() + 12345);
        std::uniform_int_distribution<int> color_dist(0, 255);

        auto color1 = color_dist(rng);
        auto color2 = color_dist(rng);
        auto color3 = color_dist(rng);

#pragma omp for collapse(2)
        for (int jj = 0; jj < n / tile_size; jj++)
            for (int ii = 0; ii < n / tile_size; ii++) {

                for (int j = jj * tile_size; j < (jj + 1) * tile_size; j++)
                    for (int i = ii * tile_size; i < (ii + 1) * tile_size; i++) {
                        int x = j;
                        int y = i;
                        unsigned char color[3];
                        if (isprime(ulam_get_map(x, y, n))) {
                            color[0] = 0;
                            color[1] = 0;
                            color[2] = 0;
                        } else {
                            color[0] = color1;
                            color[1] = color2;
                            color[2] = color3;
                        }

                        colorArray[x][y][0] = color[0];
                        colorArray[x][y][1] = color[1];
                        colorArray[x][y][2] = color[2];
                    }
            }
    }

    double end_time = omp_get_wtime();
    auto duration = end_time - start_time;
    std::cout << "\nTask completed in: " << duration << " s" << std::endl;

    /*create new file,give it a name and open it in binary mode  */
    fp= fopen(filename,"wb"); /* b -  binary mode */
    /*write ASCII header to the file*/
    fprintf(fp, "P6\n%s\n%d\n%d\n%d\n", comment, n * 3, n * 3, MaxColorComponentValue);

    for (int y = 0; y < n; y++) {
        for (int dy = 0; dy < 3; dy++) {
            for (int x = 0; x < n; x++) {
                for (int dx = 0; dx < 3; dx++) {
                    fwrite(colorArray[y][x], 1, 3, fp);
                }
            }
        }
    }

    fclose(fp);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            delete[] colorArray[i][j];
        }
        delete[] colorArray[i];
    }
    delete[] colorArray;

    return 0;
}
