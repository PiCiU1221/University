#include "header.h"

using namespace std;

/*
	Piotr Pietrusewicz 53828 120A
	West Pomeranian University of Technology
	Theme: Car Dealearship

	File contains definitions of the main functions used in the 'menu' function
*/

// Function to randomly generate 'Owner' and 'Listing' objects with data and add them to the main 'dealership' object
void generateRandomizedOwnersAndListings(Dealership& dealership) {
	int randomNumberOfOwners = generateInteger(5, 10);
	string randomName = "";

	for (int i = 0; i < randomNumberOfOwners; i++) {
		randomName = name[generateInteger(0, 9)] + to_string(generateInteger(70, 99));
		dealership.addOwner(randomName, city[generateInteger(0, 3)], ulica[generateInteger(0, 3)], generateInteger(1, 99));
	}

	int randomNumberOfListings = generateInteger(5, 10);

	for (int i = 0; i < randomNumberOfListings; i++) {
		int randomBrand = generateInteger(0, 4);
		int randomOwner = generateInteger(0, dealership.getOwnersSize() - 1);

		dealership.addListing(brand[randomBrand], model[randomBrand][generateInteger(0, 2)], generateInteger(1995, 2020),
			plate[generateInteger(0, 3)] + " " + to_string(generateInteger(10000, 99999)),
			generateInteger(70, 250), fuelType[generateInteger(0, 2)], gearboxType[generateInteger(0, 1)],
			driveType[generateInteger(0, 2)], generateInteger(5, 12), randomOwner, generateInteger(5000, 99999));
	}

	cout << "\n========================================================\n\n";
	cout << "    Wygenerowano " << randomNumberOfOwners << " w³aœcicieli i " << randomNumberOfListings << " ogloszeñ" << endl;
	cout << "\n    Press ENTER to go back to the menu\n";
	cout << "\n========================================================\n";
	cin.ignore();
	cin.get();
}

// Function to add a new owner from the user input using the overloaded '<<' operator from the 'Owner' class
void addOwnerByUser(Dealership& dealership) {
	cout << "\n    Enter the owners name: " << endl;

	Owner wlasciciel(city[generateInteger(0, 3)], ulica[generateInteger(0, 3)], generateInteger(1, 99));

	Owner wlascicielToDemonstrateUseOfOperator(city[generateInteger(0, 3)], ulica[generateInteger(0, 3)], generateInteger(1, 99));

	// Usage of the overloaded operator
	cin >> wlascicielToDemonstrateUseOfOperator;

	wlasciciel = wlascicielToDemonstrateUseOfOperator;

	dealership.addOwner(wlasciciel.getName(), wlasciciel.getCity(), wlasciciel.getStreet(), wlasciciel.getNumber());

	cout << "\n========================================================\n\n";
	cout << "    Added a new owner with the name of: " << wlasciciel.getName() << "\n\n";
	cout << "    Press ENTER to go back to the menu\n";
	cout << "\n========================================================\n";
	cin.ignore();
	cin.get();
}

