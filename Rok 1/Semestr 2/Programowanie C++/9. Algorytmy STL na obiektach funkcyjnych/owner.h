#ifndef OWNER_H
#define OWNER_H
#pragma once

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

#endif // OWNER_H