#include "Gameplay.h"
#include "GameOver.h"
#include "Menu.h"
#include <conio.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
using namespace std;

void Gameplay::gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int Gameplay::RandomFunct(int min, int max)
{
    int n = max - min + 1;
    int remainder = RAND_MAX % n;
    int x;
    do 
    {
        x = rand();
    } while (x >= RAND_MAX - remainder);
    return min + x % n;
}

void Gameplay::initializeRaceTrack()
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (j == 0 || j == height - 1)
            {
                gotoxy(j, i); 
                cout << '\xBA';
            }
            else
            {
                gotoxy(j, i); 
                cout << ' ';
            }
        }
    }
}

void Gameplay::placePlayerCar()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gotoxy(j + playerPosition, i + 19);
            cout << player[i][j];
        }
    }
}

void Gameplay::placeEnemyCar(int enemyStartPosition, int enemydownMovement)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gotoxy(j + enemyStartPosition, i + enemydownMovement);
            cout << enemy[i][j];
        }
    }
}

void Gameplay::removeAfterImage()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gotoxy(j + playerPosition, i + 19);
            cout << ' ';
        }
    }
}

void Gameplay::removeAfterImageEnemy(int enemyStartPosition, int enemydownMovement)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            gotoxy(j + enemyStartPosition, i + enemydownMovement);
            cout << ' ';
        }
    }
}

void Gameplay::removeEnemy(int enemyStartPosition, int enemydownMovement)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gotoxy(j + enemyStartPosition, i + enemydownMovement);
            cout << ' ';
        }
    }
}

bool Gameplay::checkCollision(int enemyStartPosition, int enemydownMovement)
{
    if (enemydownMovement >= 17)
    {
        return ((enemyStartPosition + 4 - playerPosition >= 0) && (enemyStartPosition + 4 - playerPosition <= 7));
    }
    return 0;
}

void Gameplay::updateHighScore()
{
    ifstream readFile("HighScore.txt");
    if (readFile.is_open())
    {
        while (!readFile.eof())
        {
            readFile >> highScore;
        }
    }

    readFile.close();

    ofstream writeFile("HighScore.txt");
    if (writeFile.is_open())
    {
        while (highScore < Score)
        {
            highScore = Score;
        }
        writeFile << highScore;
    }

    writeFile.close();
}

void Gameplay::ScoreBoard()
{
    gotoxy(36, 6);
    cout << "High Score: " << highScore;
    gotoxy(36, 7);
    cout << "------------";
    gotoxy(36, 8);
    cout << "Current score: " << Score;
    gotoxy(36, 9);
    cout << "------------";
    gotoxy(36, 10);
    cout << "Current gamespeed: " << displayGameSpeed;
    gotoxy(36, 12);
    cout << "A - move left";
    gotoxy(36, 13);
    cout << "D - move right";
    gotoxy(36, 14);
    cout << "X - exit game";
    gotoxy(36, 16);
    cout << "Avoid the incoming cars";
    gotoxy(36, 17);
    cout << "Game speed increases every 100 points";
}

void Gameplay::gameStart()
{
    Gameplay b;
    GameOver c;
    Menu a;
    system("cls");
    srand((unsigned)time(NULL));
    enemyStartPosition1 = RandomFunct(1, 10);
    enemyStartPosition2 = RandomFunct(10, 20);
    enemyStartPosition3 = RandomFunct(20, 29);

    initializeRaceTrack();
    updateHighScore();

    while (1)
    {
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 'a' || ch == 'A') 
            {
                //left
                if (playerPosition > 1)
                {
                    playerPosition -= 4;
                }
            }
            if (ch == 'd' || ch == 'D') 
            {
                //right
                if (playerPosition < 26)
                {
                    playerPosition += 4;
                }
            }
            if (ch == 'x' || ch == 'X')
            {
                //exit
                a.pickMenu();
                break;
            }
        }

        ScoreBoard();

        placePlayerCar();
        
        if (checkCollision(enemyStartPosition1, enemydownMovement1))
        {
            updateHighScore();
            c.gameOverScreen();
            break;
        }
        
        if (checkCollision(enemyStartPosition2, enemydownMovement2))
        {
            updateHighScore();
            c.gameOverScreen();
            break;
        }
        
        if (checkCollision(enemyStartPosition3, enemydownMovement3))
        {
            updateHighScore();
            c.gameOverScreen();
            break;
        }

        placeEnemyCar(enemyStartPosition1, enemydownMovement1);
        if (checkStatus1 == true)
            placeEnemyCar(enemyStartPosition2, enemydownMovement2);
        if (checkStatus2 == true)
            placeEnemyCar(enemyStartPosition3, enemydownMovement3);
        
        Sleep(gameSpeed);

        removeAfterImage();
        
        removeAfterImageEnemy(enemyStartPosition1, enemydownMovement1);
        removeAfterImageEnemy(enemyStartPosition2, enemydownMovement2);
        removeAfterImageEnemy(enemyStartPosition3, enemydownMovement3);
        
        //when to spawn enemy 1
        if ((enemydownMovement1 + 4) != 23)
        {
            enemydownMovement1 += 1;
            if (enemydownMovement1 >= 8)
            {
                checkStatus1 = true;
            }
        }
        else if ((enemydownMovement1 + 4) == 23)
        {
            removeEnemy(enemyStartPosition1, enemydownMovement1);
            enemyStartPosition1 = RandomFunct(1, 10);
            enemydownMovement1 = 0;
            Score += 5;
            checkGameSpeed += 5;
        }
        
        //when to spawn enemy 2
        if (checkStatus1 == true)
        {
            if ((enemydownMovement2 + 4) != 23)
            {
                enemydownMovement2 += 1;
                if (enemydownMovement2 >= 8)
                {
                    checkStatus2 = true;
                }
            }
            else if ((enemydownMovement2 + 4) == 23)
            {
                removeEnemy(enemyStartPosition2, enemydownMovement2);
                enemyStartPosition2 = RandomFunct(10, 20);
                enemydownMovement2 = 0;
                Score += 5;
                checkGameSpeed += 5;
            }
        }
        
        //when to spawn enemy 3
        if (checkStatus2 == true)
        {
            if ((enemydownMovement3 + 4) != 23)
            {
                enemydownMovement3 += 1;
            }
            else if ((enemydownMovement3 + 4) == 23)
            {
                removeEnemy(enemyStartPosition3, enemydownMovement3);
                enemyStartPosition3 = RandomFunct(20, 29);
                enemydownMovement3 = 0;
                Score += 5;
                checkGameSpeed += 5;
            }
        }

        //increase game speed
        if ((gameSpeed - 10) > 10)
        {
            if (checkGameSpeed == 100)
            {
                checkGameSpeed = 0;
                gameSpeed -= 10;
                displayGameSpeed += 1;
            }
        }
    }
}