#include "../header.h"

using namespace std;

// MENU 9
//
// This function allows user to search through all the listing on the chosen criteria
void searchThroughListings(Dealership& dealership) {
	vehicleType vehicleChoice = dealership.getChosenVehicleType();
	string input;
	vector<int> searchedIndexes;
	auto checker = searchedIndexes.begin();
	int indexToChoose;

	if (vehicleChoice == CAR) {
		cout << "  1] Brand" << endl;
		cout << "  2] Model" << endl;
		cout << "  3] Production year      (this and above)" << endl;
		cout << "  4] Registration number" << endl;
		cout << "  5] Horse power          (this and above)" << endl;
		cout << "  6] Fuel type            (Petrol, Diesel, Petrol + LPG)" << endl;
		cout << "  7] Gearbox type         (Manual, Automatic)" << endl;
		cout << "  8] Drive type           (Front, Rear)" << endl;
		cout << "  9] Fuel consumption     (this and below)" << endl;
		cout << " 10] Trunk capacity       (this and above)" << endl;
		cout << " 11] Seat number          (this and above)" << endl;
		cout << " 12] Body type            (Sedan, Hatchback, SUV...)" << endl;
		cout << " 13] Price                (this and above)" << endl << endl << endl;

		searchedIndexes = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
		checker = searchedIndexes.begin();
	}
	else if (vehicleChoice == MOTORCYCLE) {
		cout << "  1] Brand" << endl;
		cout << "  2] Model" << endl;
		cout << "  3] Production year      (this and above)" << endl;
		cout << "  4] Registration number" << endl;
		cout << "  5] Horse power          (this and above)" << endl;
		cout << "  6] Fuel type            (Petrol, Diesel, Petrol + LPG)" << endl;
		cout << "  7] Gearbox type         (Manual, Automatic)" << endl;
		cout << "  8] Drive type           (Front, Rear)" << endl;
		cout << "  9] Fuel consumption     (this and below)" << endl;
		cout << " 10] Engine size          (this and above)" << endl;
		cout << " 11] Top speed            (this and above)" << endl;
		cout << " 12] Motorcycle type      (Standard, Cruiser, Sport...)" << endl;
		cout << " 13] Brake type           (Disc, Drum)" << endl;
		cout << " 14] Price                (this and below)" << endl << endl << endl;

		searchedIndexes = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
		checker = searchedIndexes.begin();
	}

	do {
		cout << "\n    Enter index of the criteria to search: ";
		cin >> indexToChoose;
		// Checker variable stores information whether the entered index has been previously searched and displayed
		checker = find(searchedIndexes.begin(), searchedIndexes.end(), indexToChoose);

		if (checker == searchedIndexes.end()) {
			cout << "\n    Chosen index doesn't exist";
			cout << "\n    Try again\n";
		}
		// Repeat until the correct index is entered
	} while (checker == searchedIndexes.end());

	string searchValue;

	cout << "    Enter the value to search : ";
	cin >> searchValue;
	cout << endl;

	size_t listingsSize = dealership.getListingsSize(vehicleChoice);

	// Variable to save bool statement used for the search function to save myself writing A LOT of repetetive code
	auto searchFunction = [&](int indexToChoose, vehicleType vehicleChoice, int i) -> bool {
		switch (indexToChoose) {
		case 1:
			return dealership.getBrandWithIndex(vehicleChoice, i) == searchValue;
		case 2:
			return dealership.getModelWithIndex(vehicleChoice, i) == searchValue;
		case 3:
			return dealership.getProductionYearWithIndex(vehicleChoice, i) >= stoi(searchValue);
		case 4:
			return dealership.getRegistrationNumberWithIndex(vehicleChoice, i) == searchValue;
		case 5:
			return dealership.getHorsePowerWithIndex(vehicleChoice, i) >= stoi(searchValue);
		case 6:
			return dealership.getFuelTypeWithIndex(vehicleChoice, i) == searchValue;
		case 7:
			return dealership.getGearboxTypeWithIndex(vehicleChoice, i) == searchValue;
		case 8:
			return dealership.getDriveTypeWithIndex(vehicleChoice, i) == searchValue;
		case 9:
			return dealership.getFuelConsumptionWithIndex(vehicleChoice, i) <= stoi(searchValue);
		case 10:
			if (vehicleChoice == CAR)
				return dealership.getTrunkCapacityWithIndex(i) >= stoi(searchValue);
			else if (vehicleChoice == MOTORCYCLE)
				return dealership.getEngineSizeWithIndex(i) >= stoi(searchValue);
		case 11:
			if (vehicleChoice == CAR)
				return dealership.getSeatNumberWithIndex(i) >= stoi(searchValue);
			else if (vehicleChoice == MOTORCYCLE)
				return dealership.getTopSpeedWithIndex(i) >= stoi(searchValue);
		case 12:
			if (vehicleChoice == CAR)
				return dealership.getBodyTypeWithIndex(i) == searchValue;
			else if (vehicleChoice == MOTORCYCLE)
				return dealership.getTypeWithIndex(i) == searchValue;
		case 13:
			if (vehicleChoice == CAR)
				return dealership.getListingPriceWithIndex(vehicleChoice, i) <= stoi(searchValue);
			else if (vehicleChoice == MOTORCYCLE)
				return dealership.getBrakeTypeWithIndex(i) == searchValue;
		case 14:
			if (vehicleChoice == CAR)
				return false;
			else if (vehicleChoice == MOTORCYCLE)
				return dealership.getListingPriceWithIndex(vehicleChoice, i) <= stoi(searchValue);
		default:
			return false;
		}
	};

	int displayCount = 1;
	cout << endl;

	for (int i = 0; i < listingsSize; i++) {
		if (searchFunction(indexToChoose, vehicleChoice, i)) {
			cout << left << setw(29 - to_string(i + 1).size()) << setfill('=') << "" << " " << displayCount << ". Listing " << right << setw(28) << setfill('=') << "" << endl << endl;
			dealership.displayListing(vehicleChoice, i);
			cout << "                         Owner: " << dealership.getOwnerNameWithIndex(dealership.getListingOwnerIndexWithIndex(vehicleChoice, i)) <<
				endl << endl << endl;
			displayCount++;
		}
	}

	displayPressEnterToMenu();
}