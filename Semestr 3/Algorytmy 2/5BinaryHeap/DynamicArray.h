#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <cmath>

template <typename T>
class DynamicArray {
private:
	int allocatedSize;
	float expansionFactor;

	T* array;

public:
	int currentSize;

	// Constructor
	DynamicArray() : array(nullptr), currentSize(0), allocatedSize(1), expansionFactor(2.0) {
		array = new T[allocatedSize];
	}

	// Destructor
	~DynamicArray() {
		delete[] array;
	}

	// (a) dodanie nowego elementu na koñcu tablicy (argument: dane),

	void add(T value) {
		// There is space available for the new element
		if (allocatedSize > currentSize) {
			array[currentSize] = value;

			currentSize++;
		}
		// No space remaining
		else {
			// Use of ceil here to round up the float value
			//int newSize = allocatedSize * std::ceil(expansionFactor);

			int newSize = static_cast<int>(allocatedSize * expansionFactor);

			T* newArray = new T[newSize];

			for (int i = 0; i < currentSize; i++) {
				newArray[i] = array[i];
			}

			newArray[currentSize] = value;

			delete[] array;
			array = newArray;

			allocatedSize = newSize;

			currentSize++;
		}
	}

	// (b) zwrócenie danych i-tego elementu tablicy (argument: indeks i ¿¹danego elementu (numeruj¹c
	// od zera); wynik: dane i - tego elementu lub niepowodzenie w razie indeksu poza zakresem),

	T get(int index) {
		if (index < 0 || index >= currentSize) {
			throw std::out_of_range("Invalid index");
		}

		return array[index];
	}

	// (c) ustawienie (podmiana) danych i-tego elementu tablicy (argument: indeks i ¿¹danego elementu
	// (numeruj¹c od zera) oraz nowe dane; wynik: pusty lub niepowodzenie w razie indeksu poza
	// zakresem),

	void set(int index, T value) {
		if (index < 0 || index >= currentSize) {
			throw std::out_of_range("Invalid index");
		}

		array[index] = value;
	}

	// (b), (c) Overloaded [] operator

	T& operator[](int index) {
		if (index < 0 || index >= currentSize) {
			throw std::out_of_range("Invalid index");
		}

		return array[index];
	}

	// (d) czyszczenie tablicy tj. usuniêcie wszystkich elementów

	void deleteAll() {
		delete[] array;
		array = new T[allocatedSize];
		currentSize = 0;
	}

	// (e) zwrócenie napisowej reprezentacji tablicy — np. funkcja / metoda to string(...) (format
	// wyniku wg uznania programisty, mo¿e zawieraæ np.aktualny rozmiar tablicy, aktualny maksymalny rozmiar
	// tablicy, wypis pewnej liczby elementów pocz¹tkowych / koñcowych, opcjonalnie
	// adres tablicy w pamiêci; argumenty: równie¿ wg uznania programisty — np.liczba elementów
	// do wypisania, wskaŸnik na funkcjê wypisuj¹c¹ pojedynczy rekord danych).

	std::string to_string(bool displayAll) {
		std::ostringstream os;

		// If true is passed as an argument display all elements
		if (displayAll == true) {
			if (currentSize == 0) {
				os << " Array is empty" << std::endl;
			}
			else {
				os << " Array display:" << std::endl;

				for (int i = 0; i < currentSize; i++) {
					os << array[i] << " ";
				}
			}
			return os.str();
		}
		// If false is passed as an argument display the first 3 and the last 3 elements if possible
		else {
			// If we have less than 7 elements just display all of them using the display all function
			if (currentSize < 7) {
				return to_string(true);
			}
			else {
				os << " Array display:" << std::endl;

				// From 1 to 3
				for (int i = 0; i < 3; i++) {
					os << array[i] << "  ";
				}

				// For better looks
				os << std::endl << "  :" << std::endl << "  :" << std::endl;

				// From currentSize-1 to currentSize-3
				for (int i = currentSize - 1; i > currentSize - 4; i--) {
					os << array[i] << "  ";
				}

				return os.str();
			}
		}
	}

	// (f) b¹belkowe posortowanie tablicy(argument: wskaŸnik na komparator lub brak argumentu
	// przy za³o¿eniu istnienia przeci¹¿onego operatora < lub >); uwaga: sortowanie ma odbywaæ siê
	// w miejscu.

	void sort(int (*data_cmp)(T, T)) {
		// If the array size is less than 2
		if (currentSize < 2) {
			return;
		}
		else {
			for (int i = 0; i < currentSize - 1; i++) {
				for (int j = 0; j < currentSize - 1 - i; j++) {
					if (data_cmp(array[j], array[j + 1]) >= 0) {
						T temp = array[j];
						array[j] = array[j + 1];
						array[j + 1] = temp;
					}
				}
			}
			return;
		}
	}
};
