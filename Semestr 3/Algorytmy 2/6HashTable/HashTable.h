#ifndef HASHTABLE_H
#define HASHTABLE_H
#pragma once

#include "DynamicArray.h"
#include "LinkedList.h"

#include <string>

template <typename T>
class HashTable {
public:
	class Entry {
	public:
		std::string key;
		T object;

		Entry(std::string key, T object) : key(key), object(object) {}
	};

private:
	float fillingPercentage = 0.75;
	int currentSize = 0;
	int maxSize = 10;

	DynamicArray<LinkedList<Entry>>* hashArray;

	// Make key_cmp a static member function
	static int key_cmp(Entry first, Entry second) {
		return strcmp(first.key.c_str(), second.key.c_str());
	}

	// (f) obliczenie wartoœci funkcji mieszaj¹cej(argument: klucz; wynik: typu int — wiêcej szczegó³ów
	// dalej),

	int hashFunction(const std::string& key, int hashMaxSize) {
		int sum = 0;

		int keySize = static_cast<int>(key.size());

		for (int i = 0; i < keySize; i++) {
			sum = sum + (static_cast<int>(key[i]) * static_cast<int>(std::pow(31, keySize - (i + 1))));
		}

		return std::abs(sum) % hashMaxSize;
	}

	// (g) rozszerzenie i przemieszanie tablicy — tzw. operacja rehash (ta funkcja powinna byæ
	// wywo³ywana z wnêtrza funkcji dodaj¹cej nowy element).

	void rehash() {
		// New hash array size
		int newMaxSize = 2 * maxSize;

		// Create new hash array
		DynamicArray<LinkedList<Entry>>* newHashArray = new DynamicArray<LinkedList<Entry>>(newMaxSize);

		// Loop through every linked list in old hash array
		for (int i = 0; i < maxSize; i++) {
			LinkedList<Entry>& currentList = (*hashArray)[i];

			int j = 0;

			try {
				while (true) {
					auto entry = currentList.get(j);
					int newIndex = hashFunction(entry.key, newMaxSize);

					(*newHashArray)[newIndex].addBack(entry);

					j++;
				}
			}
			catch (const std::out_of_range&) {}
		}

		delete hashArray;
		hashArray = newHashArray;
		maxSize = newMaxSize;
	}

public:
	// Constructor
	HashTable() {
		hashArray = new DynamicArray<LinkedList<Entry>>(maxSize);
	}

	// Destructor
	~HashTable() {
		delete hashArray;
		hashArray = nullptr;
	}

	// (a) dodanie nowego elementu (argumenty: klucz oraz wartoœæ — czyli inaczej dane skojarzone z
	// kluczem),

	void add(const std::string& key, const T& object) {
		int index = hashFunction(key, maxSize);

		LinkedList<Entry>& currentList = (*hashArray)[index];
		int listSize = currentList.getSize();

		// Check if the key already exists in the list
		for (int j = 0; j < listSize; j++) {
			auto entry = currentList.get(j);

			if (entry.key == key) {
				// Key found, swap objects
				entry.object = object;
				return;
			}
		}

		// Key not found, add a new entry
		Entry newEntry(key, object);
		currentList.addBack(newEntry);

		currentSize++;

		// If number of elements exceeds the fillingPercentage increase the size and rehash
		if (static_cast<float>(currentSize) / maxSize > fillingPercentage) {
			rehash();
		}
	}

	// (b) wyszukanie elementu (argument: klucz; wynik: wskaŸnik na znaleziony element tj. parê (klucz,
	// wartoœæ) lub NULL w przypadku niepowodzenia),

	Entry* get(const std::string& key) {
		// Index of list on the hashArray where the searched element could be
		int index = hashFunction(key, maxSize);

		LinkedList<Entry>& currentList = (*hashArray)[index];
		int listSize = currentList.getSize();

		// Loop through every element in this list to try to find the entry
		for (int j = 0; j < listSize; j++) {
			auto& entry = currentList[j];

			// Entry with the searched key found
			if (entry.key == key) {
				// Return a pointer to the found entry
				return &entry;
			}
		}

		// Return nullptr if the key is not found
		return nullptr;
	}

	// (c) usuniêcie elementu (argument: klucz; wynik: flaga logiczna sygnalizuj¹ca powodzenie lub niepowodzenie),

	bool remove(const std::string& key) {
		// Index of the list in the hashArray where the searched element could be
		int index = hashFunction(key);

		LinkedList<Entry>& currentList = (*hashArray)[index];

		// Create an Entry object with the specified key for comparison
		Entry targetEntry(key, T{});

		// Use the findAndDelete function to remove the entry with the specified key
		bool removed = currentList.findAndDelete(targetEntry, &HashTable::key_cmp);

		// If an entry is removed, update the currentSize
		if (removed) {
			currentSize--;
		}

		// Return whether the removal was successful
		return removed;
	}

	// (d) czyszczenie tablicy mieszaj¹cej tj. usuniêcie wszystkich elementów,

	void clear() {
		// Loop through every linked list in hashArray and call the clear function
		for (int i = 0; i < maxSize; i++) {
			LinkedList<Entry>& currentList = (*hashArray)[i];

			currentList.deleteAll(true);
		}

		currentSize = 0;
	}

	// (e) zwrócenie napisowej reprezentacji tablicy mieszaj¹cej — np. funkcja / metoda to string(...)
	// (wynikowy napis powinien przedstawiaæ krótkie niepuste listy par(klucz, wartoœæ) wystêpuj¹ce
	// pod poszczególnymi indeksami tablicy),

	std::string to_string(bool displayAll) {
		std::ostringstream oss;

		oss << "hash table:" << std::endl;
		oss << "  current_size: " << currentSize << std::endl;
		oss << "  max_size: " << maxSize << std::endl;
		oss << "  table:" << std::endl;
		oss << "  {" << std::endl;

		int nonNullLists = 0;
		int listMinSize = std::numeric_limits<int>::max();
		int listMaxSize = 0;
		double totalListSize = 0.0;

		int counter = 0;

		for (int i = 0; i < maxSize; i++) {
			LinkedList<Entry>& currentList = (*hashArray)[i];

			int listSize = currentList.getSize();

			if (listSize > 0) {
				nonNullLists++;
				listMinSize = std::min(listMinSize, listSize);
				listMaxSize = std::max(listMaxSize, listSize);
				totalListSize += listSize;
			}

			if (listSize > 0 && (counter < 5 || displayAll)) {
				oss << "\t" << i << ": ";

				int j = 0;
				bool didPrintIndex = false;

				try {
					while (true) {
						auto entry = currentList.get(j);

						if (didPrintIndex == false) {
							oss << entry.key << " -> " << entry.object;
							didPrintIndex = true;
						}
						else if (didPrintIndex == true) {
							oss << ", " << entry.key << " -> " << entry.object;
						}

						j++;
					}
				}
				catch (const std::out_of_range&) {}

				oss << ";" << std::endl;

				counter++;
			}
		}

		if (!displayAll && counter >= 5) {
			oss << "\t..." << std::endl;
		}

		oss << "  }" << std::endl;
		oss << "  stats:" << std::endl;
		oss << "    list min size: " << listMinSize << std::endl;
		oss << "    list max size: " << listMaxSize << std::endl;
		oss << "    non-null lists: " << nonNullLists << std::endl;
		oss << "    list avg size: " << (nonNullLists > 0 ? (totalListSize / nonNullLists) : 0.0) << std::endl;

		return oss.str();
	}
};

#endif // HASHTABLE_H