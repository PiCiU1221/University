#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <vector>
#include <typeinfo>

#include "header.h"

using namespace std;

/*
	Piotr Pietrusewicz 53828 120A
	Temat: Giełda samochodowa
*/

// Klasy w pliku "header.h", a definicje ich metod w pliku "content.cpp"

// FUNKCJA 1
// Wylosuj właścicieli i ogłoszenia
void funkcja1(Gielda& gielda) {
	int randomNumber = generujInteger(5, 10);
	string randomName = "";

	for (int i = 0; i < randomNumber; i++) {
		randomName = name[generujInteger(0, 9)] + to_string(generujInteger(70, 99));
		Wlasciciel wlasciciel(randomName, miasto[generujInteger(0, 3)], ulica[generujInteger(0, 3)], generujInteger(1, 99));
		gielda.dodajWlasciciela(wlasciciel);
	}

	randomNumber = generujInteger(5, 10);

	for (int i = 0; i < randomNumber; i++) {
		int randomMarka = generujInteger(0, 4);
		Auto* auto_ = new Auto(marki[randomMarka], modele[randomMarka][generujInteger(0, 2)], generujInteger(1995, 2020),
			rejestracje[generujInteger(0, 3)] + " " + to_string(generujInteger(10000, 99999)),
			generujInteger(70, 250), rodzajPaliwa[generujInteger(0, 2)], skrzyniaBiegow[generujInteger(0, 1)],
			naped[generujInteger(0, 2)], generujInteger(5, 12));

		int randomWlasciciel = generujInteger(0, gielda.getWlascicieleSize() - 1);
		Ogloszenie ogloszenie(auto_, gielda.getWlascicielaWithIndex(randomWlasciciel), generujInteger(5000, 99999));
		gielda.dodajOgloszenie(ogloszenie);
	}

	cout << "\n========================================\n\n";
	cout << "    Wygenerowano " << gielda.getWlascicieleSize() << " właścicieli i " << gielda.getOgloszeniaSize() << " ogloszeń" << endl;
	cout << "\n    Nacisnij ENTER by wrócić do menu\n";
	cout << "\n========================================\n";
	cin.ignore();
	cin.get();
}


// FUNKCJA 2
// Dodaj właściciela
void funkcja2(Gielda& gielda) {
	cout << "\n    Podaj nazwę właściciela: " << endl;

	string input;

	cin.ignore();
	getline(cin, input);

	Wlasciciel wlasciciel(input, miasto[generujInteger(0, 3)], ulica[generujInteger(0, 3)], generujInteger(1, 99));

	gielda.dodajWlasciciela(wlasciciel);

	cout << "\n========================================\n\n";
	cout << "    Dodano nowego właściciela o nazwie: " << input << "\n\n";
	cout << "    Nacisnij ENTER by wrócić do menu\n";
	cout << "\n========================================\n";
	cin.get();
}


