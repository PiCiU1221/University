#include "../header.h"

using namespace std;

// MENU 8
//
// Function that displays all listings
void displayAllListings(Dealership& dealership) {
	vehicleType vehicleChoice = dealership.getChosenVehicleType();

	size_t listingsSize = dealership.getListingsSize(vehicleChoice);

	cout << "\n" << setfill('=') << setw(69) << "=\n";
	cout << "                         Active Listings" << endl;
	cout << "\n" << setfill('=') << setw(70) << "=\n\n";
	for (int i = 0; i < listingsSize; i++) {
		if (dealership.isSoldListing(vehicleChoice, i) == false) {
			cout << left << setw(29 - to_string(i + 1).size()) << setfill('=') << "" << " " << i + 1 << ". Listing " << right << setw(28) << setfill('=') << "" << endl;

			dealership.displayListing(vehicleChoice, i);
			cout << "                         Owner: " << dealership.getOwnerNameWithIndex(dealership.getListingOwnerIndexWithIndex(vehicleChoice, i)) << endl << endl << endl;
		}
	}

	cout << "\n" << setfill('=') << setw(69) << "=\n";
	cout << "                        Expired Listings" << endl;
	cout << "\n" << setfill('=') << setw(70) << "=\n\n";
	for (int i = 0; i < listingsSize; i++) {
		if (dealership.isSoldListing(vehicleChoice, i) == true) {
			cout << left << setw(29 - to_string(i + 1).size()) << setfill('=') << "" << " " << i + 1 << ". Listing " << right << setw(28) << setfill('=') << "" << endl;

			dealership.displayListing(vehicleChoice, i);
			cout << "                         Owner: " << dealership.getOwnerNameWithIndex(dealership.getListingOwnerIndexWithIndex(vehicleChoice, i)) << endl << endl << endl;
		}
	}

	displayPressEnterToMenu();
}