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

int number_of_platforms = 15;

int jumps = 3; // кол-во прыжков
int jumpsCount = 0; // кол-во доступных прыжков

short past_x_player = x_player;
short past_y_player = y_player;

//int a = x_platforms.size();

vector<int>x_platforms_width;
vector<int>y_platforms;
vector<int>x_platforms;

uint64_t time()
{
	return chrono::duration_cast<std::chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
}

uint64_t current_time = time(); // текушее время 
uint64_t fall_time = current_time + 300; // время пядения

short x_enemy = width - 2;
short y_enemy = y_player;

short do_x_enemy = x_enemy;
short do_y_enemy = y_enemy;

int delay_flight = time() + 300;
int keystrokes_time = time() + 2000;

bool is_keystrokes = true;

	bool is_enemy_draw = false;
	bool b = true;
	bool c = true;

void x_generator()
{
	int a = x_platforms.size();
	uniform_int_distribution<> ot_do(3, 5);
	for (int i = 0; i < number_of_platforms; i++) // ширина платформ от 3 до 5 
	{
		x_platforms_width.push_back(ot_do(gen));
		x_platforms.push_back(i);
	}
	int o = 0;
	x_platforms[o] = 1; // 0 создание каординаты на которой будет находится 1 платформа
	while (o + 1 < number_of_platforms)
	{
		x_platforms[o + 1] = x_platforms[o - 1 + 1] + x_platforms_width[o - 1 + 1] + 2;
		if (x_platforms[o + 1] + x_platforms_width[o + 1] >= width - 2)
		{
			x_platforms_width[o + 1] = width - 2 - x_platforms[o + 1];
		}
		o++;
	}
}

void y_generator()
{
	uniform_int_distribution<> ot_do(2, 4);
	for (int i = 0; i < number_of_platforms; i++)
	{
		y_platforms.push_back(ot_do(gen));
		y_platforms[i] = height - y_platforms[i] - 1;
	}
}

void draw_platforms()
{
	int a = 0;
	while (a < number_of_platforms)
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

bool is_on_x_platform(int a) {

	bool x_correct;
	x_correct = x_player >= x_platforms[a] && x_player < x_platforms_width[a] + x_platforms[a];
	return x_correct;
}

bool is_on_any_platforms()
{
	bool platform_check = false;
	for (int i = 0; i < number_of_platforms; i++)
	{
		bool x_correct = is_on_x_platform(i);
		if (x_correct == true && y_player + 1 == y_platforms[i])
		{
			platform_check = true;
		}
	}
	return platform_check;
}

void player_fall()
{
	past_y_player = y_player;
	is_on_any_platforms();
	current_time = time();
	if (current_time > fall_time && is_on_any_platforms() == false)
	{
		fall_time = time() + 1500;
		y_player++;
	}
}

void information_output()
{
	if (y_player == height - 1 || x_player == 0 || y_player == -1)
	{
		COORD position = { 1, 25 }; //позиция x и y
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, position);
		cout << "Вы проиграли";
		fflush(stdout);
		ExitProcess(0);
	}
	if (x_player >= width - 1)
	{
		COORD position = { 1, 25 }; //позиция x и y
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, position);
		cout << "Вы выйграли автомобиль";
		fflush(stdout);
		ExitProcess(0);
	}

	COORD position = { 1, 20 }; //позиция x и y
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position);
	cout << "x_player: " << x_player << " y_player: " << y_player;
	fflush(stdout);

	position = { 1, 21 }; //позиция x и y
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position);
	cout << is_keystrokes;
	fflush(stdout);
}

void log()
{
	if (time() >= keystrokes_time)
	{
		is_keystrokes = false;
	}
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	if (is_on_any_platforms() == true)
	{
		jumpsCount = jumps;
	}
	while (_kbhit()) // нажата ли клавиша
	{
		past_x_player = x_player;
		past_y_player = y_player;
		if (is_on_any_platforms() == true)
		{
			int checking_the_keyboard = _getch();
			if (checking_the_keyboard == 'a')
			{
				x_player--;
			}
			else if (checking_the_keyboard == 'd')
			{
				x_player++;
			}
			else if (checking_the_keyboard == 'w')
			{
				is_keystrokes = true;
				int w = time();
				past_y_player = y_player;
				if (jumpsCount > 0)
				{
					y_player--;
					jumpsCount--;
				}
				fall_time = w + 1500;
				keystrokes_time = time() + 2000;
			}

		}
		else
		{
			int checking_the_keyboard = _getch();
			if (checking_the_keyboard == 'a')
			{
				x_player--;
			}
			else if (checking_the_keyboard == 'd')
			{
				x_player++;
			}
			else if (checking_the_keyboard == 's')
			{
				keystrokes_time = time() + 2000;
				is_keystrokes = true;
				y_player++;
			}
			else if (checking_the_keyboard == 'w')
			{
				keystrokes_time = time() + 2000;
				is_keystrokes = true;
				int w = time();
				past_y_player = y_player;
				if (jumpsCount > 0)
				{
					y_player--;
					jumpsCount--;
				}
			}
		}
	}
	information_output();
	if (is_keystrokes == false || is_enemy_draw == true)
	{
		if (b == true)
		{
			y_enemy = y_player;
			x_enemy = x_player + 20;
			b = false;
		}
		is_enemy_draw = true;
		if (time() > delay_flight)
		{
			do_x_enemy = x_enemy;
			do_y_enemy = y_enemy;
			delay_flight = time() + 300;
			x_enemy--;
		}
	}
}

void draw_enemy()
{
	if (do_x_enemy == x_enemy && do_y_enemy == y_enemy)
	{

	}
	else if (x_enemy <= 0 && c == true)
	{
		COORD position = { do_x_enemy, do_y_enemy }; //позиция x и y
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, position);
		cout << ' ';
		fflush(stdout);
		position = { x_enemy, y_enemy }; //позиция x и y
		SetConsoleCursorPosition(hConsole, position);
		cout << '#';
		fflush(stdout);
		c = false;
	}
	else if (c == true)
	{
		COORD position = { do_x_enemy, do_y_enemy }; //позиция x и y
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, position);
		cout << ' ';
		fflush(stdout);
		position = { x_enemy, y_enemy }; //позиция x и y
		SetConsoleCursorPosition(hConsole, position);
		cout << '+';
		fflush(stdout);
		do_x_enemy = x_enemy;
		do_y_enemy = y_enemy;
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

	while (y_cursor < height - 1)
	{
		cout << "#";
		x_cursor++;
		while (x_cursor < width - 1) // пробелы
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
	if (past_x_player == x_player && past_y_player == y_player)
	{

	}
	else
	{
		COORD position = { past_x_player, past_y_player }; //позиция x и y
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, position);
		cout << ' ';
		fflush(stdout);
		position = { x_player, y_player }; //позиция x и y
		SetConsoleCursorPosition(hConsole, position);
		cout << '@';
		fflush(stdout);
		past_x_player = x_player;
		past_y_player = y_player;
	}
}

int main()
{
	x_generator();
	y_generator();
	draw();
	while (1)
	{
		is_on_any_platforms();
		player_fall();
		log();
		draw_player();
		draw_enemy();
	}
}