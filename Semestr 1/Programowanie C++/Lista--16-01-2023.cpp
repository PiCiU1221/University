#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

/*
Ogólne za³o¿enia:
- Brak wycieków pamiêci.
- Przejrzysty kod - podzia³ na funkcje, struktury, wciêcia, minimalizacja
  redundancji kodu.
- Brak zmiennych globalnych.

---------------------------------------------------------
Projekt 2
-Piotr Pietrusewicz 120A-

Program do przechowywania danych osobowych (struktura) na liœcie dwukierunkowej
(w³asna implementacja listy). Lista przechowywana i zarz¹dzana jest w pamiêci.

Dane osobowe:
- nazwisko (dowolnej d³ugoœci)
- imie (dowolnej d³ugoœci)
- wiek
- pesel
- p³eæ

Program umo¿liwia:
1. Dodawanie dowolnej liczby osób do listy
2. Wyszukiwanie osoby po nazwisku lub imieniu
3. Kasowanie wybranej osoby (po nazwisku)
4. Wyœwietlanie listy - od przodu / od ty³u
5. Odczytywanie listy z pliku (elementy z pliku dodawane s¹ do ju¿ istniej¹cej listy
w pamiêci)
6. Zapisywanie listy do pliku
7. Sortowanie listy po nazwisku (dowolny algorytm) - po jawnym wybraniu opcji z menu
8. Menu tekstowe do obs³ugi funkcjonalnoœci.

Jedynym ograniczeniem iloœci elementów na liœcie to zasoby systemu.
*/

struct ListNode {
	string imie{};
	string nazwisko{};
	int wiek{};
	string pesel{};
	char plec{};
	ListNode* next{};
	ListNode* prev{};
};

// forward declaration by uniknac bledu kompilatora dotyczacych uzywania
// niezadeklarowanych funkcji w danym momencie w kodzie
void menu(ListNode* head);

void dodawanie(ListNode* head) {
	string imie, nazwisko, pesel;
	int wiek;
	char plec;
	char tempImie[42], tempNazwisko[42], tempPesel[13] = { 0 };
	system("CLS");
	printf(" 1] Dodaj nowa osobe do listy\n");
	printf("========================================\n\n");

	// dodajemy imie
	do {
		printf(" Imie: ");
		if (scanf_s("%41s", tempImie, sizeof(tempImie)) != 1) {
			printf("Blad przy wpisywaniu\n");
		}

		// czyscimy bufor inputu by uniknac bledow
		while ((getchar()) != '\n');
		if (tempImie != NULL) {
			if (strlen(tempImie) < 2 && strlen(tempImie) < 41) {
				printf("\n========================================\n\n");
				printf("\n Wprowadzono bledne dane:\n");
				printf(" Imie powinno byc dluzsze niz 1 znak\n");
				printf(" mniejsze od 40\n\n");
				printf("========================================\n");
			}
		}
	} while (tempImie != NULL && strlen(tempImie) < 2);

	if (tempImie >= 0) {
		imie = tempImie;
	}
	// dla wygladu "usuwamy caps-locka" z calosci a dodajemy na poczatku
	transform(imie.begin(), imie.end(), imie.begin(), ::tolower);
	imie[0] = toupper(imie[0]);

	// dodajemy nazwisko
	do {
		printf(" Nazwisko: ");
		scanf_s("%41s", tempNazwisko, sizeof(tempNazwisko));
		while ((getchar()) != '\n');

		if (tempNazwisko != NULL) {
			if (strlen(tempNazwisko) < 2 && strlen(tempNazwisko) < 41) {
				printf("\n========================================\n\n");
				printf("\n Wprowadzono bledne dane:\n");
				printf(" Nazwisko powinno byc dluzsze niz 1 znak i\n");
				printf(" mniejsze od 40\n\n");
				printf("========================================\n");
			}
		}
	} while (tempNazwisko != NULL && strlen(tempNazwisko) < 2);

	if (tempNazwisko >= 0) {
		nazwisko = tempNazwisko;
	}
	transform(nazwisko.begin(), nazwisko.end(), nazwisko.begin(), ::tolower);
	nazwisko[0] = toupper(nazwisko[0]);

	// petla do sprawdzenia poprawnosci wieku
	do {
		printf(" Wiek: ");
		scanf_s("%d", &wiek);
		while ((getchar()) != '\n');

		if (wiek < 0 || wiek > 150) {
			printf("\n========================================\n\n");
			printf("\n Wprowadzono bledne dane:\n");
			printf(" Wiek powinien byc dodatni i mniejszy niz 150\n\n");
			printf("========================================\n");
		}
	} while (wiek < 0 || wiek > 150);

	// petla do sprawdzenia dlugosci peselu
	do {
		printf(" PESEL: ");
		scanf_s("%12s", tempPesel, 12);
		while ((getchar()) != '\n');

		if (strlen(tempPesel) != 11) {
			printf("\n========================================\n\n");
			printf("\n Wprowadzono bledne dane:\n");
			printf(" PESEL powinien skladac sie z 11 znakow,\n\n");
			printf("========================================\n");
		}
	} while (strlen(tempPesel) != 11);

	if (tempPesel >= 0) {
		pesel = tempPesel;
	}

	// petla do sprawdzenia poprawnosci plec
	do {
		printf(" Plec [M/K]: ");
		scanf_s("%c", &plec, 1);
		while ((getchar()) != '\n');

		if (plec != 'M' && plec != 'K') {
			printf("\n========================================\n\n");
			printf("\n Wprowadzono bledne dane:\n");
			printf(" Poprawnie nalezy wpisac 'M' lub 'K'\n\n");
			printf("========================================\n");
		}
	} while (plec != 'M' && plec != 'K');

	struct ListNode* newNode = new ListNode();
	newNode->nazwisko = nazwisko;
	newNode->imie = imie;
	newNode->wiek = wiek;
	newNode->pesel = pesel;
	newNode->plec = plec;

	struct ListNode* fakeHead = head;

	while (fakeHead->next != NULL) {
		fakeHead = fakeHead->next;
	}
	fakeHead->next = newNode;
	newNode->prev = fakeHead;

	printf("\n========================================\n\n");
	printf(" Pomyslnie dodano nowy rekord\n");
	printf(" Nacisnij enter by wrocic do menu\n\n");
	printf("========================================\n");

	cin.ignore();
}

