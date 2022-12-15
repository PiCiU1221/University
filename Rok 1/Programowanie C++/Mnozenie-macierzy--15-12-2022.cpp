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


// funkcja inicjalizujaca macierze i rezerwujaca dla nich miejsce w pamieci
int** inicjalizacja_macierzy(int matrix_rows, int matrix_columns) {
	int** matrix = (int**)malloc(sizeof(int*) * matrix_rows);

	for (int i = 0; i < matrix_rows; i++) {
		if (matrix) {
			matrix[i] = (int*)malloc(sizeof(matrix[i]) * matrix_columns);
		}
	}

	return matrix;
}

// funkcja przypisujaca losowe wartosci w zakresie od 0 do 100 w macierzy o podanych wymiarach
void przypisanie_losowych_wartosci(int** matrix, int matrix_rows, int matrix_columns) {
	for (int i = 0; i < matrix_rows; i++) {
		for (int j = 0; j < matrix_columns; j++) {
			matrix[i][j] = rand() % 100;
		}
	}
}

// funkcja na wyswietlenie wartosci elementow w macierzach
void wyswietlenie_macierzy(int** matrix, int matrix_rows, int matrix_columns) {
	for (int i = 0; i < matrix_rows; i++) {
		for (int j = 0; j < matrix_columns; j++) {
			// if'y dla wygladu i czytelnosci
			if (matrix[i][j] < 10) {
				cout << "  ";
			}
			else if (matrix[i][j] < 100) {
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

//funkcja zwalniajaca pamiec przechowujaca macierze
void zwolnienie_pamieci(int** matrix, int matrix_rows, int matrix_columns) {
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

	// rezerwujemy pamiec dla macierzy
	int** matrix_a = inicjalizacja_macierzy(matrix_a_rows, matrix_a_columns);
	int** matrix_b = inicjalizacja_macierzy(matrix_b_rows, matrix_b_columns);
	int** matrix_c = inicjalizacja_macierzy(matrix_c_rows, matrix_c_columns);

	// przypisujemy losowe wartosci do elementow macierzy
	przypisanie_losowych_wartosci(matrix_a, matrix_a_rows, matrix_a_columns);
	przypisanie_losowych_wartosci(matrix_b, matrix_b_rows, matrix_b_columns);
	przypisanie_losowych_wartosci(matrix_c, matrix_c_rows, matrix_c_columns);
	
	// wyswietlamy elementy macierzy
	cout << "Macierz A:" << endl;
	wyswietlenie_macierzy(matrix_a, matrix_a_rows, matrix_a_columns);
	cout << "Macierz B:" << endl;
	wyswietlenie_macierzy(matrix_b, matrix_b_rows, matrix_b_columns);
	cout << "Macierz C:" << endl;
	wyswietlenie_macierzy(matrix_c, matrix_c_rows, matrix_c_columns);

	// petla w ktorej wykonujemy wlasciwe mnozenie przypisujac wartosci elementow
	// macierzy c wynikami funkcji
	for (int i = 0; i < matrix_c_rows; i++) {
		for (int j = 0; j < matrix_c_columns; j++) {
			matrix_c[i][j] = mnozenie(i, j, matrix_a, matrix_b, matrix_a_columns);
		}
	}

	cout << endl;
	cout << "==================================================" << endl;

	// wyswietlamy ponownie elementy macierzy
	cout << "Macierz A:" << endl;
	wyswietlenie_macierzy(matrix_a, matrix_a_rows, matrix_a_columns);
	cout << "Macierz B:" << endl;
	wyswietlenie_macierzy(matrix_b, matrix_b_rows, matrix_b_columns);
	cout << "Macierz C:" << endl;
	wyswietlenie_macierzy(matrix_c, matrix_c_rows, matrix_c_columns);

	// na koniec dzialania programu usuwamy z pamieci wczesniej zarezerwowana pamiec
	zwolnienie_pamieci(matrix_a, matrix_a_rows, matrix_a_columns);
	zwolnienie_pamieci(matrix_b, matrix_b_rows, matrix_b_columns);
	zwolnienie_pamieci(matrix_c, matrix_c_rows, matrix_c_columns);
}