#include "header.h"

using namespace std;

/*
	Piotr Pietrusewicz 53828 120A
	West Pomeranian University of Technology
	Theme: Car Dealearship

	Main file that calls every other function from the menu
*/

void menu(Dealership& dealership) {
	int choice = -1;

	do {
		// Clean the terminal screen
		system("CLS");

		cout << "    Second Term Project\n";
		cout << "    Piotr Pietrusewicz 53828 120A\n";
		cout << "    Theme: Car Dealearship\n";
		cout << "================================================================\n\n";
		cout << "  1 ] Randomize owners and listings\n";
		cout << "  2 ] Add an owner\n";
		cout << "  3 ] Remove an owner\n";
		cout << "  4 ] Display owners\n";
		cout << "  5 ] Add a new listing\n";
		cout << "  6 ] Edit a listing\n";
		cout << "  7 ] Delete a listing\n";
		cout << "  8 ] Display listings\n";
		cout << "  9 ] Search through listings\n";
		cout << " 10 ] Display amount of owners and listings\n\n";
		cout << " 11 ] Write to a file\n";
		cout << " 12 ] Write from a file\n\n";
		cout << "  0 ] Exit\n\n";

		cin.clear();
		cin >> choice;

		if (!(choice >= 0 && choice <= 12)) {
			cout << "\n========================================================\n\n";
			cout << "    An incorrect number has been entered\n\n";
			cout << "    Press ENTER to go back to the menu\n";
			cout << "\n========================================================\n";
			cin.ignore();
			cin.get();
		}
	} while (!(choice >= 0 && choice <= 12));

	switch (choice) {
	case 0:
		exit(0);
		break;
	case 1:
		generateRandomizedOwnersAndListings(dealership);
		break;
	case 2:
		addOwnerByUser(dealership);
		break;
	case 3:
		deleteOwnerByUser(dealership);
		break;
	case 4:
		displayOwners(dealership);
		break;
	case 5:
		addListingByUser(dealership);
		break;
	case 6:
		editListing(dealership);
		break;
	case 7:
		deleteUserListing(dealership);
		break;
	case 8:
		displayAllListings(dealership);
		break;
	case 9:
		searchThroughListings(dealership);
		break;
	case 10:
		usageOfAnOverloadedOperator(dealership);
		break;
	case 11:
		writingToAFile(dealership);
		break;
	case 12:
		enteringDataFromAFile(dealership);
		break;
	default:
		cout << "\n========================================================\n\n";
		cout << "    An incorrect number has been entered\n\n";
		cout << "    Press ENTER to go back to the menu\n";
		cout << "\n========================================================\n";
		cin.ignore();
		cin.get();
		break;
	}
}

int main() {
	// This enables Polish letters to be displayed in the terminal
	setlocale(LC_CTYPE, "Polish");

	// Set the seed for the randomizer to the current time to ensure different results each time the program is run
	srand((unsigned int)time(nullptr));

	// Create an object dealership of a type Dealership to use in the menu function
	Dealership dealership;

	while (true) {
		menu(dealership);
	}
}