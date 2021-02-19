#include <vector>
#include <Windows.h>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <conio.h> // новая библиотека
#include <chrono>
#include <random>
#define _USE_MATH_DEFINES

using namespace std;

random_device rd;
mt19937 gen(rd());

int y_player = 0;
int x_player = 0;

int width = 30;
int height = 10;

int x_cursor;
int y_cursor;

COORD makeCoord(int x, int y) {
	COORD coord = { (SHORT)x, (SHORT)y };
	return coord;
}

COORD nach_kard = makeCoord(0, 0);
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

vector<int>x_platforms_width;
vector<int>y_platforms;
vector<int>x_platforms;

void log()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool z = false;
	if (z == false)
	{
		cout << "\n";
		cout << "\n";
	}
	while (_kbhit()) // нажата ли клавиша
		switch (_getch()) // сравниваем
		{
		case 'w': // сравниваем с w
			y_player--;
			cout << "x_player = " << x_player << " y_player = " << y_player;
			break;
		case 'a': // сравниваем с a
			x_player--;
			cout << "x_player = " << x_player << " y_player = " << y_player;
			break;
		case 'd': // сравниваем с d
			x_player++;
			cout << "x_player = " << x_player << " y_player = " << y_player;
			break;
		case 's': // сравниваем с s
			y_player++;
			cout << "x_player = " << x_player << " y_player = " << y_player;
			break;
		}
	if (x_player == width - 2 || y_player == height - 2 || x_player == -1 || y_player == -1)
	{
		cout << "\nВы проиграли";
		ExitProcess(0);
	}
	z = true;
}

void y_generator()
{
	uniform_int_distribution<> ot_do(2, 4);
	for (int i = 0; i < 15; i++)
	{
		y_platforms.push_back(ot_do(gen));
	}
}

void x_generator()
{
	uniform_int_distribution<> ot_do(3, 5);
	for (int i = 0; i < 15; i++)
	{
		x_platforms_width.push_back(ot_do(gen));
	}
	int o = 0;
	vector <int> x_platforms;
	while (o < 15)
	{
		x_platforms.push_back(o);
		o++;
	}
	o = 0;
	x_platforms[o] = o; // 0
	o++;
	x_platforms[o] = x_platforms_width[o] + 3; // 1
	o = 2;
	while (o < 15)
	{
		x_platforms[o] = x_platforms[o - 1] + x_platforms_width[o - 1] + 2;
		o++;
	}
	o = 0;
	while (o < 15)
	{
		cout << x_platforms[o] << " ";
		o++;
	}
}

void draw_platforms()
{
	int o = 0;
	int y = 0;
	if (x_cursor == x_player && y_cursor == y_player)
	{
		cout << "@";
	}
	else if (x_cursor == 5 && y_cursor == 5)
	{
		cout << "$";
		x_cursor++;
	}
	else if (y_platforms[o] == y_cursor)
	{
		if (x_platforms[y] == x_cursor)
		{
			cout << "%";
			y++;
		}
		y = 0;
		o++;
	}
	else
	{
		cout << " ";
	}
}

void draw()
{
	SetConsoleCursorPosition(hStdOut, nach_kard); // ПЕРЕСТАВЛЯЕМ КУРСОР В НАЧАЛО
	while (x_cursor < width)  // 20 # в ряд
	{
		cout << "#";
		x_cursor++;
	}
	cout << "\n";
	x_cursor = 0;

	while (y_cursor < height - 2)
	{
		cout << "#";
		while (x_cursor < width - 2) // пробелы
		{
			draw_platforms();
			x_cursor++;
		}
		cout << "#\n";
		x_cursor = 0;
		y_cursor++;
	}
	x_cursor = 0;
	while (x_cursor < width)  // 20 # в ряд
	{
		cout << "#";
		x_cursor++;
	}
	x_cursor = 0;
	y_cursor = 0;
}

int main()
{
	y_generator();
	x_generator();
	while (1)
	{
		log();
		draw();
	}
}