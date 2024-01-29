#pragma once

#include <iostream>

class UnionFind {
public:
	UnionFind(int n, bool unionByRank, bool pathCompression);

	~UnionFind();

	int find(int vertex);

	bool unite(int firstVertex, int secondVertex);

	int getFindCounter();

private:
	int* parent;
	int* rank;

	bool unionByRank, pathCompression;

	int findCounter = 0;
};