#ifndef BUCKETSORT_H
#define BUCKETSORT_H

#include "DynamicArray.h"
#include "LinkedList.h"

// Custom comparator for int
int dataCmpIntInside(int first, int second) {
	// Return 1 if the first object is bigger
	if (first > second) return 1;
	// Return -1 if the first object is bigger
	if (first < second) return -1;
	// Return 0 if the values are the same
	return 0;
}

void bucketSort(DynamicArray<int>* inputArray, int size, int m) {
	float w = static_cast<float>(m) / size;

	DynamicArray<LinkedList<int>>* bucketArray = new DynamicArray<LinkedList<int>>(size);

	int temp, bucketNumber = 0;

	for (int i = 0; i < size; i++) {
		temp = (*inputArray)[i];
		bucketNumber = static_cast<int>(floor(temp / w));
		(*bucketArray)[bucketNumber].addWithCmp(temp, dataCmpIntInside);
	}

	int k = 0;

	for (int i = 0; i < size; i++) {
		LinkedList<int>& currentList = (*bucketArray)[i];

		for (int j = 0; j < currentList.getSize(); j++) {
			int element = currentList[j];

			(*inputArray)[k] = element;
			k++;
		}
	}

	delete bucketArray;
}

template <typename T>
void bucketSort(DynamicArray<T>* inputArray, int size, double m, double (*objectKey)(T), int (*dataCmp)(T, T)) {
	double w = m / size;

	DynamicArray<LinkedList<T>>* bucketArray = new DynamicArray<LinkedList<T>>(size);

	int bucketNumber = 0;

	T temp;

	for (int i = 0; i < size; i++) {
		temp = (*inputArray)[i];
		bucketNumber = static_cast<int>(floor(objectKey(temp) / w));

		(*bucketArray)[bucketNumber].addWithCmp(temp, dataCmp);
	}

	int k = 0;

	for (int i = 0; i < size; i++) {
		LinkedList<T>& currentList = (*bucketArray)[i];

		for (int j = 0; j < currentList.getSize(); j++) {
			T element = currentList[j];

			(*inputArray)[k] = element;
			k++;
		}
	}

	delete bucketArray;
}

#endif // BUCKETSORT_H