#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <vector>

#include "header.h"

using namespace std;

/*
	Piotr Pietrusewicz 53828 120A
	Temat: Giełda samochodowa

	1. Stworz tablice obiektow Samolotow rand(), Samolot* samoloty;
	2. Zainicjalizuj obiekty tablicy Samolot.
	3. Pokaz tablice "samoloty".
	4. Dodaj samolot do "samoloty", zainicjalizuj dodany samolot.
	5. Usun losowo wybrany samolot.
*/

// ZAD 1
// Stworz tablice obiektow Auto
// Uzywamy tutaj "&" bo chcemy zamienic sam wskaznik, by teraz wskazywal na nowe komorki pamieci (nowa tablice)
void zad1(Auto*& tablica, int& arraySize) {
	delete[] tablica;
	tablica = nullptr;

	//int randomNumber = rand() % 6 + 5;
	int randomNumber = generujInteger(5, 10);

	arraySize = randomNumber;

	//Auto* tablica = (Auto*)malloc(sizeof(Auto) * randomNumber);
	tablica = new Auto[arraySize];
	cout << "\n========================================\n\n";
	cout << "    Wygenerowaną liczbą elementów jest: " << arraySize << endl;
	cout << "\n    Nacisnij ENTER by wrócić do menu\n";
	cout << "\n========================================\n";
	cin.ignore();
	cin.get();
}

// ZAD 2
// Zainicjalizuj obiekty tablicy Auta
void zad2(Auto* tablica, int& arraySize) {
	for (int i = 0; i < arraySize; i++) {
		dodajLosoweAuto(tablica, i);
	}

	cout << "\n========================================\n\n";
	cout << "    Dodano losową zawartość\n\n";
	cout << "    Nacisnij ENTER by wrócić do menu\n";
	cout << "\n========================================\n";
	cin.ignore();
	cin.get();
}

// ZAD 3
// Pokaz tablice Auta
void zad3(Auto* tablica, int& arraySize) {
	cout << "\n| Indeks |    Marka   | Numer Rejestracyjny | Ilosc Koni | Polubienia |" << endl;
	cout << "-----------------------------------------------------------------------" << endl;

	for (int i = 0; i < arraySize; i++) {
		cout << "| ";
		for (int j = 1; j <= 6 - policzCyfry(i); j++) {
			cout << " ";
		}
		cout << i << " | ";

		for (int j = 1; j <= 10 - tablica[i].marka.size(); j++) {
			cout << " ";
		}
		cout << tablica[i].marka << " | ";

		for (int j = 1; j <= 19 - tablica[i].numerRejestracyjny.size(); j++) {
			cout << " ";
		}
		cout << tablica[i].numerRejestracyjny << " | ";

		for (int j = 1; j <= 10 - policzCyfry(tablica[i].iloscKoni); j++) {
			cout << " ";
		}
		cout << tablica[i].iloscKoni << " | ";

		for (int j = 1; j <= 10 - policzCyfry(tablica[i].polubienia); j++) {
			cout << " ";
		}
		cout << tablica[i].polubienia << " |" << endl;
	}

	cout << "\n========================================\n\n";
	cout << "    Nacisnij ENTER by wrócić do menu\n";
	cout << "\n========================================\n";
	cin.ignore();
	cin.get();
}


// ZAD 4
// Polaczenie pierwszego, drugiego i trzeciego zadania dla tablicy wskaznikow
void zad4(Auto**& tablicaWskaznikow, int& arraySize) {
	for (int i = 0; i < arraySize; i++) {
		delete tablicaWskaznikow[i];
		tablicaWskaznikow[i] = nullptr;
	}
	delete[] tablicaWskaznikow;
	tablicaWskaznikow = nullptr;

	//int randomNumber = rand() % 6 + 5;
	int randomNumber = generujInteger(5, 10);

	arraySize = randomNumber;

	//Auto* tablica = (Auto*)malloc(sizeof(Auto) * randomNumber);
	tablicaWskaznikow = new Auto * [arraySize];
	for (int i = 0; i < arraySize; i++) {
		tablicaWskaznikow[i] = new Auto();
	}

	cout << "\n========================================\n\n";
	cout << "    Wygenerowaną liczbą elementów jest: " << arraySize << endl;
	cout << "\n    Nacisnij ENTER by wrócić do menu\n";
	cout << "\n========================================\n";
	cin.ignore();
	cin.get();

	for (int i = 0; i < arraySize; i++) {
		dodajLosoweAuto(tablicaWskaznikow, i);
	}

	cout << "\n========================================\n\n";
	cout << "    Dodano losową zawartość\n\n";
	cout << "    Nacisnij ENTER by wrócić do menu\n";
	cout << "\n========================================\n";
	cin.get();

	cout << "\n| Indeks |    Marka   | Numer Rejestracyjny | Ilosc Koni | Polubienia |" << endl;
	cout << "-----------------------------------------------------------------------" << endl;

	for (int i = 0; i < arraySize; i++) {
		cout << "| ";
		for (int j = 1; j <= 6 - policzCyfry(i); j++) {
			cout << " ";
		}
		cout << i << " | ";

		for (int j = 1; j <= 10 - tablicaWskaznikow[i]->marka.size(); j++) {
			cout << " ";
		}
		cout << tablicaWskaznikow[i]->marka << " | ";

		for (int j = 1; j <= 19 - tablicaWskaznikow[i]->numerRejestracyjny.size(); j++) {
			cout << " ";
		}
		cout << tablicaWskaznikow[i]->numerRejestracyjny << " | ";

		for (int j = 1; j <= 10 - policzCyfry(tablicaWskaznikow[i]->iloscKoni); j++) {
			cout << " ";
		}
		cout << tablicaWskaznikow[i]->iloscKoni << " | ";

		for (int j = 1; j <= 10 - policzCyfry(tablicaWskaznikow[i]->polubienia); j++) {
			cout << " ";
		}
		cout << tablicaWskaznikow[i]->polubienia << " |" << endl;
	}

	cout << "\n========================================\n\n";
	cout << "    Nacisnij ENTER by wrócić do menu\n";
	cout << "\n========================================\n";
	cin.get();
}

