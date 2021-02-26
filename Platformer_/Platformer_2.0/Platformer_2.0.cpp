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

const int width = 80;
int height = 20;

int x_cursor;
int y_cursor;

int y_player = 10;
int x_player = 3;

int kol_vo_platform = 15;

//int a = x_platforms.size();

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
	for (int i = 0; i < kol_vo_platform; i++)
	{
		y_platforms.push_back(ot_do(gen));
		y_platforms[i] = height - y_platforms[i] - 2;
	}
}

void x_generator()
{
	int a = x_platforms.size();
	uniform_int_distribution<> ot_do(3, 5);
	for (int i = 0; i < kol_vo_platform; i++) // ширина платформ от 3 до 5 
	{
		x_platforms_width.push_back(ot_do(gen));
		x_platforms.push_back(i);
	}
	int o = 0;
	x_platforms[o] = o; // 0 создание каординаты на которой будет находится 1 платформа
	while (o + 1 < kol_vo_platform)
	{
		if (x_platforms[o + 1] + x_platforms_width[o + 1] > width)
		{
			break;
		}
		else
		{
			x_platforms[o + 1] = x_platforms[o - 1 + 1] + x_platforms_width[o - 1 + 1] + 2;
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
			break;
		case 'a': // сравниваем с a
			x_player--;
			break;
		case 'd': // сравниваем с d
			x_player++;
			break;
		}
	if (x_player == width - 2 || y_player == height - 2 || x_player == -1 || y_player == -1)
	{
		cout << "\nВы проиграли";
		ExitProcess(0);
	}
	z = true;
}

void padenie_igroka()
{
	bool h = false;
	for (int i = 0; i < kol_vo_platform; i++)
	{
		tek_time = time();
		if (x_player >= x_platforms[i] && x_player < x_platforms_width[i] + x_platforms[i] && y_player + 1 == y_platforms[i])
		{
			h = true;
		}
	}
	if (tek_time > vrem_poden && h == false)
	{
		vrem_poden = vrem_poden + 300;
		y_player++;
		h = false;
	}
}

void draw_platforms()
{
	int a = 0;
	while (a < kol_vo_platform)
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
	cout << "x_player = " << x_player << " y_player = " << y_player;
	fflush(stdout);
}

int main()
{
	char buf[width / 4];
	setvbuf(stdout, buf, _IOFBF, sizeof(buf));
	y_generator();
	x_generator();
	while (1)
	{
		log();
		draw();
		padenie_igroka();
	}
}