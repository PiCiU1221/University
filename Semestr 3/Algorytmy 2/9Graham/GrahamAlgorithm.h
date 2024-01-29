#pragma once

#include "Point.h"
#include "LinkedList.h"
#include "BinaryHeap.h"
#include "DataUtils.h"

#include <chrono>

class GrahamAlgorithm {
private:
	static int dataCmp(Point first, Point second) {
		if (((first.getY() * second.getX()) - (second.getY() * first.getX())) >= 0) return 1;
		return -1;
	}

	static int findDataCmp(Point first, Point second) {
		if (first.getX() == second.getX() && first.getY() == second.getY()) return 0;
		return -1;
	}

public:
	static LinkedList<Point>* grahamScan(std::string filename, std::ostream& output, bool drawing = false) {
		Point* pointsInput;
		int pointCount;

		DataUtils::readDataFromFile(filename, pointsInput, pointCount);

		auto mainStart = std::chrono::high_resolution_clock::now();

		// Copy of the original points array and search of point with min y value
		Point* points = new Point[pointCount - 1];

		int startingPointIndex = 0;

		for (int i = 0; i < pointCount; i++) {
			if (pointsInput[i].getY() < pointsInput[startingPointIndex].getY()) {
				startingPointIndex = i;
			}
			else if (pointsInput[i].getY() == pointsInput[startingPointIndex].getY()) {
				if (pointsInput[i].getX() < pointsInput[startingPointIndex].getX()) {
					startingPointIndex = i;
				}
			}
		}

		Point startingPoint = pointsInput[startingPointIndex];

		// Create an array of points without the starting point
		int j = 0;

		for (int i = 0; i < pointCount; i++) {
			if (i != startingPointIndex) {
				points[j] = pointsInput[i];
				j++;
			}
		}

		if (drawing) {
			output << startingPoint.getX() << " " << startingPoint.getY() << std::endl << std::endl;

			output << pointCount << std::endl;
			for (int i = 0; i < pointCount - 1; i++) {
				output << points[i].getX() << " " << points[i].getY() << std::endl;
			}

			output << "\n";
		}

		// Change points coordinates to fit the new starting point
		for (int i = 0; i < pointCount - 1; i++) {
			points[i].setX(points[i].getX() - startingPoint.getX());
			points[i].setY(points[i].getY() - startingPoint.getY());
		}

		// Create DynamicArray with points array content, because BinaryHeap doesn't accept normal array
		DynamicArray<Point>* dynamicArray = new DynamicArray<Point>(pointCount - 1);
		for (int i = 0; i < pointCount - 1; i++) {
			(*dynamicArray).add(points[i]);
		}

		auto sortStart = std::chrono::high_resolution_clock::now();

		BinaryHeap<Point>* bh = new BinaryHeap<Point>(dynamicArray, pointCount - 1, dataCmp, true);
		bh->sort(dataCmp);

		auto sortEnd = std::chrono::high_resolution_clock::now();

		// Rewrite sorted data back to points array
		for (int i = 0; i < pointCount - 1; ++i) {
			points[i] = (*dynamicArray).get(i);
		}

		delete dynamicArray;

		// Change points coordinates back to the original after sorting the array
		for (int i = 0; i < pointCount - 1; i++) {
			points[i].setX(points[i].getX() + startingPoint.getX());
			points[i].setY(points[i].getY() + startingPoint.getY());
		}

		LinkedList<Point>* convexHull = new LinkedList<Point>;
		convexHull->addBack(startingPoint);
		convexHull->addBack(points[0]);

		Point firstPoint;
		Point secondPoint;
		Point thirdPoint;

		auto mainLoopStart = std::chrono::high_resolution_clock::now();

		for (int i = 1; i < pointCount - 1; i++) {
			convexHull->addBack(points[i]);

			int size = convexHull->getSize();

			do {
				size = convexHull->getSize();

				firstPoint = convexHull->get(size - 1);
				secondPoint = convexHull->get(size - 2);
				thirdPoint = convexHull->get(size - 3);

				firstPoint.setX(firstPoint.getX() - thirdPoint.getX());
				firstPoint.setY(firstPoint.getY() - thirdPoint.getY());

				secondPoint.setX(secondPoint.getX() - thirdPoint.getX());
				secondPoint.setY(secondPoint.getY() - thirdPoint.getY());

				if (!(firstPoint > secondPoint)) {
					convexHull->findAndDelete(convexHull->get(size - 2), findDataCmp);
				}
			} while ((!(firstPoint > secondPoint)) && size > 3);
		}

		auto mainLoopEnd = std::chrono::high_resolution_clock::now();
		auto mainEnd = std::chrono::high_resolution_clock::now();

		auto sortDuration = std::chrono::duration_cast<std::chrono::milliseconds>(sortEnd - sortStart).count();
		auto mainLoopDuration = std::chrono::duration_cast<std::chrono::milliseconds>(mainLoopEnd - mainLoopStart).count();
		auto mainDuration = std::chrono::duration_cast<std::chrono::milliseconds>(mainEnd - mainStart).count();

		if (drawing) {
			output << convexHull->getSize() << std::endl;
		}

		if (!drawing) {
			output << "Filename: " << filename << std::endl;
			output << "ConvexHull pointCount: " << convexHull->getSize() << std::endl;
			output << "ConvexHull point indexes: " << "\n\n";

			for (int i = 0; i < convexHull->getSize(); i++) {
				output << convexHull->get(i).getIndex() << std::endl;
			}

			output << "\nSort time: " << sortDuration << " milliseconds" << std::endl;
			output << "Main loop time: " << mainLoopDuration << " milliseconds" << std::endl;
			output << "Main time: " << mainDuration << " milliseconds" << "\n\n";

			if (filename != "points5.txt") {
				output << "=========================================================\n\n";
			}
		}

		return convexHull;
	}
};