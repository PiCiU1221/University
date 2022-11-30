// Piotr Pietrusewicz 3TI16 @2020
#include <iostream>
#include <string>

using namespace std;

int main()
{
    // deklarowanie zmiennych i tablic
    char litery[26];
    char litera = 'A';

    int liczby[26];
    int liczba = 26;

    string wyraz;

    int index = 0;

    // petla do przypisania wartosci do tablic "litery" oraz "liczby"
    do {
        litery[index] = litera;
        liczby[index] = liczba;

        // komendy pomocnicze do sprawdzenia dzialania programu:
        // cout << "Litery[" << index << "]= " << litera << endl;
        // cout << "Liczby[" << index << "]= " << liczba << endl;
        // cout << "" << endl;

        index++;
        litera++;
        liczba++;
    } while (index < 26);

    cout << "= Program do szyfrowania wyrazow =" << endl;
    cout << "" << endl;
    cout << "Podaj wyraz do zaszyfrowania: ";
    // wprowadzenie wyrazu do zaszyfrowania
    cin >> wyraz;
    cout << "" << endl;

    // petla do sprawdzenia czy uzytkownik wprowadzil liczbe, co spowodowaloby zle wyniki
    for (int i = 0; i < wyraz.length(); i++)
    {
        if (isdigit(wyraz[i]))
        {
            cout << "Wprowadziles liczbe zamiast litery!" << endl;
            return 0;
        }
    }

    // petla do "zwiekszenia" liter we wprowadzonym wyrazie jesli uzytkownik tego sam nie zrobil, by nie wystapil blad
    for (int i = 0; i < wyraz.length(); i++)
    {
        wyraz[i] = toupper(wyraz[i]);
    }

    // utworzenie tablicy z zaszyfrowanym wyrazem
    int zaszyfrowane[wyraz.length()];

    // petla do porownania liter z wyrazu do zaszyfrowania z tablica liter i przypisanie jego liter do odpowiednich indeksow tabeli "liczby"
    // oraz przypisanie tabeli "zaszyfrowane" odpowiednikow liter z szyfru
    for (int i = 0; i < wyraz.length(); i++)
    {
        for (int j = 0; j < 25; j++)
        {
            if (wyraz[i] == litery[j])
            {
                zaszyfrowane[i] = liczby[j];
            }
        }
    }

    // petla do wypisania wartosci tablicy "zaszyfrowane"
    cout << "Zaszyfrowany wyraz: ";
    for (int i = 0; i < wyraz.length(); i++)
    {
        cout << zaszyfrowane[i];
    }
    cout << "" << endl;
    return 0;
}
