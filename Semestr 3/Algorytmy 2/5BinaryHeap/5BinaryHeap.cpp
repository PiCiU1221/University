#include "BinaryHeap.h"

#include <iostream>
#include <random>
#include <chrono>

using namespace std;

// Example object for the red black tree
class SomeObject {
public:
	SomeObject() : field_1(0), field_2('a') {}

	SomeObject(int field_1, char field_2) : field_1(field_1), field_2(field_2) {};

	friend ostream& operator<<(ostream& os, const SomeObject& obj) {
		os << obj.field_1 << " | " << obj.field_2;
		return os;
	}

	int field_1;
	char field_2;
};

// Custom comparator for the red black tree data
int data_cmp(SomeObject so1, SomeObject so2) {
	// Returns 0 if equal, -1 when the node has a higher value than the searched one, 1 when the node has smaller value
	if (so1.field_1 < so2.field_1) return -1;
	if (so1.field_1 > so2.field_1) return 1;
	return 0;
}

// Function to generate random content
void generateRandomContent(BinaryHeap<SomeObject>* binaryHeap, double numberOfRandomObjects) {
	// Seed for the randomization
	unsigned int seed = 123;

	default_random_engine randomEngine(seed);
	uniform_int_distribution<int> intDistribution(1, 1000000);
	uniform_int_distribution<int> charDistribution('a', 'z');

	for (double i = 0; i < numberOfRandomObjects; i++) {
		int randomInt = intDistribution(randomEngine);
		char randomChar = charDistribution(randomEngine);

		SomeObject newObject(randomInt, randomChar);
		binaryHeap->add(newObject, data_cmp);
	}
}

// Function that runs tests
void runTest() {
	const int MAX_ORDER = 7;
	BinaryHeap <SomeObject>* binaryHeap = new BinaryHeap <SomeObject>();

	unsigned int seed = 123;

	default_random_engine randomEngine(seed);
	uniform_int_distribution<int> intDistribution(1, 1000000);
	uniform_int_distribution<int> charDistribution('a', 'z');

	for (int o = 1; o <= MAX_ORDER; o++) {
		const double n = pow(10, o);

		// Timing addition of data
		auto addStartTime = chrono::high_resolution_clock::now();

		// Generate random content for the tree
		generateRandomContent(binaryHeap, n);

		// Calculate adding time
		auto addEndTime = chrono::high_resolution_clock::now();
		auto addTotalTime = chrono::duration_cast<chrono::milliseconds>(addEndTime - addStartTime).count();
		auto addAverageTime = addTotalTime / n;

		cout << "Size: " << n << endl << endl;
		cout << "Add time: " << addTotalTime << " milliseconds" << endl;
		cout << "Average add time: " << addAverageTime << " milliseconds" << endl << endl;
		cout << binaryHeap->to_string(false) << endl << endl;

		// Timing returnAndDelete()
		auto returnAndDeleteStartTime = chrono::high_resolution_clock::now();

		for (int i = 0; i < n; i++) {
			SomeObject returned = binaryHeap->returnAndDelete(data_cmp);
		}

		// Calculate returnAndDelete() time
		auto returnAndDeleteEndTime = chrono::high_resolution_clock::now();
		auto returnAndDeleteTotalTime = chrono::duration_cast<chrono::milliseconds>(returnAndDeleteEndTime - returnAndDeleteStartTime).count();

		cout << "Return and delete time: " << returnAndDeleteTotalTime << " milliseconds" << endl << endl;
		cout << binaryHeap->to_string(false) << endl << endl;

		cout << "=============================================" << endl << endl;

		binaryHeap->deleteAll();
	}

	delete binaryHeap;
}

int main()
{
	/*
	BinaryHeap <SomeObject>* binaryHeap = new BinaryHeap <SomeObject>();

	binaryHeap->add(SomeObject(10, 'A'), data_cmp);
	cout << binaryHeap->to_string(true) << endl;
	binaryHeap->add(SomeObject(20, 'B'), data_cmp);
	cout << binaryHeap->to_string(true) << endl;
	binaryHeap->add(SomeObject(5, 'C'), data_cmp);
	cout << binaryHeap->to_string(true) << endl;
	binaryHeap->add(SomeObject(3, 'D'), data_cmp);
	cout << binaryHeap->to_string(true) << endl;
	binaryHeap->add(SomeObject(7, 'E'), data_cmp);
	cout << binaryHeap->to_string(true) << endl;
	binaryHeap->add(SomeObject(30, 'F'), data_cmp);
	cout << binaryHeap->to_string(true) << endl;
	*/

	runTest();
}