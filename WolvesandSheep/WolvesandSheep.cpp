#include<iostream>
#include<string>

using namespace std;

//Wypelnij tablice zawierajace plansze do gry//
void wrtTab(string game[][8])
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			if (i % 2 == 0) {
				if (j % 2 == 0) game[i][j] = "[]";
				else game[i][j] = "  ";
			}
			else {
				if (j % 2 == 0) game[i][j] = "  ";
				else game[i][j] = "[]";
			}
		}
}

//Drukuj plansze na konsoli//
void prntTab(string game[][8])
{
	cout << "  A  B  C  D  E  F  G  H" << endl;
	for (int i = 0; i < 8; i++) {
		cout << i + 1 << " ";
		for (int j = 0; j < 8; j++)
			cout << game[i][j] << " ";
		cout << i + 1 << endl;
	}
	cout << "  A  B  C  D  E  F  G  H" << endl;
}

//Przygotowanie do gry//
void prep(string game[][8], string index[][8])
{
	string choice;
	for (int j = 1; j < 8; j = j + 2)
		game[0][j] = "<>";
	prntTab(game);
	cout << "Graczu 1. wybierz pole z ktorego chcesz ruszyc na dole planszy: ";
	getline(cin, choice);
	system("cls");
	bool f = false;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			if (index[i][j] == choice && i == 7) {
				game[i][j] = "cc";
				f = true;
			}
			else if (index[i][j] == choice && i == 7) {
				game[i][j] = "cc";
				f = true;
			}
			else if (index[i][j] == choice && i == 7) {
				game[i][j] = "cc";
				f = true;
			}
			else if (index[i][j] == choice && i == 7) {
				game[i][j] = "cc";
				f = true;
			}
		}

	if (f == false) {
		cout << "Blad" << endl;
		system("pause");
		system("cls");
		prep(game, index);
	}
}

//Ruch wilkow//
void WolfMove(string game[][8], string index[][8])
{
	cout << "Ruch gracza 1.: " << endl;
	cout << "Wybierz pole z pionkiem: ";
	string point, dest;
	getline(cin, point);
	bool f = false;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (point == index[i][j] && game[i][j] == "<>") {
				f = true;
				cout << "Wybierz pole na ktory ma sie udac: ";
				getline(cin, dest);
				if (dest == index[i + 1][j - 1] && game[i + 1][j - 1] == "  ") {
					game[i][j] = "  ";
					game[i + 1][j - 1] = "<>";
					system("cls");
					break;
				}
				else if (dest == index[i + 1][j + 1] && game[i + 1][j + 1] == "  ") {
					game[i][j] = "  ";
					game[i + 1][j + 1] = "<>";
					system("cls");
					break;
				}
				else f = false;
			}

	if (f == false) {
		cout << "Blad" << endl;
		system("pause");
		system("cls");
		prntTab(game);
		WolfMove(game, index);
	}
}

void WWin(string gaMe[][8], int CCi, int CCj)
{
	if (gaMe[CCi - 1][CCj - 1] == "<>" || CCj - 1 < 0)									//Jesli wszystkie warunki zostane spelnione gre wygrywaja wilki//
		if (gaMe[CCi - 1][CCj + 1] == "<>" || CCj + 1 > 7)
			if (gaMe[CCi + 1][CCj - 1] == "<>" || CCj - 1 < 0 || CCi + 1 > 7)
				if (gaMe[CCi + 1][CCj + 1] == "<>" || CCj + 1 < 0 || CCi + 1 > 7) {
					cout << "Wygrana wilkow" << endl;
					system("pause");
					exit(0);
				}
}

//Ruch owcy//
void SheepMove(string game[][8], string index[][8])
{
	int desti, destj, cci, ccj;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (game[i][j] == "cc") {
				cci = i;
				ccj = j;
			}

	WWin(game, cci, ccj);

	cout << "Ruch gracza 2.: " << endl;
	cout << "Wybierz pole na ktory ma sie udac: ";
	string dest;
	getline(cin, dest);
	bool f = false;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (dest == index[i][j] && game[i][j] == "  ") {
				f = true;
				desti = i;
				destj = j;
			}

	if (f == true)																	//Podzial ruchu owcy na 4 kierunki//
	{
		int i = 1;
		f = false;
		if (desti < cci && destj < ccj)
			while (game[cci - i][ccj - i] == "  " && cci >= 0 && ccj >= 0) {
				if (cci - i == desti && ccj - i == destj) {
					f = true;
					break;
				}
				i++;
			}
		else if (desti < cci && destj > ccj)
			while (game[cci - i][ccj + i] == "  " && cci >= 0 && ccj <= 8) {
				if (cci - i == desti && ccj + i == destj) {
					f = true;
					break;
				}
				i++;
			}
		else if (desti > cci && destj < ccj)
			while (game[cci + i][ccj - i] == "  " && cci <= 8 && ccj >= 0) {
				if (cci + i == desti && ccj - i == destj) {
					f = true;
					break;
				}
				i++;
			}
		else if (desti > cci && destj > ccj)
			while (game[cci + i][ccj + i] == "  " && cci <= 8 && ccj <= 8) {
				if (cci + i == desti && ccj + i == destj) {
					f = true;
					break;
				}
				i++;
			}
		if (f == true) {
			game[desti][destj] = "cc";
			game[cci][ccj] = "  ";
			if (desti == 0) {
				system("cls");
				prntTab(game);
				cout << "Wygrana owcy" << endl;						//Zakonczenie gry - wygrana owcy//
				system("pause");
				exit(0);
			}
			system("cls");
		}
		else {
			cout << "Blad" << endl;
			system("pause");
			system("cls");
			prntTab(game);
			SheepMove(game, index);
		}
	}

	else {
		cout << "Blad" << endl;
		system("pause");
		system("cls");
		prntTab(game);
		SheepMove(game, index);
	}
}



void GAME(string game[][8], string index[][8])
{
	for (;;) {							//Gra zawarta w nieskonczonej petli//
		WolfMove(game, index);
		prntTab(game);
		SheepMove(game, index);
		prntTab(game);
	}
}

int main()
{
	string Game[8][8];
	string Index[8][8] = { { "A1","B1","C1","D1","E1","F1","G1","H1" },		//Tablica indeksow planszy//
	{ "A2","B2","C2","D2","E2","F2","G2","H2" },
	{ "A3","B3","C3","D3","E3","F3","G3","H3" },
	{ "A4","B4","C4","D4","E4","F4","G4","H4" },
	{ "A5","B5","C5","D5","E5","F5","G5","H5" },
	{ "A6","B6","C6","D6","E6","F6","G6","H6" },
	{ "A7","B7","C7","D7","E7","F7","G7","H7" },
	{ "A8","B8","C8","D8","E8","F8","G8","H8" } };
	wrtTab(Game);
	prep(Game, Index);
	prntTab(Game);
	GAME(Game, Index);
}