// ZAD 5
// Dodaj nowe Auto do Auta
void zad5(Auto*& tablica, int& arraySize) {
	//Auto* newArray = (Auto*)malloc(sizeof(Auto) * arraySize);
	Auto* newArray = new Auto[arraySize + 1];

	for (int i = 0; i < arraySize; i++) {
		newArray[i] = tablica[i];
	}

	string userInputMarka, userInputNumerRejestracyjny;
	int userInputIloscKoni;

	cout << "\n    Podaj marke: ";
	cin >> userInputMarka;
	cout << "\n    Podaj numer rejestracyjny: ";
	cin >> userInputNumerRejestracyjny;
	cout << "\n    Podaj ilosc koni: ";
	cin >> userInputIloscKoni;

	newArray[arraySize].marka = userInputMarka;
	newArray[arraySize].numerRejestracyjny = userInputNumerRejestracyjny;
	newArray[arraySize].iloscKoni = userInputIloscKoni;

	arraySize++;

	delete[] tablica;
	tablica = nullptr;
	tablica = newArray;

	cout << "\n========================================\n\n";
	cout << "    Dodano auto o podanych atrybutach\n\n";
	cout << "    Nacisnij ENTER by wrócić do menu\n";
	cout << "\n========================================\n";
	cin.ignore();
	cin.get();
}

// ZAD 6
// Usun losowo wybrane Auto
// Uzywamy tutaj "&" bo chcemy zamienic sam wskaznik, by teraz wskazywal na nowe komorki pamieci (nowa tablice)
void zad6(Auto*& tablica, int& arraySize) {
	//int indexToDelete = rand() % arraySize;
	int indexToDelete = generujInteger(0, arraySize - 1);

	cout << "\n    Losowo usunieto indeks: " << indexToDelete << endl;
	cout << "    Marka: " << tablica[indexToDelete].marka << endl;
	cout << "    Numer Rejestracyjny: " << tablica[indexToDelete].numerRejestracyjny << endl;
	cout << "    Ilość koni: " << tablica[indexToDelete].iloscKoni << endl;
	cout << "    Polubienia: " << tablica[indexToDelete].polubienia << endl;

	Auto* newArray = new Auto[arraySize - 1];

	// kopiujemy elementy ze starej tablicy do nowej z pominieciem usuwanego elementu
	for (int i = 0, j = 0; i < arraySize; i++) {
		if (i != indexToDelete) {
			newArray[j] = tablica[i];
			j++;
		}
	}

	arraySize--;

	delete[] tablica;
	tablica = nullptr;
	tablica = newArray;

	cout << "\n========================================\n\n";
	cout << "    Nacisnij ENTER by wrócić do menu\n";
	cout << "\n========================================\n";
	cin.ignore();
	cin.get();
}

