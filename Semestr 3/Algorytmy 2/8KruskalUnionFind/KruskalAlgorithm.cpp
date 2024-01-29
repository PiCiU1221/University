#include "KruskalAlgorithm.h"
#include "UnionFind.h"
#include "BucketSort.h"

#include <iostream>
#include <chrono>

Graph* KruskalAlgorithm::findMST(Graph* graph, bool unionByRank, bool pathCompression, std::ostream& outputStream) {
	int vertexCount = graph->getVertexCount();
	int edgeCount = graph->getEdgeCount();

	UnionFind* unionFind = new UnionFind(vertexCount, unionByRank, pathCompression);

	GraphVertex* verticesArray = new GraphVertex[vertexCount];
	GraphEdge* edgesArray = new GraphEdge[edgeCount];

	// Copy the data from the input graph to another array
	for (int i = 0; i < vertexCount; i++) {
		verticesArray[i] = graph->getVertex(i);
	}

	for (int i = 0; i < edgeCount; i++) {
		edgesArray[i] = graph->getEdge(i);
	}

	// Sort edges array
	auto t1 = std::chrono::high_resolution_clock::now();
	bucketSort(edgesArray, edgeCount, 1.0, graphEdgeKeyDouble, dataCmp);
	auto t2 = std::chrono::high_resolution_clock::now();
	auto sortDuration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

	GraphEdge* MSTedgesArray = new GraphEdge[vertexCount - 1];

	int j = 0;
	int outer_finds = 0;
	t1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < edgeCount; i++) {
		GraphEdge edge = edgesArray[i];

		int firstVertex = edge.getFirst();
		int secondVertex = edge.getSecond();
		outer_finds += 2;
		if (unionFind->unite(firstVertex, secondVertex)) {
			MSTedgesArray[j] = edge;
			j++;
		}

		if (j == vertexCount - 1) {
			break;
		}
	}
	t2 = std::chrono::high_resolution_clock::now();
	auto mainKruskalLoopDuration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

	double weightSum = 0.0;

	for (int i = 0; i < vertexCount - 1; i++) {
		GraphEdge edge = MSTedgesArray[i];

		weightSum += edge.getWeight();
	}

	// - liczbê krawêdzi i sumê wag w wynikowym drzewie rozpinaj¹cym,
	outputStream << "Number of edges: " << vertexCount - 1 << ", sum of weigths: " << weightSum << std::endl;
	// - czas obliczeñ kroku sortuj¹cego krawêdzie,
	outputStream << "Bucket Sort Time: " << sortDuration << " milliseconds\n";
	// - czas obliczeñ g³ównej pêtli w algorytmie Kruskala,
	outputStream << "Main Kruskal Loop Time: " << mainKruskalLoopDuration << " milliseconds\n";
	// - liczbê wykonañ operacji find (nale¿y wprowadziæ odpowiedni licznik).
	outputStream << "Number of find operations: " << unionFind->getFindCounter() << std::endl;
	outputStream << "Outer finds: " << unionFind->getFindCounter() / (double)outer_finds << std::endl << std::endl;

	Graph* MST = new Graph(verticesArray, MSTedgesArray, vertexCount, vertexCount - 1);

	return MST;
}

int KruskalAlgorithm::dataCmp(GraphEdge first, GraphEdge second) {
	if (first.getWeight() > second.getWeight()) return 1;
	if (first.getWeight() < second.getWeight()) return -1;
	return 0;
}

double KruskalAlgorithm::graphEdgeKeyDouble(GraphEdge edge) {
	return edge.getWeight();
}