// funkcja do sprawdzenia czy dwa stringi sa identyczne, dlatego pomniejszamy
// wszystkie znaki i dopiero wtedy porownujemy
bool isEqual(string a, string b) {
	transform(a.begin(), a.end(), a.begin(), ::tolower);
	transform(b.begin(), b.end(), b.begin(), ::tolower);
	return a == b;
}

void wyszukiwanie(ListNode* head) {
	string search = "";
	int wybor = 0;
	system("CLS");
	printf(" 2] Wyszukaj osobe z listy\n");
	printf("========================================\n\n");
	printf(" Wprowadz imie lub nazwisko do wyszukania: ");
	cin >> search;
	cin.clear();
	printf("\n========================================\n\n");

	struct ListNode* fakeHead = head;
	fakeHead = fakeHead->next;

	// proste do sprawdzenia czy cos znalazlo
	bool flag = false;

	do {
		// sprawdzamy czy wyszukiwana fraza pasuje do imienia, badz nazwiska
		// i wtedy wypisujemy pasujace rekordy
		if (isEqual(fakeHead->imie, search) ||
			isEqual(fakeHead->nazwisko, search)) {
			// by sprawdzic czy nie wypisalismy juz tego
			if (flag == false) {
				printf(" |                   Imie                   |");
				printf("                Nazwisko                  |");
				printf(" Wiek |");
				printf("    PESEL    |");
				printf(" Plec |\n");
				printf("------------------------------------------------------------");
				printf("--------------------------------------------------------\n");
			}
			else {
				printf("------------------------------------------------------------");
				printf("--------------------------------------------------------\n");
			}
			// c_str() bo C nie obsluguje stringow :)
			printf(" | %s", fakeHead->imie.c_str());
			// petle ktore dodaja wymagana ilosc spacji dla wygladu
			for (int i = 0; i <= (40 - fakeHead->imie.size()); i++) { printf(" "); }
			printf("|");
			printf(" %s", fakeHead->nazwisko.c_str());
			for (int i = 0; i <= (40 - fakeHead->nazwisko.size()); i++) { printf(" "); }
			printf("|");
			printf(" %d", fakeHead->wiek);
			for (int i = 0; i <= (4 - (to_string(abs(fakeHead->wiek))).size()); i++) { printf(" "); }
			printf("|");
			printf(" %s", fakeHead->pesel.c_str());
			for (int i = 0; i <= (11 - fakeHead->pesel.size()); i++) { printf(" "); }
			printf("|");
			printf(" %c", fakeHead->plec);
			printf("    |\n");
			flag = true;
		}
		// if ktory sprawdza czy adres jest "NULL", bo bez sprawdzenia tego
		// bysmy odwolali sie do nieistniejacego node
		if (fakeHead != NULL) {
			fakeHead = fakeHead->next;
		}
		// wykonujemy do momentu az node nie bedzie mial wskazanego adresu
		// nastepnego node
	} while (fakeHead != NULL);

	if (flag == false) {
		printf("\n========================================\n\n");
		printf(" Nie znaleziono zadnego rekordu o podanych danych\n");
		printf(" Nacisnij enter by wrocic do menu\n\n");
		printf("========================================\n");
	}
	else {
		printf("\n========================================\n\n");
		printf(" Nacisnij enter by wrocic do menu\n\n");
		printf("========================================\n");
	}
	flag = false;

	cin.ignore();
	cin.ignore();
}

