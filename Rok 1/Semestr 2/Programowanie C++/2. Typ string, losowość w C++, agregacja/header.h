#ifndef HEADER_H
#define HEADER_H
#pragma once

#include <string>
/*
	Piotr Pietrusewicz 53828 120A
	Temat : Gie³da samochodowa

	Plik header dla plikow projektu
*/

// by obslugiwac sterowanie gra bardziej czytelniej
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

// inicjalizacje funkcji, by moc je przeniesc z glownego pliku main na oddzielny plik content dla lepszej czytelnosci
struct Auto {
	std::string marka = "";
	std::string numerRejestracyjny = "";
	int iloscKoni = 0;
	int polubienia = 0;
};

// struct ogloszenia zawierajacy tablice structow Auto
struct Ogloszenia {
	Auto* auta;
};

extern void zad9();
extern void zad10();

extern std::string Marki[4];
extern std::string Rejestracje[4];

extern int generujInteger(int odLiczby, int doLiczby);

extern int policzCyfry(int number);

extern void dodajLosoweAuto(Auto* tablica, int i);
extern void dodajLosoweAuto(Auto** tablica, int i);

#endif // HEADER_H