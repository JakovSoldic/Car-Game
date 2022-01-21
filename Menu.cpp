#include "Menu.h"
#include "Gameplay.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cstdlib>
#include <fstream>
using namespace std;

void Menu::gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Menu::ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void Menu::ClearHighscore()
{
	ofstream file("Highscore.txt", std::ios::out | std::ios::trunc);
	file.close();
}

void Menu::pickMenu()
{
	Gameplay b;
	system("cls");
	ShowConsoleCursor(false);
	//system("color A");
	gotoxy(50, 6); 
	cout <<  "  C A R  G A M E  ";
	gotoxy(50, 8); 
	cout <<  "  START GAME  ";
	gotoxy(50, 10); 
	cout <<  "  EXIT        ";
	gotoxy(40, 12); 
	cout <<  "(Use A and D to move, press Y to accept)";
	while (1)
	{
		if (_kbhit())
		{
			input = _getch();
			if (input == 'a' || input == 'A')
			{
				gotoxy(50, 8); 
				cout <<  ">>START GAME<<";
				gotoxy(50, 10); 
				cout <<  "  EXIT        ";
				previousInput = input;
			}
			if (input == 'd' || input == 'D')
			{
				gotoxy(50, 8); 
				cout <<  "  START GAME  ";
				gotoxy(50, 10); 
				cout <<  ">>EXIT<<      ";
				previousInput = input;
			}
		}
		if ((previousInput == 'a' || previousInput == 'A') && (input == 'y' || input == 'Y'))
		{
			b.gameStart();
			break;
		}
		if ((previousInput == 'd' || previousInput == 'D') && (input == 'y' || input == 'Y'))
		{
			ClearHighscore();
			system("cls");
			break;
			exit;
		}
	}
}