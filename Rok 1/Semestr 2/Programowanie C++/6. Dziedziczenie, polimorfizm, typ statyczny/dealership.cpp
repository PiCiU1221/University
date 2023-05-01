#include "header.h"

using namespace std;

int Dealership::typeCounter = 0;

Dealership::Dealership() {}

Dealership::Dealership(const Dealership& other) {
	owners = other.owners;
	carListings = other.carListings;
	motorcycleListings = other.motorcycleListings;
}

Dealership::~Dealership() {
	for (auto owner : owners) {
		delete owner;
	}

	for (auto listing : carListings) {
		delete listing;
	}

	for (auto listing : motorcycleListings) {
		delete listing;
	}
}

void Dealership::addOwner(string name, string city, string ulica, int numer) {
	owners.push_back(new Owner(name, city, ulica, numer));
}

void Dealership::deleteOwner(int index) {
	if (index >= owners.size()) {
		cout << "Owner with this index doesn't exist\n";
		return;
	}

	for (int i = 0; i < carListings.size(); i++) {
		if (getListingOwnerIndexWithIndex(CAR, i) == index) {
			deleteListing(CAR, i);
		}
	}

	for (int i = 0; i < motorcycleListings.size(); i++) {
		if (getListingOwnerIndexWithIndex(MOTORCYCLE, i) == index) {
			deleteListing(MOTORCYCLE, i);
		}
	}

	delete owners[index];
	owners.erase(owners.begin() + index);
}

void Dealership::addCarListing(string brand, string model, int productionYear, string registrationNumber, int horsePower, string fuelType,
	string gearboxType, string driveType, int fuelConsumption, int trunkCapacity, int seatNumber, string bodyType,
	int ownerIndex, int price, bool sold) {
	carListings.push_back(new Listing(brand, model, productionYear, registrationNumber,
		horsePower, fuelType, gearboxType, driveType, fuelConsumption, trunkCapacity, seatNumber, bodyType, ownerIndex, price, sold));
}

void Dealership::addMotorcycleListing(std::string brand, std::string model, int productionYear, std::string registrationNumber, int horsePower, std::string fuelType,
	std::string gearboxType, std::string driveType, int fuelConsumption, int engineSize, int topSpeed, std::string type,
	std::string brakeType, int ownerIndex, int price, bool sold) {
	motorcycleListings.push_back(new Listing(brand, model, productionYear, registrationNumber,
		horsePower, fuelType, gearboxType, driveType, fuelConsumption, engineSize, topSpeed, type, brakeType, ownerIndex, price, sold));
}

void Dealership::deleteListing(vehicleType type, int index) {
	if (index > owners.size()) {
		cout << "Listing with this index doesn't exist\n";
		return;
	}

	if (type == CAR) {
		delete carListings[index];
		carListings.erase(carListings.begin() + index);
	}
	else {
		delete motorcycleListings[index];
		motorcycleListings.erase(motorcycleListings.begin() + index);
	}
}

// Getters definitions
size_t Dealership::getListingsSize(vehicleType type) const {
	if (type == CAR) {
		return carListings.size();
	}
	return motorcycleListings.size();
}

std::string Dealership::getBrandWithIndex(vehicleType type, int i) const {
	if (type == CAR) {
		return carListings[i]->getBrand();
	}
	return motorcycleListings[i]->getBrand();
}

std::string Dealership::getModelWithIndex(vehicleType type, int i) const {
	if (type == CAR) {
		return carListings[i]->getModel();
	}
	return motorcycleListings[i]->getModel();
}

int Dealership::getProductionYearWithIndex(vehicleType type, int i) const {
	if (type == CAR) {
		return carListings[i]->getProductionYear();
	}
	return motorcycleListings[i]->getProductionYear();
}

std::string Dealership::getRegistrationNumberWithIndex(vehicleType type, int i) const {
	if (type == CAR) {
		return carListings[i]->getRegistrationNumber();
	}
	return motorcycleListings[i]->getRegistrationNumber();
}

