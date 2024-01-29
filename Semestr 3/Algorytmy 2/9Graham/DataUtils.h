#pragma once

#include "Point.h"

#include <fstream>
#include <iostream>
#include <string>

class DataUtils {
public:
	static void readDataFromFile(const std::string filename, Point*& points, int& pointCount);
};