#pragma once

#include "GraphVertex.h"
#include "GraphEdge.h"

#include <string>

class Graph {
public:
	// Constructor to create a graph from a file
	Graph(const std::string filename);

	// Constructor to create a graph from the MST data
	Graph(GraphVertex* verticesArray, GraphEdge* edgesArray, int vertexCount, int edgeCount);

	~Graph();

	int getVertexCount();
	int getEdgeCount();

	GraphVertex getVertex(int index);
	GraphEdge getEdge(int index);

	void displayGraph();

private:
	GraphVertex* verticesArray;
	GraphEdge* edgesArray;

	int vertexCount, edgeCount;
};