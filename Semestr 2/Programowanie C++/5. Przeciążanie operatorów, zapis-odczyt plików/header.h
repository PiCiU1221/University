#ifndef HEADER_H
#define HEADER_H
#pragma once

#include <string>
#include <iostream>
#include <random>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <typeinfo>
#include <vector>

/*
	Piotr Pietrusewicz 53828 120A
	West Pomeranian University of Technology
	Theme: Car Dealearship

	Header file that contains every class declaration with some helping functions
*/

// by obslugiwac sterowanie gra bardziej czytelniej
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

extern std::string name[10];
extern std::string brand[5];
extern std::string model[5][3];
extern std::string plate[4];
extern std::string fuelType[3];
extern std::string gearboxType[2];
extern std::string driveType[3];
extern std::string city[4];
extern std::string ulica[4];

int generateInteger(int from, int to);

int countNumbers(int number);

class Owner {
	std::string name;

	class Adress {
		std::string city;
		std::string street;
		int number;
	public:
		Adress(std::string city, std::string street, int number)
			: city(city), street(street), number(number) {
		}

		friend class Owner;
	};

	Adress adress;
public:
	Owner(const std::string name, std::string city, std::string street, int number);
	Owner(std::string city, std::string street, int number);
	// copy constructor
	Owner(const Owner& other);
	~Owner();

	std::string getName() const { return name; }
	std::string getCity() const { return adress.city; }
	std::string getStreet() const { return adress.street; }
	int getNumber() const { return adress.number; }
	Owner& operator=(const Owner&);
	friend std::istream& operator>>(std::istream&, Owner&);
};

class Listing {
	class Car {
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
		Car();

		Car(const Car& other);

		// konstruktor
		Car(std::string brand, std::string model, int productionYear, std::string registrationNumber,
			int horsePower, std::string fuelType, std::string gearboxType,
			std::string driveType, int fuelConsumption);

		friend class Listing;
	};

	Car car_;
	int ownerIndex;
	int price;
public:
	// Constructors
	Listing();
	Listing(std::string brand, std::string model, int productionYear, std::string registrationNumber, int horsePower,
		std::string fuelType, std::string gearboxType, std::string driveType, int fuelConsumption, int ownerIndex, int price);
	~Listing();

	// Getters
	std::string getBrand() const { return car_.brand; }
	std::string getModel() const { return car_.model; }
	int getProductionYear() const { return car_.productionYear; }
	std::string getRegistrationNumber() const { return car_.registrationNumber; }
	int getHorsePower() const { return car_.horsePower; }
	std::string getFuelType() const { return car_.fuelType; }
	std::string getGearboxType() const { return car_.gearboxType; }
	std::string getDriveType() const { return car_.driveType; }
	int getFuelConsumption() const { return car_.fuelConsumption; }

	int getOwnerIndex() const { return ownerIndex; }

	int getPrice() const { return price; }

	// Setters
	void setBrand(std::string brand) { car_.brand = brand; }
	void setModel(std::string model) { car_.model = model; }
	void setProductionYear(int productionYear) { car_.productionYear = productionYear; }
	void setRegistrationNumber(std::string registrationNumber) { car_.registrationNumber = registrationNumber; }
	void setHorsePower(int horsePower) { car_.horsePower = horsePower; }
	void setFuelType(std::string fuelType) { car_.fuelType = fuelType; }
	void setGearboxType(std::string gearboxType) { car_.gearboxType = gearboxType; }
	void setDriveType(std::string driveType) { car_.driveType = driveType; }
	void setFuelConsumption(int fuelConsumption) { car_.fuelConsumption = fuelConsumption; }

	void setOwner(int i) { this->ownerIndex = i; }
	void setPrice(int price) { this->price = price; }

	// Method to display listing data
	void displayData() const;
	Listing& operator=(const Listing&);
};

class Dealership {
	Owner** owners;
	int ownersSize;
	Listing** listings;
	int listingsSize;
public:
	Dealership();
	Dealership(const Dealership& other);
	~Dealership();