void usuwanie(ListNode* head) {
	string search = "";
	int wybor = 0;
	system("CLS");
	printf(" 3] Usun osobe z listy\n");
	printf("========================================\n\n");
	printf(" Wprowadz imie lub nazwisko do wyszukania: ");
	cin >> search;
	cin.clear();
	printf("\n========================================\n\n");

	struct ListNode* fakeHead = head;
	fakeHead = fakeHead->next;

	// proste do sprawdzenia czy cos znalazlo
	bool flag = false;
	int indeksowanie = 1;
	// vector ktory przechowuje adresy ListNode do usuniecia
	vector<ListNode*> dane;

	do {
		// sprawdzamy czy wyszukiwana fraza pasuje do imienia, badz nazwiska
		// i wtedy wypisujemy pasujace rekordy
		if (isEqual(fakeHead->imie, search) ||
			isEqual(fakeHead->nazwisko, search)) {
			// by sprawdzic czy nie wypisalismy juz tego
			if (flag == false) {
				printf(" | Indeks |                   Imie                   |");
				printf("                Nazwisko                  |");
				printf(" Wiek |");
				printf("    PESEL    |");
				printf(" Plec |\n");
				printf("-----------------------------------------------------------------");
				printf("-------------------------------------------------------------\n");
			}
			else {
				printf("-----------------------------------------------------------------");
				printf("-------------------------------------------------------------\n");
			}

			dane.push_back(fakeHead);

			printf(" | %d", indeksowanie);
			// zmianiamy inta na stringa by obliczyc jego rozmiar funkcja size
			auto display = to_string(indeksowanie);
			// petle ktore dodaja wymagana ilosc spacji dla wygladu
			for (int i = 0; i <= (5 - display.size()); i++) { printf(" "); }

			// c_str() bo C nie obsluguje stringow :)
			printf(" | %s", fakeHead->imie.c_str());
			// petle ktore dodaja wymagana ilosc spacji dla wygladu
			for (int i = 0; i <= (40 - fakeHead->imie.size()); i++) { printf(" "); }
			printf("|");

			printf(" %s", fakeHead->nazwisko.c_str());
			for (int i = 0; i <= (40 - fakeHead->nazwisko.size()); i++) { printf(" "); }
			printf("|");

			printf(" %d", fakeHead->wiek);
			for (int i = 0; i <= (4 - (to_string(abs(fakeHead->wiek))).size()); i++) { printf(" "); }
			printf("|");

			printf(" %s", fakeHead->pesel.c_str());
			for (int i = 0; i <= (11 - fakeHead->pesel.size()); i++) { printf(" "); }
			printf("|");

			printf(" %c", fakeHead->plec);
			printf("    |\n");
			flag = true;
			indeksowanie++;
		}
		// if ktory sprawdza czy adres jest "NULL", bo bez sprawdzenia tego
		// bysmy odwolali sie do nieistniejacego node
		if (fakeHead != NULL) {
			fakeHead = fakeHead->next;
		}
		// wykonujemy do momentu az node nie bedzie mial wskazanego adresu
		// nastepnego node
	} while (fakeHead != NULL);

	if (flag == false) {
		printf("\n========================================\n\n");
		printf(" Nie znaleziono zadnego rekordu o podanych danych\n");
		printf(" Nacisnij enter by wrocic do menu\n\n");
		printf("========================================\n");

		cin.ignore();
		cin.ignore();
		menu(head);
	}
	flag = false;

	printf("========================================\n\n");
	printf(" Wprowadz indeks do usuniecia: ");
	scanf_s("%d", &wybor);
	while ((getchar()) != '\n');

	printf("\n========================================\n\n");

	ListNode* toDel = dane[wybor - 1];

	if (toDel->prev != NULL && toDel->next != NULL) {
		ListNode* prev = toDel->prev;
		ListNode* next = toDel->next;

		prev->next = next;
		next->prev = prev;
	}
	else if (toDel->next == NULL) {
		ListNode* prev = toDel->prev;
		prev->next = NULL;
	}

	free(toDel);

	printf(" Rekord zostal pomyslnie usuniety\n");
	printf(" Nacisnij enter by wrocic do menu\n\n");
	printf("========================================\n");

	cin.ignore();
}