int Dealership::getHorsePowerWithIndex(vehicleType type, int i) const {
	if (type == CAR) {
		return carListings[i]->getHorsePower();
	}
	return motorcycleListings[i]->getHorsePower();
}

std::string Dealership::getFuelTypeWithIndex(vehicleType type, int i) const {
	if (type == CAR) {
		return carListings[i]->getFuelType();
	}
	return motorcycleListings[i]->getFuelType();
}

std::string Dealership::getGearboxTypeWithIndex(vehicleType type, int i) const {
	if (type == CAR) {
		return carListings[i]->getGearboxType();
	}
	return motorcycleListings[i]->getGearboxType();
}

std::string Dealership::getDriveTypeWithIndex(vehicleType type, int i) const {
	if (type == CAR) {
		return carListings[i]->getDriveType();
	}
	return motorcycleListings[i]->getDriveType();
}

int Dealership::getFuelConsumptionWithIndex(vehicleType type, int i) const {
	if (type == CAR) {
		return carListings[i]->getFuelConsumption();
	}
	return motorcycleListings[i]->getFuelConsumption();
}

int Dealership::getListingOwnerIndexWithIndex(vehicleType type, int i) const {
	if (type == CAR) {
		return carListings[i]->getOwnerIndex();
	}
	return motorcycleListings[i]->getOwnerIndex();
}

int Dealership::getListingPriceWithIndex(vehicleType type, int i) const {
	if (type == CAR) {
		return carListings[i]->getPrice();
	}
	return motorcycleListings[i]->getPrice();
}

bool Dealership::isSoldListing(vehicleType type, int i) const {
	if (type == CAR) {
		return carListings[i]->isSold();
	}
	return motorcycleListings[i]->isSold();
}

// Setters definitions
void Dealership::setBrandWithIndex(vehicleType type, std::string brand, int i) {
	if (type == CAR) {
		return carListings[i]->setBrand(brand);
	}
	return motorcycleListings[i]->setBrand(brand);
}

void Dealership::setModelWithIndex(vehicleType type, std::string model, int i) {
	if (type == CAR) {
		return carListings[i]->setModel(model);
	}
	return motorcycleListings[i]->setModel(model);
}

void Dealership::setProductionYearWithIndex(vehicleType type, int productionYear, int i) {
	if (type == CAR) {
		return carListings[i]->setProductionYear(productionYear);
	}
	return motorcycleListings[i]->setProductionYear(productionYear);
}

void Dealership::setRegistrationNumberWithIndex(vehicleType type, std::string registrationNumber, int i) {
	if (type == CAR) {
		return carListings[i]->setRegistrationNumber(registrationNumber);
	}
	return motorcycleListings[i]->setRegistrationNumber(registrationNumber);
}

void Dealership::setHorsePowerWithIndex(vehicleType type, int horsePower, int i) {
	if (type == CAR) {
		return carListings[i]->setHorsePower(horsePower);
	}
	return motorcycleListings[i]->setHorsePower(horsePower);
}

void Dealership::setFuelTypeWithIndex(vehicleType type, std::string fuelType, int i) {
	if (type == CAR) {
		return carListings[i]->setFuelType(fuelType);
	}
	return motorcycleListings[i]->setFuelType(fuelType);
}

void Dealership::setGearboxTypeWithIndex(vehicleType type, std::string gearboxType, int i) {
	if (type == CAR) {
		return carListings[i]->setGearboxType(gearboxType);
	}
	return motorcycleListings[i]->setGearboxType(gearboxType);
}

void Dealership::setDriveTypeWithIndex(vehicleType type, std::string driveType, int i) {
	if (type == CAR) {
		return carListings[i]->setDriveType(driveType);
	}
	return motorcycleListings[i]->setDriveType(driveType);
}