// FUNKCJA 3
// Usuń właściciela
void funkcja3(Gielda& gielda) {
	int indexToDelete = 0;
	vector<int> searchedIndexes;
	// sprawdzamy zmienna checker, czy tablica nie jest pusta
	auto checker = searchedIndexes.begin();
	bool flag = false;

	int wlascicieleSize = gielda.getWlascicieleSize();
	for (int i = 0; i < wlascicieleSize; i++) {
		searchedIndexes.push_back(i);

		if (flag == false) {
			cout << "\n| Indeks |       Nazwa       | Liczba ogłoszeń |" << endl;
			cout << "------------------------------------------------" << endl;
		}

		Wlasciciel* wlasciciel_ = gielda.getWlascicielaWithIndex(i);
		cout << "| ";
		for (int j = 1; j <= 6 - policzCyfry(i); j++) {
			cout << " ";
		}
		cout << i << " | ";

		int wlascicielNameSize = wlasciciel_->getName().size();

		for (int j = 1; j <= 17 - wlascicielNameSize; j++) {
			cout << " ";
		}
		cout << wlasciciel_->getName() << " | ";

		int cyfryCount = policzCyfry(gielda.countOgloszeniaWlasciciela(wlasciciel_));

		for (int j = 1; j <= 15 - cyfryCount; j++) {
			cout << " ";
		}
		cout << gielda.countOgloszeniaWlasciciela(wlasciciel_) << " | " << endl;
		flag = true;
	}
	if (flag == false) {
		cout << "\n========================================\n\n";
		cout << "    Lista właścicieli jest pusta\n\n";
		cout << "    Nacisnij ENTER by wrócić do menu\n";
		cout << "\n========================================\n";
		cin.ignore();
		cin.get();
	}
	else {
		do {
			cout << "\n    Wprowadź indeks właściciela do usunięcia: ";
			cin >> indexToDelete;
			// zmienna checker przechowuje informacje czy wpisany indeks zostal wczesniej wyszukany i wyswietlony
			checker = find(searchedIndexes.begin(), searchedIndexes.end(), indexToDelete);

			if (checker == searchedIndexes.end()) {
				cout << "\n    Podany indeks nie istnieje";
				cout << "\n    Spróbuj jeszcze raz\n";
			}
			// powtarzamy dopoki nie zostanie wpisany poprawny indeks
		} while (checker == searchedIndexes.end());

		string wybor;

		do {
			cout << "\n========================================\n\n";
			cout << "    Czy napewno chcesz usunąć wybrane ogłoszenie?\n\n";
			cout << "    Wpisz odpowiednio [T/N]\n";
			cout << "\n========================================\n";
			cin >> wybor;

			if (wybor != "T" && wybor != "N") {
				cout << "\n    Można wybrać tylko 'T', lub 'N'";
				cout << "\n    Spróbuj jeszcze raz\n";
			}
			// powtarzamy dopoki nie zostanie wpisany poprawny indeks
		} while (wybor != "T" && wybor != "N");

		if (wybor == "T") {
			Wlasciciel* wlascicielToDelete = gielda.getWlascicielaWithIndex(indexToDelete);
			string deletedName = wlascicielToDelete->getName();
			int ogloszeniaWlasciciela = gielda.countOgloszeniaWlasciciela(wlascicielToDelete);

			gielda.usunWlasciciela(*gielda.getWlascicielaWithIndex(indexToDelete));

			cout << "\n========================================\n\n";
			cout << "    Wlasciciel o nazwie: " << deletedName << " został usunięty wraz z " << ogloszeniaWlasciciela << " ogłoszeniami\n\n";
			cout << "    Nacisnij ENTER by wrócić do menu\n";
			cout << "\n========================================\n";
			cin.ignore();
			cin.get();
		}
	}
}


// FUNKCJA 4
// Wyświetl właścicieli
void funkcja4(Gielda& gielda) {
	cout << "\n| Indeks |       Nazwa       | Liczba ogłoszeń |   Miasto  |" << endl;
	cout << "------------------------------------------------------------" << endl;

	int wlascicieleSize = gielda.getWlascicieleSize();
	for (int i = 0; i < wlascicieleSize; i++) {
		Wlasciciel* wlascicielTemp = gielda.getWlascicielaWithIndex(i);
		Wlasciciel wlascicielDereference = *wlascicielTemp;
		// uzycie konstruktora kopiujacego
		Wlasciciel wlasciciel_ = Wlasciciel(wlascicielDereference);
		cout << "| ";
		for (int j = 1; j <= 6 - policzCyfry(i); j++) {
			cout << " ";
		}
		cout << i << " | ";

		int wlascicielNameSize = wlasciciel_.getName().size();

		for (int j = 1; j <= 17 - wlascicielNameSize; j++) {
			cout << " ";
		}
		cout << wlasciciel_.getName() << " | ";

		int cyfryCount = policzCyfry(gielda.countOgloszeniaWlasciciela(wlascicielTemp));

		for (int j = 1; j <= 15 - cyfryCount; j++) {
			cout << " ";
		}
		cout << gielda.countOgloszeniaWlasciciela(wlascicielTemp) << " | ";

		int wlascicielMiastoSize = wlasciciel_.getMiasto().size();

		for (int j = 1; j <= 9 - wlascicielMiastoSize; j++) {
			cout << " ";
		}
		cout << wlasciciel_.getMiasto() << " | " << endl;
	}

	cout << "\n========================================\n\n";
	cout << "    Nacisnij ENTER by wrócić do menu\n";
	cout << "\n========================================\n";
	cin.ignore();
	cin.get();
}


