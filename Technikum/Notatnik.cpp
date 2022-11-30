//Program "Dziennik"
//Piotr Pietrusewicz 3TI @2021

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <conio.h>
#include <chrono>
#include <ctime>
#include <stdio.h>
#include <time.h>
#include <windows.h>

using namespace std;

//wczesna deklaracja uzywanych funkcji by uniknac pozniejszych bledow
void menu();
void wyswietl();
void dodawanie();
void dodawanie_dalsze();
void edytowanie();
void usuwanie();
void indeksowanie();
void powrot_do_menu();

//funkcja do podania daty i godziny w formacie YYYY-MM-DD.HH:mm:ss
const string currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d . %X", &tstruct);
    //zwrocenie wartosci funkcji
    return buf;
}

//glowny program
int main()
{
    //przywolanie funkcji menu
    menu();
    return 0;
}

//funkcja menu
void menu()
{
    //czyszczenie ekranu
    system("CLS");

    //menu tekstowe
    cout << " Piotr Pietrusewicz 3TI @2021" << endl;
    cout << "" << endl;
    cout << "= Program tworzacy dopiski do dziennika =" << endl;
    cout << "" << endl;
    cout << " = MENU =" << endl;
    cout << "[1] Wyswietl zawartosc dziennika" << endl;
    cout << "[2] Dodaj kolejny wpis" << endl;
    cout << "[3] Edytuj wpis" << endl;
    cout << "[4] Usuwanie wpisow" << endl;
    cout << "[5] Wyjscie z programu" << endl;
    cout << "" << endl;
    cout << "Twoj wybor: ";

    //tworzenie zmiennej wyboru i wpisanie go przez uzytkownika
    cin.clear();
    int wybor;
    cin >> wybor;

    //czyszczenie ekranu
    system("CLS");

    //menu wyboru
    switch(wybor)
    {
    case 1:
        //funkcja wyswietlania
        wyswietl();
        powrot_do_menu();
    case 2:
        //funkcja dodawania
        dodawanie();
    case 3:
        //funkcja usuwania
        edytowanie();
    case 4:
        //funkcja usuwania
        usuwanie();
    case 5:
        //funkcja do wychodzenia
        cout << "" << endl;
        cout << "Stworzone przez: Piotr Pietrusewicz @2021" << endl;
        exit(0);
    default:
        //czyszczenie zlego inputu by uniknac bledu
        cin.clear();
        cin.ignore(INT_MAX, '\n');

        //wyprowadzenie komunikatu
        cout << "Wpisales niepoprawna liczbe" << endl;

        //powrot do menu po wyswietleniu komunikatu bledu
        powrot_do_menu();
    }
}

//funkcja wyswietlenia
void wyswietl()
{
    //deklaracja zmiennych
    fstream plik;
    string tekst;

    //czyszczenie ekranu
    system("CLS");

    //otwarcie strumienia pliku i sprawdzenie czy plik tekstowy istnieje
    plik.open("Dziennik.txt");
    if (plik.fail())
    {
        //plik nie istnieje
        plik.close();
        cout <<"Plik nie istnieje, przejdz do opcji dodania wpisu by go utworzyc" << endl;
        powrot_do_menu();
    }
    else
    {
        //plik istnieje
        while(!plik.eof())
        {
            //wyciagniecie linii tekstu do zmiennej
            getline( plik, tekst );

            //wyswietlenie zawartosci
            cout << tekst << endl;
        }
        //zamkniecie pliku po wykonanych operacjach
        plik.close();
    }
}

//funkcja dodawania wpisow
void dodawanie()
{
    fstream plik;

    //otworzenie dostepu do pliku
    plik.open ("Dziennik.txt", ios::app );
    if( plik.fail() == true )
    {
        // w przypadku braku dostepu do pliku, np. przeniesienie do innego folderu
        plik.close();
        cout << "Brak dostepu!" << endl;
    }
    else
    {
        //usuniecie bledu z cin
        cin.ignore();
        string data_czas = currentDateTime();

        cout << "Wprowadz nowy wpis ponizej. By przerwac wpisywanie wpisz znak '/' przed nacisnieciem klawisza enter." << endl;
        cout << "" << endl;

        //wprowadzanie wpisu
        string tekst;
        getline(cin,tekst);

        //dodanie zmiennej z naglowkiem
        string naglowek = "00. ================================================================\n";
        plik << naglowek;

        //sprawdzenie czy wykonac powtornie funkcje
        if(!(tekst.find('/')<tekst.length()))
        {
            //upiekszenie i formatowanie koncowe wpisu
            string wpis = "00.                        " + data_czas + "\n" + "00. \n" + "00. " + tekst + "\n";

            //zapisywanie wpisu
            plik << wpis;
            plik.close();

            //przywolanie funkcji pomocniczej do dalszego dodawania tekstu
            dodawanie_dalsze();
        }
        else
        {
            //usuniecie z tekstu znaku zakonczenia wprowadzania
            tekst.erase(tekst.size()-1);

            //upiekszenie i formatowanie koncowe wpisu
            string wpis = "00.                        " + data_czas + "\n" + "00. \n" + "00. " + tekst + "\n";

            //zapisywanie wpisu
            plik << wpis;
            plik.close();

            //przywolanie funkcji indeksowania dla automatycznego przyporzadkowania indeksow linii
            indeksowanie();
        }
    }
}

