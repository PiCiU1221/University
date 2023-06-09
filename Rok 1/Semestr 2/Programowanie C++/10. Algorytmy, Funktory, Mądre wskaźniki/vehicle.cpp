#include "header.h"

using namespace std;

// Define the default constructor for the 'Car' class within the Listing class
Vehicle::Vehicle() = default;

Vehicle::~Vehicle() = default;

// Constructor of the 'Car' class using provided variables
Vehicle::Vehicle(std::string brand, std::string model, int productionYear, std::string registrationNumber,
	int horsePower, std::string fuelType, std::string gearboxType,
	std::string driveType, int fuelConsumption)
	: brand(brand), model(model), productionYear(productionYear),
	registrationNumber(registrationNumber), horsePower(horsePower),
	fuelType(fuelType), gearboxType(gearboxType),
	driveType(driveType), fuelConsumption(fuelConsumption) {
}

// Copy constructor of a 'Car' object inside the Listing class
Vehicle::Vehicle(const Vehicle& other)
	: brand(other.brand), model(other.model), productionYear(other.productionYear),
	registrationNumber(other.registrationNumber), horsePower(other.horsePower),
	fuelType(other.fuelType), gearboxType(other.gearboxType),
	driveType(other.driveType), fuelConsumption(other.fuelConsumption) {
}