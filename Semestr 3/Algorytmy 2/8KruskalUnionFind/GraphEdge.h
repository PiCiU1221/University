#pragma once

#include <utility>

class GraphEdge {
public:
	GraphEdge();
	GraphEdge(int first, int second, double weight);

	int getFirst();
	int getSecond();
	double getWeight();

private:
	std::pair<int, int> vertices;
	double weight;
};
