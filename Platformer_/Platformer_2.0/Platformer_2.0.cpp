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

int width = 80;
int height = 50;

int x_cursor;
int y_cursor;

int y_player = 0;
int x_player = 0;

COORD makeCoord(int x, int y) {
	COORD coord = { (SHORT)x, (SHORT)y };
	return coord;
}

uint64_t time()
{
	return chrono::duration_cast<std::chrono::microseconds>(chrono::steady_clock::now().time_since_epoch()).count();
}

uint64_t tek_time = time();
uint64_t vrem_poden = tek_time + 300;

COORD nach_kard = makeCoord(0, 0);
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

vector<int>x_platforms_width;
vector<int>y_platforms;
vector<int>x_platforms;

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
	int a = x_platforms.size();
	uniform_int_distribution<> ot_do(3, 5);
	for (int i = 0; i < 15; i++) // ширина платформ от 3 до 5 
	{
		x_platforms_width.push_back(ot_do(gen));
	}
	int o = 0;
	while (o < 15) // создание мссива каординат платформ из 15 штук 
	{
		x_platforms.push_back(o);
		o++;
	}
	o = 0;
	x_platforms[o] = o; // 0 создание каординаты на которой будет находится 1 платформа
	o++;
	while (o < 15)
	{
		if (x_platforms[o] + x_platforms_width[o] > width)
		{
			break;
		}
		else
		{
			x_platforms[o] = x_platforms[o - 1] + x_platforms_width[o - 1] + 2;
			o++;
		}
	}
} 

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

void draw_platforms()
{
	int a = 0;
	while (a < 15)
	{
		if (y_cursor == y_platforms[a] && x_cursor == x_platforms[a])
		{
			for (int i = 0; i < x_platforms_width[a]; i++)
			{
				cout << "%";
				x_cursor++;
			}
		}
		a++;
	}
	if (x_cursor == x_player && y_cursor == y_player)
	{
		cout << "@";
		x_cursor++;
	}
	else
	{
		cout << " ";
		x_cursor++;
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
		tek_time = time();
		log();
		draw();
		if (tek_time > vrem_poden)
		{
			vrem_poden = vrem_poden + 300;
			y_player++;
		}
	}
}