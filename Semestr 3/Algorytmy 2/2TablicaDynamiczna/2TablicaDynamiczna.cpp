#include "DynamicArray.h"

#include <iostream>
#include <random>
#include <chrono>

using namespace std;

// Example object for the dynamic array
class SomeObject {
public:
	SomeObject() : field_1(0), field_2('a') {}

	SomeObject(int field_1, char field_2) : field_1(field_1), field_2(field_2) {};

	friend ostream& operator<<(ostream& os, const SomeObject& obj) {
		os << obj.field_1 << " | " << obj.field_2 << endl;
		return os;
	}

	int field_1;
	char field_2;
};

// Custom comparator for the dynamic array data
int data_cmp(SomeObject so1, SomeObject so2) {
	// Returns 0 if equal, 0 < when variable has a higher value, 0 > when the variable has a smaller value
	return so1.field_1 - so2.field_1;
}

// Function to generate random content
void generateRandomContent(DynamicArray<SomeObject>* array, int numberOfRandomObjects) {
	// Seed for the randomization
	unsigned int seed = 123;

	default_random_engine randomEngine(seed);
	uniform_int_distribution<int> intDistribution(1, 10000);
	uniform_int_distribution<int> charDistribution('a', 'z');

	for (int i = 0; i < numberOfRandomObjects; i++) {
		int randomInt = intDistribution(randomEngine);
		char randomChar = charDistribution(randomEngine);

		SomeObject newObject(randomInt, randomChar);
		array->add(newObject);
	}
}

// Function that runs tests
void runTest() {
	DynamicArray <SomeObject>* testArray = new DynamicArray <SomeObject>();

	unsigned int seed = 123;

	default_random_engine randomEngine(seed);
	uniform_int_distribution<int> intDistribution(1, 10000);
	uniform_int_distribution<int> charDistribution('a', 'z');

	const int order = 7; // Order of magnitude for the data size
	const double n = pow(10, order); // Size of the data

	auto t1 = chrono::high_resolution_clock::now();
	double max_time_per_element = 0.0; // Maximum observed time for adding an element

	for (int i = 0; i < n; i++) {
		int randomInt = intDistribution(randomEngine);
		char randomChar = charDistribution(randomEngine);
		SomeObject newObject(randomInt, randomChar);

		auto t1_element = chrono::high_resolution_clock::now();
		testArray->add(newObject);
		auto t2_element = chrono::high_resolution_clock::now();

		double time_per_element = chrono::duration<double, milli>(t2_element - t1_element).count();

		if (time_per_element > max_time_per_element) {
			max_time_per_element = time_per_element;
			cout << "New maximum time per element at index: " << i << " , with time: " << time_per_element << " ms" << endl;
		}
	}

	auto t2 = chrono::high_resolution_clock::now();

	// Display the array content
	cout << endl << testArray->to_string(false) << endl;

	double total_time = chrono::duration<double, milli>(t2 - t1).count();
	double amortized_time = total_time / n;

	cout << "Total time to add " << n << " elements: " << total_time << " ms" << endl;
	cout << "Amortized time per single operation: " << amortized_time << " ms" << endl;

	testArray->deleteAll();
	delete testArray;
}

int main()
{
	DynamicArray <SomeObject>* testArray2 = new DynamicArray <SomeObject>();
	generateRandomContent(testArray2, 10);

	// (a)

	//SomeObject myObj1{ 1, 'a' };
	//testArray2->add(myObj1);

	// (b)

	//cout << testArray2->get(10);

	// (c)

	//SomeObject myObj2{ 10, 'z' };
	//testArray2->set(10, myObj2);

	// (d)

	//testArray2->deleteAll();

	// (e)

	//cout << testArray2->to_string(true);

	// (f)

	//testArray2->sort(data_cmp);

	testArray2->deleteAll();
	delete testArray2;

	runTest();
}