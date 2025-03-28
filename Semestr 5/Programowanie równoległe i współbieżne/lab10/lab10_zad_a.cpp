#include <iostream>
#include <vector>
#include <fstream>
#include <tbb/blocked_range2d.h>
#include <tbb/parallel_for.h>
#include <cmath>
#include <chrono>

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

void create3DAnaglyph(const vector<vector<Color>>& inputImage, vector<vector<Color>>& outputImage, int offset = 5) {
    int height = inputImage.size();
    int width = inputImage[0].size();

    outputImage.resize(height, vector<Color>(width));

    auto start = chrono::high_resolution_clock::now();

    parallel_for(blocked_range2d<int>(0, height, 0, width), [&](const blocked_range2d<int>& r) {
		for (int y = r.rows().begin(); y < r.rows().end(); ++y) {
			for (int x = r.cols().begin(); x < r.cols().end(); ++x) {
				int leftIndex = max(0, x - offset);
				int rightIndex = min(width - 1, x + offset);

				const Color& leftPixel = inputImage[y][leftIndex];
				const Color& rightPixel = inputImage[y][rightIndex];

				outputImage[y][x] = {
					leftPixel.r,
					rightPixel.g,
					rightPixel.b
				};
			}
		}
    });

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Time taken by create3DAnaglyph: " << duration.count() << " seconds" << endl;
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

    create3DAnaglyph(inputImage, outputImage, 5);

    writePPM(outputFilename, outputImage);

    return 0;
}
