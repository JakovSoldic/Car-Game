#pragma once
#ifndef GAMEOVER_H
#define GAMEOVER_H
#include <iostream>
using namespace std;

class GameOver
{
private:
	char input = 'h';
	char previousInput = 'c';
	friend class Gameplay;
public:
	void gotoxy(int x, int y);
	void gameOverScreen();
};
#endif
