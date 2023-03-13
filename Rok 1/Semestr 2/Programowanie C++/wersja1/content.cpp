#include <iostream>
#include <string>
#include <random>
#include <conio.h>

#include "header.h"

using namespace std;

string Marki[4] = { "Audi", "BMW", "Skoda", "Volkswagen" };
string Rejestracje[4] = { "ZST", "ZS", "ZCH", "ZPY" };

int generujInteger(int odLiczby, int doLiczby) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(odLiczby, doLiczby);
	return dis(gen);
}

int policzCyfry(int number) {
	int count = 0;

	if (number == 0) {
		return 1;
	}

	while (number != 0) {
		number /= 10;
		count++;
	}
	return count;
}

/*
// przeladowana funkcja nr 1
int policzZnaki(int number) {
	int count = 0;

	if (number == 0) {
		return 1;
	}

	while (number != 0) {
		number /= 10;
		count++;
	}
	return count;
}

// przeladowana funkcja nr 2
int policzZnaki(string string) {
	return string.size();
}
*/


// ZAD 7
// Gra w poscig
void displayGra(char gra[11][11]) {
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			cout << gra[i][j] << " ";
		}
		cout << endl;
	}

	cout << "\n========================================\n\n";
	cout << "    Nacisnij 'q' by wróciæ do menu\n";
	cout << "\n========================================\n";
}

void ucieczkaCelu(char gra[11][11], int& playerRow, int& playerCol, int& targetRow, int& targetCol) {

	if (!(playerRow == targetRow && playerCol == targetCol)) {
		if (playerRow > targetRow && targetRow > 0) {
			gra[targetRow][targetCol] = 'o';
			targetRow--;
			gra[targetRow][targetCol] = 'X';
		}
		else if (playerRow < targetRow && targetRow < 10) {
			gra[targetRow][targetCol] = 'o';
			targetRow++;
			gra[targetRow][targetCol] = 'X';
		}
		else if (playerCol > targetCol && targetCol > 0) {
			gra[targetRow][targetCol] = 'o';
			targetCol--;
			gra[targetRow][targetCol] = 'X';
		}
		else if (playerCol < targetCol && targetCol < 10) {
			gra[targetRow][targetCol] = 'o';
			targetCol++;
			gra[targetRow][targetCol] = 'X';
		}
		else {
			if (generujInteger(0, 1) == 0) {
				if (targetRow == 0) {
					gra[targetRow][targetCol] = 'o';
					targetRow++;
					gra[targetRow][targetCol] = 'X';
				}
				else if (targetRow == 10) {
					gra[targetRow][targetCol] = 'o';
					targetRow--;
					gra[targetRow][targetCol] = 'X';
				}
			}
			else {
				if (targetCol == 0) {
					gra[targetRow][targetCol] = 'o';
					targetCol++;
					gra[targetRow][targetCol] = 'X';
				}
				else if (targetCol == 10) {
					gra[targetRow][targetCol] = 'o';
					targetCol--;
					gra[targetRow][targetCol] = 'X';
				}
			}
		}
	}
	else {
		gra[targetRow][targetCol] = '@';
		gra[playerRow][playerCol] = 'o';
	}
}

void nextMove(char gra[11][11], int key, int& playerRow, int& playerCol, int& targetRow, int& targetCol) {
	switch (key) {
	case KEY_UP:
		if (playerRow > 0) {
			gra[playerRow][playerCol] = 'o'; // usun gracza ze starej pozycji
			playerRow--;
			gra[playerRow][playerCol] = '@'; // ustaw gracza na nowej pozycji
		}
		ucieczkaCelu(gra, playerRow, playerCol, targetRow, targetCol);
		break;
	case KEY_DOWN:
		if (playerRow < 10) {
			gra[playerRow][playerCol] = 'o';
			playerRow++;
			gra[playerRow][playerCol] = '@';
		}
		ucieczkaCelu(gra, playerRow, playerCol, targetRow, targetCol);
		break;
	case KEY_LEFT:
		if (playerCol > 0) {
			gra[playerRow][playerCol] = 'o';
			playerCol--;
			gra[playerRow][playerCol] = '@';
		}
		ucieczkaCelu(gra, playerRow, playerCol, targetRow, targetCol);
		break;
	case KEY_RIGHT:
		if (playerCol < 10) {
			gra[playerRow][playerCol] = 'o';
			playerCol++;
			gra[playerRow][playerCol] = '@';
		}
		ucieczkaCelu(gra, playerRow, playerCol, targetRow, targetCol);
		break;
	}
}

