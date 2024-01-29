#include "DynamicArray.h"
#include "BinaryHeap.h"

#include "CountingSort.h"
#include "BucketSort.h"

#include <iostream>
#include <chrono>
#include <random>

using namespace std;

// Example object
class SomeObject {
public:
	SomeObject() : field_1(0), field_2('a') {}

	SomeObject(double field_1, char field_2) : field_1(field_1), field_2(field_2) {};

	friend ostream& operator<<(ostream& os, const SomeObject& obj) {
		os << endl << obj.field_1 << " | " << obj.field_2;
		return os;
	}

	double field_1;
	char field_2;
};

// Custom comparator
int dataCmp(SomeObject so1, SomeObject so2) {
	// Return 1 if the first object is bigger
	if (so1.field_1 > so2.field_1) return 1;
	// Return -1 if the first object is bigger
	if (so1.field_1 < so2.field_1) return -1;
	// Return 0 if the values are the same
	return 0;
}

// Custom comparator for int
int dataCmpInt(int first, int second) {
	// Return 1 if the first object is bigger
	if (first > second) return 1;
	// Return -1 if the first object is bigger
	if (first < second) return -1;
	// Return 0 if the values are the same
	return 0;
}

// Function that extracts the double key from the object
double someObjectKeyDouble(SomeObject obj) {
	return obj.field_1;
}

// Function to generate a dynamic array of SomeObject instances
DynamicArray<SomeObject>* generateSomeObjectArray(int n, double m_double) {
	DynamicArray<SomeObject>* array = new DynamicArray<SomeObject>(n);

	// Seed for the randomization
	unsigned int seed = 123;

	default_random_engine randomEngine(seed);
	uniform_real_distribution<double> doubleDistribution(0.0, 1.0);
	uniform_int_distribution<int> charDistribution('a', 'z');

	for (int i = 0; i < n; i++) {
		SomeObject* so = new SomeObject();
		so->field_1 = ((rand() << 15) + rand()) / m_double;
		so->field_2 = charDistribution(randomEngine);
		array->add(*so);
	}

	return array;
}

// Function to generate a dynamic array of integers
DynamicArray<int>* generateIntArray(int n, int m) {
	DynamicArray<int>* array = new DynamicArray<int>(n);

	// Seed for the randomization
	unsigned int seed = 123;

	default_random_engine randomEngine(seed);
	uniform_int_distribution<int> intDistribution(0, m - 1);

	for (int i = 0; i < n; i++) {
		int randomInt = intDistribution(randomEngine);
		array->add(randomInt);
	}

	return array;
}

// Function to test sorting algorithms for integers
void testFunctionInts() {
	srand(0);

	const int MAX_ORDER = 7;
	const int m = static_cast<int>(pow(10, 7));

	for (int o = 1; o <= MAX_ORDER; o++) {
		const int n = static_cast<int>(pow(10, o));
		DynamicArray<int>* array1 = generateIntArray(n, m);

		cout << "Original Array (size 10^" << o << "):\n";
		cout << array1->to_string(false) << "\n";

		DynamicArray<int>* array2 = new DynamicArray<int>(*array1);
		DynamicArray<int>* array3 = new DynamicArray<int>(*array1);

		// Sort using counting_sort
		auto t1 = chrono::high_resolution_clock::now();
		countingSortInt(array1, n, m);
		auto t2 = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
		cout << "Counting Sort Time: " << duration << " milliseconds\n";

		// Sort using binary_heap
		t1 = chrono::high_resolution_clock::now();
		BinaryHeap<int>* bh = new BinaryHeap<int>(array2, n, dataCmpInt, false);
		bh->sort(dataCmpInt);
		t2 = chrono::high_resolution_clock::now();
		duration = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
		cout << "Binary Heap Sort Time: " << duration << " milliseconds\n";

		// Sort using bucket_sort
		t1 = chrono::high_resolution_clock::now();
		bucketSort(array3, n, m);
		t2 = chrono::high_resolution_clock::now();
		duration = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
		cout << "Bucket Sort Time: " << duration << " milliseconds\n";

		// Print the sorted array
		cout << "\nSorted Array:\n";
		cout << array1->to_string(false) << "\n";

		bool areArraysEqual = true;

		for (int i = 0; i < n; i++) {
			if ((dataCmpInt((*array1)[i], (*array2)[i]) != 0) && (dataCmpInt((*array1)[i], (*array3)[i]) != 0)) {
				cout << "Sorted arrays are not the same" << "\n\n";

				areArraysEqual = false;
				break;
			}
		}

		if (areArraysEqual) {
			cout << "Sorted arrays are equal" << "\n\n";
		}

		if (o != MAX_ORDER) {
			cout << "=============================================\n\n";
		}

		delete array1;
		delete array2;
		delete array3;
	}
}

