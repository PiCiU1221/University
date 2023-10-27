#include "header.h"

using namespace std;

Owner::Owner(const std::string name, std::string city, std::string street, int number)
	: name(name), adress(city, street, number) {
}

Owner::Owner(std::string city, std::string street, int number)
	: name("placeHolder"), adress(city, street, number) {
}

// Copy constructor of an 'Owner' class
Owner::Owner(const Owner& other)
	: name(other.name), adress(other.adress) {
}

Owner::~Owner() = default;

// Overloaded operator '=' of an 'Owner' class
Owner& Owner::operator=(const Owner& right) {
	if (&right != this) {
		this->Owner::~Owner();
		this->Owner::Owner(right);
	}
	return *this;
}

// Overloaded operator '>>' of an 'Owner' class
std::istream& operator>>(std::istream& wejscie, Owner& t) {
	wejscie >> t.name;

	return wejscie;
}