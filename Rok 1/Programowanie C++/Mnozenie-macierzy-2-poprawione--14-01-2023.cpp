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

// funkcja inicjalizujaca macierze i rezerwujaca dla nich miejsce w pamieci
int** inicjalizacja_macierzy(int matrix_rows, int matrix_columns) {
	// sprawdzenie by pozbyc sie bledu C6386
	if (matrix_rows == 0) {
		return 0;
	}

	int** matrix = (int**)malloc(sizeof(int*) * matrix_rows);

	for (int i = 0; i < matrix_rows; i++) {
		if (matrix) {
			matrix[i] = (int*)malloc(sizeof(matrix[i]) * matrix_columns);
		}
	}

	return matrix;
}

// funkcja przepisujaca dane z pliku do pamieci
void macierz_z_pliku_do_pamieci(const char* matrix_name, int** matrix, int matrix_rows, int matrix_columns) {
	FILE* file;
	char file_name[512];

	sprintf_s(file_name, "matrix_%s.txt", matrix_name);
	errno_t err = fopen_s(&file, file_name, "r");

	int readNumber = 0;

	// if by pozbyc sie erroru
	if (err && file == NULL) {
		// error o nierozpoznawaniu "cout" i musialem w calym dokumencie "std::" dodac, by sie
		// go pozbyc
		std::cout << "Plik nie mogl zostac otworzony";
	}
	else {
		// pomijamy pierwsza linijke w pliku w ktorej sa wymiary
		if (file != NULL) {
			if (fscanf_s(file, "%*[^\n]\n") == 1) {
			}
		}


		for (int i = 0; i < matrix_rows; i++) {
			for (int j = 0; j < matrix_columns; j++) {
				if (file != NULL) {
					// wyciaganie porzadanych zmiennych z pliku i dodawanie ich iloczynu do sumy
					if (fscanf_s(file, "%d", &readNumber) == 1) {
						matrix[i][j] = readNumber;
					}
				}
			}
		}
		//zamykamy dostep do pliku
		fclose(file);
	}
}

// funkcja na wyswietlenie wartosci elementow w macierzach
void wyswietlenie_macierzy(int** matrix, int matrix_rows, int matrix_columns) {
	for (int i = 0; i < matrix_rows; i++) {
		for (int j = 0; j < matrix_columns; j++) {
			// if'y dla wygladu i czytelnosci
			if (matrix[i][j] < 10) {
				cout << "    ";
			}
			else if (matrix[i][j] < 100) {
				cout << "   ";
			}
			else if (matrix[i][j] < 1000) {
				cout << "  ";
			}
			else if (matrix[i][j] < 1000) {
				cout << " ";
			}
			cout << matrix[i][j] << " | ";
		}

		cout << endl;
	}

	cout << "==================================================" << endl;
	cout << endl;
}

//funkcja wykonujaca mnozenie danych wierszy i kolumn zwracajaca wynik tego dzialania
int mnozenie(int i, int j, int** matrix_a, int** matrix_b, int matrix_a_columns) {
	int suma = 0;

	for (int t = 0; t < matrix_a_columns; t++) {
		suma += matrix_a[i][t] * matrix_b[t][j];
	}

	return suma;
}

// funkcja zapisujaca dane z pamieci macierzy c do pliku
void zapisanie_do_pliku(int** matrix, int matrix_rows, int matrix_columns) {
	FILE* file;
	char file_name[512];

	sprintf_s(file_name, "matrix_c.txt");
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
				fprintf(file, "%d ", matrix[i][j]);
			}
			// przeskakujemy na kolejna linijke po skonczeniu zapisywania wiersza
			fprintf(file, "\n");
		}
		//zamykamy dostep do pliku
		fclose(file);
	}
}

//funkcja zwalniajaca pamiec przechowujaca macierze
void zwolnienie_pamieci(int** matrix, int matrix_rows) {
	for (int i = 0; i < matrix_rows; i++) {
		free(matrix[i]);
	}

	free(matrix);
}

