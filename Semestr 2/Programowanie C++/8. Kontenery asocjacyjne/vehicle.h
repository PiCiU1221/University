#ifndef VEHICLE_H
#define VEHICLE_H
#pragma once

class Vehicle {
protected:
	std::string brand = "";
	std::string model = "";
	int productionYear = 0;
	std::string registrationNumber = "";
	int horsePower = 0;
	std::string fuelType = "";
	std::string gearboxType = "";
	std::string driveType = "";
	int fuelConsumption = 0;
public:
	// default constructor
	Vehicle();

	virtual ~Vehicle();

	Vehicle(const Vehicle& other);

	// constructor
	Vehicle(std::string brand, std::string model, int productionYear, std::string registrationNumber,
		int horsePower, std::string fuelType, std::string gearboxType,
		std::string driveType, int fuelConsumption);

	virtual void displayData() const = 0;

	// Virtual functions for the derived classes
	// Car
	virtual int getTrunkCapacity() const { return 0; }
	virtual int getSeatNumber() const { return 0; }
	virtual std::string getBodyType() const { return ""; }

	virtual void setTrunkCapacity(int trunkCapacity) {}
	virtual void setSeatNumber(int seatNumber) {}
	virtual void setBodyType(std::string bodyType) {}

	// Motorcycle
	virtual int getEngineSize() const { return 0; }
	virtual int getTopSpeed() const { return 0; }
	virtual std::string getType() const { return ""; }
	virtual std::string getBrakeType() const { return ""; }

	virtual void setEngineSize(int engineSize) {}
	virtual void setTopSpeed(int topSpeed) {}
	virtual void setType(std::string type) {}
	virtual void setBrakeType(std::string brakeType) {}

	friend class Listing;
};

#endif // VEHICLE_H