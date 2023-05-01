#include "../header.h"

using namespace std;

// MENU 1
//
// Function to randomly generate 'Owner' and 'Listing' objects with data and add them to the main 'dealership' object
void generateRandomizedOwnersAndListings(Dealership& dealership) {
	int randomNumberOfOwners = generateInteger(5, 10);
	string randomName = "";

	// Loop to generate owners with random data
	for (int i = 0; i < randomNumberOfOwners; i++) {
		randomName = name[generateInteger(0, 9)] + to_string(generateInteger(70, 99));
		dealership.addOwner(randomName, city[generateInteger(0, 3)], street[generateInteger(0, 3)], generateInteger(1, 99));
	}

	int randomNumberOfCarListings = generateInteger(5, 10);

	// Loop to generate cars with random data
	for (int i = 0; i < randomNumberOfCarListings; i++) {
		vehicleType type = CAR;
		int randomBrand = generateInteger(0, 4);
		// Use static_cast to ensure that the compiler can evaluate the difference between the two integers at the runtime
		int randomOwner = generateInteger(0, static_cast<int>(dealership.getOwnersSize()) - 1);

		// Use a dealership object method to add a new car listing using randomized values from the arrays visible in the content.cpp file
		dealership.addCarListing(carBrand[randomBrand], carModel[randomBrand][generateInteger(0, 2)], generateInteger(1995, 2023),
			plate[generateInteger(0, 3)] + " " + to_string(generateInteger(10000, 99999)), generateInteger(70, 250), fuelType[generateInteger(0, 2)],
			gearboxType[generateInteger(0, 1)], driveType[generateInteger(0, 1)], generateInteger(5, 12), generateInteger(250, 600),
			generateInteger(2, 5), bodyType[generateInteger(0, 6)], randomOwner, generateInteger(5000, 99999), generateInteger(0, 1));
	}

	int randomNumberOfMotorcycleListings = generateInteger(5, 10);

	// Loop to generate motorcycles with random data
	for (int i = 0; i < randomNumberOfMotorcycleListings; i++) {
		vehicleType type = MOTORCYCLE;
		int randomBrand = generateInteger(0, 4);
		int randomOwner = generateInteger(0, static_cast<int>(dealership.getOwnersSize()) - 1);

		dealership.addMotorcycleListing(motorcycleBrand[randomBrand], motorcycleModel[randomBrand][generateInteger(0, 2)], generateInteger(1995, 2023),
			plate[generateInteger(0, 3)] + " " + to_string(generateInteger(10000, 99999)), generateInteger(70, 250), fuelType[generateInteger(0, 2)],
			gearboxType[generateInteger(0, 1)], driveType[generateInteger(0, 1)], generateInteger(2, 7), generateInteger(250, 1000),
			generateInteger(150, 300), motorcycleType[generateInteger(0, 4)], brakeType[generateInteger(0, 1)], randomOwner, generateInteger(5000, 99999),
			generateInteger(0, 1));
	}

	cout << "\n" << setfill('=') << setw(68) << "=\n\n";
	cout << "    Generated " << randomNumberOfOwners << " owners and " << randomNumberOfCarListings + randomNumberOfMotorcycleListings << " listings" << endl;
	cout << "\n    Press ENTER to go back to the menu\n";
	cout << "\n" << setfill('=') << setw(68) << "=\n\n";
	cin.ignore();
	cin.get();
}