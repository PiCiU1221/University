#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H
#pragma once

class Motorcycle : public Vehicle {
	int engineSize = 0;
	int topSpeed = 0;
	std::string type = "";
	std::string brakeType = "";

public:
	Motorcycle(std::string brand, std::string model, int productionYear, std::string registrationNumber,
		int horsePower, std::string fuelType, std::string gearboxType, std::string driveType,
		int fuelConsumption, int engineSize, int topSpeed, std::string type, std::string brakeType);

	int getEngineSize() const { return engineSize; }
	int getTopSpeed() const { return topSpeed; }
	std::string getType() const { return type; }
	std::string getBrakeType() const { return brakeType; }

	void setEngineSize(int engineSize) { this->engineSize = engineSize; }
	void setTopSpeed(int topSpeed) { this->topSpeed = topSpeed; }
	void setType(std::string type) { this->type = type; }
	void setBrakeType(std::string brakeType) { this->brakeType = brakeType; }

	void displayData() const override;
};

#endif // MOTORCYCLE_H