void Dealership::setFuelConsumptionWithIndex(vehicleType type, int fuelConsumption, int i) {
	if (type == CAR) {
		return carListings[i]->setFuelConsumption(fuelConsumption);
	}
	return motorcycleListings[i]->setFuelConsumption(fuelConsumption);
}

void Dealership::setPriceWithIndex(vehicleType type, int price, int i) {
	if (type == CAR) {
		return carListings[i]->setPrice(price);
	}
	return motorcycleListings[i]->setPrice(price);
}

void Dealership::setSoldWithIndex(vehicleType type, int i) {
	if (type == CAR) {
		return carListings[i]->setSold();
	}
	return motorcycleListings[i]->setSold();
}

void Dealership::displayListing(vehicleType type, int i) {
	if (type == CAR) {
		return carListings[i]->displayData();
	}
	return motorcycleListings[i]->displayData();
}

int Dealership::countOwnersListings(int index) const {
	int count = 0;
	for (int i = 0; i < getListingsSize(CAR); i++) {
		if (getListingOwnerIndexWithIndex(CAR, i) == index) {
			count++;
		}
	}
	for (int i = 0; i < getListingsSize(MOTORCYCLE); i++) {
		if (getListingOwnerIndexWithIndex(MOTORCYCLE, i) == index) {
			count++;
		}
	}
	return count;
}

// Overloaded operator '<<' of a 'Dealership' class
std::ostream& operator<<(std::ostream& out, const Dealership& dealership) {
	out << "\t" << "Number of owners: " << dealership.getOwnersSize()
		<< "\n\t" << "Number of car listings: " << dealership.getListingsSize(CAR)
		<< "\n\t" << "Number of motorcycle listings: " << dealership.getListingsSize(MOTORCYCLE)
		<< "\n\t" << "Number of all listings: " << dealership.getListingsSize(CAR) + dealership.getListingsSize(MOTORCYCLE) << std::endl;
	return out;
}

// Overloaded operator '<<' of a 'Dealership' class to write into file
std::ofstream& operator<<(std::ofstream& out, const Dealership& dealership) {
	out << dealership.getOwnersSize() << '\n';
	for (int i = 0; i < dealership.getOwnersSize(); i++) {
		out << dealership.getOwnerNameWithIndex(i) << '\n' << dealership.getOwnerCityWithIndex(i) << '\n' << dealership.getOwnerStreetWithIndex(i) << '\n' <<
			dealership.getOwnerNumberWithIndex(i) << '\n';
	}
	out << dealership.getListingsSize(CAR) << '\n';
	for (int i = 0; i < dealership.getListingsSize(CAR); i++) {
		out << dealership.getListingOwnerIndexWithIndex(CAR, i) << '\n';
		out << dealership.getBrandWithIndex(CAR, i) << '\n';
		out << dealership.getModelWithIndex(CAR, i) << '\n';
		out << dealership.getProductionYearWithIndex(CAR, i) << '\n';
		out << dealership.getRegistrationNumberWithIndex(CAR, i) << '\n';
		out << dealership.getHorsePowerWithIndex(CAR, i) << '\n';
		out << dealership.getFuelTypeWithIndex(CAR, i) << '\n';
		out << dealership.getGearboxTypeWithIndex(CAR, i) << '\n';
		out << dealership.getDriveTypeWithIndex(CAR, i) << '\n';
		out << dealership.getFuelConsumptionWithIndex(CAR, i) << '\n';
		out << dealership.getTrunkCapacityWithIndex(i) << '\n';
		out << dealership.getSeatNumberWithIndex(i) << '\n';
		out << dealership.getBodyTypeWithIndex(i) << '\n';
		out << dealership.getListingPriceWithIndex(CAR, i) << '\n';
		out << dealership.isSoldListing(CAR, i) << '\n';
	}
	out << dealership.getListingsSize(MOTORCYCLE) << '\n';
	for (int i = 0; i < dealership.getListingsSize(MOTORCYCLE); i++) {
		out << dealership.getListingOwnerIndexWithIndex(MOTORCYCLE, i) << '\n';
		out << dealership.getBrandWithIndex(MOTORCYCLE, i) << '\n';
		out << dealership.getModelWithIndex(MOTORCYCLE, i) << '\n';
		out << dealership.getProductionYearWithIndex(MOTORCYCLE, i) << '\n';
		out << dealership.getRegistrationNumberWithIndex(MOTORCYCLE, i) << '\n';
		out << dealership.getHorsePowerWithIndex(MOTORCYCLE, i) << '\n';
		out << dealership.getFuelTypeWithIndex(MOTORCYCLE, i) << '\n';
		out << dealership.getGearboxTypeWithIndex(MOTORCYCLE, i) << '\n';
		out << dealership.getDriveTypeWithIndex(MOTORCYCLE, i) << '\n';
		out << dealership.getFuelConsumptionWithIndex(MOTORCYCLE, i) << '\n';
		out << dealership.getEngineSizeWithIndex(i) << '\n';
		out << dealership.getTopSpeedWithIndex(i) << '\n';
		out << dealership.getTypeWithIndex(i) << '\n';
		out << dealership.getBrakeTypeWithIndex(i) << '\n';
		out << dealership.getListingPriceWithIndex(MOTORCYCLE, i) << '\n';
		out << dealership.isSoldListing(MOTORCYCLE, i) << '\n';
	}
	return out;
}

