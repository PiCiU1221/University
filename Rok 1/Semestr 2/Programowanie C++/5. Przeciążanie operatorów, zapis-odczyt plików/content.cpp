#include "header.h"

using namespace std;

/*
	Piotr Pietrusewicz 53828 120A
	West Pomeranian University of Technology
	Theme: Car Dealearship

	File contains the definitions of the class methods and the arrays used to randomly generate data
*/

// These lines of code initialize several arrays of strings that will be used to generate random data for a car dealership simulation
string name[10] = { "Piotr", "Marcin", "Adam", "Kamil", "Hubert", "Mateusz", "Krzysztof", "Jakub", "Grzegorz", "Kacper" };
string brand[5] = { "Audi", "BMW", "Skoda", "Volkswagen", "Mercedes" };
string model[5][3] = { { "A4", "A6", "A7" }, { "Series 3", "X6", "Z4"}, { "Octavia", "Fabia", "Superb"}, { "Passat", "Golf", "Touran"}, {"A-Class", "GLC", "CLA" } };
string plate[4] = { "ZST", "ZS", "ZCH", "ZPY" };
string fuelType[3] = { "Petrol", "Diesel", "Petrol + LPG" };
string gearboxType[2] = { "Manual", "Automatic" };
string driveType[3] = { "Front", "Back", "All Wheel Drive" };
string city[4] = { "Stargard", "Szczecin", "Choszczno", "Pyrzyce" };
string ulica[4] = { "Wyszyñskiego", "Niepodleg³oœci", "Czarnieckiego", "3 Maja" };

// Function generates a random integer between 'from' and 'to'
int generateInteger(int from, int to) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(from, to);
	return dis(gen);
}

// Function counts the amount of numbers that the provided integer has
int countNumbers(int number) {
	int count = 0;

	if (number == 0) {
		return 1;
	}

	while (number != 0) {
		number /= 10;
		count++;
	}
	return count;
}

// Define the default constructor for the 'Car' class within the Listing class
Listing::Car::Car() = default;

// Constructor of the 'Car' class using provided variables
Listing::Car::Car(std::string brand, std::string model, int productionYear, std::string registrationNumber,
	int horsePower, std::string fuelType, std::string gearboxType,
	std::string driveType, int fuelConsumption)
	: brand(brand), model(model), productionYear(productionYear),
	registrationNumber(registrationNumber), horsePower(horsePower),
	fuelType(fuelType), gearboxType(gearboxType),
	driveType(driveType), fuelConsumption(fuelConsumption) {
}

// Copy constructor of a 'Car' object inside the Listing class
Listing::Car::Car(const Car& other)
	: brand(other.brand), model(other.model), productionYear(other.productionYear),
	registrationNumber(other.registrationNumber), horsePower(other.horsePower),
	fuelType(other.fuelType), gearboxType(other.gearboxType),
	driveType(other.driveType), fuelConsumption(other.fuelConsumption) {
}

Owner::Owner(const std::string name, std::string city, std::string street, int number)
	: name(name), adress(city, street, number) {
}

Owner::Owner(std::string city, std::string street, int number)
	: name("placeHolder"), adress(city, street, number) {
}

// Copy constructor of an 'Owner' class
Owner::Owner(const Owner& other)
	: name(other.name), adress(other.adress) {
}

Owner::~Owner() = default;

// Overloaded operator '=' of an 'Owner' class
Owner& Owner::operator=(const Owner& right) {
	if (&right != this) {
		this->Owner::~Owner();
		this->Owner::Owner(right);
	}
	return *this;
}

// Overloaded operator '>>' of an 'Owner' class
std::istream& operator>>(std::istream& wejscie, Owner& t) {
	wejscie >> t.name;

	return wejscie;
}

Listing::Listing() : car_(Car()), ownerIndex(0), price(0) {};