// funkcja, ktora wyswietla auta z wieksza, lub rowna iloscia koni i umozliwia polubienie wybranego auta
// ZAD 7
void zad7(Auto*& tablica, int& arraySize) {
	int searchedIloscKoni, indexToLike = 0;
	vector<int> searchedIndexes;
	// sprawdzamy zmienna checker, czy wpisany indeks zostal wyszukany
	auto checker = searchedIndexes.begin();
	bool flag = false;

	cout << "\n    Wprowadź od jakiej ilości koni wyszukac: ";
	cin >> searchedIloscKoni;

	for (int i = 0; i < arraySize; i++) {
		if (tablica[i].iloscKoni >= searchedIloscKoni) {
			searchedIndexes.push_back(i);

			if (flag == false) {
				cout << "\n| Indeks |    Marka   | Numer Rejestracyjny | Ilosc Koni | Polubienia |" << endl;
				cout << "-----------------------------------------------------------------------" << endl;
			}

			cout << "| ";
			for (int j = 1; j <= 6 - policzCyfry(i); j++) {
				cout << " ";
			}
			cout << i << " | ";

			for (int j = 1; j <= 10 - tablica[i].marka.size(); j++) {
				cout << " ";
			}
			cout << tablica[i].marka << " | ";

			for (int j = 1; j <= 19 - tablica[i].numerRejestracyjny.size(); j++) {
				cout << " ";
			}
			cout << tablica[i].numerRejestracyjny << " | ";

			for (int j = 1; j <= 10 - policzCyfry(tablica[i].iloscKoni); j++) {
				cout << " ";
			}
			cout << tablica[i].iloscKoni << " | ";

			for (int j = 1; j <= 10 - policzCyfry(tablica[i].polubienia); j++) {
				cout << " ";
			}
			cout << tablica[i].polubienia << " |" << endl;
			flag = true;
		}
	}
	if (flag == false) {
		cout << "\n========================================\n\n";
		cout << "    Nie znaleziono żadnego rekordu, który spełnia wymagania\n\n";
		cout << "    Nacisnij ENTER by wrócić do menu\n";
		cout << "\n========================================\n";
		cin.ignore();
		cin.get();
	}
	else {
		do {
			cout << "\n    Wprowadź indeks auta do polubienia: ";
			cin >> indexToLike;
			// zmienna checker przechowuje informacje czy wpisany indeks zostal wczesniej wyszukany i wyswietlony
			checker = find(searchedIndexes.begin(), searchedIndexes.end(), indexToLike);

			if (checker == searchedIndexes.end()) {
				cout << "\n    Podany indeks nie znalazł się na liście wyszukiwań";
				cout << "\n    Spróbuj jeszcze raz\n";
			}
			// powtarzamy dopoki nie zostanie wpisany poprawny indeks
		} while (checker == searchedIndexes.end());
		tablica[indexToLike].polubienia++;

		cout << "\n========================================\n\n";
		cout << "    Auto z indeksem: " << indexToLike << " zostało polubione\n\n";
		cout << "    Nacisnij ENTER by wrócić do menu\n";
		cout << "\n========================================\n";
		cin.ignore();
		cin.get();
	}
}

// ZAD 8
// Gra w poscig w pliku content.cpp
// Wykonana w zwyczajny sposob

// ZAD 9
// Gra w snake w pliku content.cpp
// Wykonana z uzyciem klas i ich metod

void menu(Auto*& tablica, Auto**& tablicaWskaznikow, int& arraySize, int& arraySizeWskaznikow) {
	// cos innego od zera, ktore jest uzywana do wyjscia
	int wybor = 10;

	do {
		// czyscimy ekran konsoli
		system("CLS");
		cout << "    Projekt Semestr 2\n";
		cout << "    Piotr Pietrusewicz 53828 120A\n";
		cout << "    Temat: Gielda samochodowa\n";
		cout << "========================================\n";
		cout << " 1] Stwórz tablice obiektów Auto\n";
		cout << " 2] Zainicjalizuj obiekty tablicy Auta\n";
		cout << " 3] Pokaż tablice Auta\n";
		cout << " 4] Zadania 1-3 na tablicy wskaznikow\n";
		cout << " 5] Dodaj nowe Auto do Auta\n";
		cout << " 6] Usuń losowo wybrane Auto\n";
		cout << " 7] Wyszukaj auta od ilości koni, by je polubić\n";
		cout << " 8] Gra w pościg\n";
		cout << " 9] Gra w snake\n";
		cout << " 0] Wyjdź\n\n";

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
		// usuwamy tablice struktur
		delete[] tablica;
		tablica = nullptr;

		// usuwamy tablice wskaznikow
		for (int i = 0; i < arraySizeWskaznikow; i++) {
			delete tablicaWskaznikow[i];
			tablicaWskaznikow[i] = nullptr;
		}
		delete[] tablicaWskaznikow;
		tablicaWskaznikow = nullptr;
		exit(0);
		break;
	case 1:
		zad1(tablica, arraySize);
		break;
	case 2:
		zad2(tablica, arraySize);
		break;
	case 3:
		zad3(tablica, arraySize);
		break;
	case 4:
		zad4(tablicaWskaznikow, arraySizeWskaznikow);
		break;
	case 5:
		zad5(tablica, arraySize);
		break;
	case 6:
		zad6(tablica, arraySize);
		break;
	case 7:
		zad7(tablica, arraySize);
		break;
	case 8:
		zad8();
		break;
	case 9:
		zad9();
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

	// jakas wartosc byleby nie zero
	int arraySize = 1;
	int arraySizeWskaznikow = 1;

	// by nie bylo problemow przy odpaleniu funkcji w menu
	Auto* tablica = new Auto[arraySize];

	// tablica wskaznikow
	Auto** tablicaWskaznikow = new Auto * [arraySizeWskaznikow];
	for (int i = 0; i < arraySizeWskaznikow; i++) {
		tablicaWskaznikow[i] = new Auto();
	}

	while (true) {
		menu(tablica, tablicaWskaznikow, arraySize, arraySizeWskaznikow);
	}
}