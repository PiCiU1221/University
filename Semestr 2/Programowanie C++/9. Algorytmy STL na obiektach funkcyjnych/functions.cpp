#include "header.h"

using namespace std;

/*
	Piotr Pietrusewicz 53828 120A
	West Pomeranian University of Technology
	Theme: Car Dealearship

	File that contains some of the functions used in the other files
*/

// Usage of overloaded operator '<<' for a 'Dealership' object
void usageOfAnOverloadedOperator(Dealership& dealership) {
	cout << "\n" << setfill('=') << setw(68) << "=\n\n";
	cout << dealership;
	cout << "\n    Press ENTER to go back to the menu\n";
	cout << "\n" << setfill('=') << setw(67) << "=\n";
	cin.ignore();
	cin.get();
}

// Writing to a file using the overloaded operator '<<' for a 'Dealership' object
void saveToAFile(Dealership& dealership) {
	std::ofstream outFile("Dealership.txt");

	// Write data to the file from the dealership object
	outFile << dealership;

	cout << "\n" << setfill('=') << setw(68) << "=\n\n";
	cout << "    Data has been saved into the 'Dealership.txt' file\n\n";
	cout << "    Press ENTER to go back to the menu\n";
	cout << "\n" << setfill('=') << setw(67) << "=\n";
	cin.ignore();
	cin.get();
}

// Reading data from a file using the overloaded operator '>>' for a 'Dealership' object
void loadDataFromAFile(Dealership& dealership) {
	std::ifstream inFile("Dealership.txt");

	// Read data from the file into the dealership object
	inFile >> dealership;

	cout << "\n" << setfill('=') << setw(68) << "=\n\n";
	cout << "    Data has been updated from the 'Dealership.txt' file\n\n";
	cout << "    Press ENTER to go back to the menu\n";
	cout << "\n" << setfill('=') << setw(67) << "=\n";
	cin.ignore();
	cin.get();
}

// Functions that handle repeated outputs to the terminal
void displayIncorrectNumberMessage() {
	cout << "\n" << setfill('=') << setw(70) << "=\n\n";
	cout << "    An incorrect number has been entered\n\n";
	cout << "    Press ENTER to go back to the menu\n";
	cout << "\n" << setfill('=') << setw(69) << "=\n";
	cin.ignore();
	cin.get();
}

void displayPressEnterToMenu() {
	cout << "\n" << setfill('=') << setw(70) << "=\n\n";
	cout << "    Press ENTER to go back to the menu\n";
	cout << "\n" << setfill('=') << setw(69) << "=\n";
	cin.ignore();
	cin.get();
}