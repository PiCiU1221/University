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
#include <sstream>
#include <iomanip>
#include <map>
#include <list>
#include <iterator>
#include <numeric>

#include "owner.h"
#include "vehicle.h"
#include "listing.h"
#include "dealership.h"
#include "car.h"
#include "motorcycle.h"

/*
	Piotr Pietrusewicz 53828 120A
	West Pomeranian University of Technology
	Theme: Car Dealearship

	Header file that contains every class declaration with some helping functions
*/

extern std::string name[10];
extern std::string carBrand[5];
extern std::string carModel[5][3];
extern std::string motorcycleBrand[5];
extern std::string motorcycleModel[5][3];
extern std::string plate[4];
extern std::string fuelType[3];
extern std::string gearboxType[2];
extern std::string driveType[2];
extern std::string city[4];
extern std::string street[4];
extern std::string bodyType[7];
extern std::string motorcycleType[5];
extern std::string brakeType[2];
extern vehicleType vehicleTypes[2];

int generateInteger(int from, int to);

int countNumbers(int number);

// Functions used in the main.cpp file
void generateRandomizedOwnersAndListings(Dealership& dealership);
void addOwnerByUser(Dealership& dealership);
void deleteOwnerByUser(Dealership& dealership);
void displayOwners(Dealership& dealership);
void addListingByUser(Dealership& dealership);
void editListing(Dealership& dealership);
void deleteUserListing(Dealership& dealership);
void displayAllListings(Dealership& dealership);
void searchThroughListings(Dealership& dealership);
void confirmSale(Dealership& dealership);
void vehicleNumberFromCities(Dealership& dealership);
void usageOfAnOverloadedOperator(Dealership& dealership);
void checkIfOwnerExists(Dealership& dealership);
void displayPrices(Dealership& dealership);
void saveToAFile(Dealership& dealership);
void loadDataFromAFile(Dealership& dealership);

// Functions that handle repeated outputs to the terminal
void displayIncorrectNumberMessage();
void displayPressEnterToMenu();

#endif // HEADER_H