// FUNKCJA 5
// Dodaj ogłoszenie
void funkcja5(Gielda& gielda) {
	int indexToChoose = 0;
	vector<int> searchedIndexes;
	// sprawdzamy zmienna checker, czy tablica nie jest pusta
	auto checker = searchedIndexes.begin();
	bool flag = false;

	int wlascicieleSize = gielda.getWlascicieleSize();
	for (int i = 0; i < wlascicieleSize; i++) {
		searchedIndexes.push_back(i);

		if (flag == false) {
			cout << "\n| Indeks |       Nazwa       | Liczba ogłoszeń |" << endl;
			cout << "------------------------------------------------" << endl;
		}

		Wlasciciel* wlasciciel_ = gielda.getWlascicielaWithIndex(i);
		cout << "| ";
		for (int j = 1; j <= 6 - policzCyfry(i); j++) {
			cout << " ";
		}
		cout << i << " | ";

		int wlascicielNameSize = wlasciciel_->getName().size();

		for (int j = 1; j <= 17 - wlascicielNameSize; j++) {
			cout << " ";
		}
		cout << wlasciciel_->getName() << " | ";

		int cyfryCount = policzCyfry(gielda.countOgloszeniaWlasciciela(wlasciciel_));

		for (int j = 1; j <= 15 - cyfryCount; j++) {
			cout << " ";
		}
		cout << gielda.countOgloszeniaWlasciciela(wlasciciel_) << " | " << endl;
		flag = true;
	}
	if (flag == false) {
		cout << "\n========================================\n\n";
		cout << "    Lista właścicieli jest pusta\n\n";
		cout << "    Nacisnij ENTER by wrócić do menu\n";
		cout << "\n========================================\n";
		cin.ignore();
		cin.get();
	}
	else {
		do {
			cout << "\n    Wprowadź indeks właściciela, który dodał ogłoszenie: ";
			cin >> indexToChoose;
			// zmienna checker przechowuje informacje czy wpisany indeks zostal wczesniej wyszukany i wyswietlony
			checker = find(searchedIndexes.begin(), searchedIndexes.end(), indexToChoose);

			if (checker == searchedIndexes.end()) {
				cout << "\n    Podany indeks nie istnieje";
				cout << "\n    Spróbuj jeszcze raz\n";
			}
			// powtarzamy dopoki nie zostanie wpisany poprawny indeks
		} while (checker == searchedIndexes.end());

		cout << "\n\n    Wybrano wlasciciela o nazwie: " << gielda.getWlascicielaWithIndex(indexToChoose)->getName() << "\n";
		cout << "\n    Podaj marke, model, rok produkcji, numer rejestracyjny, ilosc koni," << endl;
		cout << "    rodzaj paliwa, rodzaj skrzyni biegów, rodzaj napędu oraz spalanie" << endl;
		cout << "    oddzielona znakiem ';' przyklad:" << endl;
		cout << "\n    Skoda;Fabia;2010;ZST 16161;70;Benzyna;Manualna;Na przod;7" << endl;

		Auto auto_;
		string input, marka, model, rokProdukcji, numerRejestracyjny, iloscKoni, rodzajPaliwa, skrzyniaBiegow, rodzajNapedu, spalanie;
		size_t newPos, oldPos = 0;

		cin.ignore();
		getline(cin, input);

		newPos = input.find(';');
		marka = input.substr(0, newPos);
		oldPos = newPos + 1;

		if (typeid(marka) == typeid(string)) {
			auto_.setMarka(marka);
		}

		newPos = input.find(';', oldPos);
		model = input.substr(oldPos, newPos - oldPos);
		oldPos = newPos + 1;

		if (typeid(model) == typeid(string)) {
			auto_.setModel(model);
		}

		newPos = input.find(';', oldPos);
		rokProdukcji = input.substr(oldPos, newPos - oldPos);
		oldPos = newPos + 1;

		if (typeid(rokProdukcji) == typeid(int)) {
			auto_.setRokProdukcji(stoi(rokProdukcji));
		}

		newPos = input.find(';', oldPos);
		numerRejestracyjny = input.substr(oldPos, newPos - oldPos);
		oldPos = newPos + 1;

		if (typeid(numerRejestracyjny) == typeid(string)) {
			auto_.setNumerRejestracyjny(numerRejestracyjny);
		}

		newPos = input.find(';', oldPos);
		iloscKoni = input.substr(oldPos, newPos - oldPos);
		oldPos = newPos + 1;

		if (typeid(iloscKoni) == typeid(int)) {
			auto_.setIloscKoni(stoi(iloscKoni));
		}

		newPos = input.find(';', oldPos);
		rodzajPaliwa = input.substr(oldPos, newPos - oldPos);
		oldPos = newPos + 1;

		if (typeid(rodzajPaliwa) == typeid(string)) {
			auto_.setRodzajPaliwa(rodzajPaliwa);
		}

		newPos = input.find(';', oldPos);
		skrzyniaBiegow = input.substr(oldPos, newPos - oldPos);
		oldPos = newPos + 1;

		if (typeid(skrzyniaBiegow) == typeid(string)) {
			auto_.setSkrzyniaBiegow(skrzyniaBiegow);
		}

		newPos = input.find(';', oldPos);
		rodzajNapedu = input.substr(oldPos, newPos - oldPos);
		oldPos = newPos + 1;

		if (typeid(rodzajNapedu) == typeid(string)) {
			auto_.setNaped(rodzajNapedu);
		}

		spalanie = input.substr(oldPos);

		if (typeid(spalanie) == typeid(int)) {
			auto_.setSpalanie(stoi(iloscKoni));
		}

		cout << "\n\n    Dodano auto o podanych atrybutach\n";

		cout << "\n    Wprowadz cene dla wprowadzonego auta: ";

		int cena;

		cin.ignore();
		cin >> cena;

		Ogloszenie ogloszenie_;

		ogloszenie_.setAuto(auto_);
		ogloszenie_.setWlasciciel(*gielda.getWlascicielaWithIndex(indexToChoose));
		ogloszenie_.setCena(cena);

		gielda.dodajOgloszenie(ogloszenie_);

		cout << "\n========================================\n\n";
		cout << "    Dodano nowe ogłoszenie\n\n";
		cout << "    Nacisnij ENTER by wrócić do menu\n";
		cout << "\n========================================\n";
		cin.ignore();
		cin.get();
	}
}


