#pragma once
#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
using namespace std;

class Gameplay
{
	//\xF1
private:

	//general stuff
	int gameSpeed = 100;
	int checkGameSpeed = 0;
	int displayGameSpeed = 1;
	int Score = 0;
	int highScore;
	int width = 23;//height
	int height = 34;//width
	int playerPosition = 9;
	bool checkStatus1 = false;
	bool checkStatus2 = false;
	//char** raceTrack;
	friend class GameOver;
	
	//player stuff
	char player[4][4] = { ' ', '/', '\\', ' ',
						  'O', '-', '-', 'O',
						  '[', '*', '*', ']',
						  'O', '-', '-', 'O' };
	
	//enemy stuff
	int enemyStartPosition1;
	int enemyStartPosition2;
	int enemyStartPosition3;
	
	int enemydownMovement1 = 0;
	int enemydownMovement2 = 0;
	int enemydownMovement3 = 0;
	
	char enemy[4][4] = { 'O', '-', '-', 'O',
						 '[', '*', '*', ']',
						 'O', '-', '-', 'O', 
						 ' ', '\\', '/', ' ' };

public:
	void gotoxy(int x, int y);
	void ShowConsoleCursor(bool showFlag);
	int RandomFunct(int min, int max);
	void initializeRaceTrack();
	void placePlayerCar();
	void placeEnemyCar(int enemyStartPosition, int enemydownMovement);
	void removeAfterImage();
	void removeAfterImageEnemy(int enemyStartPosition, int enemydownMovement);
	void removeEnemy(int enemyStartPosition, int enemydownMovement);
	bool checkCollision(int enemyStartPosition, int enemydownMovement);
	void updateHighScore();
	void ScoreBoard();
	void gameStart();
};
#endif