// Function that deletes the chosen owner from the list
void deleteOwnerByUser(Dealership& dealership) {
	int indexToDelete = 0;
	vector<int> searchedIndexes;
	// sprawdzamy zmienna checker, czy tablica nie jest pusta
	auto checker = searchedIndexes.begin();
	bool flag = false;

	int ownersSize = dealership.getOwnersSize();
	for (int i = 0; i < ownersSize; i++) {
		searchedIndexes.push_back(i);

		if (flag == false) {
			cout << "\n| Index |        Name       | Number of listings |" << endl;
			cout << "------------------------------------------------" << endl;
		}

		cout << "| ";
		for (int j = 1; j <= 5 - countNumbers(i); j++) {
			cout << " ";
		}
		cout << i << " | ";

		string ownerName = dealership.getOwnerNameWithIndex(i);

		size_t ownerNameSize = ownerName.size();

		for (int j = 1; j <= 17 - ownerNameSize; j++) {
			cout << " ";
		}
		cout << ownerName << " | ";

		int ownerListings = dealership.countOwnersListings(i);

		int cyfryCount = countNumbers(ownerListings);

		for (int j = 1; j <= 18 - cyfryCount; j++) {
			cout << " ";
		}
		cout << ownerListings << " | " << endl;
		flag = true;
	}
	if (flag == false) {
		cout << "\n========================================================\n\n";
		cout << "    Owners list is empty!\n\n";
		cout << "    Press ENTER to go back to the menu\n";
		cout << "\n========================================================\n";
		cin.ignore();
		cin.get();
	}
	else {
		do {
			cout << "\n    Enter an owners index to delete: ";
			cin >> indexToDelete;
			// checker variable stores information whether the entered index has been previously searched and displayed
			checker = find(searchedIndexes.begin(), searchedIndexes.end(), indexToDelete);

			if (checker == searchedIndexes.end()) {
				cout << "\n    Chosen index doesn't exist";
				cout << "\n    Try again\n";
			}
			// Repeat until the correct index is entered
		} while (checker == searchedIndexes.end());

		string choice;

		do {
			cout << "\n========================================================\n\n";
			cout << "    Are you sure you want to delete this owner?\n\n";
			cout << "    Enter [Y/N]\n";
			cout << "\n========================================================\n";
			cin >> choice;

			if (choice != "Y" && choice != "N") {
				cout << "\n    You can choose only 'Y', or 'N'";
				cout << "\n    Try again\n";
			}
			// Repeat until the correct index is entered
		} while (choice != "Y" && choice != "N");

		if (choice == "Y") {
			string deletedOwnerName = dealership.getOwnerNameWithIndex(indexToDelete);
			int deletedOwnerListings = dealership.countOwnersListings(indexToDelete);

			dealership.deleteOwner(indexToDelete);

			cout << "\n========================================================\n\n";
			cout << "    Owner with the name: " << deletedOwnerName << " was deleted with their " << deletedOwnerListings << " listings\n\n";
			cout << "    Press ENTER to go back to the menu\n";
			cout << "\n========================================================\n";
			cin.ignore();
			cin.get();
		}
	}
}

// Function that displays the Owners objects data
void displayOwners(Dealership& dealership) {
	cout << "\n| Index |       Nazwa       | Liczba og³oszeñ |   Miasto  |" << endl;
	cout << "------------------------------------------------------------" << endl;

	int ownersSize = dealership.getOwnersSize();
	for (int i = 0; i < ownersSize; i++) {
		cout << "| ";
		for (int j = 1; j <= 5 - countNumbers(i); j++) {
			cout << " ";
		}
		cout << i << " | ";

		string ownerName = dealership.getOwnerNameWithIndex(i);
		size_t wlascicielNameSize = ownerName.size();

		for (int j = 1; j <= 17 - wlascicielNameSize; j++) {
			cout << " ";
		}
		cout << ownerName << " | ";

		int ownerListings = dealership.countOwnersListings(i);
		int cyfryCount = countNumbers(ownerListings);

		for (int j = 1; j <= 15 - cyfryCount; j++) {
			cout << " ";
		}
		cout << ownerListings << " | ";

		string ownerCity = dealership.getOwnerCityWithIndex(i);
		size_t wlascicielMiastoSize = ownerCity.size();

		for (int j = 1; j <= 9 - wlascicielMiastoSize; j++) {
			cout << " ";
		}
		cout << ownerCity << " | " << endl;
	}

	cout << "\n========================================================\n\n";
	cout << "    Press ENTER to go back to the menu\n";
	cout << "\n========================================================\n";
	cin.ignore();
	cin.get();
}

