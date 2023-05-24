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
		// Line of 68 '=' characters to make it look better
		cout << setfill('=') << setw(68) << "=\n\n";
		if (dealership.getChosenVehicleType() == CAR) {
			cout << "  1 ] Randomize owners and listings                _.-.___|__\n";
			cout << "  2 ] Add an owner                                |  _      _`-.\n";
			cout << "  3 ] Remove an owner                             '-(_)----(_)--`\n";
		}
		else if (dealership.getChosenVehicleType() == MOTORCYCLE) {
			cout << "  1 ] Randomize owners and listings                    ,\n";
			cout << "  2 ] Add an owner                                  .-/c-.,::\n";
			cout << "  3 ] Remove an owner                               (_)'==(_)\n";
		}
		cout << "  4 ] Display owners\n";
		cout << "  5 ] Add a new listing                        99 ] Change current\n";
		cout << "  6 ] Edit a listing                                vehicle type\n";
		cout << "  7 ] Delete a listing\n";
		cout << "  8 ] Display listings\n";
		cout << "  9 ] Search through listings\n";
		cout << " 10 ] Confirm sale\n";
		cout << " 11 ] Display amount of owners and listings\n\n";
		cout << " 12 ] Save to a file\n";
		cout << " 13 ] Load from a file\n\n";
		cout << "  0 ] Exit\n\n";

		cin.clear();
		cin >> choice;

		if (!(choice >= 0 && (choice <= 13 || choice == 99))) {
			displayIncorrectNumberMessage();
		}
	} while (!(choice >= 0 && (choice <= 13 || choice == 99)));

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
		confirmSale(dealership);
		break;
	case 11:
		usageOfAnOverloadedOperator(dealership);
		break;
	case 12:
		saveToAFile(dealership);
		break;
	case 13:
		loadDataFromAFile(dealership);
		break;
	case 99:
		dealership.setTypeCounterAddOne();
		dealership.setChosenVehicleType(vehicleTypes[dealership.getTypeCounter() % 2]);
		break;
	default:
		displayIncorrectNumberMessage();
		break;
	}
}

int main() {
	// This enables Polish letters to be displayed in the terminal
	setlocale(LC_CTYPE, "Polish");

	// Set the seed for the randomizer to the current time to ensure different results each time the program is run
	srand((unsigned int)time(nullptr));

	// Create an object dealership of a type Dealership to use in the menu function
	Dealership& dealership = Dealership::instance();

	while (true) {
		menu(dealership);
	}
}