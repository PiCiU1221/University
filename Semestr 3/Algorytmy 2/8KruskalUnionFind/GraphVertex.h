#pragma once

class GraphVertex {
public:
	GraphVertex();
	GraphVertex(double x, double y);

	double getX();
	double getY();

private:
	double x, y;
};