// Overloaded operator '>>' of a 'Dealership' class to get data from the file
std::ifstream& operator>>(std::ifstream& in, Dealership& dealership) {
	int ownersSize, carListingsSize, motorcycleListingsSize;
	std::string name, city, street, registrationNumber, brand, model, fuelType, gearboxType, driveType, bodyType, type, brakeType;
	int productionYear, horsePower, fuelConsumption, trunkCapacity, seatNumber, ownerIndex, number, price, engineSize, topSpeed;
	bool sold;

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
	in >> carListingsSize;

	// Read the car data and add them to the dealership as listings
	for (int i = 0; i < carListingsSize; i++) {
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
		in.ignore(); // Ignore the newline character
		in >> trunkCapacity;
		in.ignore(); // Ignore the newline character
		in >> seatNumber;
		in.ignore(); // Ignore the newline character
		std::getline(in, bodyType);
		in >> price;
		in.ignore(); // Ignore the newline character
		in >> sold;
		in.ignore(); // Ignore the newline character
		dealership.addCarListing(brand, model, productionYear, registrationNumber, horsePower,
			fuelType, gearboxType, driveType, fuelConsumption, trunkCapacity, seatNumber, bodyType, ownerIndex, price, sold);
	}

	// Read the number of listings
	in >> motorcycleListingsSize;

	// Read the motorcycle data and add them to the dealership as listings
	for (int i = 0; i < motorcycleListingsSize; i++) {
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
		in.ignore(); // Ignore the newline character
		in >> engineSize;
		in.ignore(); // Ignore the newline character
		in >> topSpeed;
		in.ignore(); // Ignore the newline character
		std::getline(in, type);
		std::getline(in, brakeType);
		in >> price;
		in.ignore(); // Ignore the newline character
		in >> sold;
		in.ignore(); // Ignore the newline character
		dealership.addMotorcycleListing(brand, model, productionYear, registrationNumber, horsePower,
			fuelType, gearboxType, driveType, fuelConsumption, engineSize, topSpeed, type, brakeType, ownerIndex, price, sold);
	}

	return in;
}

// Overloading operator '[]' of a 'Dealership' class
Listing* Dealership::operator [](const size_t k) {
	if (k < carListings.size()) {
		return carListings[k];
	}
	else {
		size_t motorcycleIndex = k - carListings.size();
		return motorcycleListings[motorcycleIndex];
	}
}

// Overloading operator '=' of a 'Dealership' class
Dealership& Dealership::operator=(const Dealership& right) {
	if (&right != this) {
		this->Dealership::~Dealership();
		this->Dealership::Dealership(right);
	}
	return *this;
}