// Function to add a new listing after selecting the owner from the list
void addListingByUser(Dealership& dealership) {
	int indexToChoose = 0;
	vector<int> searchedIndexes;

	// checker variable stores information whether the array is empty or not
	auto checker = searchedIndexes.begin();
	bool flag = false;

	int ownersSize = dealership.getOwnersSize();
	for (int i = 0; i < ownersSize; i++) {
		searchedIndexes.push_back(i);

		cout << "\n| Index |       Nazwa       | Liczba og³oszeñ |   Miasto  |" << endl;
		cout << "------------------------------------------------------------" << endl;

		int ownersSize = dealership.getOwnersSize();
		for (int i = 0; i < ownersSize; i++) {
			cout << "| ";
			for (int j = 1; j <= 5 - countNumbers(i); j++) {
				cout << " ";
			}
			cout << i << " | ";

			string ownerName = dealership.getOwnerNameWithIndex(i);
			size_t wlascicielNameSize = ownerName.size();

			for (int j = 1; j <= 17 - wlascicielNameSize; j++) {
				cout << " ";
			}
			cout << ownerName << " | ";

			int ownerListings = dealership.countOwnersListings(i);
			int cyfryCount = countNumbers(ownerListings);

			for (int j = 1; j <= 15 - cyfryCount; j++) {
				cout << " ";
			}
			cout << ownerListings << " | ";

			string ownerCity = dealership.getOwnerCityWithIndex(i);
			size_t wlascicielMiastoSize = ownerCity.size();

			for (int j = 1; j <= 9 - wlascicielMiastoSize; j++) {
				cout << " ";
			}
			cout << ownerCity << " | " << endl;
		}
		flag = true;
	}
	if (flag == false) {
		cout << "\n========================================================\n\n";
		cout << "    The owners array is empty!\n\n";
		cout << "    Press ENTER to go back to the menu\n";
		cout << "\n========================================================\n";
		cin.ignore();
		cin.get();
	}
	else {
		do {
			cout << "\n    Enter the index of the owner who added the listing: ";
			cin >> indexToChoose;
			// checker variable stores information whether the entered index has been previously searched and displayed
			checker = find(searchedIndexes.begin(), searchedIndexes.end(), indexToChoose);

			if (checker == searchedIndexes.end()) {
				cout << "\n    Chosen index doesn't exist";
				cout << "\n    Try again\n";
			}
			// Repeat until the correct index is entered
		} while (checker == searchedIndexes.end());

		cout << "\n\n    Selected owner has a name: " << dealership.getOwnerNameWithIndex(indexToChoose) << "\n";
		cout << "\n    Enter brand, model, production year, registration number, horse power," << endl;
		cout << "    fuel type, gearbox type, drive type oraz fuel consumption" << endl;
		cout << "    separated with the ';' character for example:" << endl;
		cout << "\n    Skoda;Fabia;2010;ZST 16161;70;Petrol;Manual;Front;7" << endl;

		string input, brand, model, productionYear, registrationNumber, horsePower, fuelType, gearboxType, driveType, fuelConsumption;
		size_t newPos, oldPos = 0;

		cin.ignore();
		getline(cin, input);

		newPos = input.find(';');
		brand = input.substr(0, newPos);
		oldPos = newPos + 1;

		// Checking the type of the entered data
		if (typeid(brand) != typeid(string)) {
			return;
		}

		newPos = input.find(';', oldPos);
		model = input.substr(oldPos, newPos - oldPos);
		oldPos = newPos + 1;

		if (typeid(model) != typeid(string)) {
			return;
		}

		newPos = input.find(';', oldPos);
		productionYear = input.substr(oldPos, newPos - oldPos);
		oldPos = newPos + 1;

		if (typeid(productionYear) != typeid(int)) {
			return;
		}

		newPos = input.find(';', oldPos);
		registrationNumber = input.substr(oldPos, newPos - oldPos);
		oldPos = newPos + 1;

		if (typeid(registrationNumber) != typeid(string)) {
			return;
		}

		newPos = input.find(';', oldPos);
		horsePower = input.substr(oldPos, newPos - oldPos);
		oldPos = newPos + 1;

		if (typeid(horsePower) != typeid(int)) {
			return;
		}

		newPos = input.find(';', oldPos);
		fuelType = input.substr(oldPos, newPos - oldPos);
		oldPos = newPos + 1;

		if (typeid(fuelType) != typeid(string)) {
			return;
		}

		newPos = input.find(';', oldPos);
		gearboxType = input.substr(oldPos, newPos - oldPos);
		oldPos = newPos + 1;

		if (typeid(gearboxType) != typeid(string)) {
			return;
		}

		newPos = input.find(';', oldPos);
		driveType = input.substr(oldPos, newPos - oldPos);
		oldPos = newPos + 1;

		if (typeid(driveType) != typeid(string)) {
			return;
		}

		fuelConsumption = input.substr(oldPos);

		if (typeid(fuelConsumption) != typeid(int)) {
			return;
		}

		cout << "\n\n    Enter the price for the newly added car: ";

		int price;

		cin.ignore();
		cin >> price;

		// stoi() function to convert string to int
		dealership.addListing(brand, model, stoi(productionYear), registrationNumber, stoi(horsePower),
			fuelType, gearboxType, driveType, stoi(fuelConsumption), indexToChoose, price);

		cout << "\n========================================================\n\n";
		cout << "    Added a new listing!\n\n";
		cout << "    Press ENTER to go back to the menu\n";
		cout << "\n========================================================\n";
		cin.ignore();
		cin.get();
	}
}

