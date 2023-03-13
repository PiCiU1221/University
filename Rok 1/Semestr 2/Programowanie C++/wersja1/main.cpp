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
void dodajLosoweAuto(Auto* tablica, int i) {
	/*
	tablica[i].marka = Marki[rand() % (4)];
	tablica[i].numerRejestracyjny = Rejestracje[rand() % (4)] + " " + to_string(rand() % 89999 + 10000);
	tablica[i].iloscKoni = rand() % 131 + 70;
	*/

	tablica[i].marka = Marki[generujInteger(0, 3)];
	tablica[i].numerRejestracyjny = Rejestracje[generujInteger(0, 3)] + " " + to_string(generujInteger(10000, 99999));
	tablica[i].iloscKoni = generujInteger(70, 200);
}

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
// Dodaj nowe Auto do Auta
void zad4(Auto*& tablica, int& arraySize) {
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

// ZAD 5
// Usun losowo wybrane Auto
// Uzywamy tutaj "&" bo chcemy zamienic sam wskaznik, by teraz wskazywal na nowe komorki pamieci (nowa tablice)
void zad5(Auto*& tablica, int& arraySize) {
	//int indexToDelete = rand() % arraySize;
	int indexToDelete = generujInteger(0, arraySize - 1);

	cout << "\n    Losowo usunieto indeks: " << indexToDelete << endl;
	cout << "    Marka: " << tablica[indexToDelete].marka << " Numer Rejestracyjny: " << tablica[indexToDelete].numerRejestracyjny << endl;

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
// ZAD 6
void zad6(Auto*& tablica, int& arraySize) {
	int searchedIloscKoni, indexToLike = 0;
	vector<int> searchedIndexes;
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
			checker = find(searchedIndexes.begin(), searchedIndexes.end(), indexToLike);

			if (checker == searchedIndexes.end()) {
				cout << "\n    Podany indeks nie znalazł się na liście wyszukiwań";
				cout << "\n    Spróbuj jeszcze raz\n";
			}
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

// ZAD 7
// Gra w poscig w pliku content.cpp

// ZAD 8
// Gra w snake w pliku content.cpp

void menu(Auto*& tablica, int& arraySize) {
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
		cout << " 4] Dodaj nowe Auto do Auta\n";
		cout << " 5] Usuń losowo wybrane Auto\n";
		cout << " 6] Wyszukaj auta od ilości koni, by je polubić\n";
		cout << " 7] Gra w pościg\n";
		cout << " 8] Gra w snake\n";
		cout << " 0] Wyjdź\n\n";

		cin.clear();
		cin >> wybor;

		if (!(wybor >= 0 && wybor <= 8)) {
			cout << "\n========================================\n\n";
			cout << "    Wpisano niepoprawną liczbę\n\n";
			cout << "    Nacisnij ENTER by wrócić do menu\n";
			cout << "\n========================================\n";
			cin.ignore();
			cin.get();
		}
	} while (!(wybor >= 0 && wybor <= 8));

	switch (wybor) {
	case 0:
		delete[] tablica;
		tablica = nullptr;
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
		zad4(tablica, arraySize);
		break;
	case 5:
		zad5(tablica, arraySize);
		break;
	case 6:
		zad6(tablica, arraySize);
		break;
	case 7:
		zad7();
		break;
	case 8:
		zad8();
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
	setlocale(LC_CTYPE, "Polish");

	// ustawiamy seed do losowania
	srand((unsigned int)time(nullptr));

	// jakas wartosc byleby nie zero
	int arraySize = 1;

	// by nie bylo problemow przy odpaleniu funkcji w menu
	Auto* tablica = new Auto[arraySize];

	while (true) {
		menu(tablica, arraySize);
	}
}