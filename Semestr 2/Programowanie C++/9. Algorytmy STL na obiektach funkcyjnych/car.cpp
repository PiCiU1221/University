#include "header.h"

using namespace std;

Car::Car(std::string brand, std::string model, int productionYear, std::string registrationNumber,
	int horsePower, std::string fuelType, std::string gearboxType,
	std::string driveType, int fuelConsumption, int trunkCapacity, int seatNumber, std::string bodyType)
	: Vehicle(brand, model, productionYear, registrationNumber, horsePower, fuelType, gearboxType, driveType, fuelConsumption),
	trunkCapacity(trunkCapacity), seatNumber(seatNumber), bodyType(bodyType) {
}

void Car::displayData() const {
	cout << "                         Brand: " << brand << endl;
	cout << "                         Model: " << model << endl;
	cout << "               Production year: " << productionYear << endl;
	cout << "           Registration number: " << registrationNumber << endl;
	cout << "                   Horse power: " << horsePower << endl;
	cout << "                     Fuel type: " << fuelType << endl;
	cout << "                  Gearbox type: " << gearboxType << endl;
	cout << "                    Drive type: " << driveType << endl;
	cout << "              Fuel consumption: " << fuelConsumption << endl;
	cout << "                Trunk Capacity: " << trunkCapacity << endl;
	cout << "                     Body Type: " << bodyType << endl;
	cout << "                   Seat Number: " << seatNumber << endl;
}