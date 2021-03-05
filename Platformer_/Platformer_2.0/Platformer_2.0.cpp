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

short y_player = 10;
short x_player = 3;

int kol_vo_platform = 15;

int jumps = 3; // кол-во прыжков
int jumpsCount; // кол-во доступных прыжков

short do_x_player = x_player;
short do_y_player = y_player;

//int a = x_platforms.size();

vector<int>x_platforms_width;
vector<int>y_platforms;
vector<int>x_platforms;

uint64_t time()
{
	return chrono::duration_cast<std::chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
}

uint64_t tek_time = time();
uint64_t vrem_poden = tek_time + 300;

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

void y_generator()
{
	uniform_int_distribution<> ot_do(2, 4);
	for (int i = 0; i < kol_vo_platform; i++)
	{
		y_platforms.push_back(ot_do(gen));
		y_platforms[i] = height - y_platforms[i] - 2;
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
	cout << " ";
	x_cursor++;
}

bool is_on_platform(int a) {

	bool x_correct;
	x_correct = x_player >= x_platforms[a] && x_player < x_platforms_width[a] + x_platforms[a];
	return x_correct;
}

bool is_on_any_platforms()
{
	bool proverka_paltform = false;
	for (int i = 0; i < kol_vo_platform; i++)
	{
		bool x_correct = is_on_platform(i);
		if (x_correct == true && y_player + 1 == y_platforms[i])
		{
			proverka_paltform = true;
		}
	}
	return proverka_paltform;
}

void jump()
{

}

void padenie_igroka()
{
	do_y_player = y_player;
	is_on_any_platforms();
	tek_time = time();
	if (tek_time > vrem_poden && is_on_any_platforms() == false)
	{
		vrem_poden = vrem_poden + 1500;
		y_player++;
	}
}

void log()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (_kbhit()) // нажата ли клавиша
	{
		do_x_player = x_player;
		do_y_player = y_player;
		if (is_on_any_platforms() == true)
		{
			int c = _getch();
			if (c == 'a')
			{
				x_player--;
			}
			else if (c == 'd')
			{
				x_player++;
			}
			else if (c == 'w')
			{
				int w = time();
				do_y_player = y_player;
				jumpsCount = jumps;
				if (jumpsCount > 0)
				{
					y_player--;
					jumpsCount--;
				}
				vrem_poden = w + 1500;
			}

		}
		else
		{
			int c = _getch();
			if (c == 'a')
			{
				x_player--;
			}
			else if (c == 'd')
			{
				x_player++;
			}
			else if (c == 's')
			{
				y_player++;
			}
			else if (c == 'w')
			{
				int w = time();
				do_y_player = y_player;
				if (jumpsCount > 0)
				{
					y_player--;
					jumpsCount--;
				}
			}
		}
	}

	if (y_player == height - 2 || x_player == -1 || y_player == -1)
	{
		cout << "\nВы проиграли";
		ExitProcess(0);
	}
	if (x_player >= width - 2 && _getch() == 'g' && _getch() == 'o')
	{
		cout << "\nВы выйграли автомобиль";
		ExitProcess(0);
	}
}

void draw()
{
	while (x_cursor < width)  // 20 # в ряд
	{
		cout << "#";
		x_cursor++;
	}
	cout << "\n";
	x_cursor = 0;
	y_cursor++;

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
	//cout << "x_player = " << x_player << " y_player = " << y_player;
	fflush(stdout);
}

void draw_player()
{
	if (do_x_player == x_player && do_y_player == y_player)
	{

	}
	else
	{
		COORD position = { do_x_player, do_y_player }; //позиция x и y
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, position);
		cout << ' ';
		fflush(stdout);
		position = { x_player, y_player }; //позиция x и y
		SetConsoleCursorPosition(hConsole, position);
		cout << '@';
		fflush(stdout);
		do_x_player = x_player;
		do_y_player = y_player;
	}
}

int main()
{
	x_generator();
	y_generator();
	jumpsCount = jumps;
	draw();
	while (1)
	{
		is_on_any_platforms();
		padenie_igroka();
		log();
		draw_player();
	}
}