// glowna funkcja main programu
int main() {
	// inicjalizacja zmiennych wymiarowych macierzy
	int matrix_a_rows, matrix_a_columns;
	int matrix_b_rows, matrix_b_columns;
	int matrix_c_rows, matrix_c_columns;

	do {
		cout << "Wprowadz liczbe wierszy pierwszej macierzy: ";
		cin >> matrix_a_rows;
		cout << "Wprowadz liczbe kolumn pierwszej macierzy: ";
		cin >> matrix_a_columns;

		cout << "" << endl;

		cout << "Wprowadz liczbe wierszy drugiej macierzy: ";
		cin >> matrix_b_rows;
		cout << "Wprowadz liczbe kolumn drugiej macierzy: ";
		cin >> matrix_b_columns;

		cout << "==================================================" << endl;
		cout << endl;

		// if sprawdzajacy poprawnosc wymiarow macierzy do mnozenia
		if (matrix_a_columns != matrix_b_rows) {
			cout << "Liczba kolumn w pierwszej macierzy musi byc taka sama jak liczba wierszy w drugiej macierzy" << endl;
			cout << "Sprobuj jeszcze raz" << endl;
			cout << endl;
			cout << "==================================================" << endl;
		}

	} while (matrix_a_columns != matrix_b_rows);

	// przypisujemy wymiary macierzy c po zewnetrzych wymiarach macierzy a i b
	matrix_c_rows = matrix_a_rows;
	matrix_c_columns = matrix_b_columns;

	// tworzymy pliki macierzy a i b i zapisujemy w nich losowe wartosci
	tworzenie_pliku_z_losowymi_wartosciami("a", matrix_a_rows, matrix_a_columns);
	tworzenie_pliku_z_losowymi_wartosciami("b", matrix_b_rows, matrix_b_columns);

	// rezerwujemy pamiec dla macierzy w pamieci
	int** matrix_a = inicjalizacja_macierzy(matrix_a_rows, matrix_a_columns);
	int** matrix_b = inicjalizacja_macierzy(matrix_b_rows, matrix_b_columns);
	int** matrix_c = inicjalizacja_macierzy(matrix_c_rows, matrix_c_columns);

	// wczytujemy pamiec z pliku do pamieci
	macierz_z_pliku_do_pamieci("a", matrix_a, matrix_a_rows, matrix_a_columns);
	macierz_z_pliku_do_pamieci("b", matrix_b, matrix_b_rows, matrix_b_columns);

	// petla w ktorej wykonujemy wlasciwe mnozenie przypisujac wartosci elementow
	// macierzy c wynikami funkcji
	for (int i = 0; i < matrix_c_rows; i++) {
		for (int j = 0; j < matrix_c_columns; j++) {
			matrix_c[i][j] = mnozenie(i, j, matrix_a, matrix_b, matrix_a_columns);
		}
	}

	// zapisanie macierzy c z pamieci do pliku
	zapisanie_do_pliku(matrix_c, matrix_c_rows, matrix_c_columns);

	cout << endl;
	cout << "==================================================" << endl;

	// wyswietlamy ponownie elementy macierzy
	cout << "Macierz A:" << endl;
	//wyswietlenie_macierzy(matrix_a, matrix_a_rows, matrix_a_columns);
	cout << "Macierz B:" << endl;
	//wyswietlenie_macierzy(matrix_b, matrix_b_rows, matrix_b_columns);
	cout << "Macierz C:" << endl;
	//wyswietlenie_macierzy(matrix_c, matrix_c_rows, matrix_c_columns);

	// na koniec dzialania programu usuwamy z pamieci wczesniej zarezerwowana pamiec
	zwolnienie_pamieci(matrix_a, matrix_a_rows);
	zwolnienie_pamieci(matrix_b, matrix_b_rows);
	zwolnienie_pamieci(matrix_c, matrix_c_rows);
}