// FUNKCJA 6
// Edytuj ogłoszenie
void funkcja6(Gielda& gielda) {
	int indexToChoose = 0;
	vector<int> searchedIndexes;
	// sprawdzamy zmienna checker, czy tablica nie jest pusta
	auto checker = searchedIndexes.begin();
	bool flag = false;

	int ogloszeniaSize = gielda.getOgloszeniaSize();
	for (int i = 0; i < ogloszeniaSize; i++) {
		searchedIndexes.push_back(i);

		if (flag == false) {
			cout << "\n| Indeks |   Wlasciciel   |    Marka   |    Model   |  Cena  |" << endl;
			cout << "-------------------------------------------------------------" << endl;
		}

		Ogloszenie* ogloszenie_ = gielda.getOgloszenieWithIndex(i);

		Auto* auto_ = ogloszenie_->getAuto();
		Wlasciciel* wlasciciel_ = ogloszenie_->getWlasciciel();

		cout << "| ";
		for (int j = 1; j <= 6 - policzCyfry(i); j++) {
			cout << " ";
		}
		cout << i << " | ";

		int wlascicielNameSize = wlasciciel_->getName().size();

		for (int j = 1; j <= 14 - wlascicielNameSize; j++) {
			cout << " ";
		}
		cout << wlasciciel_->getName() << " | ";

		int markaSize = auto_->getMarka().size();

		for (int j = 1; j <= 10 - markaSize; j++) {
			cout << " ";
		}
		cout << auto_->getMarka() << " | ";

		int modelSize = auto_->getModel().size();

		for (int j = 1; j <= 10 - modelSize; j++) {
			cout << " ";
		}
		cout << auto_->getModel() << " | ";

		int cenaSize = policzCyfry(ogloszenie_->getCena());

		for (int j = 1; j <= 6 - cenaSize; j++) {
			cout << " ";
		}
		cout << ogloszenie_->getCena() << " | " << endl;

		flag = true;
	}
	if (flag == false) {
		cout << "\n========================================\n\n";
		cout << "    Lista ogłoszeń jest pusta\n\n";
		cout << "    Nacisnij ENTER by wrócić do menu\n";
		cout << "\n========================================\n";
		cin.ignore();
		cin.get();
	}
	else {
		do {
			cout << "\n    Wprowadź indeks ogłoszenia do edycji: ";
			cin >> indexToChoose;
			// zmienna checker przechowuje informacje czy wpisany indeks zostal wczesniej wyszukany i wyswietlony
			checker = find(searchedIndexes.begin(), searchedIndexes.end(), indexToChoose);

			if (checker == searchedIndexes.end()) {
				cout << "\n    Podany indeks nie istnieje";
				cout << "\n    Spróbuj jeszcze raz\n";
			}
			// powtarzamy dopoki nie zostanie wpisany poprawny indeks
		} while (checker == searchedIndexes.end());

		Ogloszenie* ogloszenie_ = gielda.getOgloszenieWithIndex(indexToChoose);

		Auto* auto_ = ogloszenie_->getAuto();
		Wlasciciel* wlasciciel_ = ogloszenie_->getWlasciciel();

		cout << "\n\n    Wybrano ogłoszenie wlasciciela o nazwie: " << wlasciciel_->getName() << "\n\n";

		string input;

		cout << "  1]                     Marka: " << auto_->getMarka() << endl;
		cout << "  2]                     Model: " << auto_->getModel() << endl;
		cout << "  3]             Rok produkcji: " << auto_->getRokProdukcji() << endl;
		cout << "  4]       Numer rejestracyjny: " << auto_->getNumerRejestracyjny() << endl;
		cout << "  5]                Ilość koni: " << auto_->getIloscKoni() << endl;
		cout << "  6]             Rodzaj paliwa: " << auto_->getRodzajPaliwa() << endl;
		cout << "  7]           Skrzynia biegow: " << auto_->getSkrzyniaBiegow() << endl;
		cout << "  8]                     Napęd: " << auto_->getNaped() << endl;
		cout << "  9]                  Spalanie: " << auto_->getSpalanie() << endl;
		cout << " 10]                      Cena: " << ogloszenie_->getCena() << endl << endl << endl;

		vector<int> searchedIndexes = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		do {
			cout << "\n    Wprowadź indeks atrybutu do edycji: ";
			cin >> indexToChoose;
			// zmienna checker przechowuje informacje czy wpisany indeks zostal wczesniej wyszukany i wyswietlony
			checker = find(searchedIndexes.begin(), searchedIndexes.end(), indexToChoose);

			if (checker == searchedIndexes.end()) {
				cout << "\n    Podany indeks jest nieprawidłowy";
				cout << "\n    Spróbuj jeszcze raz\n";
			}
			// powtarzamy dopoki nie zostanie wpisany poprawny indeks
		} while (checker == searchedIndexes.end());

		switch (indexToChoose) {
		case 1:
			cout << " Wprowadź nową markę: ";
			cin.ignore();
			getline(cin, input);
			auto_->setMarka(input);
			cout << "\n========================================\n\n";
			cout << "    Dodano poprawioną marke\n\n";
			break;
		case 2:
			cout << " Wprowadź nowy model: ";
			cin.ignore();
			getline(cin, input);
			auto_->setModel(input);
			cout << "\n========================================\n\n";
			cout << "    Dodano poprawiony model\n\n";
			break;
		case 3:
			cout << " Wprowadź nowy rok produkcji: ";
			cin.ignore();
			getline(cin, input);
			auto_->setRokProdukcji(stoi(input));
			cout << "\n========================================\n\n";
			cout << "    Dodano poprawiony rok produkcji\n\n";
			break;
		case 4:
			cout << " Wprowadź nowy numer rejestracyjny: ";
			cin.ignore();
			getline(cin, input);
			auto_->setNumerRejestracyjny(input);
			cout << "\n========================================\n\n";
			cout << "    Dodano poprawiony numer rejestracyjny\n\n";
			break;
		case 5:
			cout << " Wprowadź nową ilość koni: ";
			cin.ignore();
			getline(cin, input);
			auto_->setIloscKoni(stoi(input));
			cout << "\n========================================\n\n";
			cout << "    Dodano poprawioną ilość koni\n\n";
			break;
		case 6:
			cout << " Wprowadź nowy rodzaj paliwa: ";
			cin.ignore();
			getline(cin, input);
			auto_->setRodzajPaliwa(input);
			cout << "\n========================================\n\n";
			cout << "    Dodano poprawiony rodzaj paliwa\n\n";
			break;
		case 7:
			cout << " Wprowadź nowy rodzaj skrzyni biegów: ";
			cin.ignore();
			getline(cin, input);
			auto_->setSkrzyniaBiegow(input);
			cout << "\n========================================\n\n";
			cout << "    Dodano nowy rodzaj skrzyni biegów\n\n";
			break;
		case 8:
			cout << " Wprowadź nowy rodzaj napędu: ";
			cin.ignore();
			getline(cin, input);
			auto_->setNaped(input);
			cout << "\n========================================\n\n";
			cout << "    Dodano nowy rodzaj napędu\n\n";
			break;
		case 9:
			cout << " Wprowadź poprawione spalanie: ";
			cin.ignore();
			getline(cin, input);
			auto_->setSpalanie(stoi(input));
			cout << "\n========================================\n\n";
			cout << "    Dodano poprawione spalanie\n\n";
			break;
		case 10:
			cout << " Wprowadź nową cene: ";
			cin.ignore();
			getline(cin, input);
			ogloszenie_->setCena(stoi(input));
			cout << "\n========================================\n\n";
			cout << "    Dodano nową cene\n\n";
			break;
		default:
			cout << "\n========================================\n\n";
			cout << "    Wystąpił bląd w wyborze pozycji\n\n";
			break;
		}


		cout << "    Nacisnij ENTER by wrócić do menu\n";
		cout << "\n========================================\n";
		cin.get();
	}
}


