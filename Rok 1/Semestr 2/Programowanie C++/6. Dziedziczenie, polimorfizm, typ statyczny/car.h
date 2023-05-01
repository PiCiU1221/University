#ifndef CAR_H
#define CAR_H
#pragma once

class Car : public Vehicle {
	int trunkCapacity = 0;
	int seatNumber = 0;
	std::string bodyType = "";

public:
	Car(std::string brand, std::string model, int productionYear, std::string registrationNumber,
		int horsePower, std::string fuelType, std::string gearboxType,
		std::string driveType, int fuelConsumption, int trunkCapacity, int seatNumber, std::string bodyType);

	int getTrunkCapacity() const { return trunkCapacity; }
	int getSeatNumber() const { return seatNumber; }
	std::string getBodyType() const { return bodyType; }

	void setTrunkCapacity(int trunkCapacity) { this->trunkCapacity = trunkCapacity; }
	void setSeatNumber(int seatNumber) { this->seatNumber = seatNumber; }
	void setBodyType(std::string bodyType) { this->bodyType = bodyType; }

	void displayData() const override;
};

#endif // CAR_H