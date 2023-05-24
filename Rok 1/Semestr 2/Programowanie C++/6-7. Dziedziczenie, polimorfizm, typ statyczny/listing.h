#ifndef LISTING_H
#define LISTING_H
#pragma once

class Listing {
	Vehicle* vehicle_ = nullptr;
	int ownerIndex = 0;
	int price = 0;
	bool sold = false;
public:
	// Car
	Listing(std::string brand, std::string model, int productionYear, std::string registrationNumber, int horsePower, std::string fuelType,
		std::string gearboxType, std::string driveType, int fuelConsumption, int trunkCapacity, int seatNumber, std::string bodyType,
		int ownerIndex, int price, bool sold);
	// Motocycle
	Listing(std::string brand, std::string model, int productionYear, std::string registrationNumber, int horsePower, std::string fuelType,
		std::string gearboxType, std::string driveType, int fuelConsumption, int engineSize, int topSpeed, std::string type,
		std::string brakeType, int ownerIndex, int price, bool sold);
	~Listing();

	// Getters
	std::string getBrand() const { return vehicle_->brand; }
	std::string getModel() const { return vehicle_->model; }
	int getProductionYear() const { return vehicle_->productionYear; }
	std::string getRegistrationNumber() const { return vehicle_->registrationNumber; }
	int getHorsePower() const { return vehicle_->horsePower; }
	std::string getFuelType() const { return vehicle_->fuelType; }
	std::string getGearboxType() const { return vehicle_->gearboxType; }
	std::string getDriveType() const { return vehicle_->driveType; }
	int getFuelConsumption() const { return vehicle_->fuelConsumption; }

	// Car getters
	int getTrunkCapacity() const { return vehicle_->getTrunkCapacity(); }
	int getSeatNumber() const { return vehicle_->getSeatNumber(); }
	std::string getBodyType() const { return vehicle_->getBodyType(); }

	// Motocycle getters
	int getEngineSize() const { return vehicle_->getEngineSize(); }
	int getTopSpeed() const { return vehicle_->getTopSpeed(); }
	std::string getType() const { return vehicle_->getType(); }
	std::string getBrakeType() const { return vehicle_->getBrakeType(); }

	int getOwnerIndex() const { return ownerIndex; }
	int getPrice() const { return price; }
	bool isSold() const { return sold; }

	// Setters
	void setBrand(std::string brand) { vehicle_->brand = brand; }
	void setModel(std::string model) { vehicle_->model = model; }
	void setProductionYear(int productionYear) { vehicle_->productionYear = productionYear; }
	void setRegistrationNumber(std::string registrationNumber) { vehicle_->registrationNumber = registrationNumber; }
	void setHorsePower(int horsePower) { vehicle_->horsePower = horsePower; }
	void setFuelType(std::string fuelType) { vehicle_->fuelType = fuelType; }
	void setGearboxType(std::string gearboxType) { vehicle_->gearboxType = gearboxType; }
	void setDriveType(std::string driveType) { vehicle_->driveType = driveType; }
	void setFuelConsumption(int fuelConsumption) { vehicle_->fuelConsumption = fuelConsumption; }

	// Car setters
	void setTrunkCapacity(int trunkCapacity) { vehicle_->setTrunkCapacity(trunkCapacity); }
	void setSeatNumber(int seatNumber) { vehicle_->setSeatNumber(seatNumber); }
	void setBodyType(std::string bodyType) { vehicle_->setBodyType(bodyType); }

	// Motocycle setters
	void setEngineSize(int engineSize) { vehicle_->setEngineSize(engineSize); }
	void setTopSpeed(int topSpeed) { vehicle_->setTopSpeed(topSpeed); }
	void setType(std::string type) { vehicle_->setType(type); }
	void setBrakeType(std::string brakeType) { vehicle_->setBrakeType(brakeType); }

	void setOwner(int i) { this->ownerIndex = i; }
	void setPrice(int price) { this->price = price; }
	void setSold() { this->sold = true; }

	// Method to display listing data
	void displayData() const;
	Listing& operator=(const Listing&);
};

#endif // LISTING_H