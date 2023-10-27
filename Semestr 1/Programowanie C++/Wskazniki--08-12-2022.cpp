#include <iostream>

using namespace std;

/*int** p;

p = (int**)malloc(sizeof(int*) * 6);

for (int i = 0; i < 6; i++) {
	p[i] = (int*)malloc(sizeof(int) * 6);
}

p[5][5] = 10;
*/

// WSKAZNIKI
// ZAD 1
/*  Napisz funkcjê otrzymuj¹c¹ jako argumenty wskaŸniki do dwóch zmiennych typu int, która zwraca jako
	wartoœæ mniejsz¹ z liczb wskazywanych przez argumenty.
*/

int zad1_funkcja(int *a, int *b) {
	if (*a < *b) {
		return *a;
	}
	else {
		return *b;
	}
}

void zad1() {
	int a = 2, b = 1;
	int* wsk1 = &a;
	int* wsk2 = &b;

	cout << "Mniejsza wartosc jest rowna: " << zad1_funkcja(wsk1, wsk2) << endl;
}

// ZAD 2
/*  Napisz funkcjê otrzymuj¹c¹ jako argumenty wskaŸniki do dwóch zmiennych typu int, która zwraca jako
	wartoœæ wskaŸnik na zmienn¹ przechowuj¹c¹ mniejsz¹ z liczb wskazywanych przez argumenty.
*/

int zad2_funkcja(int* a, int* b) {
	if (*a < *b) {
		return *a;
	}
	else {
		return *b;
	}
}

void zad2() {
	int a = 2, b = 1;
	int* wsk1 = &a;
	int* wsk2 = &b;

	cout << "Wartosc wskaznika mniejszej liczby: " << zad1_funkcja(wsk1, wsk2) << endl;
}

// ZAD 3
/*  Napisz funkcjê otrzymuj¹c¹ jako argumenty wskaŸniki do dwóch zmiennych typu int, która zamienia ze sob¹
	wartoœci wskazywanych zmiennych.
*/

void zad3_funkcja(int* a, int* b) {
	int zamiennik = 0;
	zamiennik = *a;
	*a = *b;
	*b = zamiennik;

	cout << "a: " << *a << " | b: " << *b << endl;
}

void zad3() {
	int a = 1, b = 2;
	int* wsk1 = &a;
	int* wsk2 = &b;

	cout << "a: " << a << " | b: " << b << endl;

	zad3_funkcja(wsk1, wsk2);
}

// ZAD 4
/*  Napisz bezargumentow¹ funkcjê, która rezerwuje pamiêæ dla pojedynczej zmiennej typu int i zwraca jako
	wartoœæ wskaŸnik do niej.
*/

int* zad4_funkcja() {
	int* wsk = (int*)malloc(sizeof(int));
	return wsk;
}

void zad4() {
	int* wsk = zad4_funkcja();
	cout << wsk << endl;
	free(wsk);
}

// ZAD 5
/*  Napisz bezargumentow¹ funkcjê, która rezerwuje pamiêæ dla pojedynczej zmiennej typu double i zwraca
	jako wartoœæ wskaŸnik do niej.
*/

double* zad5_funkcja() {
	double* wsk = (double*)malloc(sizeof(double));
	return wsk;
}

void zad5() {
	double* wsk = zad5_funkcja();
	cout << wsk << endl;
	free(wsk);
}

// ZAD 6
/*  Napisz funkcjê, która dostaje jako argument dodatni¹ liczbê ca³kowit¹ n, rezerwuje w pamiêci blok n
	zmiennych typu int i zwraca jako wartoœæ wskaŸnik do pocz¹tku zarezerwowanego bloku pamiêci.
*/

int* zad6_funkcja(int n) {
	int* wsk = (int*)malloc(sizeof(int) * n);
	return wsk;
}

void zad6() {
	int n = 10;
	cout << zad6_funkcja(n) << endl;
}

// ZAD 7
/*  Napisz funkcjê, która dostaje jako argument dodatni¹ liczbê ca³kowit¹ n, rezerwuje w pamiêci blok n
	zmiennych typu double i zwraca jako wartoœæ wskaŸnik do pocz¹tku zarezerwowanego bloku pamiêci.
*/

double* zad7_funkcja(int n) {
	double* wsk = (double*)malloc(sizeof(double) * n);
	return wsk;
}

void zad7() {
	int n = 10;
	cout << zad7_funkcja(n) << endl;
}

// ZAD 8
/*  Napisz funkcjê, która dostaje jako argument dodatni¹ liczbê ca³kowit¹ n, rezerwuje w pamiêci blok n
	zmiennych typu ‘int *’ i zwraca jako wartoœæ wskaŸnik do pocz¹tku zarezerwowanego bloku pamiêci.
*/

int* zad8_funkcja(int n) {
	int* wsk = (int*)malloc(sizeof(int*) * n);
	return wsk;
}

