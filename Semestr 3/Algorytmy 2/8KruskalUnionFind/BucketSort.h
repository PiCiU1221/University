#pragma once

#include "LinkedList.h"

template <typename T>
void bucketSort(T* inputArray, int size, double m, double (*objectKey)(T), int (*dataCmp)(T, T)) {
	double w = m / size;

	LinkedList<T>* bucketArray = new LinkedList<T>[size];

	int bucketNumber = 0;

	for (int i = 0; i < size; i++) {
		T temp = inputArray[i];
		bucketNumber = static_cast<int>(floor(objectKey(temp) / w));
		bucketArray[bucketNumber].addWithCmp(temp, dataCmp);
	}

	int k = 0;

	for (int i = 0; i < size; i++) {
		LinkedList<T>& currentList = bucketArray[i];

		for (int j = 0; j < currentList.getSize(); j++) {
			T element = currentList[j];
			inputArray[k] = element;
			k++;
		}
	}

	delete[] bucketArray;
}