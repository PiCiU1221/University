#include <iostream>
#include <random>

using namespace std;

// Mnozenie macierzy
// Piotr Pietrusewicz 120A

// 1. Uzytkownik wprowadza wymiary
// 2. Inicjalizacja macierzy a, b, c (rand 0-100)
// 3. Mnozenie
// 4. Wyswietlamy na ekran
// 5. Sprzatamy po sobie (free)
// 
// Druga czesc:
// macierz a i b z plikow i odczytujemy je z nich
// na poczatku wymiary macierzy oddzielone spacja
// macierz c rowniez do pliku

// funkcja przypisujaca losowe wartosci w zakresie od 0 do 100 w macierzy o podanych wymiarach
void tworzenie_pliku_z_losowymi_wartosciami(const char* matrix_name, int matrix_rows, int matrix_columns) {
	FILE* file;
	char file_name[512];

	// uzywamy pliku o nazwie skladajacej sie ze zmiennej przekazanej do funkcji
	sprintf_s(file_name, "matrix_%s.txt", matrix_name);
	errno_t err = fopen_s(&file, file_name, "w");

	// if by pozbyc sie erroru
	if (err && file == NULL) {
		// error o nierozpoznawaniu "cout" i musialem w calym dokumencie "std::" dodac, by sie
		// go pozbyc
		std::cout << "Plik nie mogl zostac otworzony";
	}
	else {
		// zapisujemy rozmiar macierzy na poczatku pliku
		fprintf(file, "%d ", matrix_rows);
		fprintf(file, "%d\n", matrix_columns);

		for (int i = 0; i < matrix_rows; i++) {
			for (int j = 0; j < matrix_columns; j++) {
				// zapisujemy losowa liczbe od 0 do 100
				fprintf(file, "%d ", rand() % 100);
			}
			// przeskakujemy na kolejna linijke po skonczeniu zapisywania wiersza
			fprintf(file, "\n");
		}
		//zamykamy dostep do pliku
		fclose(file);
	}
}

// funkcja na wyswietlenie wartosci elementow w macierzach
void wyswietlenie_macierzy(const char* matrix_name, int matrix_rows, int matrix_columns) {
	FILE* file;
	char file_name[512];

	sprintf_s(file_name, "matrix_%s.txt", matrix_name);
	errno_t err = fopen_s(&file, file_name, "r");

	if (err && file == NULL) {
		std::cout << "Plik nie mogl zostac otworzony";
	}
	else {
		int display = 0;

		// wymiary i informacje o macierzy
		std::cout << "Wymiary " << matrix_name << ": ";

		if (fscanf_s(file, "%d", &display) == 1) {
			std::cout << display;
		}
		std::cout << " x ";

		if (fscanf_s(file, "%d", &display) == 1) {
			std::cout << display << endl;
		}

		//petle wypisywania macierzy z pliku na ekran
		for (int i = 0; i < matrix_rows; i++) {
			for (int j = 0; j < matrix_columns; j++) {
				if (fscanf_s(file, "%d", &display) == 1) {
					//if'y dla wygladu
					if (display < 10) {
						std::cout << "    ";
					}
					else if (display < 100) {
						std::cout << "   ";
					}
					else if (display < 1000) {
						std::cout << "  ";
					}
					else if (display < 10000) {
						std::cout << " ";
					}
					std::cout << display << " | ";
				}
			}
			std::cout << endl;
		}
		//zamkniecie dostepu do pliku
		fclose(file);
	}

	std::cout << "==================================================" << endl;
	std::cout << endl;
}

