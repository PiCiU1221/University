#ifndef HEADER_H
#define HEADER_H
#pragma once

#include <string>

// by obslugiwac sterowanie gra bardziej czytelniej
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

struct Auto {
	std::string marka = "";
	std::string numerRejestracyjny = "";
	int iloscKoni = 0;
	int polubienia = 0;
};

extern void zad7();
extern void zad8();

extern std::string Marki[4];
extern std::string Rejestracje[4];

extern int generujInteger(int odLiczby, int doLiczby);

extern int policzCyfry(int number);

#endif // HEADER_H