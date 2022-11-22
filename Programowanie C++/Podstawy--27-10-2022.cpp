#include <iostream>
using namespace std;

int main()
{
    // ZAD 1
    // Napisz program wypisujący na standardowym wyjściu napis "Hello World"
    /*
    printf("Hello World!\n");
    */
    
    // ZAD 2
    // Napisz program wypisujący w kolejnych wierszach standardowego wyjścia pojedyncze słowa następującego napisu "Bardzo długi napis"
    /*
    printf("Bardzo\ndlugi\nnapis");
    */

    // ZAD 3
    // Napisz program wypisujący na standardowym wyjściu następujący napis "Napis zawierający różne dziwne znaczki //\ \ $ & %"
    /*
    printf("Napis zawierajacy rozne dziwne znaczki //\\ \\$ & %");
    */

    // ZAD 4
    // Napisz program, który wczytuje ze standardowego wejścia liczbę całkowitą i wypisuje ją na standardowym wyjściu
    /*
    int a;
    scanf_s("%d", &a);
    printf("%d", a);
    */

    // ZAD 5
    // Napisz program, który wczytuje ze standardowego wejścia liczbę wymierną i wypisuje ją na standardowym wyjściu
    /*
    float a;
    scanf_s("%f", &a);
    printf("%f", a);
    */

    // ZAD 6
    // Napisz program, który wczytuje ze standardowego wejścia trzy liczby całkowite, a następnie wypisuje je w oddzielnych liniach na standardowym wyjściu
    /*
    int a, b, c;
    scanf_s("%d %d %d", &a, &b, &c);
    printf("%d\n%d\n%d\n", a, b, c);
    */

    // ZAD 7
    // Napisz program, który wczytuje ze standardowego wejścia liczbę całkowitą i wypisuje na standardowym wyjściu liczbę o jeden większą
    /*
    int a;
    scanf_s("%d", &a);
    a++;
    printf("%d", a);
    */

    // ZAD 8
    // Napisz program, który wczytuje ze standardowego wejścia trzy liczby całkowite i wypisuje na standardowym wyjściu ich średnią arytmetyczną
    /*
    int a, b, c;
    float srednia;
    scanf_s("%d %d %d", &a, &b, &c);
    srednia = float(a + b + c) / 3;
    printf("%f", srednia);
    */

    // ZAD 9
    // Napisz program, który wczytuje ze standardowego wejścia nieujemną liczbę wymierną x i wypisuje na standardowym wyjściu sqrt(x)
    /*
    float a, wynik;
    scanf_s("%f", &a);
    if (a < 0) {
        a *= -1;
    }
    wynik = sqrt(a);
    printf("%f", wynik);
    */

    // ZAD 10
    // Napisz program, który wczytuje ze standardowego wejścia liczbę wymierną x i wypisuje na standardowym wyjściu wartość bezwzględną z x
    /*
    float a;
    scanf_s("%f", &a);
    if (a < 0) {
        a *= -1;
    }
    printf("%f", a);
    */

    // ZAD 11
    // Napisz program, który wczytuje ze standardowego wejścia liczbę wymierną i wypisuje ją na standardowym wyjściu z dokładnością do dwóch miejsc po przecinku
    /*
    float a;
    scanf_s("%f", &a);
    printf("%.2f", a);
    */

    // ZAD 12
    // Napisz program, który wczytuje ze standardowego wejścia liczbę wymierną i wypisuje ją na standardowym wyjściu w notacji wykładniczej (czyli takiej, w której 0.2 to 2.0e-1)
    /*
    float a;
    scanf_s("%f", &a);
    printf("%e", a);
    */
}