void zad8() {
	int n = 10;
	cout << zad8_funkcja(n) << endl;
}

// ZAD 9
/*	Napisz funkcjê która dostaje jako argumenty dwa wskaŸniki na tablice jednowymiarowe tegosamego
	rozmiaru oraz dodatni¹ liczbê zawieraj¹c¹ iloœæ elementów w tablicy. Zadaniem funkcji jest zamiana
	wartoœci zapisanych w tablicach. Wyœwietl zawartoœci tablic prze i po zmianie.	
*/

void zad9_funkcja(int* tab1, int* tab2, int n) {
	for (int i = 0; i < n; i++) {
		tab1[i] = i;
		tab2[i] = i;
	}

	cout << endl << "Po:" << endl << endl;

	for (int i = 0; i < n; i++) {
		printf("tab1[%d] = %d | tab2[%d] = %d\n", i, tab1[i], i, tab2[i]);
	}
}

void zad9() {
	const int n = 10;
	int tab1[n] = { 1,2,3,4,5,6,7,8,9,10 };
	int tab2[n] = { 1,2,3,4,5,6,7,8,9,10 };
	int* wsk1 = &tab1[0];
	int* wsk2 = &tab2[0];

	for (int i = 0; i < n; i++) {
		printf("tab1[%d] = %d | tab2[%d] = %d\n", i, tab1[i], i, tab2[i]);
	}

	zad9_funkcja(wsk1, wsk2, n);
}

// ZAD 10
/*  Napisz funkcjê która dostaje jako argumenty dwa wskaŸniki na tablice jednowymiarowe ró¿nego rozmiaru
	oraz dwie dodatnie liczby zawieraj¹c¹ iloœci elementów w tablicach. Zadaniem funkcji jest zamiana
	wartoœci zapisanych w tablicach – nale¿y zwróciæ uwagê ¿e jedna tablica mo¿e zawieraæ mniej elementów
	od drugiej. Wyœwietl zawartoœci tablic przed i po zmianie
*/

void zad10_funkcja(int* tab1, int* tab2, int n, int m) {
	int pauza = 0;
	int zamiennik = 0;
	bool check = true;

	if (n >= m) {
		pauza = m;
		check = true;
	}
	else {
		pauza = n;
		check = false;
	}

	for (int i = 0; i < pauza; i++) {
		zamiennik = tab1[i];
		tab1[i] = tab2[i];
		tab2[i] = zamiennik;
	}

	cout << endl << " Po:" << endl << endl;

	for (int i = 0; i < pauza; i++) {
		printf("tab1[%d] = %d | tab2[%d] = %d\n", i, tab1[i], i, tab2[i]);
	}

	if (check == true) {
		for (int i = pauza; i < n; i++) {
			printf("tab1[%d] = %d |\n", i, tab1[i]);
		}
	}
	else {
		for (int i = pauza; i < m; i++) {
			printf("            | tab2[%d] = %d\n", i, tab2[i]);
		}
	}
}

void zad10() {
	const int n = 5, m = 10;
	int tab1[n] = { 5,4,3,2,1 };
	int tab2[m] = { 1,2,3,4,5,6,7,8,9,10 };

	int* wsk1 = &tab1[0];
	int* wsk2 = &tab2[0];

	int pauza = 0;
	bool check = true;

	if (n >= m) {
		pauza = m;
		check = true;
	}
	else {
		pauza = n;
		check = false;
	}

	for (int i = 0; i < pauza; i++) {
		printf("tab1[%d] = %d | tab2[%d] = %d\n", i, tab1[i], i, tab2[i]);
	}

	if (check == true) {
		for (int i = pauza; i < n; i++) {
			printf("tab1[%d] = %d |\n", i, tab1[i]);
		}
	}
	else {
		for (int i = pauza; i < m; i++) {
			printf("            | tab2[%d] = %d\n", i, tab2[i]);
		}
	}

	zad10_funkcja(wsk1, wsk2, n, m);
}

// ZAD 11
/*  Napisz funkcjê, która dostaje jako argument dodatnie liczby ca³kowite n i m, tworzy dynamiczn¹
	dwuwymiarow¹ tablicê tablic elementów typu int o wymiarach n na m, i zwraca jako wartoœæ wskaŸnik do
	niej.
*/

int** zad11_funkcja(int n, int m) {
	int** tab = (int**)malloc(sizeof(int*) * n);

	for (int i = 0; i < n; i++) {
		tab[i] = (int*)malloc(sizeof(int) * m);
	}

	return tab;
}

void zad11() {
	int n = 5;
	int m = 10;

	int** wsk = zad11_funkcja(n, m);

	cout << zad11_funkcja(n, m) << endl;

	for (int i = 0; i < n; i++) {
		free(wsk[i]);
	}
	free(wsk);
}

