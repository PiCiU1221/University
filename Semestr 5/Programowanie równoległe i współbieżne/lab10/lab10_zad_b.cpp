#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <tbb/tbb.h>
#include <tbb/parallel_for.h>
#include <chrono>

using namespace std;
using namespace tbb;

const double CxMin = -2.5;
const double CxMax = 1.5;
const double CyMin = -2.0;
const double CyMax = 2.0;

const int IterationMax = 200;
const double EscapeRadius = 2.0;
double ER2 = EscapeRadius * EscapeRadius;

int iXmax;
int iYmax;

vector<vector<vector<unsigned char>>> colorArray;

int main(int argc, char* argv[])
{
    int num_threads = std::stoi(argv[1]);
    int image_size = std::stoi(argv[2]);

    iXmax = image_size;
    iYmax = image_size;

    double PixelWidth = (CxMax - CxMin) / iXmax;
    double PixelHeight = (CyMax - CyMin) / iYmax;

    colorArray.resize(iYmax, vector<vector<unsigned char>>(iXmax, vector<unsigned char>(3)));

	vector<int> iteration_counts(num_threads, 0);

	// uzywam areny do kontrolowania ilosci watkow
    task_arena arena(num_threads);
    
	auto start_time = chrono::high_resolution_clock::now();

	arena.execute([&] {
		parallel_for(blocked_range2d<int>(0, iYmax, 0, iXmax), [&](const blocked_range2d<int>& r) {
			for (int iY = r.rows().begin(); iY < r.rows().end(); ++iY) {
				double Cy = CyMin + iY * PixelHeight;
				if (std::fabs(Cy) < PixelHeight / 2) Cy = 0.0; // Main antenna

				for (int iX = r.cols().begin(); iX < r.cols().end(); ++iX) {
					double Cx = CxMin + iX * PixelWidth;
					double Zx = 0.0, Zy = 0.0, Zx2 = Zx * Zx, Zy2 = Zy * Zy;
					int Iteration;

					for (Iteration = 0; Iteration < IterationMax && (Zx2 + Zy2 < ER2); ++Iteration) {
						Zy = 2 * Zx * Zy + Cy;
						Zx = Zx2 - Zy2 + Cx;
						Zx2 = Zx * Zx;
						Zy2 = Zy * Zy;
					}
					
					int thread_id = this_task_arena::current_thread_index();
                    iteration_counts[thread_id] += Iteration;

					unsigned char color[3];
					if (Iteration == IterationMax) {
						color[0] = 0;
						color[1] = 0;
						color[2] = 0;
					} else {
						int uniqueThreadColor = 100 / num_threads * this_task_arena::current_thread_index() + 50;
						color[0] = uniqueThreadColor;
						color[1] = 128;
						color[2] = 0;
					}

					colorArray[iY][iX][0] = color[0];
					colorArray[iY][iX][1] = color[1];
					colorArray[iY][iX][2] = color[2];
				}
			}
		}, auto_partitioner());
    });

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end_time - start_time;
    cout << "\nTask completed in: " << duration.count() << " seconds" << std::endl;

	cout << "\nIteration counts per thread:" << std::endl;
    for (int i = 0; i < num_threads; ++i) {
        cout << "Thread " << i << ": " << iteration_counts[i] << " iterations" << std::endl;
    }

    const int MaxColorComponentValue = 255;
    std::ofstream file("mandelbrot_tbb.ppm", std::ios::binary);
    file << "P6\n" << iXmax << " " << iYmax << "\n" << MaxColorComponentValue << "\n";
    for (int y = 0; y < iYmax; ++y) {
        for (int x = 0; x < iXmax; ++x) {
            file.write(reinterpret_cast<const char*>(colorArray[y][x].data()), 3);
        }
    }
    file.close();

    return 0;
}