//funkcja do dalszego dodawania wpisow
void dodawanie_dalsze()
{
    fstream plik;

    //otwarcie dostepu do pliku
    plik.open ("Dziennik.txt", ios::app );

    //przerwa dla estetyki
    cout << "" << endl;

    //wprowadzanie wpisu
    string tekst;
    getline(cin,tekst);

    //sprawdzenie czy wykonac powtornie funkcje
    if(!(tekst.find('/')<tekst.length()))
    {
        //upiekszenie i formatowanie koncowe wpisu
        string wpis = "00. " + tekst + "\n";

        //zapisywanie wpisu
        plik << wpis;
        plik.close();

        //przejscie do funkcji pomocniczej
        dodawanie_dalsze();
    }
    else
    {
        //usuniecie z tekstu znaku zakonczenia wprowadzania
        tekst.erase(tekst.size()-1);

        //upiekszenie i formatowanie koncowe wpisu
        string wpis = "00. " + tekst + "\n";

        //zapisywanie wpisu
        plik << wpis;
        plik.close();

        //otwarcie pliku by dodac upiekszajaca stopke
        plik.open ("Dziennik.txt", ios::app );

        //dodanie stopki
        string stopka = "00. \n" + string("00. ================================================================\n");

        //zapisywanie zmian
        plik << stopka;
        plik.close();

        //przywolanie funkcji indeksowania dla automatycznego przyporzadkowania indeksow linii
        indeksowanie();
    }
}

//funkcja do edytowania
void edytowanie()
{
    //deklarowanie zmiennych funkcji
    string indeks_linii;
    string line;
    string tekst;
    string wpis;

    //czyszczenie ekranu dla estetyki
    system("CLS");

    //wywolanie procedury wyswietlania dla latwiejszego usuwania
    wyswietl();

    //wprowadzenie zakresu indeksow do usuniecia
    cout << " " << endl;
    cout << "Wprowadz indeks linii ktora chcesz edytowac: ";
    cin >> indeks_linii;
    cout << " " << endl;

    //ustawienie wartosci zmiennej dla prawidlowego dzialania w przypadku gdy indeks jest mniejszy od 10
    if (indeks_linii.size() < 2)
    {
        indeks_linii = "0" + indeks_linii;
    }

    //przypisanie zmiennej pomocniczej
    string licznik_string = indeks_linii;

    //otwarcie dostepu do plikow
    ifstream plik;
    plik.open("Dziennik.txt");

    ofstream temp;
    temp.open("temp.txt");

    //petla do edytowania
    while (getline(plik, line))
    {
        if (!(line.find(licznik_string) == 0))
        {
            //wpisywanie linijek do pliku
            temp << line << endl;
        }
        else
        {
            //wykonanie w przypadku, gdy przepisywana linia przypada poszukiwanemu indeksowi
            cout << line << endl;
            cout << "" << endl;
            cout << "Wprowadz edytowana linie:" << endl;

            //wprowadzanie poprawionego tekstu
            getline(cin >> ws, tekst);

            //zapisywanie poprawionej linii do pliku tymczasowego
            wpis = "00. " + tekst + "\n";
            temp << wpis;
            cin.clear();
        }
    }

    //zamkniecie dostepu do pliku tymczasowego i glownego
    plik.close();
    temp.close();

    //zamiana pliku tymczasowego na glowny
    remove("Dziennik.txt");
    rename("temp.txt", "Dziennik.txt");

    //wyswietlenie komunikatu po wykonanej operacji
    cout << "" << endl;
    cout << "Linia: " << indeks_linii << " zostala edytowana." << endl;

    //automatyczne indeksowanie na koncu dla uporzadkowania linii
    indeksowanie();
}

