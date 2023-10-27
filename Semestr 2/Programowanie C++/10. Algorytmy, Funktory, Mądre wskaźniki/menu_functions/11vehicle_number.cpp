#include "../header.h"

using namespace std;

// MENU 11
//
// Number of vehicles from specified city

void vehicleNumberFromCities(Dealership& dealership) {
	size_t carSize = dealership.getListingsSize(CAR);
	size_t motorcycleSize = dealership.getListingsSize(MOTORCYCLE);

	list<string> registrationNumberList;

	for (int i = 0; i < carSize; i++) {
		registrationNumberList.push_back(dealership.getRegistrationNumberWithIndex(CAR, i));
	}

	for (int i = 0; i < motorcycleSize; i++) {
		registrationNumberList.push_back(dealership.getRegistrationNumberWithIndex(MOTORCYCLE, i));
	}

	cout << "Enter the prefix of the registration number below. For example: 'ZST'" << endl;
	string prefix;
	cin >> prefix;

	auto partitionPredicate = [prefix](const string& regNumber) {
		return regNumber.substr(0, prefix.size()) == prefix;
	};

	// Partition the list based on the given predicate
	auto partitionIter = partition(registrationNumberList.begin(),
		registrationNumberList.end(),
		partitionPredicate);

	// Count the registration numbers matching the prefix
	__int64 count = distance(registrationNumberList.begin(), partitionIter);

	// Print the partitioned list
	cout << endl << prefix << " registration numbers:\n\n";
	for (auto it = registrationNumberList.begin(); it != partitionIter; ++it) {
		cout << *it << endl;
	}

	cout << "\nNumber of specified registration numbers: " << count << endl;

	cout << "\n" << setfill('=') << setw(68) << "=\n\n";
	cout << "    Press ENTER to go back to the menu\n";
	cout << "\n" << setfill('=') << setw(67) << "=\n";

	cin.ignore();
	cin.get();
}