void wyswietlanie(ListNode* head) {
	string search = "";
	int wybor = 0;
	struct ListNode* fakeHead = head;

	if (fakeHead->next == NULL) {
		printf("\n========================================\n\n");
		printf(" Lista jest pusta\n");
		printf(" Nacisnij enter by wrocic do menu\n\n");
		printf("========================================\n");

		cin.ignore();
		menu(head);
	}

	system("CLS");
	printf(" 4] Wyswietlanie listy\n");
	printf("========================================\n\n");
	printf(" 1] Od przodu\n");
	printf(" 2] Od tylu\n\n ");
	printf(" Wprowadz wybor opcji: ");
	cin >> wybor;
	cin.clear();
	printf("\n========================================\n\n");

	switch (wybor) {
	case 1:
		fakeHead = fakeHead->next;
		break;
	case 2:
		while (fakeHead->next != NULL) {
			fakeHead = fakeHead->next;
		}
	default:
		break;
	}

	// proste do sprawdzenia czy cos znalazlo
	bool flag = false;

	do {
		// by sprawdzic czy nie wypisalismy juz tego
		if (flag == false) {
			printf(" |                   Imie                   |");
			printf("                Nazwisko                  |");
			printf(" Wiek |");
			printf("    PESEL    |");
			printf(" Plec |\n");
			printf("------------------------------------------------------------");
			printf("--------------------------------------------------------\n");
		}
		else {
			printf("------------------------------------------------------------");
			printf("--------------------------------------------------------\n");
		}
		// c_str() bo C nie obsluguje stringow :)
		printf(" | %s", fakeHead->imie.c_str());
		// petle ktore dodaja wymagana ilosc spacji dla wygladu
		for (int i = 0; i <= (40 - fakeHead->imie.size()); i++) { printf(" "); }
		printf("|");
		printf(" %s", fakeHead->nazwisko.c_str());
		for (int i = 0; i <= (40 - fakeHead->nazwisko.size()); i++) { printf(" "); }
		printf("|");
		printf(" %d", fakeHead->wiek);
		for (int i = 0; i <= (4 - (to_string(abs(fakeHead->wiek))).size()); i++) { printf(" "); }
		printf("|");
		printf(" %s", fakeHead->pesel.c_str());
		for (int i = 0; i <= (11 - fakeHead->pesel.size()); i++) { printf(" "); }
		printf("|");
		printf(" %c", fakeHead->plec);
		printf("    |\n");
		flag = true;

		// if ktory sprawdza czy adres jest "NULL", bo bez sprawdzenia tego
		// bysmy odwolali sie do nieistniejacego node
		if (fakeHead != NULL) {
			if (wybor == 1) {
				fakeHead = fakeHead->next;
			}
			else if (wybor == 2 && fakeHead->wiek != NULL) {
				fakeHead = fakeHead->prev;
			}
		}
		// wykonujemy do momentu az node nie bedzie mial wskazanego adresu
		// nastepnego node
	} while (fakeHead != NULL && fakeHead->wiek != NULL);

	printf("\n========================================\n\n");
	printf(" Nacisnij enter by wrocic do menu\n\n");
	printf("========================================\n");


	cin.ignore();
	cin.ignore();
}

