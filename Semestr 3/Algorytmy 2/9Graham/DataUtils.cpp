#include "DataUtils.h"
#include "Point.h"

#include <fstream>
#include <iostream>
#include <string>

void DataUtils::readDataFromFile(const std::string filename, Point*& points, int& pointCount) {
	std::string fullFilePath = "excercises/" + filename;
	std::ifstream file(fullFilePath.c_str());

	if (!file.is_open()) {
		std::cerr << "Error: Unable to open file." << std::endl;
		return;
	}

	// Read the number of points
	file >> pointCount;

	points = new Point[pointCount];

	for (int i = 0; i < pointCount; i++) {
		double x, y;
		file >> x >> y;
		points[i] = Point(x, y, i);
	}

	file.close();
}