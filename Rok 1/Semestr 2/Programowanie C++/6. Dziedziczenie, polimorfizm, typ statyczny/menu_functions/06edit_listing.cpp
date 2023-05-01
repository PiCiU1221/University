#include "../header.h"

using namespace std;

// MENU 6
//
// Function to edit the chosen listing attribute
void editListing(Dealership& dealership) {
	int indexToChoose, typeChoice = 0;
	vector<int> searchedIndexes;

	// Checker variable stores information whether the array is empty or not
	auto checker = searchedIndexes.begin();
	bool flag = false;

	size_t pushBackForMotorcycles = 0;
	vehicleType vehicleChoice = dealership.getChosenVehicleType();

	if (vehicleChoice == MOTORCYCLE) {
		pushBackForMotorcycles = dealership.getListingsSize(CAR);
	}

	size_t listingsSize = dealership.getListingsSize(vehicleChoice);

	for (int i = 0; i < listingsSize; i++) {
		searchedIndexes.push_back(i);

		if (flag == false) {
			cout << "\n| Index |     Owner    |     Brand    |     Model    |  Price  |" << endl;
			cout << "----------------------------------------------------------------" << endl;
		}

		// Using the [] overloaded operator
		// pushBackForMotorcycles because in order to use the [] operator we have to skip the car indexes
		Listing* listing_ = dealership[i + pushBackForMotorcycles];

		cout << "| " << i << right << setfill(' ') << setw(5 - to_string(i).size()) << "" << " | ";

		string ownerName = dealership.getOwnerNameWithIndex(dealership.getListingOwnerIndexWithIndex(vehicleChoice, i));
		cout << ownerName << right << setfill(' ') << setw(12 - ownerName.size()) << "" << " | ";

		string brand = dealership.getBrandWithIndex(vehicleChoice, i);
		cout << brand << right << setfill(' ') << setw(12 - brand.size()) << "" << " | ";

		string model = dealership.getModelWithIndex(vehicleChoice, i);
		cout << model << right << setfill(' ') << setw(12 - model.size()) << "" << " | ";

		int price = listing_->getPrice();
		cout << price << right << setfill(' ') << setw(7 - to_string(price).size()) << "" << " |\n";

		flag = true;
	}
	if (flag == false) {
		cout << "\n" << setfill('=') << setw(68) << "=\n\n";
		cout << "    Array of listings is empty!\n\n";
		cout << "    Press ENTER to go back to the menu\n";
		cout << "\n" << setfill('=') << setw(67) << "=\n";
		cin.ignore();
		cin.get();
	}
	else {
		do {
			cout << "\n    Enter the index of the listing to edit: ";
			cin >> indexToChoose;
			// Checker variable stores information whether the entered index has been previously searched and displayed
			checker = find(searchedIndexes.begin(), searchedIndexes.end(), indexToChoose);

			if (checker == searchedIndexes.end()) {
				cout << "\n    Chosen index doesn't exist";
				cout << "\n    Try again\n";
			}
			// Repeat until the correct index is entered
		} while (checker == searchedIndexes.end());

		if (vehicleChoice == CAR) {
			cout << "\n\n    Selected owner has a name: " << dealership.getOwnerNameWithIndex(dealership.getListingOwnerIndexWithIndex(vehicleChoice, indexToChoose)) << "\n\n";

			string input;

			cout << "  1]                     Brand: " << dealership.getBrandWithIndex(vehicleChoice, indexToChoose) << endl;
			cout << "  2]                     Model: " << dealership.getModelWithIndex(vehicleChoice, indexToChoose) << endl;
			cout << "  3]           Production year: " << dealership.getProductionYearWithIndex(vehicleChoice, indexToChoose) << endl;
			cout << "  4]       Registration number: " << dealership.getRegistrationNumberWithIndex(vehicleChoice, indexToChoose) << endl;
			cout << "  5]               Horse power: " << dealership.getHorsePowerWithIndex(vehicleChoice, indexToChoose) << endl;
			cout << "  6]                 Fuel type: " << dealership.getFuelTypeWithIndex(vehicleChoice, indexToChoose) << endl;
			cout << "  7]              Gearbox type: " << dealership.getGearboxTypeWithIndex(vehicleChoice, indexToChoose) << endl;
			cout << "  8]                Drive type: " << dealership.getDriveTypeWithIndex(vehicleChoice, indexToChoose) << endl;
			cout << "  9]          Fuel Consumption: " << dealership.getFuelConsumptionWithIndex(vehicleChoice, indexToChoose) << endl;
			cout << " 10]            Trunk Capacity: " << dealership.getTrunkCapacityWithIndex(indexToChoose) << endl;
			cout << " 11]               Seat number: " << dealership.getSeatNumberWithIndex(indexToChoose) << endl;
			cout << " 12]                 Body type: " << dealership.getBodyTypeWithIndex(indexToChoose) << endl;
			cout << " 13]                     Price: " << dealership.getListingPriceWithIndex(vehicleChoice, indexToChoose) << endl << endl << endl;

			int listingIndex = indexToChoose;

			vector<int> searchedIndexes = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };

			do {
				cout << "\n    Enter the index of the attribute to edit: ";
				cin >> indexToChoose;
				// Checker variable stores information whether the entered index has been previously searched and displayed
				checker = find(searchedIndexes.begin(), searchedIndexes.end(), indexToChoose);

				if (checker == searchedIndexes.end()) {
					cout << "\n    Chosen index doesn't exist";
					cout << "\n    Try again\n";
				}
				// Repeat until the correct index is entered
			} while (checker == searchedIndexes.end());

			switch (indexToChoose) {
			case 1:
				cout << " Enter a new brand: ";
				cin.ignore();
				getline(cin, input);
				dealership.setBrandWithIndex(vehicleChoice, input, listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Brand has been updated\n\n";
				break;
			case 2:
				cout << " Enter a new model: ";
				cin.ignore();
				getline(cin, input);
				dealership.setModelWithIndex(vehicleChoice, input, listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Model has been updated\n\n";
				break;
			case 3:
				cout << " Enter a new production year: ";
				cin.ignore();
				getline(cin, input);
				dealership.setProductionYearWithIndex(vehicleChoice, stoi(input), listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Production year has been updated\n\n";
				break;
			case 4:
				cout << " Enter a new registration number: ";
				cin.ignore();
				getline(cin, input);
				dealership.setRegistrationNumberWithIndex(vehicleChoice, input, listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Registration number has been updated\n\n";
				break;
			case 5:
				cout << " Enter a new horse power: ";
				cin.ignore();
				getline(cin, input);
				dealership.setHorsePowerWithIndex(vehicleChoice, stoi(input), listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Horse power has been updated\n\n";
				break;
			case 6:
				cout << " Enter a new fuel type: ";
				cin.ignore();
				getline(cin, input);
				dealership.setFuelTypeWithIndex(vehicleChoice, input, listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Fuel type has been updated\n\n";
				break;
			case 7:
				cout << " Enter a new gearbox type: ";
				cin.ignore();
				getline(cin, input);
				dealership.setGearboxTypeWithIndex(vehicleChoice, input, listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Gearbox type has been updated\n\n";
				break;
			case 8:
				cout << " Enter a new drive type: ";
				cin.ignore();
				getline(cin, input);
				dealership.setDriveTypeWithIndex(vehicleChoice, input, listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Drive type has been updated\n\n";
				break;
			case 9:
				cout << " Enter a new fuel consumption: ";
				cin.ignore();
				getline(cin, input);
				dealership.setFuelConsumptionWithIndex(vehicleChoice, stoi(input), listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Fuel consumption has been updated\n\n";
				break;
			case 10:
				cout << " Enter a new trunk capacity: ";
				cin.ignore();
				getline(cin, input);
				dealership.setTrunkCapacityWithIndex(stoi(input), listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Trunk Capacity has been updated\n\n";
				break;
			case 11:
				cout << " Enter a new seat number: ";
				cin.ignore();
				getline(cin, input);
				dealership.setSeatNumberWithIndex(stoi(input), listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Seat number has been updated\n\n";
				break;
			case 12:
				cout << " Enter a new body type: ";
				cin.ignore();
				getline(cin, input);
				dealership.setBodyTypeWithIndex(input, listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Body type has been updated\n\n";
				break;
			case 13:
				cout << " Enter a new price: ";
				cin.ignore();
				getline(cin, input);
				dealership.setPriceWithIndex(vehicleChoice, stoi(input), listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Price has been updated\n\n";
				break;
			default:
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    An error accured\n\n";
				break;
			}
		}
		else if (vehicleChoice == MOTORCYCLE) {
			cout << "\n\n    Selected owner has a name: " << dealership.getOwnerNameWithIndex(indexToChoose) << "\n\n";

			string input;

			cout << "  1]                     Brand: " << dealership.getBrandWithIndex(vehicleChoice, indexToChoose) << endl;
			cout << "  2]                     Model: " << dealership.getModelWithIndex(vehicleChoice, indexToChoose) << endl;
			cout << "  3]           Production year: " << dealership.getProductionYearWithIndex(vehicleChoice, indexToChoose) << endl;
			cout << "  4]       Registration number: " << dealership.getRegistrationNumberWithIndex(vehicleChoice, indexToChoose) << endl;
			cout << "  5]               Horse power: " << dealership.getHorsePowerWithIndex(vehicleChoice, indexToChoose) << endl;
			cout << "  6]                 Fuel type: " << dealership.getFuelTypeWithIndex(vehicleChoice, indexToChoose) << endl;
			cout << "  7]              Gearbox type: " << dealership.getGearboxTypeWithIndex(vehicleChoice, indexToChoose) << endl;
			cout << "  8]                Drive type: " << dealership.getDriveTypeWithIndex(vehicleChoice, indexToChoose) << endl;
			cout << "  9]          Fuel Consumption: " << dealership.getFuelConsumptionWithIndex(vehicleChoice, indexToChoose) << endl;
			cout << " 10]              Engine Size: " << dealership.getEngineSizeWithIndex(indexToChoose) << endl;
			cout << " 11]                 Top Speed: " << dealership.getTopSpeedWithIndex(indexToChoose) << endl;
			cout << " 12]           Motorcycle type: " << dealership.getTypeWithIndex(indexToChoose) << endl;
			cout << " 13]                Brake type: " << dealership.getBrakeTypeWithIndex(indexToChoose) << endl;
			cout << " 14]                     Price: " << dealership.getListingPriceWithIndex(vehicleChoice, indexToChoose) << endl << endl << endl;

			int listingIndex = indexToChoose;

			vector<int> searchedIndexes = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };

			do {
				cout << "\n    Enter the index of the attribute to edit: ";
				cin >> indexToChoose;
				// Checker variable stores information whether the entered index has been previously searched and displayed
				checker = find(searchedIndexes.begin(), searchedIndexes.end(), indexToChoose);

				if (checker == searchedIndexes.end()) {
					cout << "\n    Chosen index doesn't exist";
					cout << "\n    Try again\n";
				}
				// Repeat until the correct index is entered
			} while (checker == searchedIndexes.end());

			switch (indexToChoose) {
			case 1:
				cout << " Enter a new brand: ";
				cin.ignore();
				getline(cin, input);
				dealership.setBrandWithIndex(vehicleChoice, input, listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Brand has been updated\n\n";
				break;
			case 2:
				cout << " Enter a new model: ";
				cin.ignore();
				getline(cin, input);
				dealership.setModelWithIndex(vehicleChoice, input, listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Model has been updated\n\n";
				break;
			case 3:
				cout << " Enter a new production year: ";
				cin.ignore();
				getline(cin, input);
				dealership.setProductionYearWithIndex(vehicleChoice, stoi(input), listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Production year has been updated\n\n";
				break;
			case 4:
				cout << " Enter a new registration number: ";
				cin.ignore();
				getline(cin, input);
				dealership.setRegistrationNumberWithIndex(vehicleChoice, input, listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Registration number has been updated\n\n";
				break;
			case 5:
				cout << " Enter a new horse power: ";
				cin.ignore();
				getline(cin, input);
				dealership.setHorsePowerWithIndex(vehicleChoice, stoi(input), listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Horse power has been updated\n\n";
				break;
			case 6:
				cout << " Enter a new fuel type: ";
				cin.ignore();
				getline(cin, input);
				dealership.setFuelTypeWithIndex(vehicleChoice, input, listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Fuel type has been updated\n\n";
				break;
			case 7:
				cout << " Enter a new gearbox type: ";
				cin.ignore();
				getline(cin, input);
				dealership.setGearboxTypeWithIndex(vehicleChoice, input, listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Gearbox type has been updated\n\n";
				break;
			case 8:
				cout << " Enter a new drive type: ";
				cin.ignore();
				getline(cin, input);
				dealership.setDriveTypeWithIndex(vehicleChoice, input, listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Drive type has been updated\n\n";
				break;
			case 9:
				cout << " Enter a new fuel consumption: ";
				cin.ignore();
				getline(cin, input);
				dealership.setFuelConsumptionWithIndex(vehicleChoice, stoi(input), listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Fuel consumption has been updated\n\n";
				break;
			case 10:
				cout << " Enter a new engine size: ";
				cin.ignore();
				getline(cin, input);
				dealership.setEngineSizeWithIndex(stoi(input), listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Engine size has been updated\n\n";
				break;
			case 11:
				cout << " Enter a new top speed: ";
				cin.ignore();
				getline(cin, input);
				dealership.setTopSpeedWithIndex(stoi(input), listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Top speed has been updated\n\n";
				break;
			case 12:
				cout << " Enter a new motorcycle type: ";
				cin.ignore();
				getline(cin, input);
				dealership.setTypeWithIndex(input, listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Motorcycle type has been updated\n\n";
				break;
			case 13:
				cout << " Enter a new brake type: ";
				cin.ignore();
				getline(cin, input);
				dealership.setBrakeTypeWithIndex(input, listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Brake type has been updated\n\n";
				break;
			case 14:
				cout << " Enter a new price: ";
				cin.ignore();
				getline(cin, input);
				dealership.setPriceWithIndex(vehicleChoice, stoi(input), listingIndex);
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    Price has been updated\n\n";
				break;
			default:
				cout << "\n" << setfill('=') << setw(68) << "=\n\n";
				cout << "    An error accured\n\n";
				break;
			}
		}

		cout << "    Press ENTER to go back to the menu\n";
		cout << "\n" << setfill('=') << setw(67) << "=\n";
		cin.get();
	}
}