void dodawanie_z_pliku(ListNode* head) {
	system("CLS");
	printf(" 5] Dodaj osoby z pliku\n");

	FILE* file;

	errno_t err = fopen_s(&file, "lista.txt", "r");
	char readData[42], readPesel[13], readChar[1] = { 0 };
	int readInt = 0;


	// if by pozbyc sie erroru
	if (err && file == NULL) {
		printf("Plik nie mogl zostac otworzony");
	}
	else {
		if (file != NULL) {
			while (fscanf_s(file, "%42s", readData, sizeof(readData)) != EOF) {
				struct ListNode* newNode = new ListNode();
				newNode->nazwisko = readData;
				if (fscanf_s(file, "%42s", readData, sizeof(readData)) != NULL) {
					newNode->imie = readData;
				}
				if (fscanf_s(file, "%d", &readInt) != NULL) {
					newNode->wiek = readInt;
				}
				if (fscanf_s(file, "%13s", readPesel, sizeof(readPesel)) != NULL) {
					newNode->pesel = readPesel;
				}
				if (fscanf_s(file, "%1s", &readChar, sizeof(readChar)) != NULL) {
					newNode->plec = readChar[0];
				}

				struct ListNode* fakeHead = head;

				while (fakeHead->next != NULL) {
					fakeHead = fakeHead->next;
				}
				fakeHead->next = newNode;
				newNode->prev = fakeHead;
			}
		}
		//zamykamy dostep do pliku
		fclose(file);
	}

	printf("========================================\n\n");
	printf(" Pomyslnie dopisano rekordy z pliku\n");
	printf(" Nacisnij enter by wrocic do menu\n\n");
	printf("========================================\n");

	cin.ignore();
}

void zapisywanie_do_pliku(ListNode* head) {
	system("CLS");
	printf(" 6] Zapisz liste do pliku\n");
	struct ListNode* fakeHead = head;
	fakeHead = fakeHead->next;
	FILE* file;

	errno_t err = fopen_s(&file, "lista.txt", "w");


	// if by pozbyc sie erroru
	if (err && file == NULL) {
		printf("Plik nie mogl zostac otworzony");
	}
	else {
		while (fakeHead != NULL) {
			fprintf(file, "%s ", fakeHead->nazwisko.c_str());
			fprintf(file, "%s ", fakeHead->imie.c_str());
			fprintf(file, "%d ", fakeHead->wiek);
			fprintf(file, "%s ", fakeHead->pesel.c_str());
			fprintf(file, "%c\n", fakeHead->plec);

			fakeHead = fakeHead->next;
		}
		//zamykamy dostep do pliku
		fclose(file);
	}

	printf("========================================\n\n");
	printf(" Pomyslnie zapisano rekordy do pliku\n");
	printf(" Nacisnij enter by wrocic do menu\n\n");
	printf("========================================\n");

	cin.ignore();
}