// FUNKCJA 7
// Usuń ogłoszenie
void funkcja7(Gielda& gielda) {
	int indexToChoose = 0;
	vector<int> searchedIndexes;
	// sprawdzamy zmienna checker, czy tablica nie jest pusta
	auto checker = searchedIndexes.begin();
	bool flag = false;

	int ogloszeniaSize = gielda.getOgloszeniaSize();
	for (int i = 0; i < ogloszeniaSize; i++) {
		searchedIndexes.push_back(i);

		if (flag == false) {
			cout << "\n| Indeks |   Wlasciciel   |    Marka   |    Model   |  Cena  |" << endl;
			cout << "-------------------------------------------------------------" << endl;
		}

		Ogloszenie* ogloszenie_ = gielda.getOgloszenieWithIndex(i);

		Auto* auto_ = ogloszenie_->getAuto();
		Wlasciciel* wlasciciel_ = ogloszenie_->getWlasciciel();

		cout << "| ";
		for (int j = 1; j <= 6 - policzCyfry(i); j++) {
			cout << " ";
		}
		cout << i << " | ";

		int wlascicielNameSize = wlasciciel_->getName().size();

		for (int j = 1; j <= 14 - wlascicielNameSize; j++) {
			cout << " ";
		}
		cout << wlasciciel_->getName() << " | ";

		int markaSize = auto_->getMarka().size();

		for (int j = 1; j <= 10 - markaSize; j++) {
			cout << " ";
		}
		cout << auto_->getMarka() << " | ";

		int modelSize = auto_->getModel().size();

		for (int j = 1; j <= 10 - modelSize; j++) {
			cout << " ";
		}
		cout << auto_->getModel() << " | ";

		int cenaSize = policzCyfry(ogloszenie_->getCena());

		for (int j = 1; j <= 6 - cenaSize; j++) {
			cout << " ";
		}
		cout << ogloszenie_->getCena() << " | " << endl;

		flag = true;
	}
	if (flag == false) {
		cout << "\n========================================\n\n";
		cout << "    Lista ogłoszeń jest pusta\n\n";
		cout << "    Nacisnij ENTER by wrócić do menu\n";
		cout << "\n========================================\n";
		cin.ignore();
		cin.get();
	}
	else {
		do {
			cout << "\n    Wprowadź indeks ogłoszenia do usuniecia: ";
			cin >> indexToChoose;
			// zmienna checker przechowuje informacje czy wpisany indeks zostal wczesniej wyszukany i wyswietlony
			checker = find(searchedIndexes.begin(), searchedIndexes.end(), indexToChoose);

			if (checker == searchedIndexes.end()) {
				cout << "\n    Podany indeks nie istnieje";
				cout << "\n    Spróbuj jeszcze raz\n";
			}
			// powtarzamy dopoki nie zostanie wpisany poprawny indeks
		} while (checker == searchedIndexes.end());

		string wybor;

		do {
			cout << "\n========================================\n\n";
			cout << "    Czy napewno chcesz usunąć wybrane ogłoszenie?\n\n";
			cout << "    Wpisz odpowiednio [T/N]\n";
			cout << "\n========================================\n";
			cin >> wybor;

			if (wybor != "T" && wybor != "N") {
				cout << "\n    Można wybrać tylko 'T', lub 'N'";
				cout << "\n    Spróbuj jeszcze raz\n";
			}
			// powtarzamy dopoki nie zostanie wpisany poprawny indeks
		} while (wybor != "T" && wybor != "N");

		if (wybor == "T") {
			gielda.usunOgloszenie(*gielda.getOgloszenieWithIndex(indexToChoose));

			cout << "\n========================================\n\n";
			cout << "    Usunięto wybrane ogłoszenie\n\n";
			cout << "    Nacisnij ENTER by wrócić do menu\n";
			cout << "\n========================================\n";
			cin.ignore();
			cin.get();
		}
	}
}


