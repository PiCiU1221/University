#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	
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
        
        //printf("Wynik: %d\n", wynik);
        return wynik;
    }
    
    // (3) punkt
    
    // Liczymy dlugosci obu polowek
    int dlugoscPierwszej = strlen(argv[1]) / 2;
    int dlugoscDrugiej = strlen(argv[1]) - dlugoscPierwszej;
    
    // Tworzymy tablice char dla polowek
    char pierwszaPolowa[dlugoscPierwszej + 1];
    char drugaPolowa[dlugoscDrugiej + 1];
    
    // Uzywamy funkcji kopiujacej zawartosc argumentu do polowek
    // w argumentach podajemy od ktorej pozycji kopiujemy i ilosc
    // elementow
    
    strncpy(pierwszaPolowa, argv[1], dlugoscPierwszej);
    strncpy(drugaPolowa, argv[1] + dlugoscPierwszej, dlugoscDrugiej);
    
    // Dodajemy na koniec tablicy char null character by zaznaczyc
    // koniec zawartosci
    
    pierwszaPolowa[dlugoscPierwszej] = '\0';
    drugaPolowa[dlugoscDrugiej] = '\0';
    
    // Do testowania dzielenia na polowy
    //printf("Pierwsza: %s\nDruga: %s\n", pierwszaPolowa, drugaPolowa);
    
    // (4), (5), (6) punkt
    
    pid_t dziecko1, dziecko2;
    
    dziecko1 = fork();
    
    // Sprawdzamy czy pierwszy proces sie utworzyl
    if (dziecko1 < 0) {
		fprintf(stderr, "Blad przy tworzeniu pierwszego procesu\n");
		exit(1);
	// Jesli sie utworzyl to uruchamiamy ten sam program z odpowiednia
	// polowa jako argument
	} else if (dziecko1 == 0) {
		// pierwszy argument tej funkcji to sciezka do pliku, u nas jest
		// ten sam wiec argv[0], drugi to nazwa programu, czyli to samo,
		// trzeci to argument, a czwarty informuje o koncu wpisywania
		// argumentow
		execl(argv[0], argv[0], pierwszaPolowa, NULL);
		
		// w przypadku gdy program sie nie uruchomil wyswietlamy blad
		// i konczymy program z kodem bledu '1'
		perror("execl");
		_exit(1);
		
	// Blok else wykonuje rodzic
	} else {
		
		dziecko2 = fork();
		
		// To samo dla drugiego dziecka
		if (dziecko2 < 0) {
			fprintf(stderr, "Blad przy tworzeniu drugiego procesu\n");
			exit(1);
		} else if (dziecko2 == 0) {
			execl(argv[0], argv[0], drugaPolowa, NULL);
			
			perror("execl");
			_exit(1);
			
		// Block else wykonuje rodzic
		} else {
			// Rodzic czeka na zakonczenie utworzonych procesow
			
			int status1, status2;
			
			// Pierwszy argument to PID dziecka przechowywany w takich
			// zmiennych po uzyciu fork(), w drugim podajemy wskazniki
			// nas zmienne przechowujace kody bledu dzieci, a ostatni
			// parametr nie uruchamia zadnych dodatkowych parametrow
			// i czekamy tylko na zakonczenie
			waitpid(dziecko1, &status1, 0);
			waitpid(dziecko2, &status2, 0);
			
			// PID rodzica
			//printf("Rodzic (PID: %d)\n", getpid());
			
			// Informacje o pierwszym dziecku
			printf("%d %d %s %d\n", getpid(), dziecko1, pierwszaPolowa, WEXITSTATUS(status1));
			
			// Informacje o drugim dziecku
			printf("%d %d %s %d\n", getpid(), dziecko2, drugaPolowa, WEXITSTATUS(status2));
			
			// Zwracamy sumę kodów zakończenia obu dzieci
			return WEXITSTATUS(status1) + WEXITSTATUS(status2);
		}
	}
    
    return 0;
}
