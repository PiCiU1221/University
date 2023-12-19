#ifndef BINARYHEAP_H
#define BINARYHEAP_H
#pragma once

#include "DynamicArray.h"

template <typename T>
class BinaryHeap {
private:
	DynamicArray<T>* heapArray;
	int size;

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

	/*
	void heapifyDown(int index, int (*data_cmp)(T, T)) {
		if (hasRightChild(index)) {
			int leftChild = getLeftChild(index);
			int rightChild = getRightChild(index);

			// check if left child is bigger
			if (data_cmp(heapArray->get(leftChild), heapArray->get(rightChild)) >= 0) {
				// check if we need to swap left child with parent
				if (data_cmp(heapArray->get(leftChild), heapArray->get(index)) >= 0) {
					swap(leftChild, index);
					heapifyDown(index, data_cmp);
				}
			}
			else {
				// check if we need to swap right child with parent
				if (data_cmp(heapArray->get(rightChild), heapArray->get(index)) >= 0) {
					swap(rightChild, index);
					heapifyDown(index, data_cmp);
				}
			}
		}
		else if (hasLeftChild(index)) {
			int leftChild = getLeftChild(index);

			// check if we need to swap left child with parent
			if (data_cmp(heapArray->get(leftChild), heapArray->get(index)) >= 0) {
				swap(leftChild, index);
				heapifyDown(index, data_cmp);
			}
		}
	}
	*/

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

public:
	// Constructor
	BinaryHeap() : heapArray(new DynamicArray <T>()), size(0) {}

	// Destruktor
	~BinaryHeap() {
		deleteAll();

		delete heapArray;
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
};

#endif // BINARYHEAP_H