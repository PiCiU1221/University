#include "../header.h"

using namespace std;

// MENU 3
//
// Function that deletes the chosen owner from the list
void deleteOwnerByUser(Dealership& dealership) {
	int indexToDelete = -1;

	// Vector that holds the displayed indexes that will be useful to decide if the index from the input is correct
	vector<int> searchedIndexes;

	// We are checking the variable 'checker' if the array is not empty
	auto checker = searchedIndexes.begin();

	// Bool variable to make sure we would display the top of the table once
	bool flag = false;

	size_t ownersSize = dealership.getOwnersSize();
	for (int i = 0; i < ownersSize; i++) {
		searchedIndexes.push_back(i);

		if (flag == false) {
			cout << "\n| Index |     Name     | Num of listings |    City   |" << endl;
			cout << "------------------------------------------------------" << endl;
		}

		cout << "| " << i << right << setfill(' ') << setw(5 - to_string(i).size()) << "" << " | ";

		string ownerName = dealership.getOwnerNameWithIndex(i);
		cout << ownerName << right << setfill(' ') << setw(12 - ownerName.size()) << "" << " | ";

		int ownerListings = dealership.countOwnersListings(i);
		cout << ownerListings << right << setfill(' ') << setw(15 - to_string(ownerListings).size()) << "" << " | ";

		string ownerCity = dealership.getOwnerCityWithIndex(i);
		cout << ownerCity << right << setfill(' ') << setw(9 - ownerCity.size()) << "" << " |\n";

		flag = true;
	}
	if (flag == false) {
		cout << "\n" << setfill('=') << setw(68) << "=\n\n";
		cout << "    Owners list is empty!\n\n";
		cout << "    Press ENTER to go back to the menu\n";
		cout << "\n" << setfill('=') << setw(67) << "=\n";
		cin.ignore();
		cin.get();
	}
	else {
		do {
			cout << "\n    Enter an owners index to delete: ";
			cin >> indexToDelete;
			// Checker variable stores information whether the entered index has been previously searched and displayed
			checker = find(searchedIndexes.begin(), searchedIndexes.end(), indexToDelete);

			if (checker == searchedIndexes.end()) {
				cout << "\n    Chosen index doesn't exist";
				cout << "\n    Try again\n";
			}
			// Repeat until the correct index is entered
		} while (checker == searchedIndexes.end());

		string choice;

		do {
			cout << "\n" << setfill('=') << setw(68) << "=\n\n";
			cout << "    Are you sure you want to delete this owner?\n\n";
			cout << "    Enter [Y/N]\n";
			cout << "\n" << setfill('=') << setw(67) << "=\n";
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

			cout << "\n" << setfill('=') << setw(68) << "=\n\n";
			cout << "    Owner with the name: " << deletedOwnerName << " was deleted with their " << deletedOwnerListings << " listings\n\n";
			cout << "    Press ENTER to go back to the menu\n";
			cout << "\n" << setfill('=') << setw(67) << "=\n";
			cin.ignore();
			cin.get();
		}
	}
}