// ZAD 12
/*  Napisz funkcjê, która dostaje jako argumenty wskaŸnik do tablicy dwuwymiarowej elementów typu int
	oraz jej wymiary n i m, i usuwa z pamiêci otrzyman¹ tablicê.
*/

void zad12_funkcja(int** wsk, int n, int m) {
	for (int i = 0; i < n; i++) {
		free(wsk[i]);
	}
	free(wsk);
}

void zad12() {
	int n = 5;
	int m = 10;

	int** wsk = zad11_funkcja(n, m);

	zad12_funkcja(wsk, n, m);
}

// ZAD 13
/*  Rozwi¹¿ powy¿sze dwa zadania w wersji z trójwymiarowymi tablicami.
*/

int*** zad13_funkcja_tworzenia(int n, int m, int o) {
	int*** tab = (int***)malloc(sizeof(int**) * n);

	for (int i = 0; i < n; i++) {
		tab[i] = (int**)malloc(sizeof(int*) * m);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			tab[i][j] = (int*)malloc(sizeof(int) * o);
		}
	}

	return tab;
}

void zad13_funkcja_usuwania(int*** wsk, int n, int m, int o) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			free(wsk[i][j]);
		}
	}

	for (int i = 0; i < n; i++) {
		free(wsk[i]);
	}

	free(wsk);
}

void zad13() {
	int n = 5;
	int m = 10;
	int o = 15;

	int*** wsk = zad13_funkcja_tworzenia(n, m, o);

	zad13_funkcja_usuwania(wsk, n, m, o);
}

// ZAD 14
/*	Napisz funkcjê, która dostaje w argumentach tablicê dwuwymiarow¹ elementów typu int oraz jej wymiary
	n i m, i wype³nia j¹ zerami.
*/

void zad14_funkcja(int** wsk, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			wsk[i][j] = 0;
		}
	}
}

void zad14() {
	int n = 5, m = 10;
	int** wsk = zad11_funkcja(n, m);

	zad14_funkcja(wsk, n, m);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("tab[%d][%d] = %d ", i, j, wsk[i][j]);
		}
		cout << endl;
	}

	zad12_funkcja(wsk, n, m);
}

// ZAD 15
/*  Napisz funkcjê, która dostaje w argumentach tablicê dwuwymiarow¹ o elementach typu int oraz jej
	wymiary n i m, i zwraca jako wartoœæ sumê wartoœci elementów tablicy.
*/

void zad15_funkcja_zapisania_liczb(int** wsk, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			wsk[i][j] = j;
		}
	}
}

int zad15_funkcja(int** wsk, int n, int m) {
	int suma = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			suma += wsk[i][j];
		}
	}
	return suma;
}

void zad15() {
	int n = 5, m = 10;
	int** wsk = zad11_funkcja(n, m);

	zad15_funkcja_zapisania_liczb(wsk, n, m);
	cout << "Suma elementow tablic jest rowna: " << zad15_funkcja(wsk, n, m) << endl;
	zad12_funkcja(wsk, n, m);
}

// ZAD 16
/*  Napisz funkcjê, która dostaje jako argumenty dwuwymiarow¹ tablicê tablic o elementach typu int oraz jej
	wymiary, i zwraca jako wartoœæ indeks wiersza o najwiêkszej œredniej wartoœci elementów. Przyjmujemy,
	¿e dwa elementy le¿¹ w tym samym wierszu, je¿eli maj¹ taki sam pierwszy indeks.
*/

void zad16_funkcja_zapisania_roznych_liczb(int** wsk, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			wsk[i][j] = i + j;
		}
	}
}

int zad16_funkcja(int** wsk, int n, int m) {
	int najwiekszy_wiersz = 0;
	int poprzednia_srednia = 0;
	int srednia = 0;

	for (int i = 0; i < n; i++) {
		srednia = 0;
		for (int j = 0; j < m; j++) {
			srednia += wsk[i][j];
		}
		if (srednia > poprzednia_srednia) {
			najwiekszy_wiersz = i;
			poprzednia_srednia = srednia;
		}
	}

	return najwiekszy_wiersz;
}

void zad16() {
	int n = 5, m = 10;
	int** wsk = zad11_funkcja(n, m);

	zad16_funkcja_zapisania_roznych_liczb(wsk, n, m);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("tab[%d][%d] = %d ", i, j, wsk[i][j]);
		}
		cout << endl;
	}

	cout << "Indeks wiersza o najwiekszej sredniej wartosci elementow: " << zad16_funkcja(wsk, n, m) << endl;
	zad12_funkcja(wsk, n, m);
}

int main() {
	//zad1();
	//zad2();
	//zad3();
	//zad4();
	//zad5();
	//zad6();
	//zad7();
	//zad8();
	//zad9();
	//zad10();
	//zad11();
	//zad12();
	//zad13();
	//zad14();
	//zad15();
	zad16();
}