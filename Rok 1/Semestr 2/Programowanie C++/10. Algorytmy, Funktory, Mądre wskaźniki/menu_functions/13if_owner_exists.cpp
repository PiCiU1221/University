#include "../header.h"

using namespace std;

// MENU 13
//
// Function to check if the owner with the name, that the user inputs, exists or not
void checkIfOwnerExists(Dealership& dealership) {
	cout << "Insert username to check if exists: ";
	string username;
	cin >> username;

	if (dealership.checkIfOwnerExists(username)) {
		cout << "User with the name: " << username << " exists" << endl;
	}
	else {
		cout << "User with the name: " << username << "doesn't exist" << endl;
	}

	cin.ignore();
	cin.get();
}