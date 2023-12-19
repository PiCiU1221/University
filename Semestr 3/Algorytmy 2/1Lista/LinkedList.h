/*
	Algorytmy 2
	Laboratorium: lista

	Piotr Pietrusewicz 53828 gr. 220A
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

template <typename T>
class LinkedList {
private:
	// Nested Node class
	template <typename T>
	class Node {
	public:
		T data;
		Node* next;
		Node* prev;

		Node(T value) : data(value), next(nullptr), prev(nullptr) {}
	};

	// LinkedList private variables
	Node<T>* head;
	Node<T>* tail;
	//int size;

public:
	int size;

	// Constructor
	LinkedList() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	// Destructor
	~LinkedList() {
		deleteAll(true);
	}

	// (a*) dodanie nowego elementu na koñcu listy (argument: dane),

	void addBack(T value) {
		Node<T>* newNode = new Node<T>(value);

		// If the list is empty make this new node a head
		if (size == 0) {
			head = newNode;
			tail = newNode;
		}
		// If there is a head make this new node a tail
		else {
			newNode->prev = tail;
			tail->next = newNode;
			tail = newNode;
		}

		size++;
	}

	// (b*) dodanie nowego elementu na pocz¹tku listy (argument: dane),

	void addFront(T value) {
		Node<T>* newNode = new Node<T>(value);

		// If the list is empty make this new node a head
		if (size == 0) {
			head = newNode;
			tail = newNode;
		}
		// If there is a head make this new node a new head
		else {
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}

		size++;
	}

	// (c*) usuniêcie ostatniego elementu,

	void deleteLast() {
		// If there is nothing to delete don't do anything
		if (size == 0) {
			return;
		}
		// If there is only one node delete it
		else if (size == 1) {
			delete tail;
			head = nullptr;
			tail = nullptr;
		}
		// If there is more than one element
		else {
			Node<T>* temp = tail->prev;
			temp->next = nullptr;
			delete tail;
			tail = temp;
		}

		size--;
	}

	// (d*) usuniêcie pierwszego elementu,

	void deleteFirst() {
		// If there is nothing to delete don't do anything
		if (size == 0) {
			return;
		}
		// If there is only one node delete it
		else if (size == 1) {
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		// If there is more than one element
		else {
			Node<T>* temp = head->next;
			temp->prev = nullptr;
			delete head;
			head = temp;
		}

		size--;
	}

	// (e*) zwrócenie danych i-tego elementu listy (argument: indeks i ¿¹danego elementu (numeruj¹c od
	// zera); wynik: dane i - tego elementu lub niepowodzenie w razie indeksu poza zakresem),

	// As a function
	T get(int index) {
		// If the index is negative, or too big throw an out_of_range exception
		if (index < 0 || index >= size) {
			throw std::out_of_range("Invalid index");
		}

		Node<T>* temp = head;
		for (int i = 0; i < index; i++) {
			temp = temp->next;
		}

		return temp->data;
	}

	// (f*) ustawienie (podmiana) danych i-tego elementu listy (argumenty: indeks i ¿¹danego elementu
	// (numeruj¹c od zera) oraz nowe dane; wynik: pusty lub niepowodzenie w razie indeksu poza
	// zakresem),

	// Function returns boolean value to tell if the operation was successfull or not
	bool set(int index, T value) {
		// If the index is negative, or too big return false
		if (index < 0 || index >= size) {
			return false;
		}

		Node<T>* temp = head;
		for (int i = 0; i < index; i++) {
			temp = temp->next;
		}

		temp->data = value;

		// If we got here, everything went as expected - return true
		return true;
	}

	// (e) and (f) in a single overloaded [] operator
	// T& is used here to be able to edit the value
	T& operator[](int index) {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Invalid index");
		}

		/*
		Node<T>* temp = head;
		for (int i = 0; i < index; i++) {
			temp = temp->next;
		}

		return temp->data;
		*/

		// When the searched index is closer to the begining
		if (index <= size / 2) {
			Node<T>* temp = head;

			for (int i = 0; i < index; i++) {
				temp = temp->next;
			}

			//std::cout << " Od przodu" << std::endl;

			return temp->data;
		}
		// When the searched index is closer to the end
		else {
			Node<T>* temp = tail;

			for (int i = size - 1; i > index; i--) {
				temp = temp->prev;
			}

			//std::cout << " Od tylu" << std::endl;

			return temp->data;
		}
	}

	// (g*) wyszukanie elementu (argumenty: dane wzorcowe oraz informacja lub komparator definiuj¹ce
	// klucz wyszukiwania — szczegó³owe wskazówki dalej; wynik: wskaŸnik na odnaleziony element
	// listy lub NULL w przypadku niepowodzenia),

	int search(T value, int (*data_cmp)(T, T)) {
		Node<T>* temp = head;
		int counter = 0;

		while (temp) {
			if (data_cmp(value, temp->data) == 0) {
				return counter;
			}

			temp = temp->next;

			counter++;
		}
		return -1;
	}

	// (h*) wyszukanie i usuniêcie elementu (argumenty: jak wy¿ej; wynik: flaga logiczna sygnalizuj¹ca
	// powodzenie lub niepowodzenie),

	bool findAndDelete(T value, int (*data_cmp)(T, T)) {
		Node<T>* temp = head;

		while (temp) {
			if (data_cmp(value, temp->data) == 0) {
				// If the searched element is head
				if (temp->prev == nullptr) {
					head = temp->next;
					head->prev = nullptr;
				}
				// If the searched element is tail
				else if (temp->next == nullptr) {
					tail = temp->prev;
					tail->next = nullptr;
				}
				else {
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
				}

				delete temp;
				size--;

				// If we found this searched element and deleted it, return true
				return true;
			}

			temp = temp->next;
		}
		// If we couldnt find the element, return false
		return false;
	}

	// (i*) dodanie nowego elementu z wymuszeniem porz¹dku (argumenty: dane i informacja lub komparator definiuj¹ce klucz porz¹dkowania),

	bool addWithCmp(T value, int (*data_cmp)(T, T)) {
		Node<T>* newNode = new Node<T>(value);

		// If the list is empty
		if (head == nullptr) {
			addFront(value);

			return true;
		}
		else {
			Node<T>* temp = head;

			while (temp) {
				// Comparator returns value smaller or equal than zero, it means that the new node should be before temp
				if (data_cmp(value, temp->data) <= 0) {
					newNode->prev = temp->prev;
					newNode->next = temp;

					// If the new Node should be placed in the front
					if (!(temp->prev)) {
						addFront(value);

						return true;
					}
					// If not we do this instead
					else {
						temp->prev->next = newNode;
						temp->prev = newNode;

						return true;
					}
				}

				temp = temp->next;
			}

			// If we got here it means that its bigger than every other element on the list, we need to put it in the back
			addBack(value);

			return true;
		}
		// If we somehow got in here return false
		return false;
	}

	// (j*) czyszczenie listy tj. usuniêcie wszystkich elementów,

	void deleteAll(bool deleteObjects) {
		Node<T>* temp = head;

		while (temp) {
			Node<T>* next = temp->next;

			if (deleteObjects == true) {
				delete temp;
			}

			temp = next;
		}

		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	// (k*) zwrócenie napisowej reprezentacji listy — np.funkcja / metoda to string(...) (format wyniku wg uznania programisty, mo¿e zawieraæ np.rozmiar listy, wypis pewnej liczby elementów
	// pocz¹tkowych / koñcowych, opcjonalnie adres listy w pamiêci; argumenty: równie¿ wg uznania
	// programisty — np.liczba elementów do wypisania, wskaŸnik na funkcjê wypisuj¹c¹ pojedynczy
	// rekord / obiekt danych).

	std::string to_string(bool displayAll) {
		std::ostringstream os;

		// If true is passed as an argument display all elements
		if (displayAll == true) {
			if (size == 0) {
				os << " List is empty" << std::endl;
			}
			else {
				os << " List display:" << std::endl;

				Node<T>* temp = head;

				while (temp) {
					os << temp->data;

					temp = temp->next;
				}
			}
			return os.str();
		}
		// If false is passed as an argument display the first 3 and the last 3 elements if possible
		else {
			// If we have less than 7 elements just display all of them using the display all function
			if (size < 7) {
				return to_string(true);
			}
			else {
				os << " List display:" << std::endl;

				// From 1 to 3
				Node<T>* temp = head;
				int i = 1;

				while (i <= 3) {
					os << temp->data;

					temp = temp->next;

					i++;
				}

				// For better looks
				os << "  :" << std::endl << "  :" << std::endl << "  :" << std::endl;

				// From end to end-2
				temp = tail;
				i = 1;

				while (i <= 3) {
					os << temp->data;

					temp = temp->prev;

					i++;
				}

				return os.str();
			}
		}
	}
};

#endif // LINKEDLIST_H