Listing::Listing(std::string brand, std::string model, int productionYear, std::string registrationNumber, int horsePower,
	std::string fuelType, std::string gearboxType, std::string driveType, int fuelConsumption, int ownerIndex, int price)
	: car_(brand, model, productionYear, registrationNumber, horsePower, fuelType, gearboxType, driveType, fuelConsumption),
	ownerIndex(ownerIndex), price(price) {
}

Listing::~Listing() = default;

void Listing::displayData() const {
	cout << "                         Brand: " << getBrand() << endl;
	cout << "                         Model: " << getModel() << endl;
	cout << "               Production year: " << getProductionYear() << endl;
	cout << "           Registration number: " << getRegistrationNumber() << endl;
	cout << "                   Horse power: " << getHorsePower() << endl;
	cout << "                     Fuel type: " << getFuelType() << endl;
	cout << "                  Gearbox type: " << getGearboxType() << endl;
	cout << "                    Drive type: " << getDriveType() << endl;
	cout << "              Fuel consumption: " << getFuelConsumption() << endl;
	cout << "---------------------------------------------------------------" << endl;
	cout << "                         Price: " << getPrice() << endl;
}

// Overloaded operator '=' of a 'Listing' class
Listing& Listing::operator=(const Listing& right) {
	if (&right != this) {
		this->Listing::~Listing();
		this->Listing::Listing(right);
	}
	return *this;
}

Dealership::Dealership() : owners(nullptr), ownersSize(0), listings(nullptr), listingsSize(0) {}

Dealership::Dealership(const Dealership& other) : ownersSize(other.ownersSize), listingsSize(other.listingsSize) {
	owners = new Owner * [ownersSize];
	for (int i = 0; i < ownersSize; i++) {
		owners[i] = new Owner(*(other.owners[i]));
	}

	listings = new Listing * [listingsSize];
	for (int i = 0; i < listingsSize; i++) {
		listings[i] = new Listing(*(other.listings[i]));
	}
}

Dealership::~Dealership() {
	for (int i = 0; i < ownersSize; i++) {
		delete owners[i];
	}
	delete[] owners;

	for (int i = 0; i < listingsSize; i++) {
		delete listings[i];
	}
	delete[] listings;
}

void Dealership::addOwner(string name, string city, string ulica, int numer) {
	Owner** newOwner = new Owner * [ownersSize + 1];

	for (int i = 0; i < ownersSize; i++) {
		newOwner[i] = owners[i];
	}

	newOwner[ownersSize] = new Owner(name, city, ulica, numer);

	delete[] owners;

	owners = newOwner;

	ownersSize++;
}

void Dealership::deleteOwner(int index) {
	for (int i = 0; i < listingsSize; i++) {
		if (getListingOwnerIndexWithIndex(i) == index) {
			deleteListing(i);
		}
	}

	if (index > ownersSize) {
		cout << "Owner with this index doesn't exist\n";
		return;
	}

	delete owners[index];
	for (int i = index; i < ownersSize - 1; i++) {
		owners[i] = owners[i + 1];
	}

	owners[ownersSize - 1] = nullptr;
	ownersSize--;
}

void Dealership::addListing(std::string brand, std::string model, int productionYear, std::string registrationNumber, int horsePower,
	std::string fuelType, std::string gearboxType, std::string driveType, int fuelConsumption, int ownerIndex, int price) {
	Listing** newOgloszenia = new Listing * [listingsSize + 1];

	for (int i = 0; i < listingsSize; i++) {
		newOgloszenia[i] = listings[i];
	}

	newOgloszenia[listingsSize] = new Listing(brand, model, productionYear, registrationNumber,
		horsePower, fuelType, gearboxType, driveType, fuelConsumption, ownerIndex, price);

	delete[] listings;

	listings = newOgloszenia;

	listingsSize++;
}

void Dealership::deleteListing(int index) {
	if (index > ownersSize) {
		cout << "Listing with this index doesn't exist\n";
		return;
	}

	delete listings[index];
	for (int i = index; i < listingsSize - 1; i++) {
		listings[i] = listings[i + 1];
	}

	listings[listingsSize - 1] = nullptr;
	listingsSize--;
}

