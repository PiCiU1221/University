#include "../header.h"

using namespace std;

// MENU 4
//
// Function that displays the Owners objects data
void displayOwners(Dealership& dealership) {
	cout << "\n| Index |     Name     | Num of listings |    City   |" << endl;
	cout << "------------------------------------------------------" << endl;

	size_t ownersSize = dealership.getOwnersSize();
	for (int i = 0; i < ownersSize; i++) {
		cout << "| " << i << right << setfill(' ') << setw(5 - to_string(i).size()) << "" << " | ";

		string ownerName = dealership.getOwnerNameWithIndex(i);
		cout << ownerName << right << setfill(' ') << setw(12 - ownerName.size()) << "" << " | ";

		int ownerListings = dealership.countOwnersListings(i);
		cout << ownerListings << right << setfill(' ') << setw(15 - to_string(ownerListings).size()) << "" << " | ";

		string ownerCity = dealership.getOwnerCityWithIndex(i);
		cout << ownerCity << right << setfill(' ') << setw(9 - ownerCity.size()) << "" << " |\n";
	}

	displayPressEnterToMenu();
}