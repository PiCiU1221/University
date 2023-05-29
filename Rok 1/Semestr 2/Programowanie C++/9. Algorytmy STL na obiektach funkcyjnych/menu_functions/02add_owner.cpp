#include "../header.h"

using namespace std;

// MENU 2
//
// Function to add a new owner from the user input using the overloaded '<<' operator from the 'Owner' class
void addOwnerByUser(Dealership& dealership) {
	cout << "\n    Enter the owners name: " << endl;

	// Creating a new owner object with randomized adress nested class properties
	Owner wlasciciel(city[generateInteger(0, 3)], street[generateInteger(0, 3)], generateInteger(1, 99));

	// Usage of the overloaded operator that was required by the assigment
	cin >> wlasciciel;

	// Adding a new owner by passing the values from the wlasciciel object with updated data from the overloaded '>>' operator
	dealership.addOwner(wlasciciel.getName(), wlasciciel.getCity(), wlasciciel.getStreet(), wlasciciel.getNumber());

	cout << "\n" << setfill('=') << setw(68) << "=\n\n";
	cout << "    Added a new owner with the name of: " << wlasciciel.getName() << "\n\n";
	cout << "    Press ENTER to go back to the menu\n";
	cout << "\n" << setfill('=') << setw(68) << "=\n\n";
	cin.ignore();
	cin.get();
}