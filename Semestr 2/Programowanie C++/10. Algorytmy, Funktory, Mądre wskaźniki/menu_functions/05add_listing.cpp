#include "../header.h"

using namespace std;

// MENU 5
//
// Function to add a new listing after selecting the owner from the list
void addListingByUser(Dealership& dealership) {
	int indexToChoose = 0;
	int typeChoice = 0;
	vector<int> searchedIndexes;

	// Checker variable stores information whether the array is empty or not
	auto checker = searchedIndexes.begin();
	bool flag = false;

	size_t ownersSize = dealership.getOwnersSize();

	if (ownersSize == 0) {
		cout << "\n" << setfill('=') << setw(68) << "=\n\n";
		cout << "    The owners array is empty!\n\n";
		cout << "    Press ENTER to go back to the menu\n";
		cout << "\n" << setfill('=') << setw(68) << "=\n";
		cin.ignore();
		cin.get();
		return;
	}

	cout << "\n| Index |     Name     | Num of listings |    City   |" << endl;
	cout << "------------------------------------------------------" << endl;

	for (int i = 0; i < ownersSize; i++) {
		searchedIndexes.push_back(i);

		cout << "| " << i << right << setfill(' ') << setw(5 - to_string(i).size()) << "" << " | ";

		string ownerName = dealership.getOwnerNameWithIndex(i);
		cout << ownerName << right << setfill(' ') << setw(12 - ownerName.size()) << "" << " | ";

		int ownerListings = dealership.countOwnersListings(i);
		cout << ownerListings << right << setfill(' ') << setw(15 - to_string(ownerListings).size()) << "" << " | ";

		string ownerCity = dealership.getOwnerCityWithIndex(i);
		cout << ownerCity << right << setfill(' ') << setw(9 - ownerCity.size()) << "" << " |\n";
	}

	do {
		cout << "\n    Enter the index of the owner who added the listing: ";
		cin >> indexToChoose;

		// Checker variable stores information whether the entered index has been previously searched and displayed
		checker = find(searchedIndexes.begin(), searchedIndexes.end(), indexToChoose);

		if (checker == searchedIndexes.end()) {
			cout << "\n    Wrong number";
			cout << "\n    Try again\n";
		}
		// Repeat until the correct index is entered
	} while (checker == searchedIndexes.end());

	vector<int> possibleTypes = { 1, 2 };

	// Chosen type is CAR
	if (dealership.getChosenVehicleType() == CAR) {
		cout << "\n\n    Selected owner has a name: " << dealership.getOwnerNameWithIndex(indexToChoose) << "\n";
		cout << "\n    Enter brand, model, production year, registration number, horse power," << endl;
		cout << "    fuel type, gearbox type, drive type, fuel consumption, trunk capacity" << endl;
		cout << "    seat number and body type" << endl;
		cout << "    separated with the ';' character for example:" << endl;
		cout << "\nSkoda;Fabia;2010;ZST 16161;70;Petrol;Manual;Front;7;380;5;Hatchback" << endl;

		string input, brand, model, productionYear, registrationNumber, horsePower, fuelType, gearboxType, driveType,
			fuelConsumption, trunkCapacity, seatNumber, bodyType;

		cin.ignore();
		getline(cin, input);

		stringstream ss(input);
		getline(ss, brand, ';');
		getline(ss, model, ';');
		getline(ss, productionYear, ';');
		getline(ss, registrationNumber, ';');
		getline(ss, horsePower, ';');
		getline(ss, fuelType, ';');
		getline(ss, gearboxType, ';');
		getline(ss, driveType, ';');
		getline(ss, fuelConsumption, ';');
		getline(ss, trunkCapacity, ';');
		getline(ss, seatNumber, ';');
		getline(ss, bodyType, ';');

		cout << "\n\n    Enter the price for the newly added car: ";

		int price;

		cin >> price;

		string ownerName = dealership.getOwnerNameWithIndex(indexToChoose);

		// stoi() function to convert string to int
		dealership.addCarListing(brand, model, stoi(productionYear), registrationNumber, stoi(horsePower), fuelType, gearboxType,
			driveType, stoi(fuelConsumption), stoi(trunkCapacity), stoi(seatNumber), bodyType, ownerName, price, false);
	}
	// Chosen type is MOTORCYCLE
	else if (dealership.getChosenVehicleType() == MOTORCYCLE) {
		cout << "\n\n    Selected owner has a name: " << dealership.getOwnerNameWithIndex(indexToChoose) << "\n";
		cout << "\n    Enter brand, model, production year, registration number, horse power," << endl;
		cout << "    fuel type, gearbox type, drive type, fuel consumption, engine size" << endl;
		cout << "    top speed, motorcycle type and brakes type" << endl;
		cout << "    separated with the ';' character for example:" << endl;
		cout << "Honda;CBR;2015;ZST 17123;126;Petrol;Manual;Back;6;998;300;Sport;Disc" << endl;

		string input, brand, model, productionYear, registrationNumber, horsePower, fuelType, gearboxType, driveType,
			fuelConsumption, engineSize, topSpeed, type, brakeType;

		cin.ignore();
		getline(cin, input);

		stringstream ss(input);
		getline(ss, brand, ';');
		getline(ss, model, ';');
		getline(ss, productionYear, ';');
		getline(ss, registrationNumber, ';');
		getline(ss, horsePower, ';');
		getline(ss, fuelType, ';');
		getline(ss, gearboxType, ';');
		getline(ss, driveType, ';');
		getline(ss, fuelConsumption, ';');
		getline(ss, engineSize, ';');
		getline(ss, topSpeed, ';');
		getline(ss, type, ';');
		getline(ss, brakeType, ';');

		cout << "\n\n    Enter the price for the newly added motorcycle: ";

		int price;

		cin >> price;

		string ownerName = dealership.getOwnerNameWithIndex(indexToChoose);

		// stoi() function to convert string to int
		dealership.addMotorcycleListing(brand, model, stoi(productionYear), registrationNumber, stoi(horsePower), fuelType, gearboxType,
			driveType, stoi(fuelConsumption), stoi(engineSize), stoi(topSpeed), type, brakeType, ownerName, price, false);
	}

	cout << "\n" << setfill('=') << setw(68) << "=\n\n";
	cout << "    Added a new listing!\n\n";
	cout << "    Press ENTER to go back to the menu\n";
	cout << "\n" << setfill('=') << setw(67) << "=\n";
	cin.ignore();
	cin.get();
}