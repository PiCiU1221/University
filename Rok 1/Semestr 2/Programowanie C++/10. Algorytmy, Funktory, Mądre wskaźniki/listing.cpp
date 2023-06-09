#include "header.h"

using namespace std;

Listing::Listing(std::string brand, std::string model, int productionYear, std::string registrationNumber, int horsePower, std::string fuelType,
	std::string gearboxType, std::string driveType, int fuelConsumption, int trunkCapacity, int seatNumber, std::string bodyType,
	string ownerName, int price, bool sold) : ownerName(ownerName), price(price), sold(sold) {
	vehicle_ = make_unique<Car>(brand, model, productionYear, registrationNumber, horsePower, fuelType, gearboxType, driveType, fuelConsumption,
		trunkCapacity, seatNumber, bodyType);
}

Listing::Listing(std::string brand, std::string model, int productionYear, std::string registrationNumber, int horsePower, std::string fuelType,
	std::string gearboxType, std::string driveType, int fuelConsumption, int engineSize, int topSpeed, std::string type, std::string brakeType,
	string ownerName, int price, bool sold) : ownerName(ownerName), price(price), sold(sold) {
	vehicle_ = make_unique<Motorcycle>(brand, model, productionYear, registrationNumber, horsePower, fuelType, gearboxType, driveType, fuelConsumption,
		engineSize, topSpeed, type, brakeType);
}

void Listing::displayData() const {
	vehicle_->displayData();
	cout << setfill('-') << setw(68) << "-" << endl;
	cout << "                         Price: " << getPrice() << endl;
}

// Overloaded operator '=' of a 'Listing' class
Listing& Listing::operator=(const Listing& right) {
	if (&right != this) {
		ownerName = right.ownerName;
		price = right.price;
		sold = right.sold;

		// Check the type of the right-hand side object's vehicle_
		// dynamic_cast is used to change the variables types in the runtime
		if (dynamic_cast<Car*>(right.vehicle_.get())) {
			vehicle_ = make_unique<Car>(*dynamic_cast<Car*>(right.vehicle_.get()));
		}
		else if (dynamic_cast<Motorcycle*>(right.vehicle_.get())) {
			vehicle_ = make_unique<Motorcycle>(*dynamic_cast<Motorcycle*>(right.vehicle_.get()));
		}
	}
	return *this;
}