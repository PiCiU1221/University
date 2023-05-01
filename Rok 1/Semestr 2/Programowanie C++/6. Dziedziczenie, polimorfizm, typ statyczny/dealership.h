#ifndef DEALERSHIP_H
#define DEALERSHIP_H
#pragma once

// Custom data type to handle two vehicle types that the program has. It makes it more readable and easier to maintain
enum vehicleType {
	CAR,
	MOTORCYCLE
};

class Dealership {
	std::vector<Owner*>owners;
	std::vector<Listing*> carListings;
	std::vector<Listing*> motorcycleListings;
	vehicleType typeChoice = CAR;
	static int typeCounter;
public:
	Dealership();
	Dealership(const Dealership& other);
	~Dealership();

	// Methods that are using arrays of pointers
	void addOwner(std::string name, std::string city, std::string ulica, int numer);
	void deleteOwner(int index);

	void addCarListing(std::string brand, std::string model, int productionYear, std::string registrationNumber, int horsePower, std::string fuelType,
		std::string gearboxType, std::string driveType, int fuelConsumption, int trunkCapacity, int seatNumber, std::string bodyType,
		int ownerIndex, int price, bool sold);
	void addMotorcycleListing(std::string brand, std::string model, int productionYear, std::string registrationNumber, int horsePower, std::string fuelType,
		std::string gearboxType, std::string driveType, int fuelConsumption, int engineSize, int topSpeed, std::string type,
		std::string brakeType, int ownerIndex, int price, bool sold);

	void deleteListing(vehicleType type, int index);

	// Getters
	size_t getOwnersSize() const { return owners.size(); }
	size_t getListingsSize(vehicleType type) const;
	vehicleType getChosenVehicleType() const { return typeChoice; }
	int getTypeCounter() { return typeCounter; }

	std::string getOwnerNameWithIndex(int i) const { return owners[i]->getName(); }
	std::string getOwnerCityWithIndex(int i) const { return owners[i]->getCity(); }
	std::string getOwnerStreetWithIndex(int i) const { return owners[i]->getStreet(); }
	int getOwnerNumberWithIndex(int i) const { return owners[i]->getNumber(); }

	std::string getBrandWithIndex(vehicleType type, int i) const;
	std::string getModelWithIndex(vehicleType type, int i) const;
	int getProductionYearWithIndex(vehicleType type, int i) const;
	std::string getRegistrationNumberWithIndex(vehicleType type, int i) const;
	int getHorsePowerWithIndex(vehicleType type, int i) const;
	std::string getFuelTypeWithIndex(vehicleType type, int i) const;
	std::string getGearboxTypeWithIndex(vehicleType type, int i) const;
	std::string getDriveTypeWithIndex(vehicleType type, int i) const;
	int getFuelConsumptionWithIndex(vehicleType type, int i) const;

	// Car getters
	int getTrunkCapacityWithIndex(int i) const { return carListings[i]->getTrunkCapacity(); }
	int getSeatNumberWithIndex(int i) const { return carListings[i]->getSeatNumber(); }
	std::string getBodyTypeWithIndex(int i) const { return carListings[i]->getBodyType(); }

	// Motorcycle getters
	int getEngineSizeWithIndex(int i) const { return motorcycleListings[i]->getEngineSize(); }
	int getTopSpeedWithIndex(int i) const { return motorcycleListings[i]->getTopSpeed(); }
	std::string getTypeWithIndex(int i) const { return motorcycleListings[i]->getType(); }
	std::string getBrakeTypeWithIndex(int i) const { return motorcycleListings[i]->getBrakeType(); }

	int getListingOwnerIndexWithIndex(vehicleType type, int i) const;

	int getListingPriceWithIndex(vehicleType type, int i) const;

	bool isSoldListing(vehicleType type, int i) const;

	// Setters
	void setChosenVehicleType(vehicleType vehicle) { this->typeChoice = vehicle; }
	void setTypeCounterAddOne() { this->typeCounter++; }

	void setBrandWithIndex(vehicleType type, std::string brand, int i);
	void setModelWithIndex(vehicleType type, std::string model, int i);
	void setProductionYearWithIndex(vehicleType type, int productionYear, int i);
	void setRegistrationNumberWithIndex(vehicleType type, std::string registrationNumber, int i);
	void setHorsePowerWithIndex(vehicleType type, int horsePower, int i);
	void setFuelTypeWithIndex(vehicleType type, std::string fuelType, int i);
	void setGearboxTypeWithIndex(vehicleType type, std::string gearboxType, int i);
	void setDriveTypeWithIndex(vehicleType type, std::string driveType, int i);
	void setFuelConsumptionWithIndex(vehicleType type, int fuelConsumption, int i);

	// Car setters
	void setTrunkCapacityWithIndex(int trunkCapacity, int i) { carListings[i]->setTrunkCapacity(trunkCapacity); }
	void setSeatNumberWithIndex(int seatNumber, int i) { carListings[i]->setSeatNumber(seatNumber); }
	void setBodyTypeWithIndex(std::string bodyType, int i) { carListings[i]->setBodyType(bodyType); }

	// Motocycle setters
	void setEngineSizeWithIndex(int engineSize, int i) { motorcycleListings[i]->setEngineSize(engineSize); }
	void setTopSpeedWithIndex(int topSpeed, int i) { motorcycleListings[i]->setTopSpeed(topSpeed); }
	void setTypeWithIndex(std::string type, int i) { motorcycleListings[i]->setType(type); }
	void setBrakeTypeWithIndex(std::string brakeType, int i) { motorcycleListings[i]->setBrakeType(brakeType); }

	void setPriceWithIndex(vehicleType type, int price, int i);
	void setSoldWithIndex(vehicleType type, int i);

	int countOwnersListings(int index) const;
	void displayListing(vehicleType type, int i);

	friend std::ostream& operator<<(std::ostream&, const Dealership&);
	friend std::ofstream& operator<<(std::ofstream&, const Dealership&);
	friend std::ifstream& operator>>(std::ifstream& in, Dealership& dealership);
	Listing* operator [](const size_t);
	Dealership& operator=(const Dealership&);
};

#endif // DEALERSHIP_H