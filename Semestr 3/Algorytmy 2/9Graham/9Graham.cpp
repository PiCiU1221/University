#include "GrahamAlgorithm.h"

#include <iostream>
#include <string>

using namespace std;

void selectedFileDrawingDataDisplay() {
	// Choose the desired dataset
	//string filename = "points1.txt";
	string filename = "points2.txt";
	//string filename = "points3.txt";
	//string filename = "points4.txt";
	//string filename = "points5.txt";

	ostringstream outputDraw;

	LinkedList<Point>* convexHull = GrahamAlgorithm::grahamScan(filename, outputDraw, true);

	string listDisplay = convexHull->to_string(true);

	// Display for the python code
	cout << outputDraw.str();
	cout << listDisplay;
}

void experiments() {
	ostringstream output;

	string filename1 = "points1.txt";
	string filename2 = "points2.txt";
	string filename3 = "points3.txt";
	string filename4 = "points4.txt";
	string filename5 = "points5.txt";

	LinkedList<Point>* convexHull1 = GrahamAlgorithm::grahamScan(filename1, output);
	LinkedList<Point>* convexHull2 = GrahamAlgorithm::grahamScan(filename2, output);
	LinkedList<Point>* convexHull3 = GrahamAlgorithm::grahamScan(filename3, output);
	LinkedList<Point>* convexHull4 = GrahamAlgorithm::grahamScan(filename4, output);
	LinkedList<Point>* convexHull5 = GrahamAlgorithm::grahamScan(filename5, output);

	cout << output.str();
}

int main()
{
	selectedFileDrawingDataDisplay();
	//experiments();

	return 0;
}