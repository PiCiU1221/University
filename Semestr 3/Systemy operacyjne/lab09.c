#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

int main(int argc, char* argv[]) {
	// (1) punkt

	// Sprawdzamy czy podano dokladnie jeden argument
	if (argc != 2) {
		fprintf(stderr, "Nie podano dokladnie 1 argumentu\n");
		return 1;
	}

	// Sprawdzamy czy argument ma poprawna dlugosc
	if (strlen(argv[1]) < 1 || strlen(argv[1]) > 25) {
		fprintf(stderr, "Zla dlugosc argumentu (od 1 do 25)\n");
		return 1;
	}

	// Sprawdzamy czy argument sklada sie z samych cyfr
	for (int i = 0; argv[1][i] != '\0'; i++) {
		if (!isdigit(argv[1][i])) {
			fprintf(stderr, "Argument nie sklada sie z samych cyfr\n");
			return 1;
		}
	}

	// (2) punkt

	// Sprawdzamy czy argument ma dlugosc 1
	if (strlen(argv[1]) == 1) {
		// String do int
		int wynik = argv[1][0] - '0';

		return wynik;
	}

	// (3) punkt

	// Liczymy dlugosci obu polowek
	int dlugoscPierwszej = strlen(argv[1]) / 2;
	int dlugoscDrugiej = strlen(argv[1]) - dlugoscPierwszej;

	// Tworzymy tablice char dla polowek
	char* pierwszaPolowa = (char*)malloc(dlugoscPierwszej + 1);
	char* drugaPolowa = (char*)malloc(dlugoscDrugiej + 1);

	// Uzywamy funkcji kopiujacej zawartosc argumentu do polowek
	// w argumentach podajemy od ktorej pozycji kopiujemy i ilosc
	// elementow
	strncpy_s(pierwszaPolowa, dlugoscPierwszej + 1, argv[1], _TRUNCATE);
	strncpy_s(drugaPolowa, dlugoscDrugiej + 1, argv[1] + dlugoscPierwszej, _TRUNCATE);

	// Dodajemy na koniec tablicy char null character by zaznaczyc
	// koniec zawartosci
	pierwszaPolowa[dlugoscPierwszej] = '\0';
	drugaPolowa[dlugoscDrugiej] = '\0';

	// (4), (5), (6) punkt

	// Tworzenie zmiennych typow Windows API do przechowywania danych startowych i danych o procesie
	// "A" na koncu STARTUPINFOA oznacza typ danych ANSI ze znakami ASCII
	STARTUPINFOA startupInfo1, startupInfo2;
	PROCESS_INFORMATION processInfo1, processInfo2;

	// Przypisujemy zera w pamięci tych zmiennych by miec pewność, że nie ma w nich zapisanych żadnych danych by uniknąć błędów
	ZeroMemory(&startupInfo1, sizeof(startupInfo1));
	ZeroMemory(&startupInfo2, sizeof(startupInfo2));

	ZeroMemory(&processInfo1, sizeof(processInfo1));
	ZeroMemory(&processInfo2, sizeof(processInfo2));

	// Tworzenie command line dla nowego procesu, który zawiera nazwe programu(argv[0]) i argument(pierwszaPolowa)
	char commandLine1[256];
	_snprintf_s(commandLine1, sizeof(commandLine1), _TRUNCATE, "\"%s\" %s", argv[0], pierwszaPolowa);

	// Tworzenie pierwszego dziecka
	// Przekazujemy po referencji zmienne si1 i pi1, do których zostaną wpisane odpowiednie dane
	if (!CreateProcessA(NULL, commandLine1, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo1, &processInfo1)) {
		fprintf(stderr, "Blad przy tworzeniu pierwszego procesu (%d)\n", GetLastError());
		return 1;
	}

	// Tworzenie command line dla nowego procesu, który zawiera nazwe programu(argv[0]) i argument(drugaPolowa)
	char commandLine2[256];
	_snprintf_s(commandLine2, sizeof(commandLine2), _TRUNCATE, "\"%s\" %s", argv[0], drugaPolowa);

	// Tworzenie drugiego dziecka
	// Przekazujemy po referencji zmienne si1 i pi1, do których zostaną wpisane odpowiednie dane
	if (!CreateProcessA(NULL, commandLine2, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo2, &processInfo2)) {
		fprintf(stderr, "Blad przy tworzeniu drugiego procesu (%d)\n", GetLastError());
		return 1;
	}

	// Parent czeka az dzieci sie skoncza
	WaitForSingleObject(processInfo1.hProcess, INFINITE);
	WaitForSingleObject(processInfo2.hProcess, INFINITE);

	// Zmienna Windows API do przechowywania kodu zakonczenia
	DWORD exitCode1, exitCode2;

	// Funkcja która wpisuje kod zakończenia do zmiennej typu DWORD
	GetExitCodeProcess(processInfo1.hProcess, &exitCode1);
	GetExitCodeProcess(processInfo2.hProcess, &exitCode2);

	// Zamykamy procesy i wątki dzieci
	CloseHandle(processInfo1.hProcess);
	CloseHandle(processInfo1.hThread);

	CloseHandle(processInfo2.hProcess);
	CloseHandle(processInfo2.hThread);

	// Printujemy dzialania dzieci do terminala
	printf("%d %d %s %d\n", GetCurrentProcessId(), processInfo1.dwProcessId, pierwszaPolowa, exitCode1);
	printf("%d %d %s %d\n", GetCurrentProcessId(), processInfo2.dwProcessId, drugaPolowa, exitCode2);

	// Zwalniamy pamięć, która wcześniej została zadeklarowana dla tablic char pierwszaPolowa i drugaPolowa
	free(pierwszaPolowa);
	free(drugaPolowa);

	// Parent zwraca kod powrotu równy sumie kodów powrotu otrzymanych od dzieci
	return exitCode1 + exitCode2;
}