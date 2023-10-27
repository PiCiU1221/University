#ifndef HEADER_H
#define HEADER_H
#pragma once

#include <string>
#include <iostream>

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

//void zad9();
//void zad10();

extern std::string name[10];
extern std::string marki[5];
extern std::string modele[5][3];
extern std::string rejestracje[4];
extern std::string rodzajPaliwa[3];
extern std::string skrzyniaBiegow[2];
extern std::string naped[3];
extern std::string miasto[4];
extern std::string ulica[4];

int generujInteger(int odLiczby, int doLiczby);

int policzCyfry(int number);


class Auto {
	std::string marka = "";
	std::string model = "";
	int rokProdukcji = 0;
	std::string numerRejestracyjny = "";
	int iloscKoni = 0;
	std::string rodzajPaliwa = "";
	std::string skrzyniaBiegow = "";
	std::string naped = "";
	int spalanie = 0;

public:
	// konstruktor domyslny
	Auto();

	// konstruktor
	Auto(std::string marka, std::string model, int rokProdukcji, std::string numerRejestracyjny,
		int iloscKoni, std::string rodzajPaliwa, std::string skrzyniaBiegow,
		std::string naped, int spalanie);

	// zwracanie wartosci
	std::string getMarka() const { return marka; }
	std::string getModel() const { return model; }
	int getRokProdukcji() const { return rokProdukcji; }
	std::string getNumerRejestracyjny() const { return numerRejestracyjny; }
	int getIloscKoni() const { return iloscKoni; }
	std::string getRodzajPaliwa() const { return rodzajPaliwa; }
	std::string getSkrzyniaBiegow() const { return skrzyniaBiegow; }
	std::string getNaped() const { return naped; }
	int getSpalanie() const { return spalanie; }

	// edytowanie wartosci
	void setMarka(std::string marka) { this->marka = marka; }
	void setModel(std::string model) { this->model = model; }
	void setRokProdukcji(int rokProdukcji) { this->rokProdukcji = rokProdukcji; }
	void setNumerRejestracyjny(std::string numerRejestracyjny) { this->numerRejestracyjny = numerRejestracyjny; }
	void setIloscKoni(int iloscKoni) { this->iloscKoni = iloscKoni; }
	void setRodzajPaliwa(std::string rodzajPaliwa) { this->rodzajPaliwa = rodzajPaliwa; }
	void setSkrzyniaBiegow(std::string skrzyniaBiegow) { this->skrzyniaBiegow = skrzyniaBiegow; }
	void setNaped(std::string naped) { this->naped = naped; }
	void setSpalanie(int spalanie) { this->spalanie = spalanie; }
};


class Wlasciciel {
	const std::string name;

	class Adres {
		std::string miasto;
		std::string ulica;
		int numer;
	public:
		Adres() = default;
		Adres(std::string miasto, std::string ulica, int numer)
			: miasto(miasto), ulica(ulica), numer(numer) {
		}

		friend class Wlasciciel;
	};

	Adres adres;
public:
	Wlasciciel();
	Wlasciciel(const std::string name, std::string miasto, std::string ulica, int numer);
	// konstruktor kopiujacy
	Wlasciciel(const Wlasciciel& other);
	~Wlasciciel();

	std::string getName() const { return name; }
	std::string getMiasto() const { return adres.miasto; }
	std::string getUlica() const { return adres.ulica; }
	int getNumer() const { return adres.numer; }
};


class Ogloszenie {
	Auto* auto_;
	Wlasciciel* wlasciciel_;
	int cena;
public:
	Ogloszenie();
	Ogloszenie(Auto* auto_, Wlasciciel* wlasciciel_, int cena);
	~Ogloszenie();

	Auto* getAuto() const { return auto_; }
	Wlasciciel* getWlasciciel() const { return wlasciciel_; }
	int getCena() const { return cena; }

	void setAuto(const Auto& autoObj) { auto_ = new Auto(autoObj); }
	void setWlasciciel(const Wlasciciel& wlascicielObj) { wlasciciel_ = new Wlasciciel(wlascicielObj); }
	void setCena(int cena) { cena = cena; }

	void wyswietlDane() const;
};


class Gielda {
	Wlasciciel** wlasciciele;
	int wlascicieleSize;
	Ogloszenie** ogloszenia;
	int ogloszeniaSize;
public:
	Gielda();
	~Gielda();

	void dodajWlasciciela(const Wlasciciel& wlasciciel);
	void usunWlasciciela(const Wlasciciel& wlasciciel);
	void dodajOgloszenie(const Ogloszenie& ogloszenie);
	void usunOgloszenie(const Ogloszenie& ogloszenie);

	int getWlascicieleSize() const { return wlascicieleSize; }
	int getOgloszeniaSize() const { return ogloszeniaSize; }
	Wlasciciel* getWlascicielaWithIndex(int i) const { return wlasciciele[i]; }
	Ogloszenie* getOgloszenieWithIndex(int i) const { return ogloszenia[i]; }

	int countOgloszeniaWlasciciela(Wlasciciel* wlasciciel) const;
};


#endif // HEADER_H