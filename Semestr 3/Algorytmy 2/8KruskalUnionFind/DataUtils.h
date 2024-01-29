#pragma once

#include "GraphVertex.h"
#include "GraphEdge.h"

#include <fstream>
#include <iostream>
#include <string>

class DataUtils {
public:
	static void readDataFromFile(const std::string filename, GraphVertex*& vertices, GraphEdge*& edges, int& vertexCount, int& edgeCount);
};