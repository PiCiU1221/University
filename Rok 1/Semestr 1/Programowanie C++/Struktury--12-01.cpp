#include <iostream>
#include <cmath>

using namespace std;

//  STRUKTURY 12.01

//  ZAD 1
/*  Zdefiniuj strukturê trojkat przechowuj¹c¹ d³ugoœci boków trójk¹ta. Napisz funkcjê, która otrzymuje jako
	argument zmienn¹ typu struct trojkat, i zwraca jako wartoœæ obwód trójk¹ta przekazanego w argumencie.
*/

struct trojkat {
	int bokA, bokB, bokC;
};

int obwodTrojkata(trojkat trojkat1) {
	return trojkat1.bokA + trojkat1.bokB + trojkat1.bokC;
}

//  ZAD 2
/*  Napisz funkcjê, która otrzymuje jako argumenty zmienn¹ troj1 typu struct trojkat zdefiniowanego w
	poprzednim zadaniu oraz zmienn¹ troj2 wskaŸnik na zmienn¹ typu struct trojkat, i przepisuje zawartoœæ
	zmiennej troj1 do zmiennej wskazywanej przez troj2.
*/

void zad2(trojkat* troj1, trojkat* troj2) {
	cout << troj1 << endl;
	memcpy(troj2, troj1, sizeof(troj1));
}

//  ZAD 3
/*	Zdefiniuj strukturê punkt s³u¿¹c¹ do przechowywania wspó³rzêdnych punktów w trójwymiarowej
	przestrzeni kartezjañskiej. Napisz funkcjê, która otrzymuje jako argumenty tablicê tab o argumentach typu
	struct punkt oraz jej rozmiar, i zwraca jako wartoœæ najmniejsz¹ spoœród odleg³oœci pomiêdzy punktami
	przechowywanymi w tablicy tab. Zak³adamy, ¿e otrzymana w argumencie tablica ma co najmniej dwa
	argumenty.
*/

struct punkt {
	int X;
	int Y;
	int Z;
};

double obliczenieOdleglosci(punkt tab[], int tabSize) {
	double najmniejszaOdleglosc = sqrt((tab[0].X - tab[1].X) * (tab[0].X - tab[1].X) + (tab[0].Y - tab[1].Y) * (tab[0].Y - tab[1].Y) + (tab[0].Z - tab[1].Z) * (tab[0].Z - tab[1].Z));
	double obliczenia = 0;
	for (int i = 0; i < tabSize; i++) {
		for (int j = 0; j < tabSize; j++) {
			if (j != i) {
				obliczenia = sqrt((tab[i].X - tab[j].X) * (tab[i].X - tab[j].X) + (tab[i].Y - tab[j].Y) * (tab[i].Y - tab[j].Y) + (tab[i].Z - tab[j].Z) * (tab[i].Z - tab[j].Z));
				/*cout << tab[i].X << " ";
				cout << tab[i].Y << " ";
				cout << tab[i].Z << " ";
				cout << tab[j].X << " ";
				cout << tab[j].Y << " ";
				cout << tab[j].Z << "  ";
				cout << (tab[i].X - tab[j].X) * (tab[i].X - tab[j].X) << " ";
				cout << (tab[i].Y - tab[j].Y) * (tab[i].Y - tab[j].Y) << " ";
				cout << (tab[i].Z - tab[j].Z) * (tab[i].Z - tab[j].Z) << "  ";
				cout << obliczenia << endl;*/
				if (obliczenia < najmniejszaOdleglosc) {
					najmniejszaOdleglosc = obliczenia;
				}
			}
		}
	}
	return najmniejszaOdleglosc;
}

//  ZAD 4
/*  Napisz funkcjê, która otrzymuje jako argumenty tablice tab1 i tab2 o argumentach typu struct punkt
	zdefiniowanego w rozwi¹zaniu poprzedniego zadania oraz ich rozmiar, i przepisuje zwartoœæ tablicy tab1 do
	tablicy tab2.
*/

void zad4(punkt tab1[], punkt tab2[]) {
	for (int i = 0; i < 4; i++) {
		tab2[i] = tab1[i];
	}
}

//  ZAD 6
/*  Zdefiniuj strukturê zespolone s³u¿¹c¹ do przechowywania liczb zespolonych. Zdefiniowana struktura
	powinna zawieraæ pola im i re typu double s³u¿¹ce do przechowywania odpowiednio czêœci urojonej i
	rzeczywistej liczby zespolonej. Napisz funkcjê dodaj, która dostaje dwa argumenty typu zespolone i zwraca
	jako wartoœæ ich sumê.
*/

struct zespolone {
	double re;
	double im;
};

auto zad6(zespolone liczba1, zespolone liczba2) {
	zespolone wynik = { 0, 0 };
	wynik.re = liczba1.re + liczba2.re;
	wynik.im = liczba1.im + liczba2.im;
	return wynik;
}

//  ZAD 7
/* Zdefiniuj strukturê student s³u¿¹c¹ do przechowywania danych osobowych studenta (struktura powinna
	zawieraæ takie pola, jak: imie, nazwisko, adres, pesel, kierunek i numer legitymacji). Napisz funkcjê, która
	otrzymuje jako argument wskaŸnik na strukturê student i wczytuje dane ze standardowego wejœcia do
	rekordu wskazywanego przez argument funkcji.
*/

struct student {
	string imie;
	string nazwisko;
	string pesel;
	long numer_legitymacji;
};

void zad7(student* student) {
	string string = "";
	long integer = 0;

	printf("Imie: ");
	cin >> string;
	student->imie = string;
	printf("Nazwisko: ");
	cin >> string;
	student->nazwisko = string;
	printf("Pesel: ");
	cin >> string;
	student->pesel = string;

	printf("Numer legitymacji: ");
	cin >> integer;
	student->numer_legitymacji = integer;
}

int main() {
	// ZAD 2 
	/*
	trojkat troj1 = { 1, 2, 3 };
	trojkat troj2 = { 3, 4, 5 };

	zad2(&troj1, &troj2);

	cout << troj1.bokA;
	cout << troj2.bokA;
	*/

	// ZAD 3
	/*
	punkt tab[] = { {1,2,3}, {3,4,5}, {1,2,1}, {4,5,6} };
	cout << obliczenieOdleglosci(tab, 4);
	*/

	// ZAD 4
	/*
	punkt tab1[] = { {1,2,3}, {3,4,5}, {1,2,1}, {4,5,6} };
	punkt tab2[] = { {1,2,3}, {1,2,1}, {4,5,6}, {1,2,1} };

	zad4(tab1, tab2);

	for (int i = 0; i < 4; i++) {
		cout << tab2[i].X << endl;
	}
	*/

	// ZAD 7

	/*
	student student = { "Jan", "Nowak", "035454548", 52800 };
	cout << student.imie << " " << student.nazwisko << " ";
	cout << student.pesel << " " << student.numer_legitymacji << endl;

	zad7(&student);

	cout << student.imie << " " << student.nazwisko << " ";
	cout << student.pesel << " " << student.numer_legitymacji << endl;
	*/
}