// Function to test sorting algorithms for objects
void testFunctionSomeObjects() {
	srand(0);

	const int MAX_ORDER = 7;
	const double m_double = pow(2, 30);

	for (int o = 1; o <= MAX_ORDER; o++) {
		const int n = static_cast<int>(pow(10, o));

		DynamicArray<SomeObject>* array1 = generateSomeObjectArray(n, m_double);

		cout << "Original Array (size 10^" << o << "):\n";
		cout << array1->to_string(false) << "\n";

		DynamicArray<SomeObject>* array2 = new DynamicArray<SomeObject>(*array1);

		// Sort using binary_heap
		auto t1 = chrono::high_resolution_clock::now();
		BinaryHeap<SomeObject>* bh = new BinaryHeap<SomeObject>(array1, n, dataCmp, true);
		bh->sort(dataCmp);
		auto t2 = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
		cout << "Binary Heap Sort Time: " << duration << " milliseconds\n";

		// Sort using bucket_sort
		t1 = chrono::high_resolution_clock::now();
		bucketSort(array2, n, 1.0, someObjectKeyDouble, dataCmp);
		t2 = chrono::high_resolution_clock::now();
		duration = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
		cout << "Bucket Sort Time: " << duration << " milliseconds\n";

		// Print the sorted array
		cout << "\nSorted Array:\n";
		cout << array2->to_string(false) << "\n";

		bool areArraysEqual = true;

		for (int i = 0; i < n; i++) {
			if (dataCmp((*array1)[i], (*array2)[i]) != 0) {
				cout << "Sorted arrays are not the same" << "\n\n";

				areArraysEqual = false;
				break;
			}
		}

		if (areArraysEqual) {
			cout << "Sorted arrays are equal" << "\n\n";
		}

		if (o != MAX_ORDER) {
			cout << "=============================================\n\n";
		}

		delete array1;
		delete array2;
	}
}

int main()
{
	/*
	DynamicArray<int> myArray(9);
	myArray.add(1);
	myArray.add(5);
	myArray.add(7);
	myArray.add(3);
	myArray.add(8);
	myArray.add(6);
	myArray.add(2);
	myArray.add(4);
	myArray.add(9);
	*/

	// Heap sort

	//BinaryHeap<int> myHeap(&myArray, myArray.currentSize, dataCmpInt);
	//cout << "BinaryHeap Content: " << myHeap.to_string(true) << endl;
	//myHeap.sort(data_cmp_int);
	//cout << "BinaryHeap Content: " << myHeap.to_string(true) << endl;
	//cout << myArray.to_string(true) << endl;

	// Counting sort

	//countingSortInt(&myArray, 9, 10);
	//cout << myArray.to_string(true);

	// Bucket sort

	//bucketSort(&myArray, 9, 10);
	//cout << myArray.to_string(true);

	/*
	const int n = 11;  // Adjust the size as needed
	const double m_double = static_cast<double>(1 << 30);

	DynamicArray<SomeObject>* array1 = generateSomeObjectArray(n, m_double);

	// Print the original array
	cout << "Original Array:" << endl;
	for (int i = 0; i < n; i++) {
		cout << (*array1)[i] << " ";
	}
	cout << endl;

	// Sorting using bucketSort with SomeObject
	bucketSort<SomeObject>(array1, n, 1.0, someObjectKeyDouble, dataCmp);

	// Print the sorted array
	cout << "\nSorted Array:" << endl;
	for (int i = 0; i < n; i++) {
		cout << (*array1)[i] << " ";
	}
	cout << endl;

	delete array1;
	*/

	//testFunctionInts();

	testFunctionSomeObjects();

	return 0;
}