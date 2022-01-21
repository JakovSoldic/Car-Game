#pragma once
#ifndef MENU_H
#define MENU_H
#include <iostream>
using namespace std;

class Menu
{
private:
	char input = 'h';
	char previousInput = 'c';
	friend class Gameplay;
	friend class GameOver;
public:
	void gotoxy(int x, int y);
	void ShowConsoleCursor(bool showFlag);
	void ClearHighscore();
	void pickMenu();
};
#endif

