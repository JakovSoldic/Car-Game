#include "GameOver.h"
#include "Gameplay.h"
#include "Menu.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

void GameOver::gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GameOver::gameOverScreen()
{
	GameOver c;
	Gameplay b;
	Menu a;
	system("cls");
	//system("color A");
	gotoxy(50, 5);
	cout << "  G A M E  O V E R ";
	gotoxy(50, 6);
	cout << "     R E T R Y?    ";
	gotoxy(50, 8);
	cout << "  YES        ";
	gotoxy(60, 8);
	cout << "      NO     ";
	gotoxy(40, 12);
	cout << "(Use A and D to move, press Y to accept)";
	while (1)
	{
		if (_kbhit())
		{
			input = _getch();
			if (input == 'a' || input == 'A')
			{
				gotoxy(50, 8);
				cout << ">>YES<<      ";
				gotoxy(60, 8);
				cout << "      NO     ";
				previousInput = input;
			}
			if (input == 'd' || input == 'D')
			{
				gotoxy(50, 8);
				cout << "  YES        ";
				gotoxy(60, 8);
				cout << "    >>NO<<   ";
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
			a.pickMenu();
			break;
		}
		Sleep(1);
	}
}