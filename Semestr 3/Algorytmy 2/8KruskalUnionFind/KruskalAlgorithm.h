#pragma once

#include "Graph.h"

class KruskalAlgorithm {
public:
	static Graph* findMST(Graph* graph, bool unionByRank, bool pathCompression, std::ostream& outputStream);

private:
	static int dataCmp(GraphEdge first, GraphEdge second);
	static double graphEdgeKeyDouble(GraphEdge edge);
};