void zad7() {
	char gra[11][11] = {};

	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			gra[i][j] = 'o';
		}
	}

	int key = 0;
	int playerRow = generujInteger(0, 10);
	int playerCol = generujInteger(0, 10);
	int targetRow = 0;
	int targetCol = 0;
	int dystansOdGracza = 3;
	bool run = true;
	int moveCounter = 0;

	// losujemy pozycje, dopoki nie bedzie oddalona o zmienna dystansOdGracza
	do {
		targetRow = generujInteger(0, 10);
		targetCol = generujInteger(0, 10);
	} while (abs(targetRow - playerRow) < dystansOdGracza && abs(targetCol - playerCol) < dystansOdGracza);

	gra[playerRow][playerCol] = '@';
	gra[targetRow][targetCol] = 'X';

	while (run) {
		// czyscimy ekran
		system("CLS");

		// wyswietlamy zawartosc tablicy/planszy
		displayGra(gra);

		key = _getch();
		switch (key) {
		case KEY_UP: // gorna strzalka
		case KEY_DOWN: // dolna strzalka
		case KEY_LEFT: // lewa strzalka
		case KEY_RIGHT: // prawa strzalka
			nextMove(gra, key, playerRow, playerCol, targetRow, targetCol);
			break;
		case 'q':
			run = false;
			break;
		}

		moveCounter++;

		if (playerRow == targetRow && playerCol == targetCol) {
			run = false;
			cout << "\n========================================\n\n";
			cout << "    Koniec gry!\n";
			cout << "    Udalo ci sie dogonic cel w: " << floor(moveCounter / 2) << " ruchach!\n\n";
			cout << "    Nacisnij ENTER by wróciæ do menu\n";
			cout << "\n========================================\n";
			cin.ignore();
			cin.get();
		}
	}
}

class Food {
public:
	int row;
	int col;

	void render(char gra[11][11]) {
		// losujemy pozycje, dopoki nie bedzie oddalona o zmienna dystansOdGracza
		do {
			row = generujInteger(0, 10);
			col = generujInteger(0, 10);
		} while (gra[row][col] != 'o');

		gra[row][col] = 'X';
	}
};

class Player {
public:
	int row;
	int col;
	int lenght;
	int points = 0;

	vector<pair<int, int>> ogonVector;

	void render(char gra[11][11]) {
		gra[row][col] = '@';

		// jesli ogon jest dluzszy niz rozmiar (np. podczas ruchu to usuwamy pierwszy dodany element)
		if (ogonVector.size() > lenght - 1) {
			auto firstElement = ogonVector.front();
			gra[firstElement.first][firstElement.second] = 'o';
			ogonVector.erase(ogonVector.begin());
		}

		// petla foreach (przelatuje przez kazdy element vectora)
		for (auto element : ogonVector) {
			gra[element.first][element.second] = '&';
		}
	}

	void move(char gra[11][11], int key, Food& food, bool& run) {
		switch (key) {
		case KEY_UP:
			if (row > 0) {
				// dajemy na koniec vektora aktualna pozycje przed zmiana, by mogl powstac na niej ogon
				ogonVector.push_back(make_pair(row, col));
				// aktualizujemy pozycje w oparciu o ruch gracza
				row--;
				// sprawdzamy czy gracz nie wszedl w swoj ogon na nowej pozycji
				if (gra[row][col] == '&') {
					run = false;
				}
				// dodajemy char glowy snake na nowe miejsce
			}
			else {
				// gdy gracz wyszedlby za plansze przenosimy go na gore
				ogonVector.push_back(make_pair(row, col));
				row = 10;
			}
			break;
		case KEY_DOWN:
			if (row < 10) {
				ogonVector.push_back(make_pair(row, col));
				row++;
				if (gra[row][col] == '&') {
					run = false;
				}
			}
			else {
				ogonVector.push_back(make_pair(row, col));
				row = 0;
			}
			break;
		case KEY_LEFT:
			if (col > 0) {
				ogonVector.push_back(make_pair(row, col));
				col--;
				if (gra[row][col] == '&') {
					run = false;
				}
			}
			else {
				ogonVector.push_back(make_pair(row, col));
				col = 10;
			}
			break;
		case KEY_RIGHT:
			if (col < 10) {
				ogonVector.push_back(make_pair(row, col));
				col++;
				if (gra[row][col] == '&') {
					run = false;
				}
			}
			else {
				ogonVector.push_back(make_pair(row, col));
				col = 0;
			}
			break;
		}
		if (row == food.row && col == food.col) {
			points++;
			lenght++;
			food.render(gra);
			displayGra(gra);
		}
	}
};

// ZAD 8
// Gra w snake
void zad8() {
	char gra[11][11] = {};

	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			gra[i][j] = 'o';
		}
	}

	Player player;
	Food food;

	int key = 0;
	player.row = generujInteger(1, 9);
	player.col = generujInteger(1, 9);
	player.lenght = 2;
	player.ogonVector.push_back(make_pair(player.row - 1, player.col));
	food.row = 0;
	food.col = 0;
	bool run = true;
	int moveCounter = 0;

	player.render(gra);
	food.render(gra);

	while (run) {
		// czyscimy ekran
		system("CLS");

		// wyswietlamy zawartosc tablicy/planszy
		displayGra(gra);

		key = _getch();
		switch (key) {
		case KEY_UP: // gorna strzalka
		case KEY_DOWN: // dolna strzalka
		case KEY_LEFT: // lewa strzalka
		case KEY_RIGHT: // prawa strzalka
			player.move(gra, key, food, run);
			player.render(gra);
			break;
		case 'q':
			run = false;
			break;
		}

		if (run == false) {
			cout << "\n========================================\n\n";
			cout << "    Koniec gry!\n";
			cout << "    Zdobyte punkty: " << player.points << " punktow!\n\n";
			cout << "    Nacisnij ENTER by wróciæ do menu\n";
			cout << "\n========================================\n";
			cin.ignore();
			cin.get();
		}
	}
}