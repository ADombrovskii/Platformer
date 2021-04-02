#include <vector>
#include <Windows.h>
#include <math.h>
#include <iomanip>
#include <conio.h> // новая библиотека
#include <chrono>
#include <random>

#include <iostream>
#include <string>
#include <fstream>
#define _USE_MATH_DEFINES

using namespace std;

const int width = 80;
int height = 20;

int x_cursor;
int y_cursor;

vector<int>x_platforms_width;
vector<int>y_platforms;
vector<int>x_platforms;

random_device rd;
mt19937 gen(rd());

short y_player = 10;
short x_player = 3;

short past_x_player = x_player;
short past_y_player = y_player;

int is_player_near_platform = false;
int is_player_near_platform2 = false;

short x_enemy = width - 2;
short y_enemy = y_player;

short do_x_enemy = x_enemy;
short do_y_enemy = y_enemy;

uint64_t time()
{
	return chrono::duration_cast<std::chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
}

int delay_flight = time() + 100;
int keystrokes_time = time() + 2000;

bool is_keystrokes = true;

bool is_enemy_draw = false;
bool b = true;
bool is_enemy_dead = false;
bool enemy_rose;

uint64_t fall_time = time() + 1000;

int jumps = 3; // кол-во прыжков
int jumpsCount = 0; // кол-во доступных прыжков

bool g = false;

void load()
{
	string line;
	ifstream in("C:\\Users\\User\\Desktop\\a.txt"); // окрываем файл для чтения
	if (in.is_open())
	{
		while (getline(in, line))
		{
			x_platforms.push_back(stoi(line));
			getline(in, line);
			x_platforms_width.push_back(stoi(line));
			getline(in, line);
			y_platforms.push_back(stoi(line));
		}
	}
	in.close();     // закрываем файл
	//cout << "End of program" << endl;
}

void draw_platforms()
{
	for (int a = 0; a < x_platforms.size(); a++)
	{
		if (y_cursor == y_platforms[a] && x_cursor == x_platforms[a])
		{
			for (int i = 0; i < x_platforms_width[a]; i++)
			{
				cout << "%";
				x_cursor++;
			}
		}
	}
	cout << " ";
	x_cursor++;
	fflush(stdout);
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
	while (x_cursor < width)  // 20 # в ряд
	{
		cout << "#";
		x_cursor++;
	}
}

bool is_player_on_any_platforms()
{
	bool platform_check = false;
	for (int i = 0; i < x_platforms.size(); i++)
	{
		bool x_correct = x_player >= x_platforms[i] && x_player < x_platforms_width[i] + x_platforms[i];
		if (x_correct == true && y_player + 1 == y_platforms[i])
		{
			platform_check = true;
		}
	}
	return platform_check;
}

bool is_player_under_any_platforms()
{
	bool platform_check2 = false;
	for (int i = 0; i < x_platforms.size(); i++)
	{
		bool x_correct = x_player >= x_platforms[i] && x_player < x_platforms_width[i] + x_platforms[i];
		if (x_correct == true && y_player - 1 == y_platforms[i])
		{
			platform_check2 = true;
		}
	}
	return platform_check2;
}

bool left_enemy()
{
	is_player_near_platform = false;
	for (int i = 0; i < x_platforms.size(); i++)
	{
		if (x_platforms[i] - 1 == x_player && y_platforms[i] == y_player)
		{
			is_player_near_platform = true;
		}
	}
	return is_player_near_platform;
}

bool right_enemy()
{
	is_player_near_platform2 = false;
	for (int i = 0; i < x_platforms.size(); i++)
	{
		if (x_platforms[i] + x_platforms_width[i] == x_player && y_platforms[i] == y_player)
		{
			is_player_near_platform2 = true;
		}
	}
	return is_player_near_platform2;
}

void player_fall()
{
	past_y_player = y_player;
	is_player_on_any_platforms();
	if (is_player_on_any_platforms() == true)
	{
		fall_time = time() + 400;
	}
	if (time() > fall_time && is_player_on_any_platforms() == false)
	{
		fall_time = time() + 1000;
		y_player++;
	}
}

