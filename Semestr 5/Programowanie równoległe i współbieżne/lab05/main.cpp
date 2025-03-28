#include <stdio.h>
#include <math.h>
#include <iostream>
#include <omp.h>
#include <chrono>

const double CxMin=-2.5;
const double CxMax=1.5;
const double CyMin=-2.0;
const double CyMax=2.0;

const int IterationMax=200;
const double EscapeRadius=2;
double ER2=EscapeRadius*EscapeRadius;

int iXmax;
int iYmax;

unsigned char*** colorArray;

int main(int argc, char* argv[])
{
    int num_threads = atoi(argv[1]);
    int image_size = atoi(argv[2]);

    iXmax = image_size;
    iYmax = image_size;

    double PixelWidth=(CxMax-CxMin)/iXmax;
    double PixelHeight=(CyMax-CyMin)/iYmax;

    colorArray = new unsigned char **[iYmax];
    for (int i = 0; i < iYmax; ++i) {
        colorArray[i] = new unsigned char*[iXmax];
        for (int j = 0; j < iXmax; ++j) {
            colorArray[i][j] = new unsigned char[3];
        }
    }

    omp_set_num_threads(num_threads);

    const int MaxColorComponentValue=255;
    FILE * fp;
    char *filename="new1.ppm";
    char *comment="# ";/* comment should start with # */

    int iteration_counts[num_threads] = {0};

    double start_time = omp_get_wtime();

#pragma omp parallel num_threads(num_threads)
    {
        int tid = omp_get_thread_num();

#pragma omp for schedule(dynamic)
        for (int iY = 0; iY < iYmax; iY++) {
            //double thread_start_time = omp_get_wtime();

            double Cy = CyMin + iY * PixelHeight;
            if (fabs(Cy) < PixelHeight / 2) Cy = 0.0; /* Main antenna */
            for (int iX = 0; iX < iXmax; iX++) {
                double Cx = CxMin + iX * PixelWidth;
                /* initial value of orbit = critical point Z= 0 */
                double Zx = 0.0;
                double Zy = 0.0;
                double Zx2 = Zx * Zx;
                double Zy2 = Zy * Zy;

                int Iteration;

                for (Iteration = 0; Iteration < IterationMax && ((Zx2 + Zy2) < ER2); Iteration++) {
                    Zy = 2 * Zx * Zy + Cy;
                    Zx = Zx2 - Zy2 + Cx;
                    Zx2 = Zx * Zx;
                    Zy2 = Zy * Zy;
                }

                iteration_counts[tid] += Iteration;

                /* compute  pixel color (24 bit = 3 bytes) */
                unsigned char color[3];
                if (Iteration == IterationMax) { /*  interior of Mandelbrot set = black */
                    color[0] = 0;
                    color[1] = 0;
                    color[2] = 0;
                } else { /* exterior of Mandelbrot set = white */
                    int uniqueThreadColor = 100 / num_threads * tid + 50;
                    color[0] = uniqueThreadColor; /* Red*/
                    color[1] = 128; /* Green */
                    color[2] = 0; /* Blue */
                };

                colorArray[iY][iX][0] = color[0];
                colorArray[iY][iX][1] = color[1];
                colorArray[iY][iX][2] = color[2];
            }

            //double thread_end_time = omp_get_wtime();
            //auto thread_duration = thread_end_time - thread_start_time;
            //std::cout << "Thread " << tid << " completed its task in: " << thread_duration << " s" << std::endl;
        }
    }

    double end_time = omp_get_wtime();
    auto duration = end_time - start_time;
    std::cout << "\nTask completed in: " << duration << " s" << std::endl;

    std::cout << "\nIteration counts per thread:" << std::endl;
    for (int i = 0; i < num_threads; ++i) {
        std::cout << "Thread " << i << ": " << iteration_counts[i] << " iterations" << std::endl;
    }

    /*create new file,give it a name and open it in binary mode  */
    fp= fopen(filename,"wb"); /* b -  binary mode */
    /*write ASCII header to the file*/
    fprintf(fp,"P6\n %s\n %d\n %d\n %d\n",comment,iXmax,iYmax,MaxColorComponentValue);

    for (int y = 0; y < iYmax; y++) {
        for (int x = 0; x < iXmax; x++) {
            fwrite(colorArray[y][x],1,3,fp);
        }
    }

    fclose(fp);

    for (int i = 0; i < iYmax; ++i) {
        for (int j = 0; j < iXmax; ++j) {
            delete[] colorArray[i][j];
        }
        delete[] colorArray[i];
    }
    delete[] colorArray;

    return 0;
}
