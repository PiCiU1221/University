#ifndef BINARYHEAP_H
#define BINARYHEAP_H
#pragma once

#include "DynamicArray.h"

template <typename T>
class BinaryHeap {
private:
	DynamicArray<T>* heapArray;
	int size;
	bool myArray = false;
	bool topDown;

	// used in (e) and (f)
	int getParent(int index) {
		return (index - 1) / 2;
	}

	// used in (e) and (f)
	void swap(int child, int parent) {
		T temp = heapArray->get(child);
		heapArray->set(child, heapArray->get(parent));
		heapArray->set(parent, temp);
	}

	// used in (f)
	int getLeftChild(int index) {
		return 2 * index + 1;
	}

	// used in (f)
	int getRightChild(int index) {
		return 2 * index + 2;
	}

	// used in (f)
	bool hasRightChild(int index) {
		int rightChildIndex = 2 * index + 2;
		if (rightChildIndex < size) {
			return true;
		}
		else {
			return false;
		}
	}

	// used in (f)
	bool hasLeftChild(int index) {
		int leftChildIndex = 2 * index + 1;

		if (leftChildIndex < size) {
			return true;
		}
		else {
			return false;
		}
	}

	// (e) przekopcowanie rekurencyjne w górê poczynaj¹c od podanego indeksu(argumenty: indeks oraz
	// informacja lub komparator definiuj¹ce klucz porz¹dkowania),

	void heapifyUp(int index, int (*data_cmp)(T, T)) {
		if (index == 0) {
			return;
		}

		int parent = getParent(index);
		if (data_cmp(heapArray->get(index), heapArray->get(parent)) >= 0) {
			swap(index, parent);
			heapifyUp(parent, data_cmp);
		}
	}

	// (f) przekopcowanie rekurencyjne w dó³ poczynaj¹c od podanego indeksu(argumenty: indeks oraz
	// informacja lub komparator definiuj¹ce klucz porz¹dkowania).

	void heapifyDown(int index, int (*data_cmp)(T, T)) {
		int largest = index;

		int leftChild = getLeftChild(index);
		int rightChild = getRightChild(index);

		// Check if left child exists and is greater than the current largest
		if (hasLeftChild(index) && data_cmp(heapArray->get(leftChild), heapArray->get(largest)) >= 0) {
			largest = leftChild;
		}

		// Check if right child exists and is greater than the current largest
		if (hasRightChild(index) && data_cmp(heapArray->get(rightChild), heapArray->get(largest)) >= 0) {
			largest = rightChild;
		}

		// If the largest element is not the current index, swap and continue heapifying
		if (largest != index) {
			swap(index, largest);
			heapifyDown(largest, data_cmp);
		}
	}

	// Function to fix heap after retrieving an external array
	void fixHeap(bool topDown, int (*data_cmp)(T, T)) {
		// Top-down method
		if (topDown) {
			for (int i = 0; i < size; i++) {
				heapifyUp(i, data_cmp);
			}
		}
		// Bottom-up method
		else {
			for (int i = (size / 2) - 1; i >= 0; i--) {
				heapifyDown(i, data_cmp);
			}
		}
	}

	// Used in the sort function
	void swapElements() {
		// Swap the first and last elements
		T temp = (*heapArray)[0];
		(*heapArray)[0] = (*heapArray)[size - 1];
		(*heapArray)[size - 1] = temp;
	}

public:
	// Constructor
	BinaryHeap() : heapArray(new DynamicArray <T>()), size(0), myArray(true) {}

	// New constructor that takes a pointer of an array and doesnt create its own one, but works on the provided one
	BinaryHeap(DynamicArray<T>* array, int arraySize, int (*data_cmp)(T, T), bool topDown) : heapArray(array), size(arraySize), topDown(topDown) {
		fixHeap(topDown, data_cmp);
	}

	// Destruktor
	~BinaryHeap() {
		if (myArray) {
			deleteAll();

			delete heapArray;
		}
	}

	// (a) dodanie nowego elementu (argumenty: dane i informacja lub komparator definiuj¹ce klucz
	// porz¹dkowania),

	void add(T value, int (*data_cmp)(T, T)) {
		heapArray->add(value);

		size++;

		heapifyUp(size - 1, data_cmp);
	}

	// (b) pobranie i usuniêcie elementu maksymalnego tj. korzenia kopca (argument: informacja lub
	// komparator definiuj¹ce klucz porz¹dkowania — potrzebne do naprawienia kopca po usuniêciu
	// korzenia; wynik: dane zwi¹zane z elementem maksymalnym lub niepowodzenie w razie pustego
	// kopca),

	T returnAndDelete(int (*data_cmp)(T, T)) {
		if (size == 0) {
			return T();
		}
		else if (size == 1) {
			size--;
			return heapArray->get(0);
		}

		T temp = heapArray->get(0);

		heapArray->set(0, heapArray->get(size - 1));

		size--;

		heapifyDown(0, data_cmp);

		return temp;
	}

	// (c) czyszczenie kopca tj. usuniêcie wszystkich elementów,

	void deleteAll() {
		size = 0;

		heapArray->deleteAll();
	}

	// (d) zwrócenie napisowej reprezentacji kopca — np. funkcja / metoda to string(...) (argumenty i format wyniku wg uznania programisty — mo¿na wykorzystaæ m.in. napis pochodz¹cy
	// z tablicy dynamicznej, któr¹ kopiec opakowuje),

	std::string to_string(bool displayAll) {
		return heapArray->to_string(displayAll);
	}

	// Heap sort function

	void sort(int (*data_cmp)(T, T)) {
		while (size > 1) {
			swapElements();

			size--;

			heapifyDown(0, data_cmp);
		}
	}
};

#endif // BINARYHEAP_H