#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	printf("INST. WARUNKOW I WYBORU\n\n");
	// ZAD 1
	/* Napisz program, który wczytuje ze standardowego wejœcia liczbê ca³kowit¹ n i wypisuje na standardowe wyjœcie
	   wartoœæ bezwzglêdn¹ z n.Do rozwi¹zania zadania nie u¿ywaj funkcji bibliotecznych za wyj¹tkiem operacji
	   wejœcia / wyjœcia. */

	/*
	int a;
	scanf_s("%d", &a);
	if (a < 0) {
		a *= -1;
	}
	printf("%d", a);
	*/

	// ZAD 2
	/* Napisz program, który wczytuje ze standardowego wejœcia dwie liczby ca³kowite i wypisuje na standardowym
	   wyjœciu wiêksz¹ z nich (w przypadku gdy podane liczby s¹ równe, program powinien wypisaæ któr¹kolwiek z
       nich). 
	*/

	/*
	int a, b;
	scanf_s("%d", &a);
	scanf_s("%d", &b);
	if (a >= b) {
		printf("%d", a);
	}
	else {
		printf("%d", b);
	}
	*/

	// ZAD 3
	/* Napisz program, który wczytuje ze standardowego wejœcia trzy liczby ca³kowite i wypisuje na standardowym
	   wyjœciu najwiêksz¹ z ich wartoœci (pamiêtaj o przypadku gdy wszystkie podane liczby lub dwie z nich s¹ równe).
	*/

	/*
	int a, b, c;
	scanf_s("%d", &a);
	scanf_s("%d", &b);
	scanf_s("%d", &c);
	if (a >= b) {
		if (a >= c) {
			printf("%d", a);
		}
		else {
			printf("%d", c);
		}
	}
	else {
		if (b >= c) {
			printf("%d", b);
		}
		else {
			printf("%d", c);
		}
	}
	*/

	// ZAD 4
	/* Napisz program, który wczytuje ze standardowego wejœcia dwie liczby ca³kowite i wypisuje t¹ o wiêkszej
	   wartoœci bezwzglêdnej.
	*/

	/*
	int a, b, a1, b1;
	scanf_s("%d", &a);
	scanf_s("%d", &b);
	a1 = a;
	b1 = b;
	if (a < 0) {
		a *= -1;
	}
	if (b < 0) {
		b *= -1;
	}
	if (a >= b) {
		printf("%d", a1);
	}
	else {
		printf("%d", b1);
	}
	*/

	// ZAD 5
	/* Napisz program obliczaj¹cy pole trójk¹ta na podstawie wymiarów podanych przez u¿ytkownika. U¿ytkownik
	   powinien mieæ mo¿liwoœæ podania d³ugoœci podstawy i wysokoœci lub wszystkich boków trójk¹ta. 
	*/

	/*
	int wybor, a, b, c, h, p;
	float wynik;
	printf("Pole trojkata na podstawie:\n\n1) Dlugosci podstawy i wysokosci.\n2) Dlugosci wszystkich bokow trojkata\n");
	scanf_s("%d", &wybor);
	switch (wybor) {
	case 1:
		printf("\nPodaj dlugosc podstawy: ");
		scanf_s("%d", &a);
		printf("Podaj dlugosci wysokosci: ");
		scanf_s("%d", &h);
		wynik = a * h / 2;
		break;
	case 2:
		printf("\nPodaj dlugosc boku a: ");
		scanf_s("%d", &a);
		printf("Podaj dlugosc boku b: ");
		scanf_s("%d", &b);
		printf("Podaj dlugosc boku c: ");
		scanf_s("%d", &c);
		p = (a + b + c) / 2;
		wynik = sqrt(p * (p - a) * (p - b) * (p - c));
		break;
	}
	printf("\nPole trojkata wynosi: %.2f", wynik);
	*/

	// ZAD 6
	/* Napisz program, który wczytuje ze standardowego wejœcia wspó³czynniki uk³adu dwóch równañ liniowych z
	   dwoma niewiadomymi i wypisuje na standardowym wyjœciu rozwi¹zanie uk³adu równañ. W przypadku
	   nieskoñczonej liczby lub braku rozwi¹zañ program powinien wypisaæ na standardowym wyjœciu odpowiedni¹
	   informacjê.
	*/

	/*
	float a1, b1, a2, b2, c1, c2, wg, wx, wy, x, y;
	printf("(a1) * x + (b1) * y = (c1)\n");
	printf("(a2) * x + (b2) * y = (c2)\n\n");
	printf("a1: ");
	scanf_s("%f", &a1);
	printf("b1: ");
	scanf_s("%f", &b1);
	printf("c1: ");
	scanf_s("%f", &c1);
	printf("a2: ");
	scanf_s("%f", &a2);
	printf("b2: ");
	scanf_s("%f", &b2);
	printf("c2: ");
	scanf_s("%f", &c2);

	wg = (a1 * b2) - (b1 * a2);
	wx = (c1 * b2) - (b1 * c2);
	wy = (a1 * c2) - (c1 * a2);

	x = wx / wg;
	y = wy / wg;

	if (isinf(x) || isinf(y)) {
		printf("Uklad sprzeczny, brak rozwiazan");
	}
	else if (isnan(x) || isnan(y)){
		printf("Uklad nieoznaczony, ma nieskonczenie wiele rozwiazan");
	}
	else {
		printf("\nX jest rowne: %2.f\nY jest rowne: %2.f", x, y);
	}
	*/

	// ZAD 7
	/* Napisz program, który wczytuje ze standardowego wejœcia wspó³czynniki równania kwadratowego z jedn¹
	   niewiadom¹ i wypisuje na standardowym wyjœciu wszystkie rozwi¹zania rzeczywiste tego równania lub
	   odpowiedni¹ informacjê w przypadku braku rozwi¹zañ.
	*/

	/*
	float a, b, c, delta, x1, x2;
	printf("(a)x^2 + (b)x + (c) = 0\n\n");
	printf("a: ");
	scanf_s("%f", &a);
	printf("b: ");
	scanf_s("%f", &b);
	printf("c: ");
	scanf_s("%f", &c);

	delta = b * b - (4 * a * c);

	if (delta > 0) {
		x1 = (-b - sqrt(delta)) / (2 * a);
		x2 = (-b + sqrt(delta)) / (2 * a);
		printf("Rownanie ma 2 rozwiazania:\nx1: %2.f  x2: %2.f", x1, x2);
	}
	else if (delta == 0) {
		x1 = -b / (2 * a);
		printf("Rownanie ma 1 rozwiazanie:\nx1: %2.f", x1);
	}
	else {
		printf("Rownanie nie ma rozwiazan");
	}
	*/

	// ZAD 8 
	/* Napisz program, który w zale¿noœci od wyboru u¿ytkownika wczytuje ze standardowego wejœcia wymiary:
	   kwadratu, prostok¹ta lub trójk¹ta i wypisuje na standardowym wyjœciu pole figury o wczytanych wymiarach.
	*/

	/*
	int wybor;
	float wynik, a, b, c, p;
	printf("Oblicz pole:\n1) Kwadratu\n2) Prostokata\n3) Trojkata\n");
	scanf_s("%d", &wybor);
	switch (wybor) {
	case 1:
		printf("Podaj dlugosc boku a kwadratu: ");
		scanf_s("%f", &a);
		wynik = a * a;
		printf("Pole kwadratu wynosi: %2.f", wynik);
		break;
	case 2:
		printf("Podaj dlugosc boku a prostokata: ");
		scanf_s("%f", &a);
		printf("Podaj dlugosc boku b prostokata: ");
		scanf_s("%f", &b);
		wynik = a * b;
		printf("Pole prostokatu wynosi: %2.f", wynik);
		break;
	case 3:
		printf("Podaj dlugosc boku a trojkata: ");
		scanf_s("%f", &a);
		printf("Podaj dlugosc boku b trojkata: ");
		scanf_s("%f", &b);
		printf("Podaj dlugosc boku c trojkata: ");
		scanf_s("%f", &c);
		p = (a + b + c) / 2;
		wynik = sqrt(p * (p - a) * (p - b) * (p - c));
		printf("Pole trojkata wynosi: %2.f", wynik);
		break;
	}
	*/

	// ZAD 9
	/* Napisz program kalkulator, który wykonuje wybran¹ przez u¿ytkownika operacj¹ arytmetyczn¹ na dwóch
	   wczytanych liczbach. Program powinien wczytywaæ dane ze standardowego wejœcia i wypisywaæ wynik na
	   standardowym wyjœciu.
	*/

	/*
	float a, b, wynik;
	int wybor;
	printf("Kalkulator\n\nPodaj pierwsza liczbe: ");
	scanf_s("%f", &a);
	printf("\n1) Dodawanie\n2) Odejmowanie\n3) Mnozenie\n4) Dzielenie\n");
	scanf_s("%d", &wybor);
	printf("Podaj druga liczbe: ");
	scanf_s("%f", &b);
	switch (wybor) {
	case 1:
		wynik = a + b;
		break;
	case 2:
		wynik = a - b;
		break;
	case 3:
		wynik = a * b;
		break;
	case 4:
		wynik = a / b;
		break;
	}
	printf("\nWynik dzialania: %2.f", wynik);
	*/
}