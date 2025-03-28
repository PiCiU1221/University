#include <iostream>
#include <vector>
#include <fstream>
#include <tbb/blocked_range.h>
#include <tbb/blocked_range2d.h>
#include <tbb/parallel_for.h>
#include <cmath>

using namespace std;
using namespace tbb;

struct Color {
    unsigned char r, g, b;
};

void readPPM(const string& filename, vector<vector<Color>>& image) {
    ifstream file(filename, ios::binary);

    string format;
    file >> format;

    int width, height;
    file >> width >> height;
    int maxColorValue;
    file >> maxColorValue;

    file.ignore(1);

    image.resize(height, vector<Color>(width));

    for (int y = 0; y < height; ++y) {
        file.read(reinterpret_cast<char*>(image[y].data()), width * 3);
    }

    file.close();
}

void applyKuwaharaFilter(const vector<vector<Color>>& inputImage, vector<vector<Color>>& outputImage, int kernelRadius = 2) {
    int height = inputImage.size();
    int width = inputImage[0].size();

    outputImage.resize(height, vector<Color>(width));

    parallel_for(blocked_range2d<int>(kernelRadius, height - kernelRadius, kernelRadius, width - kernelRadius), [&](const blocked_range2d<int>& r) {
        for (int y = r.rows().begin(); y != r.rows().end(); ++y) {
            for (int x = r.cols().begin(); x != r.cols().end(); ++x) {
                array<double, 4> meanR = {0.0, 0.0, 0.0, 0.0};
                array<double, 4> meanG = {0.0, 0.0, 0.0, 0.0};
                array<double, 4> meanB = {0.0, 0.0, 0.0, 0.0};
                array<double, 4> variance = {0.0, 0.0, 0.0, 0.0};
                array<int, 4> counts = {0, 0, 0, 0};

                parallel_for(blocked_range<int>(-kernelRadius, kernelRadius + 1), [&](const blocked_range<int>& range) {
                    for (int ky = range.begin(); ky != range.end(); ++ky) {
                        for (int kx = -kernelRadius; kx <= kernelRadius; ++kx) {
                            int subregion = (ky <= 0 ? 0 : 1) * 2 + (kx <= 0 ? 0 : 1);
                            const Color& neighbor = inputImage[y + ky][x + kx];

                            meanR[subregion] += neighbor.r;
                            meanG[subregion] += neighbor.g;
                            meanB[subregion] += neighbor.b;
                            counts[subregion]++;
                        }
                    }
                });

                for (int i = 0; i < 4; ++i) {
                    if (counts[i] > 0) {
                        meanR[i] /= counts[i];
                        meanG[i] /= counts[i];
                        meanB[i] /= counts[i];
                    }
                }

                parallel_for(blocked_range<int>(-kernelRadius, kernelRadius + 1), [&](const blocked_range<int>& range) {
                    for (int ky = range.begin(); ky != range.end(); ++ky) {
                        for (int kx = -kernelRadius; kx <= kernelRadius; ++kx) {
                            int subregion = (ky <= 0 ? 0 : 1) * 2 + (kx <= 0 ? 0 : 1);
                            const Color& neighbor = inputImage[y + ky][x + kx];

                            variance[subregion] += pow(neighbor.r - meanR[subregion], 2) +
                                                   pow(neighbor.g - meanG[subregion], 2) +
                                                   pow(neighbor.b - meanB[subregion], 2);
                        }
                    }
                });

                int bestRegion = 0;
                for (int i = 1; i < 4; ++i) {
                    if (variance[i] < variance[bestRegion]) {
                        bestRegion = i;
                    }
                }

                outputImage[y][x] = { static_cast<unsigned char>(min(255.0, max(0.0, meanR[bestRegion]))),
                                      static_cast<unsigned char>(min(255.0, max(0.0, meanG[bestRegion]))),
                                      static_cast<unsigned char>(min(255.0, max(0.0, meanB[bestRegion]))) };
            }
        }
    });
}

void writePPM(const string& filename, const vector<vector<Color>>& image) {
    ofstream file(filename, ios::binary);

    int width = image[0].size();
    int height = image.size();
    file << "P6\n" << width << " " << height << "\n255\n";

    for (const auto& row : image) {
        for (const auto& pixel : row) {
            file.write(reinterpret_cast<const char*>(&pixel), 3);
        }
    }

    file.close();
}

int main() {
    vector<vector<Color>> inputImage, outputImage;

    string filename = "image.ppm";
    string outputFilename = "output.ppm";

    readPPM(filename, inputImage);

    applyKuwaharaFilter(inputImage, outputImage);

    writePPM(outputFilename, outputImage);

    return 0;
}