	// Methods that are using arrays of pointers
	void addOwner(std::string name, std::string city, std::string ulica, int numer);
	void deleteOwner(int index);
	void addListing(std::string brand, std::string model, int productionYear, std::string registrationNumber, int horsePower,
		std::string fuelType, std::string gearboxType, std::string driveType, int fuelConsumption, int ownerIndex, int price);
	void deleteListing(int index);

	// Getters
	int getOwnersSize() const { return ownersSize; }
	int getListingsSize() const { return listingsSize; }

	std::string getOwnerNameWithIndex(int i) const { return owners[i]->getName(); }
	std::string getOwnerCityWithIndex(int i) const { return owners[i]->getCity(); }
	std::string getOwnerStreetWithIndex(int i) const { return owners[i]->getStreet(); }
	int getOwnerNumberWithIndex(int i) const { return owners[i]->getNumber(); }

	std::string getBrandWithIndex(int i) const { return listings[i]->getBrand(); }
	std::string getModelWithIndex(int i) const { return  listings[i]->getModel(); }
	int getProductionYearWithIndex(int i) const { return  listings[i]->getProductionYear(); }
	std::string getRegistrationNumberWithIndex(int i) const { return  listings[i]->getRegistrationNumber(); }
	int getHorsePowerWithIndex(int i) const { return  listings[i]->getHorsePower(); }
	std::string getFuelTypeWithIndex(int i) const { return  listings[i]->getFuelType(); }
	std::string getGearboxTypeWithIndex(int i) const { return  listings[i]->getGearboxType(); }
	std::string getDriveTypeWithIndex(int i) const { return  listings[i]->getDriveType(); }
	int getFuelConsumptionWithIndex(int i) const { return  listings[i]->getFuelConsumption(); }

	int getListingOwnerIndexWithIndex(int i) const { return listings[i]->getOwnerIndex(); }

	int getListingPriceWithIndex(int i) const { return listings[i]->getPrice(); }

	// Setters
	void setBrandWithIndex(std::string brand, int i) { listings[i]->setBrand(brand); }
	void setModelWithIndex(std::string model, int i) { listings[i]->setModel(model); }
	void setProductionYearWithIndex(int productionYear, int i) { listings[i]->setProductionYear(productionYear); }
	void setRegistrationNumberWithIndex(std::string registrationNumber, int i) { listings[i]->setRegistrationNumber(registrationNumber); }
	void setHorsePowerWithIndex(int horsePower, int i) { listings[i]->setHorsePower(horsePower); }
	void setFuelTypeWithIndex(std::string fuelType, int i) { listings[i]->setFuelType(fuelType); }
	void setGearboxTypeWithIndex(std::string gearboxType, int i) { listings[i]->setGearboxType(gearboxType); }
	void setDriveTypeWithIndex(std::string driveType, int i) { listings[i]->setDriveType(driveType); }
	void setFuelConsumptionWithIndex(int fuelConsumption, int i) { listings[i]->setFuelConsumption(fuelConsumption); }

	void setPriceWithIndex(int price, int i) { listings[i]->setPrice(price); }

	int countOwnersListings(int index) const;
	void displayListing(int i) { listings[i]->displayData(); }
	friend std::ostream& operator<<(std::ostream&, const Dealership&);
	friend std::ofstream& operator<<(std::ofstream&, const Dealership&);
	friend std::ifstream& operator>>(std::ifstream& in, Dealership& dealership);
	Listing* operator [](const size_t);
	Dealership& operator=(const Dealership&);
};

void generateRandomizedOwnersAndListings(Dealership& dealership);
void addOwnerByUser(Dealership& dealership);
void deleteOwnerByUser(Dealership& dealership);
void displayOwners(Dealership& dealership);
void addListingByUser(Dealership& dealership);
void editListing(Dealership& dealership);
void deleteUserListing(Dealership& dealership);
void displayAllListings(Dealership& dealership);
void searchThroughListings(Dealership& dealership);
void usageOfAnOverloadedOperator(Dealership& dealership);
void writingToAFile(Dealership& dealership);
void enteringDataFromAFile(Dealership& dealership);

#endif // HEADER_H