#include "RedBlackTree.h"

#include <iostream>
#include <random>
#include <chrono>

using namespace std;

// Example object for the red black tree
class SomeObject {
public:
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
void generateRandomContent(RedBlackTree<SomeObject>* redBlackTree, double numberOfRandomObjects) {
	// Seed for the randomization
	unsigned int seed = 123;

	default_random_engine randomEngine(seed);
	uniform_int_distribution<int> intDistribution(1, 1000000);
	uniform_int_distribution<int> charDistribution('a', 'z');

	for (double i = 0; i < numberOfRandomObjects; i++) {
		int randomInt = intDistribution(randomEngine);
		char randomChar = charDistribution(randomEngine);

		SomeObject newObject(randomInt, randomChar);
		redBlackTree->add(newObject, data_cmp);
	}
}

// Function that runs tests
void runTest() {
	const int MAX_ORDER = 7;
	RedBlackTree<SomeObject>* redBlackTree = new RedBlackTree<SomeObject>();

	unsigned int seed = 123;

	default_random_engine randomEngine(seed);
	uniform_int_distribution<int> intDistribution(1, 1000000);
	uniform_int_distribution<int> charDistribution('a', 'z');

	for (int o = 1; o <= MAX_ORDER; o++) {
		const double n = pow(10, o);

		// Timing addition of data
		auto addStartTime = chrono::high_resolution_clock::now();

		// Generate random content for the tree
		generateRandomContent(redBlackTree, n);

		auto addEndTime = chrono::high_resolution_clock::now();
		auto addTotalTime = chrono::duration_cast<chrono::milliseconds>(addEndTime - addStartTime).count();
		auto addAverageTime = addTotalTime / n;

		// Measuring the height of the tree
		int treeHeight = redBlackTree->height();

		// Calculating some extra statistics as per your requirement
		double heightToSizeRatio = double(treeHeight) / n;
		double logBase2Size = log2(n);
		double heightToLogSizeRatio = double(treeHeight) / logBase2Size;

		// Searching in the tree
		const double m = pow(10, 4);  // Number of search attempts

		auto searchStartTime = chrono::high_resolution_clock::now();

		for (int i = 0; i < m; i++) {
			int randomInt = intDistribution(randomEngine);
			char randomChar = charDistribution(randomEngine);
			SomeObject randomSearchObject(randomInt, randomChar);

			RedBlackTree<SomeObject>::Node<SomeObject>* result = redBlackTree->findNode(randomSearchObject, data_cmp);
		}

		auto searchEndTime = chrono::high_resolution_clock::now();
		auto searchTotalTime = chrono::duration_cast<chrono::milliseconds>(searchEndTime - searchStartTime).count();
		double searchAvgTime = searchTotalTime / m;

		// Output statistics for this iteration
		cout << "Size: " << n << endl;
		cout << "Add time: " << addTotalTime << " milliseconds" << endl;
		cout << "Average add time: " << addAverageTime << " milliseconds" << endl << endl;

		cout << "Height: " << treeHeight << endl;
		cout << "Height to Size Ratio: " << heightToSizeRatio << endl << endl;

		cout << "Log(2) of Size: " << logBase2Size << endl;
		cout << "Height to Log(2) of Size Ratio: " << heightToLogSizeRatio << endl << endl;

		cout << "Search time: " << searchTotalTime << " milliseconds" << endl;
		cout << "Average search time: " << searchAvgTime << " milliseconds" << endl << endl;

		cout << redBlackTree->to_string(false);

		cout << "=============================================" << endl << endl;

		redBlackTree->deleteAll();
	}

	delete redBlackTree;
}

int main()
{
	/*
	RedBlackTree<SomeObject>* rbTree = new RedBlackTree<SomeObject>();

	// Inserting elements into the Red-Black Tree using the custom object and comparator
	rbTree->add(SomeObject(10, 'A'), data_cmp);
	cout << rbTree->to_string();
	rbTree->add(SomeObject(20, 'B'), data_cmp);
	cout << rbTree->to_string();
	rbTree->add(SomeObject(5, 'C'), data_cmp);
	cout << rbTree->to_string();
	rbTree->add(SomeObject(3, 'D'), data_cmp);
	cout << rbTree->to_string();
	rbTree->add(SomeObject(7, 'E'), data_cmp);
	cout << rbTree->to_string();
	rbTree->add(SomeObject(30, 'F'), data_cmp);
	cout << rbTree->to_string();

	// Finding elements in the Red-Black Tree with the custom comparator
	SomeObject valueToFind(7, 'E'); // Creating a search object
	RedBlackTree<SomeObject>::Node<SomeObject>* foundNode = rbTree->findNode(valueToFind, data_cmp);

	if (foundNode != nullptr) {
		std::cout << "Found value " << foundNode->data << " in the Red-Black Tree!" << std::endl;
	}
	else {
		std::cout << "Value not found in the Red-Black Tree." << std::endl;
	}
	*/

	RedBlackTree<SomeObject>* rbTree = new RedBlackTree<SomeObject>();

	generateRandomContent(rbTree, 25);

	cout << rbTree->to_string();

	/*
	vector<SomeObject> preOrderResult = rbTree->preOrderTraversal();

	for (int i = 0; i < preOrderResult.size(); i++) {
		cout << preOrderResult[i] << endl;
	}

	cout << endl;
	*/

	//runTest();

	return 0;
}