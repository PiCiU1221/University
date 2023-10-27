#include "header.h"

using namespace std;

Motorcycle::Motorcycle(std::string brand, std::string model, int productionYear, std::string registrationNumber,
	int horsePower, std::string fuelType, std::string gearboxType, std::string driveType,
	int fuelConsumption, int engineSize, int topSpeed, std::string type, std::string brakeType)
	: Vehicle(brand, model, productionYear, registrationNumber, horsePower, fuelType, gearboxType, driveType, fuelConsumption),
	engineSize(engineSize),
	topSpeed(topSpeed),
	type(type),
	brakeType(brakeType)
{
}

void Motorcycle::displayData() const {
	cout << "                         Brand: " << brand << endl;
	cout << "                         Model: " << model << endl;
	cout << "               Production year: " << productionYear << endl;
	cout << "           Registration number: " << registrationNumber << endl;
	cout << "                   Horse power: " << horsePower << endl;
	cout << "                     Fuel type: " << fuelType << endl;
	cout << "                  Gearbox type: " << gearboxType << endl;
	cout << "                    Drive type: " << driveType << endl;
	cout << "              Fuel consumption: " << fuelConsumption << endl;
	cout << "                   Engine Size: " << engineSize << endl;
	cout << "                     Top Speed: " << topSpeed << endl;
	cout << "                          Type: " << type << endl;
	cout << "                    Brake Type: " << brakeType << endl;
}