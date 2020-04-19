#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>


using namespace std;
bool gameOver, gameRunning;
const int width = 25;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
string color;
string response;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN, SECRETE };
eDirecton dir;
int lastScore;
string lastWords;








void Setup()
{
	ifstream inFile;
	inFile.open("saveGame.txt");
	if (inFile.fail())
	{
		cerr << "Did not open saveGame, create a txt doc named saveGame in folder with this .exe" << endl;
		exit(1);
	}




	inFile >> lastScore;
	inFile.close();
	cout << "*************************************************************************" << endl;
	cout << "*                WELCOME TO MASONS SNAKE GAME                           *" << endl;
	cout << "*                    Your last score was: " << lastScore; cout << "                              *" << endl;
	cout << "            type your favorite color to play: "; cin >> color;





	gameOver = false;
	gameRunning = true;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;



}


void Draw()
{


	if (color == "blue")
		system("color B4");
	if (color == "green")
		system("color D6");
	system("cls"); //system("clear");
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{

					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}

				}
				if (!print)
					cout << " ";

			}


			if (j == width - 1)
				cout << "#";

		}

		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << " Score:" << score << endl;
	if (color == "red, orange")
	{
		cout << color << "                is a really shitty color" << endl;
	}
	if (color == "yellow")
	{
		cout << color << "                 Hmmm... this must be connor, have fun bro, look for the secrete key ;)" << endl;
	}
	if (color == "green")
	{
		cout << color << "                 Green, this is probably Halle, have fun <3" << endl;
	}
	if (color == "blue")
	{
		cout << color << "                 This must be paps, whats up dad? are you proud!!!" << endl;
	}

}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'm':
			dir = SECRETE;
			break;
		}

	}


}

void Logic()
{

	ofstream outFile;
	outFile.open("saveGame.txt");




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
	case LEFT:
		x--;
		cout << "                     !!!!You just pushed left!!!!" << endl;
		break;
	case RIGHT:
		x++;
		cout << "                   !!!!You just pushed right!!!!" << endl;
		break;
	case UP:
		y--;
		cout << "                      !!!!You just went up!!!!" << endl;
		break;
	case DOWN:
		y++;
		cout << "                  !!!!You just pushed down!!!!" << endl;
		break;
	case SECRETE:
		y++;
		score += 10000;
		cout << "                     !!!!You just unlocked the secrete!!!!" << endl;
		break;
	default:
		cout << "                  !!!!Are you going to start the game?!!!!" << endl;
		break;
	}


	if (x > width || x < 0 || y > height || y < 0)
	{
		outFile << lastScore;
		outFile.close();
		gameOver = true;
	}

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
		{
			outFile << lastScore;
			outFile.close();
			gameOver = true;
		}


		if (x == fruitX && y == fruitY)
		{
			nTail++;



			score += 10;
			fruitX = rand() % width;
			fruitY = rand() % height;


		}



	lastScore = score;








}



int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();

	}

	return 1;




}