// FUNKCJA 8
// Wyświetl ogłoszenia
void funkcja8(Gielda& gielda) {
	int ogloszeniaSize = gielda.getOgloszeniaSize();
	for (int i = 0; i < ogloszeniaSize; i++) {
		if (policzCyfry(i) == 2) {
			cout << "======================= " << i + 1 << ". Ogłoszenie ========================" << endl;
		}
		else {
			cout << "======================== " << i + 1 << ". Ogłoszenie ========================" << endl;
		}
		Ogloszenie* ogloszenie_ = gielda.getOgloszenieWithIndex(i);

		Auto* auto_ = ogloszenie_->getAuto();
		Wlasciciel* wlasciciel_ = ogloszenie_->getWlasciciel();

		ogloszenie_->wyswietlDane();
	}

	cout << "\n========================================\n\n";
	cout << "    Nacisnij ENTER by wrócić do menu\n";
	cout << "\n========================================\n";
	cin.ignore();
	cin.get();
}


// FUNKCJA 9
// Wyszukaj ogłoszenia
void funkcja9(Gielda& gielda) {
	string input;

	cout << "  1] Marka" << endl;
	cout << "  2] Model" << endl;
	cout << "  3] Rok produkcji        (ten i wyższe)" << endl;
	cout << "  4] Numer rejestracyjny" << endl;
	cout << "  5] Ilość koni           (te i wyższe)" << endl;
	cout << "  6] Rodzaj paliwa        (Benzyna, Diesel, Benzyna + LPG)" << endl;
	cout << "  7] Skrzynia biegow      (Manualna, Automatyczna)" << endl;
	cout << "  8] Napęd                (Na przod, Na tyl, Na cztery kola)" << endl;
	cout << "  9] Spalanie             (ten i w dół)" << endl;
	cout << " 10] Cena                 (ta i w góre)" << endl << endl << endl;

	vector<int> searchedIndexes = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	auto checker = searchedIndexes.begin();

	int indexToChoose;

	do {
		cout << "\n    Wprowadź indeks kryterium do wyszukania: ";
		cin >> indexToChoose;
		// zmienna checker przechowuje informacje czy wpisany indeks zostal wczesniej wyszukany i wyswietlony
		checker = find(searchedIndexes.begin(), searchedIndexes.end(), indexToChoose);

		if (checker == searchedIndexes.end()) {
			cout << "\n    Podany indeks jest nieprawidłowy";
			cout << "\n    Spróbuj jeszcze raz\n";
		}
		// powtarzamy dopoki nie zostanie wpisany poprawny indeks
	} while (checker == searchedIndexes.end());

	string searchValue;

	cout << "	Wprowadz dane do wyszukania: ";
	cin >> searchValue;
	cout << endl;

	int ogloszeniaSize = gielda.getOgloszeniaSize();

	for (int i = 0; i < ogloszeniaSize; i++) {
		Ogloszenie* ogloszenie_ = gielda.getOgloszenieWithIndex(i);
		Auto* auto_ = ogloszenie_->getAuto();

		switch (indexToChoose) {
		case 1:
			if (auto_->getMarka() == searchValue) {
				ogloszenie_->wyswietlDane();
			}
			break;
		case 2:
			if (auto_->getModel() == searchValue) {
				ogloszenie_->wyswietlDane();
			}
			break;
		case 3:
			if (auto_->getRokProdukcji() >= stoi(searchValue)) {
				ogloszenie_->wyswietlDane();
			}
			break;
		case 4:
			if (auto_->getNumerRejestracyjny() == searchValue) {
				ogloszenie_->wyswietlDane();
			}
			break;
		case 5:
			if (auto_->getIloscKoni() >= stoi(searchValue)) {
				ogloszenie_->wyswietlDane();
			}
			break;
		case 6:
			if (auto_->getRodzajPaliwa() == searchValue) {
				ogloszenie_->wyswietlDane();
			}
			break;
		case 7:
			if (auto_->getSkrzyniaBiegow() == searchValue) {
				ogloszenie_->wyswietlDane();
			}
			break;
		case 8:
			if (auto_->getSkrzyniaBiegow() == searchValue) {
				ogloszenie_->wyswietlDane();
			}
			break;
		case 9:
			if (auto_->getSpalanie() <= stoi(searchValue)) {
				ogloszenie_->wyswietlDane();
			}
			break;
		case 10:
			if (ogloszenie_->getCena() >= stoi(searchValue)) {
				ogloszenie_->wyswietlDane();
			}
			break;
		default:
			cout << "Nieprawidłowy wybór kryterium wyszukiwania." << endl;
		}
	}

	cout << "\n========================================\n\n";
	cout << "    Nacisnij ENTER by wrócić do menu\n";
	cout << "\n========================================\n";
	cin.ignore();
	cin.get();
}