//funkcja do usuwania
void usuwanie()
{
    //deklarowanie zmiennych do funkcji
    string indeks_od;
    string indeks_do;
    string numer_od;
    string numer_do;
    string licznik_string;
    bool kontrolka = false;

    //czyszczenie ekranu dla estetyki
    system("CLS");

    //wywolanie procedury wyswietlania dla latwiejszego usuwania
    wyswietl();

    //wprowadzenie zakresu indeksow do usuniecia
    cout << " " << endl;
    cout << "Wprowadz indeks OD ktorego chcesz usunac: ";
    cin >> indeks_od;

    cout << "Wprowadz indeks DO ktorego chcesz usunac: ";
    cin >> indeks_do;
    cout << " " << endl;

    //sprawdzenie czy uzytkownik nie wprowadzil blednych danych
    if (stoi(indeks_od)>stoi(indeks_do))
    {
        //czyszczenie ekranu dla estetyki
        system("CLS");

        //wyprowadzenie komunikatu dla uzytkownika
        cout << "Podana liczba 'OD' jest wieksza od 'DO'. Wroc spowrotem do usuwania...";

        //czekanie na wcisniecie klawisza
        getch();

        //powrot do funkcji usuwania
        usuwanie();
    }

    //przypisanie pierwotnych wartosci zmiennych do pozniejszego uzycia w celach estetycznych
    numer_od = indeks_od;
    numer_do = indeks_do;

    //ustawienie prawidlowej wartosci kontrolki gdy wprowadzona liczba ma tylko 1 znak
    if (indeks_od.size() < 2)
    {
        indeks_od = "0" + indeks_od;
        kontrolka = true;
    }

    //zadeklarowanie zmiennych dla lepszej czytelnosci
    int i      = stoi(numer_od);
    int koniec = stoi(numer_do);

    do {
        string line;

        //sprawdzenie zmiennej kontrolki by program wiedzial czy dodac dodatkowy prefix
        if (kontrolka == true && i < 10)
        {
            licznik_string = "0" + to_string(i);
        }
        else
        {
            licznik_string = to_string(i);
        }

        //otwarcie dostepu do plikow
        ifstream plik;
        plik.open("Dziennik.txt");

        ofstream temp;
        temp.open("temp.txt");

        //petla do usuwania
        while (getline(plik, line))
        {
            if (line.substr(0, licznik_string.size()) != licznik_string)
                temp << line << endl;
        }

        //zamkniecie dostepu do pliku tymczasowego i glownego
        plik.close();
        temp.close();

        //zamiana pliku tymczasowego na glowny
        remove("Dziennik.txt");
        rename("temp.txt", "Dziennik.txt");

        //licznik petli
        i += 1;

    } while ( i <= koniec );

    //wyprowadzenie komunikatu dla uzytkownika
    cout << "Linie od: " << numer_od << " do: " << numer_do << " zostaly usuniete, jesli istnialy." << endl;

    //automatyczne indeksowanie na koncu dla uporzadkowania linii
    indeksowanie();
}

//funkcja sluzaca do indeksowania linijek
void indeksowanie()
{
    //deklarowanie zmiennych
    string line;
    string do_wklejenia;
    string linia;
    string nr;
    int licznik = 0;

    //otwarcie dostepu do plikow
    ifstream plik;
    plik.open("Dziennik.txt");

    ofstream temp;
    temp.open("temp.txt");

    //petla do indeksowania
    while (getline(plik, line))
    {
        //wprowadzenie licznika petli
        licznik += 1;

        //przypisywanie zmiennej nr w zaleznosci, czy indeks jest wiekszy od 10
        if (licznik < 10)
            nr = "0" + to_string(licznik);
        else
            nr = to_string(licznik);

        //operacje zamieniajace 4 pierwsze znaki zmiennej string na prawidlowy indeks
        do_wklejenia = nr + "] ";
        linia = line.replace(0,4, do_wklejenia);
        temp << linia << endl;
    }

    //komunikat potwierdzajacy dla uzytkownika
    cout << " " << endl;
    cout << "Dodano indeksowanie tekstu" << endl;

    //zamkniecie dostepu do plikow
    plik.close();
    temp.close();

    //zamiana pliku tymczasowego na glowny
    remove("Dziennik.txt");
    rename("temp.txt", "Dziennik.txt");

    //powrot do menu
    powrot_do_menu();
}

//funkcja dla lepszej optymalizacji sluzaca o ironio do powrotu do menu
void powrot_do_menu()
{
    //komunikat potwierdzajacy dla uzytkownika
    cout << "" << endl;
    cout << "Nacisnij dowolny przycisk by wrocic do menu...";

    //oczekiwanie na przycisk
    getch();

    //powrot do menu
    menu();
}
