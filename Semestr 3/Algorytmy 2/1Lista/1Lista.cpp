/*
	Algorytmy 2
	Laboratorium: lista

	Piotr Pietrusewicz 53828 gr. 220A
*/

#include "LinkedList.h"

#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

// Example object for the linked list
class SomeObject {
public:
	SomeObject(int field_1, char field_2) : field_1(field_1), field_2(field_2) {};

	friend ostream& operator<<(ostream& os, const SomeObject& obj) {
		os << obj.field_1 << " | " << obj.field_2 << endl;
		return os;
	}

	int field_1;
	char field_2;
};

// Custom comparator for the linked list data
int data_cmp(SomeObject so1, SomeObject so2) {
	// Returns 0 if equal, 0 < when the node has a higher value than the searched one, 0 > when the node has smaller value
	return so1.field_1 - so2.field_1;
}

// Function to generate random content
void generateRandomContent(LinkedList<SomeObject>* list, int numberOfRandomObjects) {
	// Seed for the randomization
	unsigned int seed = 123;

	default_random_engine randomEngine(seed);
	uniform_int_distribution<int> intDistribution(1, 10000);
	uniform_int_distribution<int> charDistribution('a', 'z');

	for (int i = 0; i < numberOfRandomObjects; i++) {
		int randomInt = intDistribution(randomEngine);
		char randomChar = charDistribution(randomEngine);

		SomeObject newObject(randomInt, randomChar);
		//list->addWithCmp(newObject, data_cmp);
		list->addBack(newObject);
	}
}

// Function that runs tests
void runTest() {
	const int MAX_ORDER = 6;

	LinkedList<SomeObject>* testList = new LinkedList<SomeObject>();

	unsigned int seed = 123;

	default_random_engine randomEngine(seed);
	uniform_int_distribution<int> intDistribution(1, 10000);
	uniform_int_distribution<int> charDistribution('a', 'z');

	for (int o = 1; o <= MAX_ORDER; o++) {
		const double n = pow(10, o);

		auto totalStartTime = chrono::high_resolution_clock::now();

		for (int i = 0; i < n; i++) {
			int randomInt = intDistribution(randomEngine);
			char randomChar = charDistribution(randomEngine);
			SomeObject newObject(randomInt, randomChar);
			testList->addBack(newObject);
		}

		auto totalEndTime = chrono::high_resolution_clock::now();
		auto totalDuration = chrono::duration_cast<chrono::milliseconds>(totalEndTime - totalStartTime).count();

		double averageTime = static_cast<double>(totalDuration) / n;

		cout << "Added " << n << " elements in " << totalDuration << " ms, ";
		cout << "Average time: " << averageTime << " ms" << endl;

		const double m = pow(10, 4);

		totalStartTime = chrono::high_resolution_clock::now();

		for (int i = 0; i < m; i++) {
			int randomInt = intDistribution(randomEngine);
			char randomChar = charDistribution(randomEngine);
			SomeObject searchObject(randomInt, randomChar);
			testList->findAndDelete(searchObject, data_cmp);
		}

		cout << "Size now: " << testList->size << endl;

		totalEndTime = chrono::high_resolution_clock::now();
		totalDuration = chrono::duration_cast<chrono::milliseconds>(totalEndTime - totalStartTime).count();

		averageTime = static_cast<double>(totalDuration) / m;

		cout << "Searched/removed " << m << " elements in " << totalDuration << " ms, ";
		cout << "Average time: " << averageTime << " ms" << endl << endl;

		cout << testList->to_string(false) << endl;

		testList->deleteAll(true);
	}

	testList = nullptr;
}

int main()
{
	LinkedList<SomeObject>* list = new LinkedList<SomeObject>();

	// Call the function that generates random objects
	//generateRandomContent(list, 1000);

	// Some test lines

	/*
	SomeObject myObj1{ 1, 'a' };
	SomeObject myObj2{ 2, 'b' };
	SomeObject myObj3{ 3, 'c' };
	SomeObject myObj4{ 4, 'd' };
	SomeObject myObj5{ 5, 'e' };

	list->addBack(myObj1);
	list->addBack(myObj2);
	list->addBack(myObj3);
	list->addBack(myObj4);
	list->addBack(myObj5);

	//cout << list->get(0);
	cout << (*list)[0];
	cout << (*list)[1];
	cout << (*list)[2];
	cout << (*list)[3];
	cout << (*list)[4] << endl;
	*/

	// (a)
	//SomeObject myObj1{ 1, 'a' };
	//list->addBack(myObj1);

	// (b)
	//SomeObject myObj2{ 2, 'b' };
	//list->addBack(myObj2);

	// (c)
	//list->deleteLast();

	// (d)
	//list->deleteFirst();

	// (e)
	//SomeObject something =  list->get(3);

	// (f)
	/*
	SomeObject myObj3{ 3, 'c' };
	bool result = list->set(2, myObj3);
	cout << result << endl;
	*/

	// (e) and (f) using overloaded [] operator
	//SomeObject myObj4{ 4, 'd' };
	//(*list)[1] = myObj4;

	// (g)
	//int result1 = list->search(SomeObject(3, ' '), data_cmp);
	//cout << list->get(result) << endl;

	// (h)
	//bool result2 = list->findAndDelete(SomeObject(3, ' '), data_cmp);
	//cout << result2 << endl;

	// (i)
	//bool result3 = list->addWithCmp(SomeObject(3, 'z'), data_cmp);
	//cout << result3 << endl;

	// (j)
	//list->deleteAll(true);

	// (k)
	//string listDisplay = list->to_string(false);
	//cout << listDisplay;

	// Time tests
	runTest();
}