void swapNodes(ListNode* item1, ListNode* item2, ListNode* head) {
	ListNode* temp = item1->prev;

	/*
	cout << "head " << head << endl;
	cout << "item1->nazwisko " << item1->nazwisko << endl;
	cout << "item1 " << item1 << endl;
	cout << "item1->next " << item1->next << endl;
	cout << "item1->prev " << item1->prev << endl;
	cout << "item2->nazwisko " << item2->nazwisko << endl;
	cout << "item2 " << item2 << endl;
	cout << "item2->next " << item2->next << endl;
	cout << "item2->prev " << item2->prev << endl;
	*/

	temp->next = item2;

	item1->next = item2->next;
	item1->prev = item2;

	item2->prev = temp;
	item2->next = item1;

	if (item1->next != NULL) {
		temp = item1->next;
		temp->prev = item1;
	}

	/*
	cout << "item1 " << item1 << endl;
	cout << "item1->next " << item1->next << endl;
	cout << "item1->prev " << item1->prev << endl;
	cout << "item2 " << item2 << endl;
	cout << "item2->next " << item2->next << endl;
	cout << "item2->prev " << item2->prev << endl << endl;
	*/
}

void sortowanie(ListNode* head) {
	system("CLS");
	printf(" 7] Posortuj liste\n");
	printf("========================================\n\n");

	ListNode* item1 = head->next;
	ListNode* item2 = head->next->next;

	ListNode* fakeHead = head->next;
	int count = 0;
	while (fakeHead != NULL) {
		count++;
		fakeHead = fakeHead->next;
	}
	int limit = count - 1;
	bool didSwap = true;

	while (didSwap) {
		didSwap = 0;
		item1 = head->next;
		item2 = head->next->next;
		for (int i = 0; i < limit; i++) {
			if (strcmp(item1->nazwisko.c_str(), item2->nazwisko.c_str()) > 0) {
				swapNodes(item1, item2, head);
				didSwap = 1;
				item2 = item1->next;
			}
			else {
				item1 = item1->next;
				item2 = item2->next;
			}
		}
		limit--;
	}

	/*for (int i = 1; i < count; i++) {
		item1 = head->next;
		item2 = head->next->next;
		for (int j = 1; j < count - i; j++) {
			if (strcmp(item1->nazwisko.c_str(), item2->nazwisko.c_str()) > 0) {
				swapNodes(item1, item2, head);
			}
			item1 = item1->next;
			item2 = item2->next;
		}
	}*/

	printf(" Pomyslnie posortowano dane po nazwisku\n");
	printf(" Nacisnij enter by wrocic do menu\n\n");
	printf("========================================\n");

	cin.ignore();
}

void czyszczenie_koncowe(ListNode* head) {
	struct ListNode* fakeHead = head;

	while (fakeHead->next != NULL) {
		fakeHead = fakeHead->next;
	}

	while (fakeHead->prev != NULL) {
		fakeHead = fakeHead->prev;
		free(fakeHead->next);
	}

	free(fakeHead);

	exit(0);
}

void menu(ListNode* head) {
	// cos innego od zera, ktore jest uzywana do wyjscia
	int wybor = 10;
	// czyscimy ekran konsoli
	system("CLS");

	do {
		printf("    Projekt 2\n");
		printf("    Piotr Pietrusewicz 53828 120A\n");
		printf("========================================\n");
		printf(" 1] Dodaj nowa osobe do listy\n");
		printf(" 2] Wyszukaj osobe z listy\n");
		printf(" 3] Usun osobe z listy\n");
		printf(" 4] Wyswietl liste\n");
		printf(" 5] Dodaj osoby z pliku\n");
		printf(" 6] Zapisz liste do pliku\n");
		printf(" 7] Posortuj liste\n\n");
		printf(" 0] Wyjdz\n\n");

		scanf_s("%d", &wybor);
		while ((getchar()) != '\n');
	} while (!(wybor >= 0 && wybor <= 7));

	switch (wybor) {
	case 0:
		czyszczenie_koncowe(head);
		break;
	case 1:
		dodawanie(head);
		break;
	case 2:
		wyszukiwanie(head);
		break;
	case 3:
		usuwanie(head);
		break;
	case 4:
		wyswietlanie(head);
		break;
	case 5:
		dodawanie_z_pliku(head);
		break;
	case 6:
		zapisywanie_do_pliku(head);
		break;
	case 7:
		sortowanie(head);
		break;
	default:
		cin.clear();
		printf("Wpisano niepoprawna liczbe\n\n");
		printf("Nacisnij enter by wrocic do menu");
		cin.ignore();
	}
}

int main() {
	struct ListNode* head = new ListNode();

	while (true) {
		menu(head);
	}
}