void menu(Gielda& gielda) {
	// cos innego od zera, ktore jest uzywana do wyjscia
	int wybor = 10;

	do {
		// czyscimy ekran konsoli
		system("CLS");
		cout << "    Projekt Semestr 2\n";
		cout << "    Piotr Pietrusewicz 53828 120A\n";
		cout << "    Temat: Giełda samochodowa\n";
		cout << "========================================\n";
		cout << "  1] Wylosuj właścicieli i ogłoszenia\n";
		cout << "  2] Dodaj właściciela\n";
		cout << "  3] Usuń właściciela\n";
		cout << "  4] Wyświetl właścicieli\n";
		cout << "  5] Dodaj ogłoszenie\n";
		cout << "  6] Edytuj ogłoszenie\n";
		cout << "  7] Usuń ogłoszenie\n";
		cout << "  8] Wyświetl ogłoszenia\n";
		cout << "  9] Wyszukaj ogłoszenia\n";
		cout << "  0] Wyjdź\n\n";

		cin.clear();
		cin >> wybor;

		if (!(wybor >= 0 && wybor <= 9)) {
			cout << "\n========================================\n\n";
			cout << "    Wpisano niepoprawną liczbę\n\n";
			cout << "    Nacisnij ENTER by wrócić do menu\n";
			cout << "\n========================================\n";
			cin.ignore();
			cin.get();
		}
	} while (!(wybor >= 0 && wybor <= 9));

	switch (wybor) {
	case 0:
		exit(0);
		break;
	case 1:
		funkcja1(gielda);
		break;
	case 2:
		funkcja2(gielda);
		break;
	case 3:
		funkcja3(gielda);
		break;
	case 4:
		funkcja4(gielda);
		break;
	case 5:
		funkcja5(gielda);
		break;
	case 6:
		funkcja6(gielda);
		break;
	case 7:
		funkcja7(gielda);
		break;
	case 8:
		funkcja8(gielda);
		break;
	case 9:
		funkcja9(gielda);
		break;
	default:
		cout << "\n========================================\n\n";
		cout << "    Wpisano niepoprawną liczbę\n\n";
		cout << "    Nacisnij ENTER by wrócić do menu\n";
		cout << "\n========================================\n";
		cin.ignore();
		cin.get();
		break;
	}
}

int main() {
	// ustawiamy widocznosc polskich znakow w terminalu
	setlocale(LC_CTYPE, "Polish");

	// ustawiamy seed do losowania
	srand((unsigned int)time(nullptr));

	Gielda gielda;

	while (true) {
		menu(gielda);
	}
}