void information_output()
{
	if (y_player == height - 1 || x_player == 0 || y_player == 0)
	{
		COORD position = { 0, 25 }; //позиция x и y
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, position);
		cout << "Вы проиграли";
		fflush(stdout);
		ExitProcess(0);
	}
	if (x_player >= width - 1)
	{
		COORD position = { 0, 25 }; //позиция x и y
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, position);
		cout << "Вы выйграли автомобиль";
		fflush(stdout);
		ExitProcess(0);
	}
	COORD position = { 0, 20 }; //позиция x и y
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position);
	cout << "x_player: " << x_player << " y_player: " << y_player;
	fflush(stdout);
}

void log()
{
	if (time() >= keystrokes_time)
	{
		is_keystrokes = false;
	}
	if (is_player_on_any_platforms() == true)
	{
		jumpsCount = jumps;
	}
	while (_kbhit()) // нажата ли клавиша
	{
		past_x_player = x_player;
		past_y_player = y_player;
		int checking_the_keyboard = _getch();
		if (right_enemy() == false)
		{
			if (checking_the_keyboard == 'a')
			{
				x_player--;
			}
		}
		if (left_enemy() == false)
		{
			if (checking_the_keyboard == 'd')
			{
				x_player++;
			}
		}
		if (is_player_under_any_platforms() == false)
		{
			if (checking_the_keyboard == 'w')
			{
				if (g == false)
				{
					is_keystrokes = true;
					past_y_player = y_player;
					if (jumpsCount > 0)
					{
						y_player--;
						jumpsCount--;
					}
					fall_time = time() + 1000;
					keystrokes_time = time() + 2000;
				}
				else if (g == true)
				{
					is_keystrokes = true;
					keystrokes_time = time() + 2000;
					y_player--;
				}
			}
		}
		if (is_player_on_any_platforms() == false)
		{
			if (checking_the_keyboard == 's')
			{
				keystrokes_time = time() + 2000;
				is_keystrokes = true;
				y_player++;
			}
		}
		if (checking_the_keyboard == 'x')
		{
			COORD position = { 0, 25 }; //позиция x и y
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleCursorPosition(hConsole, position);
			cout << "Почему.";
			fflush(stdout);
			ExitProcess(0);
		}
		if (checking_the_keyboard == 't')
		{
			COORD position = { 0, 21 }; //позиция x и y
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleCursorPosition(hConsole, position);
			string gc_gs;
			cin >> gc_gs;
			if (gc_gs == "gc")
			{
				g = true;
			}
			if (gc_gs == "gs")
			{
				g = false;
			}
			position = { 0, 21 }; //позиция x и y
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleCursorPosition(hConsole, position);
			cout << "                     ";
			fflush(stdout);
		}
	}
	for (int i = 0; i < x_platforms.size(); i++)
	{
		if (x_enemy == x_platforms[i] + x_platforms_width[i] && y_enemy == y_platforms[i])
		{
			y_enemy--;
			enemy_rose = true;
		}
		else if (x_enemy == x_platforms[i] - 1 && y_enemy + 1 == y_platforms[i] && enemy_rose == true)
		{
			y_enemy++;
			enemy_rose = false;
		}
	}
	if (is_keystrokes == false || is_enemy_draw == true)
	{
		if (b == true)
		{
			y_enemy = y_player;
			x_enemy = x_player + 10;
			b = false;
			is_enemy_dead = false;
			if (x_enemy >= 78)
			{
				x_enemy = 78;
			}
		}
		is_enemy_draw = true;
		if (time() > delay_flight)
		{
			do_x_enemy = x_enemy;
			do_y_enemy = y_enemy;
			delay_flight = time() + 150;
			x_enemy--;
		}
	}
	information_output();
}

void draw_enemy()
{
	if (do_x_enemy == x_enemy && do_y_enemy == y_enemy)
	{

	}
	else if (x_enemy <= 0 && is_enemy_dead == false)
	{
		COORD position = { 1, do_y_enemy }; //позиция x и y
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, position);
		cout << ' ';
		fflush(stdout);
		position = { 0, y_enemy }; //позиция x и y
		SetConsoleCursorPosition(hConsole, position);
		cout << '#';
		fflush(stdout);
		is_enemy_dead = true;
		is_enemy_draw = false;
		b = true;
	}
	else if (is_enemy_dead == false)
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
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	load();
	draw();
	while (1)
	{
		log();
		draw_player();
		draw_enemy();
		if (g == false)
		{
			player_fall();
		}
	}
}