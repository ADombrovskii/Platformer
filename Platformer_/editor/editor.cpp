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

ofstream out;

int b = 0;

const int width = 80;
int height = 20;

int x_cursor = 0;
int y_cursor = 0;

int do_x_platform_width;

struct Platform
{
	int x;
	int y;
	int xw;
};

Platform platform;
vector<Platform>platforms;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

bool a = false;

int _platform_width;

void editor(HANDLE hStdin, bool o)
{
	const short bufferSize = 128;
	INPUT_RECORD IrInBuf[bufferSize];
	DWORD cNumRead = 0;
	BOOL peekSuccessful = PeekConsoleInput(hStdin, IrInBuf, bufferSize, &cNumRead);
	if (cNumRead > 0) {
		ReadConsoleInput(hStdin, IrInBuf, bufferSize, &cNumRead);
		//cout << cNumRead << "\n";
		MOUSE_EVENT_RECORD Event_Mouse;
		for (DWORD i = 0; i < cNumRead; i++)
		{
			if (IrInBuf[i].EventType == MOUSE_EVENT)
			{
				Event_Mouse = IrInBuf[i].Event.MouseEvent;
				if (Event_Mouse.dwEventFlags == 0 && Event_Mouse.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
				{
					platform.x = Event_Mouse.dwMousePosition.X;
					platform.y = Event_Mouse.dwMousePosition.Y;
					a = true;
				}
				if (Event_Mouse.dwEventFlags == MOUSE_MOVED) // ПРОВЕРЯЕТ СВЯЗАНО СОБЫТИЕ ЛИ С ДВИЖЕНИЕМ
				{
					if (a == true)
					{
						do_x_platform_width = platform.xw;
						platform.xw = Event_Mouse.dwMousePosition.X - platform.x + 1;
						platforms.push_back(platform);
						_platform_width = platform.x - Event_Mouse.dwMousePosition.X;
						if (_platform_width < 0)
						{
							_platform_width = 0;
						}
					}
				}
				if (Event_Mouse.dwEventFlags == 0 && Event_Mouse.dwButtonState == 0)
				{
					//platform.xw = Event_Mouse.dwMousePosition.X - platform.x + 1;
					//platforms.push_back(platform);

					/*cout << "x_platforms = " << platform.x << " y_platforms = " << platform.y << endl;
					cout << "x_platforms_width = " << platform.xw;

					if (b == 0)
					{
						out << platforms[platforms.size() - 1].x;
						out << endl << platforms[platforms.size() - 1].xw;
						out << endl << platforms[platforms.size() - 1].y;
						out.flush();
						b = 1;
					}
					else
					{
						out << endl << platforms[platforms.size() - 1].x;
						out << endl << platforms[platforms.size() - 1].xw;
						out << endl << platforms[platforms.size() - 1].y;
						out.flush();
					}*/
					cout << "x_platforms = " << platform.x << " y_platforms = " << platform.y << endl;
					cout << "x_platforms_width = " << platform.xw << endl;
					cout << "x_platforms = " << platform.x - abs(_platform_width) << " y_platforms = " << platform.y << endl;
					cout << "x_platforms_width = " << platform.xw + abs(_platform_width);

					if (b == 0)
					{
						out << platforms[platforms.size() - 1].x - abs(_platform_width);
						out << endl << platforms[platforms.size() - 1].xw + abs(_platform_width);
						out << endl << platforms[platforms.size() - 1].y;
						out.flush();
						b = 1;
					}
					else
					{
						out << endl << platforms[platforms.size() - 1].x - abs(_platform_width);
						out << endl << platforms[platforms.size() - 1].xw + abs(_platform_width);
						out << endl << platforms[platforms.size() - 1].y;
						out.flush();
					}
					a = false;
					//cout << "Вы отпустили мышь";
				}
				//if (Event_Mouse.dwEventFlags == DOUBLE_CLICK)
				//{
				//	cout << "Двойное нажатие левой кнопки мыши\n";
				//}
			}
		}
	}
}

void draw_platforms(Platform a, int b, int c)
{
	for (int i = 0; i < a.xw; i++)
	{
		COORD position = { short(a.x + i), short(a.y) }; //позиция x и y
		SetConsoleCursorPosition(hConsole, position);
		cout << '%';
		fflush(stdout);
	}
	for (int i = 0; i < b; i++)
	{
		COORD position = { short(a.x - i), short(a.y) }; //позиция x и y
		SetConsoleCursorPosition(hConsole, position);
		cout << '%';
		fflush(stdout);
	}
	for (int i = 0; i < c - a.xw; i++)
	{
		COORD position = { short(a.x + a.xw + i), short(a.y) }; //позиция x и y
		SetConsoleCursorPosition(hConsole, position);
		cout << ' ';
		fflush(stdout);
	}
	COORD position = { 0, 20 }; //позиция x и y
	SetConsoleCursorPosition(hConsole, position);
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
			cout << " ";
			x_cursor++;
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

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD fdvMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin, fdvMode);
	int o = 0;
	bool p = true;
	draw();
	out.open("C:\\Users\\user\\Desktop\\a.txt");
	while (1)
	{
		if (p == true)
		{
			editor(hStdin, o);
			if (platforms.size() >= 1)
			{
				p = false;
			}
		}
		else
		{
			draw_platforms(platforms[platforms.size() - 1], _platform_width, do_x_platform_width);
			p = true;
		}
	}
}