int Dealership::countOwnersListings(int index) const {
	int count = 0;
	for (int i = 0; i < listingsSize; i++) {
		if (getListingOwnerIndexWithIndex(i) == index) {
			count++;
		}
	}
	return count;
}

// Overloaded operator '<<' of a 'Dealership' class
std::ostream& operator<<(std::ostream& out, const Dealership& dealership) {
	out << "\t" << "Number of owners: " << dealership.ownersSize << "\n\t" << "Number of listings: " << dealership.listingsSize << std::endl;
	return out;
}

// Overloaded operator '<<' of a 'Dealership' class to write into file
std::ofstream& operator<<(std::ofstream& out, const Dealership& dealership) {
	out << dealership.ownersSize << '\n';
	for (int i = 0; i < dealership.ownersSize; i++) {
		out << dealership.getOwnerNameWithIndex(i) << '\n' << dealership.getOwnerCityWithIndex(i) << '\n' << dealership.getOwnerStreetWithIndex(i) << '\n' <<
			dealership.getOwnerNumberWithIndex(i) << '\n';
	}
	out << dealership.listingsSize << '\n';
	for (int i = 0; i < dealership.listingsSize; i++) {
		out << dealership.getListingOwnerIndexWithIndex(i) << '\n';
		out << dealership.getBrandWithIndex(i) << '\n';
		out << dealership.getModelWithIndex(i) << '\n';
		out << dealership.getProductionYearWithIndex(i) << '\n';
		out << dealership.getRegistrationNumberWithIndex(i) << '\n';
		out << dealership.getHorsePowerWithIndex(i) << '\n';
		out << dealership.getFuelTypeWithIndex(i) << '\n';
		out << dealership.getGearboxTypeWithIndex(i) << '\n';
		out << dealership.getDriveTypeWithIndex(i) << '\n';
		out << dealership.getFuelConsumptionWithIndex(i) << '\n';
		out << dealership.getListingPriceWithIndex(i) << '\n';
	}
	return out;
}

// Overloaded operator '>>' of a 'Dealership' class to get data from the file
std::ifstream& operator>>(std::ifstream& in, Dealership& dealership) {
	int ownersSize, listingsSize;
	std::string name, city, street, registrationNumber, brand, model, fuelType, gearboxType, driveType;
	int productionYear, horsePower, fuelConsumption, ownerIndex, number;
	int price;

	// Read the number of owners
	in >> ownersSize;
	in.ignore(); // Ignore the newline character

	// Read the owner data and add them to the dealership
	for (int i = 0; i < ownersSize; i++) {
		std::getline(in, name);
		std::getline(in, city);
		std::getline(in, street);
		in >> number;
		in.ignore(); // Ignore the newline character
		dealership.addOwner(name, city, street, number);
	}

	// Read the number of listings
	in >> listingsSize;

	// Read the car data and add them to the dealership as listings
	for (int i = 0; i < listingsSize; i++) {
		in >> ownerIndex;
		in.ignore(); // Ignore the newline character
		std::getline(in, brand);
		std::getline(in, model);
		in >> productionYear;
		in.ignore(); // Ignore the newline character
		std::getline(in, registrationNumber);
		in >> horsePower;
		in.ignore();
		std::getline(in, fuelType);
		std::getline(in, gearboxType);
		std::getline(in, driveType);
		in >> fuelConsumption;
		in >> price;
		in.ignore(); // Ignore the newline character
		dealership.addListing(brand, model, productionYear, registrationNumber, horsePower,
			fuelType, gearboxType, driveType, fuelConsumption, ownerIndex, price);
	}

	return in;
}

// Overloading operator '[]' of a 'Dealership' class
Listing* Dealership::operator [](const size_t k) {
	return listings[k];
}

// Overloading operator '=' of a 'Dealership' class
Dealership& Dealership::operator=(const Dealership& right) {
	if (&right != this) {
		this->Dealership::~Dealership();
		this->Dealership::Dealership(right);
	}
	return *this;
}