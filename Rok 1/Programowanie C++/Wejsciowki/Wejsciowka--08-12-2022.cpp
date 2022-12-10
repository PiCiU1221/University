#include <iostream>

using namespace std;

//  120A - Piotr Pietrusewicz

int zad1_funkcja(int tab[], int n) {
	int srednia = 0;
	for (int i = 0; i < n; i++) {
		srednia += tab[i];
	}
	return srednia / n;
}

void zad1() {
	const int n = 10;
	int tab[n] = { 1,2,3,4,5,6,7,8,9,10 };
	
	 printf("Srednia arytmetyczna elementow tablicy jest rowna: %d\n", zad1_funkcja(tab, n));
}

int zad2_funkcja(int n) {
	if (n < 2) {
		return 1;
	}
	else {
		return n * zad2_funkcja(n - 1);
	}
}

void zad2() {
	int n = 0;
	cout << "Wpisz n: ";
	cin >> n;
	cout << "Silnia z " << n << " jest rowna: " << zad2_funkcja(n) << endl;
}

void zad3_funkcja(int a, int b, int c) {
	if (a < b) {
		if (a < c) {
			if (b < c) {
				cout << a << b << c;
			}
			else {
				cout << a << c << b;
			}
		}
		else {
			cout << c << a << b;
		}
	}
	else {
		if (b < c) {
			if (a < c) {
				cout << b << a << c;
			}
			else {
				cout << b << c << a;
			}
		}
		else {
			cout << c << b << a;
		}
	}
}

void zad3() {
	int a = 2, b = 1, c = 3;
	zad3_funkcja(a, b, c);
}

int main() {
	// 1. funkcja ktora zwroci srednia arytmetyczna tablicy przekazanej do tej funkcji
	//	  dowolna ilosc elementow
	// 2. funkcja ktora zwroci silnie dla przekazanej wartosci w sposob rekurencyjny
	// 3. funkcja ktora wyswietli wartosci parametrow na ekranie rosnacych (3 int)

	zad1();
	zad2();
	zad3();
}