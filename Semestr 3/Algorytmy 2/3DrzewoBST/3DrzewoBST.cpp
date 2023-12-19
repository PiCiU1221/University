#include "BinarySearchTree.h"

#include <iostream>
#include <random>
#include <chrono>

using namespace std;

// Example object for the binary search tree
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

// Custom comparator for the binary search tree data
int data_cmp(SomeObject so1, SomeObject so2) {
	// Returns 0 if equal, 0 < when the node has a higher value than the searched one, 0 > when the node has smaller value
	return so1.field_1 - so2.field_1;
}

// Function to generate random content
void generateRandomContent(BinarySearchTree<SomeObject>* binarySearchTree, double numberOfRandomObjects) {
	// Seed for the randomization
	unsigned int seed = 123;

	default_random_engine randomEngine(seed);
	uniform_int_distribution<int> intDistribution(1, 10000000);
	uniform_int_distribution<int> charDistribution('a', 'z');

	for (double i = 0; i < numberOfRandomObjects; i++) {
		int randomInt = intDistribution(randomEngine);
		char randomChar = charDistribution(randomEngine);

		SomeObject newObject(randomInt, randomChar);
		binarySearchTree->add(newObject, data_cmp);
	}
}

// Function that runs tests
void runTest() {
	const int MAX_ORDER = 7;
	BinarySearchTree<SomeObject>* binarySearchTree = new BinarySearchTree<SomeObject>();

	unsigned int seed = 123;

	default_random_engine randomEngine(seed);
	uniform_int_distribution<int> intDistribution(1, 10000);
	uniform_int_distribution<int> charDistribution('a', 'z');

	for (int o = 1; o <= MAX_ORDER; o++) {
		const double n = pow(10, o);

		// Timing addition of data
		auto addStartTime = chrono::high_resolution_clock::now();

		// Generate random content for the tree
		generateRandomContent(binarySearchTree, n);

		auto addEndTime = chrono::high_resolution_clock::now();
		auto addTotalTime = chrono::duration_cast<chrono::milliseconds>(addEndTime - addStartTime).count();
		auto addAverageTime = addTotalTime / n;

		// Measuring the height of the tree
		int treeHeight = binarySearchTree->height();

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

			BinarySearchTree<SomeObject>::Node<SomeObject>* result = binarySearchTree->findNode(randomSearchObject, data_cmp);
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

		cout << binarySearchTree->to_string(false);

		cout << "=============================================" << endl << endl;

		binarySearchTree->deleteAll();
	}

	delete binarySearchTree;
}

int main() {
	BinarySearchTree<SomeObject>* binarySearchTree = new BinarySearchTree<SomeObject>();

	// (a)

	/*
	SomeObject someObject1(1, 'A');
	SomeObject someObject2(2, 'B');
	SomeObject someObject3(3, 'C');
	SomeObject someObject4(4, 'D');
	SomeObject someObject5(5, 'E');

	binarySearchTree->add(someObject1, data_cmp);
	binarySearchTree->add(someObject2, data_cmp);
	binarySearchTree->add(someObject3, data_cmp);
	binarySearchTree->add(someObject4, data_cmp);
	binarySearchTree->add(someObject5, data_cmp);
	*/

	SomeObject obj0(10, ' ');
	SomeObject obj1(5, ' ');
	SomeObject obj2(-2, ' ');
	SomeObject obj3(7, ' ');
	SomeObject obj4(15, ' ');
	SomeObject obj5(12, ' ');
	SomeObject obj6(30, ' ');
	SomeObject obj7(25, ' ');
	SomeObject obj8(35, ' ');
	SomeObject obj9(33, ' ');
	SomeObject obj10(11, ' ');
	SomeObject obj11(24, ' ');

	binarySearchTree->add(obj0, data_cmp);
	binarySearchTree->add(obj1, data_cmp);
	binarySearchTree->add(obj2, data_cmp);
	binarySearchTree->add(obj3, data_cmp);
	binarySearchTree->add(obj4, data_cmp);
	binarySearchTree->add(obj5, data_cmp);
	binarySearchTree->add(obj6, data_cmp);
	binarySearchTree->add(obj7, data_cmp);
	binarySearchTree->add(obj8, data_cmp);
	binarySearchTree->add(obj9, data_cmp);
	binarySearchTree->add(obj10, data_cmp);
	binarySearchTree->add(obj11, data_cmp);

	// (b)

	/*
	BinarySearchTree<SomeObject>::Node<SomeObject>* foundNode = binarySearchTree->findNode(obj4, data_cmp);
	BinarySearchTree<SomeObject>::Node<SomeObject>* foundNode2 = binarySearchTree->findNode(obj8, data_cmp);
	BinarySearchTree<SomeObject>::Node<SomeObject>* foundNode3 = binarySearchTree->findNode(obj6, data_cmp);
	*/

	/*
	if (foundNode != nullptr) {
		cout << "Found node data: " << foundNode->data << endl << endl;
	}
	else {
		cout << "Node is not in the tree" << endl << endl;
	}
	*/

	// (c)

	//binarySearchTree.deleteNode(foundNode, data_cmp);
	//binarySearchTree.deleteNode(foundNode2, data_cmp);
	//binarySearchTree.deleteNode(foundNode3, data_cmp);

	// (d)

	/*
	vector<SomeObject> preOrderResult = binarySearchTree->preOrderTraversal();

	for (int i = 0; i < preOrderResult.size(); i++) {
		cout << preOrderResult[i] << endl;
	}

	cout << endl;
	*/

	// (e)

	/*
	vector<SomeObject> inOrderResult = binarySearchTree->inOrderTraversal();

	for (int i = 0; i < inOrderResult.size(); i++) {
		cout << inOrderResult[i] << endl;
	}

	cout << endl;
	*/

	// (f)

	//binarySearchTree->deleteAll();

	// (g)

	//cout << "Tree height: " << binarySearchTree->height() << endl;

	// (h)

	/*
	generateRandomContent(binarySearchTree, 50);

	string treeDisplay = binarySearchTree->to_string(true);
	cout << treeDisplay;

	delete binarySearchTree;
	*/

	runTest();
}