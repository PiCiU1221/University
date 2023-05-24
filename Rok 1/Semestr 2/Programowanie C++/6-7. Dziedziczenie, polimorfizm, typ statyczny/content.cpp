#include "header.h"

using namespace std;

/*
	Piotr Pietrusewicz 53828 120A
	West Pomeranian University of Technology
	Theme: Car Dealearship

	File contains the definitions of the class methods and the arrays used to randomly generate data
*/

// These lines of code initialize several arrays of strings that will be used to generate random data for a car dealership simulation
string name[10] = { "Piotr", "Marcin", "Adam", "Kamil", "Hubert", "Mateusz", "Krzysztof", "Jakub", "Grzegorz", "Kacper" };
string carBrand[5] = { "Audi", "BMW", "Skoda", "Volkswagen", "Mercedes" };
string carModel[5][3] = { { "A4", "A6", "A7" }, { "Series 3", "X6", "Z4"}, { "Octavia", "Fabia", "Superb"}, { "Passat", "Golf", "Touran"}, {"A-Class", "GLC", "CLA" } };
string motorcycleBrand[5] = { "Honda", "Yamaha", "Kawasaki", "Suzuki", "Ducati" };
string motorcycleModel[5][3] = { { "CBR", "Gold Wing", "Africa Twin" }, { "R1", "MT-09", "XSR900" }, { "Ninja", "Z900", "Versys"}, { "GSX-R", "Hayabusa", "V-Strom"}, {"Panigale", "Monster", "Multistrada" } };
string plate[4] = { "ZST", "ZS", "ZCH", "ZPY" };
string fuelType[3] = { "Petrol", "Diesel", "Petrol + LPG" };
string gearboxType[2] = { "Manual", "Automatic" };
string driveType[2] = { "Front", "Rear" };
string city[4] = { "Stargard", "Szczecin", "Choszczno", "Pyrzyce" };
string street[4] = { "Wyszynskiego", "Niepodleglosci", "Czarnieckiego", "3 Maja" };
string bodyType[7] = { "Sedan", "Hatchback", "SUV", "Coupe", "Sport", "Compact" };
string motorcycleType[5] = { "Standard", "Cruiser", "Sport", "Touring", "Dirt" };
string brakeType[2] = { "Disc", "Drum" };
vehicleType vehicleTypes[2] = { CAR, MOTORCYCLE };

// Function generates a random integer between 'from' and 'to'
int generateInteger(int from, int to) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(from, to);
	return dis(gen);
}