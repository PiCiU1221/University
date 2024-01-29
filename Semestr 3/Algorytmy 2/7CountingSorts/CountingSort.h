#ifndef COUNTINGSORT_H
#define COUNTINGSORT_H

#include "DynamicArray.h"

void countingSortInt(DynamicArray<int>* dynamicArray, int size, int m) {
	int* counts = new int[m];

	for (int i = 0; i < m; i++) {
		counts[i] = 0;
	}

	for (int i = 0; i < size; i++) {
		counts[(*dynamicArray)[i]]++;
	}

	int k = 0;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < counts[i]; j++) {
			(*dynamicArray)[k++] = i;
		}
	}

	delete[] counts;
}

#endif // COUNTINGSORT_H