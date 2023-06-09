#include "../header.h"

using namespace std;

// MENU 12
//
// Function that shows the usage of an overloaded operator '<<' for a 'Dealership' object
void usageOfAnOverloadedOperator(Dealership& dealership) {
	cout << "\n" << setfill('=') << setw(68) << "=\n\n";
	cout << dealership;
	cout << "\n    Press ENTER to go back to the menu\n";
	cout << "\n" << setfill('=') << setw(67) << "=\n";
	cin.ignore();
	cin.get();
}