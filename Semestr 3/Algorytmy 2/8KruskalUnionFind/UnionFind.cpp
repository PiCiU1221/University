#include "UnionFind.h"

UnionFind::UnionFind(int n, bool unionByRank, bool pathCompression) {
	parent = new int[n];
	rank = new int[n];

	for (int i = 0; i < n; i++) {
		parent[i] = i;
		rank[i] = 0;
	}

	this->unionByRank = unionByRank;
	this->pathCompression = pathCompression;
}

UnionFind::~UnionFind() {
	delete[] parent;
	delete[] rank;
}

int UnionFind::find(int vertex) {
	findCounter++;

	int parentVertex = parent[vertex];

	if (pathCompression) {
		if (parentVertex != vertex) {
			int temp = find(parentVertex);
			if (parent[vertex] != temp) {
				parent[vertex] = temp;
			}
		}
		return parent[vertex];
	}
	else {
		if (parentVertex != vertex) {
			return find(parentVertex);
		}
		return vertex;
	}
}

bool UnionFind::unite(int firstVertex, int secondVertex) {
	int firstParent = find(firstVertex);
	int secondParent = find(secondVertex);

	if (firstParent != secondParent) {
		if (unionByRank) {
			if (rank[firstParent] < rank[secondParent]) {
				parent[firstParent] = secondParent;
			}
			else if (rank[firstParent] > rank[secondParent]) {
				parent[secondParent] = firstParent;
			}
			else {
				parent[firstParent] = secondParent;
				rank[secondParent]++;
			}
		}
		else {
			parent[firstParent] = secondParent;
		}

		return true;
	}

	return false;
}

int UnionFind::getFindCounter() {
	return findCounter;
}