// Function to edit the chosen listing attribute
void editListing(Dealership& dealership) {
	int indexToChoose = 0;
	vector<int> searchedIndexes;

	// checker variable stores information whether the array is empty or not
	auto checker = searchedIndexes.begin();
	bool flag = false;

	int listingsSize = dealership.getListingsSize();
	for (int i = 0; i < listingsSize; i++) {
		searchedIndexes.push_back(i);

		if (flag == false) {
			cout << "\n| Index |     Owner    |    Brand   |    Model   |  Cena  |" << endl;
			cout << "-------------------------------------------------------------" << endl;
		}

		// using the [] overloaded operator
		Listing* listing_ = dealership[i];

		cout << "| ";
		for (int j = 1; j <= 5 - countNumbers(i); j++) {
			cout << " ";
		}
		cout << i << " | ";

		string ownerName = dealership.getOwnerNameWithIndex(i);
		size_t ownerNameSize = ownerName.size();

		for (int j = 1; j <= 14 - ownerNameSize; j++) {
			cout << " ";
		}
		cout << ownerName << " | ";

		string brand = dealership.getBrandWithIndex(i);
		size_t brandSize = brand.size();

		for (int j = 1; j <= 10 - brandSize; j++) {
			cout << " ";
		}
		cout << brand << " | ";

		string model = dealership.getModelWithIndex(i);
		size_t modelSize = model.size();

		for (int j = 1; j <= 10 - modelSize; j++) {
			cout << " ";
		}
		cout << model << " | ";

		size_t priceSize = countNumbers(listing_->getPrice());

		for (int j = 1; j <= 6 - priceSize; j++) {
			cout << " ";
		}
		cout << listing_->getPrice() << " | " << endl;

		flag = true;
	}
	if (flag == false) {
		cout << "\n========================================================\n\n";
		cout << "    Array of listings is empty!\n\n";
		cout << "    Press ENTER to go back to the menu\n";
		cout << "\n========================================================\n";
		cin.ignore();
		cin.get();
	}
	else {
		do {
			cout << "\n    Enter the index of the listing to edit: ";
			cin >> indexToChoose;
			// checker variable stores information whether the entered index has been previously searched and displayed
			checker = find(searchedIndexes.begin(), searchedIndexes.end(), indexToChoose);

			if (checker == searchedIndexes.end()) {
				cout << "\n    Chosen index doesn't exist";
				cout << "\n    Try again\n";
			}
			// Repeat until the correct index is entered
		} while (checker == searchedIndexes.end());

		cout << "\n\n    Selected owner has a name: " << dealership.getOwnerNameWithIndex(indexToChoose) << "\n\n";

		string input;

		cout << "  1]                     Brand: " << dealership.getBrandWithIndex(indexToChoose) << endl;
		cout << "  2]                     Model: " << dealership.getModelWithIndex(indexToChoose) << endl;
		cout << "  3]           Production year: " << dealership.getProductionYearWithIndex(indexToChoose) << endl;
		cout << "  4]       Registration number: " << dealership.getRegistrationNumberWithIndex(indexToChoose) << endl;
		cout << "  5]               Horse power: " << dealership.getHorsePowerWithIndex(indexToChoose) << endl;
		cout << "  6]                 Fuel type: " << dealership.getFuelTypeWithIndex(indexToChoose) << endl;
		cout << "  7]              Gearbox type: " << dealership.getGearboxTypeWithIndex(indexToChoose) << endl;
		cout << "  8]                Drive type: " << dealership.getDriveTypeWithIndex(indexToChoose) << endl;
		cout << "  9]          Fuel Consumption: " << dealership.getFuelConsumptionWithIndex(indexToChoose) << endl;
		cout << " 10]                     Price: " << dealership.getListingPriceWithIndex(indexToChoose) << endl << endl << endl;

		int listingIndex = indexToChoose;

		vector<int> searchedIndexes = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		do {
			cout << "\n    Enter the index of the attribute to edit: ";
			cin >> indexToChoose;
			// checker variable stores information whether the entered index has been previously searched and displayed
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
			dealership.setBrandWithIndex(input, listingIndex);
			cout << "\n========================================================\n\n";
			cout << "    Brand has been updated\n\n";
			break;
		case 2:
			cout << " Enter a new model: ";
			cin.ignore();
			getline(cin, input);
			dealership.setModelWithIndex(input, listingIndex);
			cout << "\n========================================================\n\n";
			cout << "    Model has been updated\n\n";
			break;
		case 3:
			cout << " Enter a new production year: ";
			cin.ignore();
			getline(cin, input);
			dealership.setProductionYearWithIndex(stoi(input), listingIndex);
			cout << "\n========================================================\n\n";
			cout << "    Production year has been updated\n\n";
			break;
		case 4:
			cout << " Enter a new registration number: ";
			cin.ignore();
			getline(cin, input);
			dealership.setRegistrationNumberWithIndex(input, listingIndex);
			cout << "\n========================================================\n\n";
			cout << "    Registration number has been updated\n\n";
			break;
		case 5:
			cout << " Enter a new horse power: ";
			cin.ignore();
			getline(cin, input);
			dealership.setHorsePowerWithIndex(stoi(input), listingIndex);
			cout << "\n========================================================\n\n";
			cout << "    Horse power has been updated\n\n";
			break;
		case 6:
			cout << " Enter a new fuel type: ";
			cin.ignore();
			getline(cin, input);
			dealership.setFuelTypeWithIndex(input, listingIndex);
			cout << "\n========================================================\n\n";
			cout << "    Fuel type has been updated\n\n";
			break;
		case 7:
			cout << " Enter a new gearbox type: ";
			cin.ignore();
			getline(cin, input);
			dealership.setGearboxTypeWithIndex(input, listingIndex);
			cout << "\n========================================================\n\n";
			cout << "    Gearbox type has been updated\n\n";
			break;
		case 8:
			cout << " Enter a new drive type: ";
			cin.ignore();
			getline(cin, input);
			dealership.setDriveTypeWithIndex(input, listingIndex);
			cout << "\n========================================================\n\n";
			cout << "    Drive type has been updated\n\n";
			break;
		case 9:
			cout << " Enter a new fuel consumption: ";
			cin.ignore();
			getline(cin, input);
			dealership.setFuelConsumptionWithIndex(stoi(input), listingIndex);
			cout << "\n========================================================\n\n";
			cout << "    Fuel consumption has been updated\n\n";
			break;
		case 10:
			cout << " enter a new price: ";
			cin.ignore();
			getline(cin, input);
			dealership.setPriceWithIndex(stoi(input), listingIndex);
			cout << "\n========================================================\n\n";
			cout << "    Price has been updated\n\n";
			break;
		default:
			cout << "\n========================================================\n\n";
			cout << "    An error accured\n\n";
			break;
		}

		cout << "    Press ENTER to go back to the menu\n";
		cout << "\n========================================================\n";
		cin.get();
	}
}

