// SnakeGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

int width, height;
int x, y;
int fruitX, fruitY;
int dir;
enum direction {
	STOP=0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
bool stop;
int score;
int nTail;
int tailX[100], tailY[100];

void setup()
{
	width = 20;
	height =20;
	x = 10;
	y = 10;
	fruitX = (rand() % (width-2))+1;
	fruitY = (rand() % (height-2))+1;
	stop = false;
	score = 0;
	nTail = 0;
}

void draw()
{
	system("cls");
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;

	for (int i = 1; i < height - 1; i++)
	{
		
		for (int j = 0; j< width; j++)
		{
			if(j==0 || j==width-1)
				cout << "#";
			else if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "$";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						cout << "o";
					}
							
				}
				if(!print)
					cout << " ";
			}
					
		}
		cout << endl;
	}

	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
}

void input()
{
	if (_kbhit())
	{
		//cout << "hit: ";
		//char c = _getch();
		//cout << c;
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'w':
			dir = UP;
			break;
		case 'q':
			stop = true;
			break;
		}
	}
}

void logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
		//cout << dir;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
				break;

	}
	
	if (x < 1 || x >= width - 1 || y < 1 || y >= height - 1)
		stop = true;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
				stop  = true;

	if (x == fruitX && y == fruitY)
	{
		cout << "entered";
		nTail++;
		score += 10;
		fruitX = (rand() % (width - 2)) + 1;
		fruitY = (rand() % (height - 2)) + 1;
	}
}

int main()
{
	int dif;
	cout << "Snake Game" << endl;
	cout << "Enter Dificulty(1-10): ";
	cin >> dif;
	setup();
	while (!stop)
	{
		draw();
		input();
		logic();
		Sleep(100/dif);
	}
    return 0;
}

