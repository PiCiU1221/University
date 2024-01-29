#include "DataUtils.h"

#include <fstream>
#include <iostream>
#include <string>

void DataUtils::readDataFromFile(const std::string filename, GraphVertex*& vertices, GraphEdge*& edges, int& vertexCount, int& edgeCount) {
	std::string fullFilePath = "excercises/" + filename;
	std::ifstream file(fullFilePath.c_str());

	if (!file.is_open()) {
		std::cerr << "Error: Unable to open file." << std::endl;
		return;
	}

	// Read the number of vertices
	file >> vertexCount;

	vertices = new GraphVertex[vertexCount];

	for (int i = 0; i < vertexCount; i++) {
		double x, y;
		file >> x >> y;
		vertices[i] = GraphVertex(x, y);
	}

	// Read the number of edges
	file >> edgeCount;

	edges = new GraphEdge[edgeCount];

	for (int i = 0; i < edgeCount; i++) {
		int first, second;
		double weight;
		file >> first >> second >> weight;
		edges[i] = GraphEdge(first, second, weight);
	}

	file.close();
}