// Function that deletes the user chosen listing
void deleteUserListing(Dealership& dealership) {
	int indexToChoose = 0;
	vector<int> searchedIndexes;

	// checker variable stores information whether the array is empty or not
	auto checker = searchedIndexes.begin();
	bool flag = false;

	int listingsSize = dealership.getListingsSize();
	for (int i = 0; i < listingsSize; i++) {
		searchedIndexes.push_back(i);

		if (flag == false) {
			cout << "\n| Index |      Owner     |    Brand   |    Model   |  Price  |" << endl;
			cout << "--------------------------------------------------------------" << endl;
		}

		cout << "| ";
		for (int j = 1; j <= 5 - countNumbers(i); j++) {
			cout << " ";
		}
		cout << i << " | ";

		string ownerName = dealership.getOwnerNameWithIndex(i);
		size_t ownerNameSize = ownerName.size();

		for (int j = 1; j <= 14 - ownerNameSize; j++) {
			cout << " ";
		}
		cout << ownerName << " | ";

		string brand = dealership.getBrandWithIndex(i);
		size_t brandSize = brand.size();

		for (int j = 1; j <= 10 - brandSize; j++) {
			cout << " ";
		}
		cout << brand << " | ";

		string model = dealership.getModelWithIndex(i);
		size_t modelSize = model.size();

		for (int j = 1; j <= 10 - modelSize; j++) {
			cout << " ";
		}
		cout << model << " | ";

		int price = dealership.getListingPriceWithIndex(i);
		size_t priceSize = countNumbers(price);

		for (int j = 1; j <= 7 - priceSize; j++) {
			cout << " ";
		}
		cout << price << " | " << endl;

		flag = true;
	}
	if (flag == false) {
		cout << "\n========================================================\n\n";
		cout << "    Array of listings is empty\n\n";
		cout << "    Press ENTER to go back to the menu\n";
		cout << "\n========================================================\n";
		cin.ignore();
		cin.get();
	}
	else {
		do {
			cout << "\n    Enter a listing index to delete: ";
			cin >> indexToChoose;
			// checker variable stores information whether the entered index has been previously searched and displayed
			checker = find(searchedIndexes.begin(), searchedIndexes.end(), indexToChoose);

			if (checker == searchedIndexes.end()) {
				cout << "\n    Chosen index doesn't exist";
				cout << "\n    Try again\n";
			}
			// Repeat until the correct index is entered
		} while (checker == searchedIndexes.end());

		string choice;

		do {
			cout << "\n========================================================\n\n";
			cout << "    Are you sure you want to delete this listing?\n\n";
			cout << "    Enter [Y/N]\n";
			cout << "\n========================================================\n";
			cin >> choice;

			if (choice != "Y" && choice != "N") {
				cout << "\n    You can choose only 'Y', or 'N'";
				cout << "\n    Try again\n";
			}
			// Repeat until the correct index is entered
		} while (choice != "Y" && choice != "N");

		if (choice == "Y") {
			dealership.deleteListing(indexToChoose);

			cout << "\n========================================================\n\n";
			cout << "    Selected listing has been deleted\n\n";
			cout << "    Press ENTER to go back to the menu\n";
			cout << "\n========================================================\n";
			cin.ignore();
			cin.get();
		}
	}
}

