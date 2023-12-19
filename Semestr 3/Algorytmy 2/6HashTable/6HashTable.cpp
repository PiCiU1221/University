#include "HashTable.h"

#include <iostream>
#include <string>
#include <random>
#include <chrono>

using namespace std;

// Example object for the hash table
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

// Function to generate a random key
string generateRandomKey(default_random_engine& randomEngine) {
	uniform_int_distribution<int> charDistribution('a', 'z');

	string randomKey;

	for (int j = 0; j < 6; j++) {
		randomKey += static_cast<char>(charDistribution(randomEngine));
	}

	return randomKey;
}

// Function to generate random content
void generateRandomContent(HashTable<SomeObject>* hashTable, double numberOfRandomObjects) {
	// Seed for the randomization
	unsigned int seed = 123;

	default_random_engine randomEngine(seed);
	uniform_int_distribution<int> intDistribution(100000, 999999);
	uniform_int_distribution<int> charDistribution('a', 'z');

	for (int i = 0; i < numberOfRandomObjects; i++) {
		string randomKey = generateRandomKey(randomEngine);

		int randomInt = intDistribution(randomEngine);
		char randomChar = charDistribution(randomEngine);

		SomeObject newObject(randomInt, randomChar);

		hashTable->add(randomKey, newObject);
	}
}

// Function that runs tests

void runTest() {
	const int MAX_ORDER = 7;
	HashTable<SomeObject>* hashTable = new HashTable<SomeObject>();

	unsigned int seed = 123;

	default_random_engine randomEngine(seed);

	for (int o = 1; o <= MAX_ORDER; o++) {
		const double n = pow(10, o);

		// Timing addition of data
		auto addStartTime = chrono::high_resolution_clock::now();

		// Generate random content for the hash table
		generateRandomContent(hashTable, n);

		// Calculate adding time
		auto addEndTime = chrono::high_resolution_clock::now();
		auto addTotalTime = chrono::duration_cast<chrono::milliseconds>(addEndTime - addStartTime).count();
		auto addAverageTime = addTotalTime / n;

		cout << "Add time: " << addTotalTime << " milliseconds" << endl;
		cout << "Average add time: " << addAverageTime << " milliseconds" << endl << endl;
		cout << hashTable->to_string(false) << endl << endl;

		// Searching in the hash table
		const double m = pow(10, 4);
		int hits = 0;
		auto searchStartTime = chrono::high_resolution_clock::now();

		for (int i = 0; i < m; i++) {
			string randomKey = generateRandomKey(randomEngine);

			auto entry = hashTable->get(randomKey);

			if (entry != nullptr) {
				hits++;
			}
		}

		auto searchEndTime = chrono::high_resolution_clock::now();
		auto searchTotalTime = chrono::duration_cast<chrono::milliseconds>(searchEndTime - searchStartTime).count();
		auto searchAverageTime = searchTotalTime / m;

		cout << "Search time: " << searchTotalTime << " milliseconds" << endl;
		cout << "Average search time: " << searchAverageTime << " milliseconds" << endl;
		cout << "Hits: " << hits << endl << endl;

		cout << "=============================================" << endl << endl;

		// Clear the hash table for the next iteration
		hashTable->clear();
	}

	delete hashTable;
}

/*
void runTest() {
	const int MAX_ORDER = 7;
	HashTable<int>* hashTable = new HashTable<int>();

	unsigned int seed = 123;

	default_random_engine randomEngine(seed);

	for (int o = 1; o <= MAX_ORDER; o++) {
		const double n = pow(10, o);

		// Timing addition of data
		auto addStartTime = chrono::high_resolution_clock::now();

		// Generate random content for the hash table
		for (int i = 0; i < n; i++) {
			hashTable->add(generateRandomKey(randomEngine), i);
		}

		// Calculate adding time
		auto addEndTime = chrono::high_resolution_clock::now();
		auto addTotalTime = chrono::duration_cast<chrono::milliseconds>(addEndTime - addStartTime).count();
		auto addAverageTime = addTotalTime / n;

		cout << "Add time: " << addTotalTime << " milliseconds" << endl;
		cout << "Average add time: " << addAverageTime << " milliseconds" << endl << endl;
		cout << hashTable->to_string(false) << endl << endl;

		// Searching in the hash table
		const double m = pow(10, 4);
		int hits = 0;
		auto searchStartTime = chrono::high_resolution_clock::now();

		for (int i = 0; i < m; i++) {
			string randomKey = generateRandomKey(randomEngine);

			auto entry = hashTable->get(randomKey);

			if (entry != nullptr) {
				hits++;
			}
		}

		auto searchEndTime = chrono::high_resolution_clock::now();
		auto searchTotalTime = chrono::duration_cast<chrono::milliseconds>(searchEndTime - searchStartTime).count();
		auto searchAverageTime = searchTotalTime / m;

		cout << "Search time: " << searchTotalTime << " milliseconds" << endl;
		cout << "Average search time: " << searchAverageTime << " milliseconds" << endl;
		cout << "Hits: " << hits << endl << endl;

		cout << "=============================================" << endl << endl;

		// Clear the hash table for the next iteration
		hashTable->clear();
	}

	delete hashTable;
}
*/

int main() {
	// Create a HashTable object
	//HashTable<SomeObject> hashTable;

	// (a)

	/*
	// Add some instances of SomeObject to the hash table
	hashTable.add("mudwrl", SomeObject(425811, 'a'));
	hashTable.add("fixxie", SomeObject(854961, 'b'));
	hashTable.add("cixxih", SomeObject(108209, 'c'));
	hashTable.add("dnjqyl", SomeObject(761203, 'd'));
	hashTable.add("hwmdzu", SomeObject(493654, 'e'));
	hashTable.add("kudwrw", SomeObject(273624, 'f'));
	hashTable.add("nnjqyv", SomeObject(392255, 'g'));
	hashTable.add("ludwsb", SomeObject(257412, 'h'));
	hashTable.add("nlbeqy", SomeObject(721784, 'i'));
	hashTable.add("yudwsb", SomeObject(891592, 'j'));
	*/

	// (b)

	/*
	// Test get function
	HashTable<SomeObject>::Entry* foundEntry = hashTable.get("nlbeqy");

	if (foundEntry) {
		cout << "Found entry: " << foundEntry->key << " -> " << foundEntry->object << endl;
	}
	else {
		cout << "Entry not found." << endl;
	}
	*/

	//cout << hashTable.to_string(true);

	// (c)

	/*
	// Test remove function
	bool removed = hashTable.remove("nlbeqy");
	if (removed) {
		cout << "Element removed successfully." << endl;
	}
	else {
		cout << "Element not found." << endl;
	}
	*/

	// (e)

	// Display the contents of the hash table
	//cout << hashTable.to_string(true);

	// (d)

	// Clear the hash table
	//hashTable.clear();

	// Display the contents after clearing
	//cout << "After clearing:" << endl;
	//cout << hashTable.to_string(true);

	runTest();

	return 0;
}