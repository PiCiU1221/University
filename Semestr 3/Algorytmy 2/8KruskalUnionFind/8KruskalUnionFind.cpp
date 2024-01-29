#include "DataUtils.h"

#include "Graph.h"
#include "UnionFind.h"
#include "KruskalAlgorithm.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
	// Choose the desired dataset
	//string filename = "g1.txt";
	string filename = "g2.txt";
	//string filename = "g3.txt";

	// Create a graph with the data
	Graph* graph = new Graph(filename);

	// Use std::ostringstream to capture the output as a string
	ostringstream output;

	// Parameters for the findMST function
	bool unionByRank = true;
	bool pathCompression = true;

	// Pass it into the kruskal algo function
	Graph* MST1 = KruskalAlgorithm::findMST(graph, false, false, output);
	Graph* MST2 = KruskalAlgorithm::findMST(graph, unionByRank, false, output);
	Graph* MST3 = KruskalAlgorithm::findMST(graph, false, pathCompression, output);
	Graph* MST4 = KruskalAlgorithm::findMST(graph, unionByRank, pathCompression, output);

	cout << output.str();

	// Display input graph
	//graph->displayGraph();

	// Display MST
	//MST->displayGraph();

	delete graph;
	delete MST1, MST2, MST3, MST4;

	return 0;
}