// Function that displays all listings
void displayAllListings(Dealership& dealership) {
	int listingsSize = dealership.getListingsSize();
	for (int i = 0; i < listingsSize; i++) {
		if (countNumbers(i) >= 2) {
			cout << "======================= " << i + 1 << ". Listing ========================" << endl;
		}
		else {
			cout << "======================== " << i + 1 << ". Listing ========================" << endl;
		}

		dealership.displayListing(i);
		cout << "                         Owner: " << dealership.getOwnerNameWithIndex(dealership.getListingOwnerIndexWithIndex(i)) << endl << endl << endl;
	}

	cout << "\n========================================================\n\n";
	cout << "    Press ENTER to go back to the menu\n";
	cout << "\n========================================================\n";
	cin.ignore();
	cin.get();
}

// This function allows user to search through all the listing on the chosen criteria
void searchThroughListings(Dealership& dealership) {
	string input;

	cout << "  1] Brand" << endl;
	cout << "  2] Model" << endl;
	cout << "  3] Production year      (this and above)" << endl;
	cout << "  4] Registration number" << endl;
	cout << "  5] Horse power          (this and above)" << endl;
	cout << "  6] Fuel type            (Petrol, Diesel, Petrol + LPG)" << endl;
	cout << "  7] Gearbox type         (Manual, Automatic)" << endl;
	cout << "  8] Drive type           (Front, Back, All Wheel Drive)" << endl;
	cout << "  9] Fuel consumption     (this and below)" << endl;
	cout << " 10] Price                (this and above)" << endl << endl << endl;

	vector<int> searchedIndexes = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	auto checker = searchedIndexes.begin();

	int indexToChoose;

	do {
		cout << "\n    Enter index of the criteria to search: ";
		cin >> indexToChoose;
		// checker variable stores information whether the entered index has been previously searched and displayed
		checker = find(searchedIndexes.begin(), searchedIndexes.end(), indexToChoose);

		if (checker == searchedIndexes.end()) {
			cout << "\n    Podany indeks jest nieprawid³owy";
			cout << "\n    Spróbuj jeszcze raz\n";
		}
		// Repeat until the correct index is entered
	} while (checker == searchedIndexes.end());

	string searchValue;

	cout << "	Enter the value to search: ";
	cin >> searchValue;
	cout << endl;

	int listingsSize = dealership.getListingsSize();

	for (int i = 0; i < listingsSize; i++) {
		switch (indexToChoose) {
		case 1:
			if (dealership.getBrandWithIndex(i) == searchValue) {
				dealership.displayListing(i);
				cout << "                         Owner: " << dealership.getOwnerNameWithIndex(dealership.getListingOwnerIndexWithIndex(i)) << endl << endl << endl;
			}
			break;
		case 2:
			if (dealership.getModelWithIndex(i) == searchValue) {
				dealership.displayListing(i);
				cout << "                         Owner: " << dealership.getOwnerNameWithIndex(dealership.getListingOwnerIndexWithIndex(i)) << endl << endl << endl;
			}
			break;
		case 3:
			if (dealership.getProductionYearWithIndex(i) >= stoi(searchValue)) {
				dealership.displayListing(i);
				cout << "                         Owner: " << dealership.getOwnerNameWithIndex(dealership.getListingOwnerIndexWithIndex(i)) << endl << endl << endl;
			}
			break;
		case 4:
			if (dealership.getRegistrationNumberWithIndex(i) == searchValue) {
				dealership.displayListing(i);
				cout << "                         Owner: " << dealership.getOwnerNameWithIndex(dealership.getListingOwnerIndexWithIndex(i)) << endl << endl << endl;
			}
			break;
		case 5:
			if (dealership.getHorsePowerWithIndex(i) >= stoi(searchValue)) {
				dealership.displayListing(i);
				cout << "                         Owner: " << dealership.getOwnerNameWithIndex(dealership.getListingOwnerIndexWithIndex(i)) << endl << endl << endl;
			}
			break;
		case 6:
			if (dealership.getFuelTypeWithIndex(i) == searchValue) {
				dealership.displayListing(i);
				cout << "                         Owner: " << dealership.getOwnerNameWithIndex(dealership.getListingOwnerIndexWithIndex(i)) << endl << endl << endl;
			}
			break;
		case 7:
			if (dealership.getGearboxTypeWithIndex(i) == searchValue) {
				dealership.displayListing(i);
				cout << "                         Owner: " << dealership.getOwnerNameWithIndex(dealership.getListingOwnerIndexWithIndex(i)) << endl << endl << endl;
			}
			break;
		case 8:
			if (dealership.getDriveTypeWithIndex(i) == searchValue) {
				dealership.displayListing(i);
				cout << "                         Owner: " << dealership.getOwnerNameWithIndex(dealership.getListingOwnerIndexWithIndex(i)) << endl << endl << endl;
			}
			break;
		case 9:
			if (dealership.getFuelConsumptionWithIndex(i) <= stoi(searchValue)) {
				dealership.displayListing(i);
				cout << "                         Owner: " << dealership.getOwnerNameWithIndex(dealership.getListingOwnerIndexWithIndex(i)) << endl << endl << endl;
			}
			break;
		case 10:
			if (dealership.getListingPriceWithIndex(i) >= stoi(searchValue)) {
				dealership.displayListing(i);
			}
			break;
		default:
			cout << "Wrong search criteria was chosen" << endl;
		}
	}

	cout << "\n========================================================\n\n";
	cout << "    Press ENTER to go back to the menu\n";
	cout << "\n========================================================\n";
	cin.ignore();
	cin.get();
}