//funkcja wykonujaca mnozenie danych wierszy i kolumn zwracajaca wynik tego dzialania
int mnozenie(int i, int j, int matrix_a_columns) {
	int suma = 0;

	//otwieramy 2 pliki jednoczesnie macierzy a i b
	FILE* file_a;
	char file_name[512];

	sprintf_s(file_name, "matrix_%s.txt", "a");
	errno_t err_a = fopen_s(&file_a, file_name, "r");

	FILE* file_b;

	sprintf_s(file_name, "matrix_%s.txt", "b");
	errno_t err_b = fopen_s(&file_b, file_name, "r");

	int a, b = 0;

	// if'y by pozbyc sie erroru, ktory musialem duzo razy powtorzyc bo inaczej
	// nie znikalo :/
	if (err_a && file_a && err_b && file_b == NULL) {
		std::cout << "Plik nie mogl zostac otworzony";
	}
	else {
		// pomijamy pierwsza linijke w pliku w ktorej sa wymiary
		if (file_a != NULL) {
			if (fscanf_s(file_a, "%*[^\n]\n") == 1) {
			}
		}
		// to samo w drugiej macierzy
		if (file_b != NULL) {
			if (fscanf_s(file_b, "%*[^\n]\n") == 1) {
			}
		}

		// poprzez przekazana w funkcji informacje o poszukiwanej pozycji pomijamy linijki by
		// dostac sie do odpowiedniego wiersza
		for (int m = 0; m < i; m++) {
			if (file_a != NULL) {
				if (fscanf_s(file_a, "%*[^\n]\n") == 1) {
				}
			}
		}

		// glowna funkcja mnozenia
		for (int t = 0; t < matrix_a_columns; t++) {
			// zmieniamy pozycje wiersza w zaleznosci jaka potrzebujemy z przekazanych zmiennych
			for (int m = 0; m < j; m++) {
				if (file_b != NULL) {
					if (fscanf_s(file_b, "%d", &b) == 1) {
					}
				}
			}

			if (file_a && file_b != NULL) {
				// wyciaganie porzadanych zmiennych z pliku i dodawanie ich iloczynu do sumy
				if ((fscanf_s(file_a, "%d", &a) == 1) && (fscanf_s(file_b, "%d", &b) == 1)) {
					suma += a * b;
				}

				// przesuwamy sie linie w dol do kolejnych dzialan na macierzy b
				if (fscanf_s(file_b, "%*[^\n]\n") == 1) {
				}
			}
		}
	}
	// zamykamy dostep do pliku
	if (file_a && file_b != NULL) {
		fclose(file_a);
		fclose(file_b);
	}
	// zwracamy wartosc zmiennej suma do funkcji jako wynik mnozenia dla danego elementu macierzy c
	return suma;
}

//funkcja tworzaca plik z macierza c i wpisujaca tam poprawne wyniki
void tworzenie_macierzy_c(int matrix_c_rows, int matrix_c_columns, int matrix_a_columns) {
	FILE* file;
	char file_name[512];

	sprintf_s(file_name, "matrix_%s.txt", "c");
	errno_t err = fopen_s(&file, file_name, "w");

	if (err && file == NULL) {
		std::cout << "Plik nie mogl zostac otworzony";
	}
	else {
		fprintf(file, "%d ", matrix_c_rows);
		fprintf(file, "%d\n", matrix_c_columns);

		// jako wartosc elementu na danych wspolrzednych wywolujemy funkcje ktora
		// zwraca nam wynik mnozenia
		for (int i = 0; i < matrix_c_rows; i++) {
			for (int j = 0; j < matrix_c_columns; j++) {
				fprintf(file, "%d ", mnozenie(i, j, matrix_a_columns));
			}
			fprintf(file, "\n");
		}
		fclose(file);
	}
}

// glowna funkcja main programu
int main() {
	srand((unsigned int)time(NULL));

	// inicjalizacja zmiennych wymiarowych macierzy
	int matrix_a_rows, matrix_a_columns;
	int matrix_b_rows, matrix_b_columns;
	int matrix_c_rows, matrix_c_columns;

	do {
		// wprowadzanie danych o wymiarach od uzytkownika
		std::cout << "Wprowadz liczbe wierszy pierwszej macierzy: ";
		cin >> matrix_a_rows;
		std::cout << "Wprowadz liczbe kolumn pierwszej macierzy: ";
		cin >> matrix_a_columns;

		std::cout << "" << endl;

		std::cout << "Wprowadz liczbe wierszy drugiej macierzy: ";
		cin >> matrix_b_rows;
		std::cout << "Wprowadz liczbe kolumn drugiej macierzy: ";
		cin >> matrix_b_columns;

		std::cout << "==================================================" << endl;
		std::cout << endl;

		// if sprawdzajacy poprawnosc wymiarow macierzy do mnozenia
		if (matrix_a_columns != matrix_b_rows) {
			std::cout << "Liczba kolumn w pierwszej macierzy musi byc taka sama jak liczba wierszy w drugiej macierzy" << endl;
			std::cout << "Sprobuj jeszcze raz" << endl;
			std::cout << endl;
			std::cout << "==================================================" << endl;
		}

	} while (matrix_a_columns != matrix_b_rows);

	// przypisujemy wymiary macierzy c po zewnetrzych wymiarach macierzy a i b
	matrix_c_rows = matrix_a_rows;
	matrix_c_columns = matrix_b_columns;

	// przypisujemy losowe wartosci do elementow macierzy a i b
	tworzenie_pliku_z_losowymi_wartosciami("a", matrix_a_rows, matrix_a_columns);
	tworzenie_pliku_z_losowymi_wartosciami("b", matrix_b_rows, matrix_b_columns);

	//tworzenie pliku z macierza c i wpisywanie tam przemnozonych wynikow
	tworzenie_macierzy_c(matrix_c_rows, matrix_c_columns, matrix_a_columns);

	// wyswietlamy elementy macierzy po wykonaniu dzialan
	wyswietlenie_macierzy("a", matrix_a_rows, matrix_a_columns);
	wyswietlenie_macierzy("b", matrix_b_rows, matrix_b_columns);
	wyswietlenie_macierzy("c", matrix_c_rows, matrix_c_columns);
}