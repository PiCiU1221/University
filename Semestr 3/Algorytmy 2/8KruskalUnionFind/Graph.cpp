#include "Graph.h"

#include "DataUtils.h"
#include "BucketSort.h"

Graph::Graph(const std::string filename) {
	int vertexCount = 0;
	int edgeCount = 0;
	GraphVertex* verticesArray = nullptr;
	GraphEdge* edgesArray = nullptr;

	DataUtils::readDataFromFile(filename, verticesArray, edgesArray, vertexCount, edgeCount);

	this->verticesArray = verticesArray;
	this->edgesArray = edgesArray;
	this->vertexCount = vertexCount;
	this->edgeCount = edgeCount;
}

Graph::Graph(GraphVertex* verticesArray, GraphEdge* edgesArray, int vertexCount, int edgeCount) {
	this->verticesArray = verticesArray;
	this->edgesArray = edgesArray;
	this->vertexCount = vertexCount;
	this->edgeCount = edgeCount;
}

Graph::~Graph() {
	delete[] verticesArray;
	delete[] edgesArray;
}

int Graph::getVertexCount() {
	return vertexCount;
}

int Graph::getEdgeCount() {
	return edgeCount;
}

GraphVertex Graph::getVertex(int index) {
	return verticesArray[index];
}

GraphEdge Graph::getEdge(int index) {
	return edgesArray[index];
}

void Graph::displayGraph() {
	std::cout << "Vertex Count: " << vertexCount << std::endl;
	std::cout << "Edge Count: " << edgeCount << std::endl;

	std::cout << "Vertices:" << std::endl;
	for (int i = 0; i < vertexCount; ++i) {
		GraphVertex vertex = getVertex(i);
		std::cout << "Vertex " << i << ": (" << vertex.getX() << ", " << vertex.getY() << ")" << std::endl;
	}

	std::cout << "Edges:" << std::endl;
	for (int i = 0; i < edgeCount; ++i) {
		GraphEdge edge = getEdge(i);
		std::cout << "Edge " << i << ": (" << edge.getFirst() << ", " << edge.getSecond() << "), Weight: " << edge.getWeight() << std::endl;
	}
}