// Usage of overloaded operator '<<' for a 'Dealership' object
void usageOfAnOverloadedOperator(Dealership& dealership) {
	cout << "\n========================================================\n\n";
	cout << dealership;
	cout << "\n    Press ENTER to go back to the menu\n";
	cout << "\n========================================================\n";
	cin.ignore();
	cin.get();
}

// Writing to a file using the overloaded operator '<<' for a 'Dealership' object
void writingToAFile(Dealership& dealership) {
	std::ofstream outFile("Dealership.txt");

	// Write data to the file from the dealership object
	outFile << dealership;

	cout << "\n========================================================\n\n";
	cout << "    Data has been saved into the 'Dealership.txt' file\n\n";
	cout << "    Press ENTER to go back to the menu\n";
	cout << "\n========================================================\n";
	cin.ignore();
	cin.get();
}

// Reading data from a file using the overloaded operator '>>' for a 'Dealership' object
void enteringDataFromAFile(Dealership& dealership) {
	std::ifstream inFile("Dealership.txt");

	// Read data from the file into the dealership object
	inFile >> dealership;

	cout << "\n========================================================\n\n";
	cout << "    Data has been updated from the 'Dealership.txt' file\n\n";
	cout << "    Press ENTER to go back to the menu\n";
	cout << "\n========================================================\n";
	cin.ignore();
	cin.get();
}