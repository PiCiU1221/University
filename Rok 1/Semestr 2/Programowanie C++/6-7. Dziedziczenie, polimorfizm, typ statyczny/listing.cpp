#include "header.h"

using namespace std;

Listing::Listing(std::string brand, std::string model, int productionYear, std::string registrationNumber, int horsePower, std::string fuelType,
	std::string gearboxType, std::string driveType, int fuelConsumption, int trunkCapacity, int seatNumber, std::string bodyType,
	int ownerIndex, int price, bool sold) : ownerIndex(ownerIndex), price(price), sold(sold) {
	vehicle_ = new Car(brand, model, productionYear, registrationNumber, horsePower, fuelType, gearboxType, driveType, fuelConsumption,
		trunkCapacity, seatNumber, bodyType);
}

Listing::Listing(std::string brand, std::string model, int productionYear, std::string registrationNumber, int horsePower, std::string fuelType,
	std::string gearboxType, std::string driveType, int fuelConsumption, int engineSize, int topSpeed, std::string type, std::string brakeType,
	int ownerIndex, int price, bool sold) : ownerIndex(ownerIndex), price(price), sold(sold) {
	vehicle_ = new Motorcycle(brand, model, productionYear, registrationNumber, horsePower, fuelType, gearboxType, driveType, fuelConsumption,
		engineSize, topSpeed, type, brakeType);
}

Listing::~Listing() {
	delete vehicle_;
	vehicle_ = nullptr;
};

void Listing::displayData() const {
	vehicle_->displayData();
	cout << setfill('-') << setw(68) << "-" << endl;
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