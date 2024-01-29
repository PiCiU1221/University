#include "GraphEdge.h"

GraphEdge::GraphEdge() : vertices{ 0, 0 }, weight(0.0) {}

GraphEdge::GraphEdge(int first, int second, double weight) : vertices{ first, second }, weight(weight) {}

int GraphEdge::getFirst() {
	return vertices.first;
}

int GraphEdge::getSecond() {
	return vertices.second;
}

double GraphEdge::getWeight() {
	return weight;
}