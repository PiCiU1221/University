#pragma once

#include <ostream>

class Point {
	double x, y;
	int index;

public:

	Point() : x(0.0), y(0.0), index(0) {}

	Point(double x, double y, int index) {
		this->x = x;
		this->y = y;
		this->index = index;
	}

	double getX() { return x; }
	double getY() { return y; }
	int getIndex() { return index; }

	void setX(double x) { this->x = x; }
	void setY(double y) { this->y = y; }
	void setIndex(int index) { this->index = index; }

	// Return true if the second point is on the left or equal
	bool operator>(const Point& second) const {
		return ((y * second.x) - (second.y * x)) >= 0;
	}

	friend std::ostream& operator<<(std::ostream& os, const Point& point) {
		os << point.x << " " << point.y << std::endl;
		return os;
	}
};
