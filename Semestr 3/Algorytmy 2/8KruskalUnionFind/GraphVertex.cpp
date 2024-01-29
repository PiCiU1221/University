#include "GraphVertex.h"

GraphVertex::GraphVertex() : x(0.0), y(0.0) {}

GraphVertex::GraphVertex(double x, double y) : x(x), y(y) {}

double GraphVertex::getX() {
	return x;
}

double GraphVertex::getY() {
	return y;
}