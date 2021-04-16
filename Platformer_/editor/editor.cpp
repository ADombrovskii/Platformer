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
						cout << "x_platforms = " << platform.x << " y_platforms = " << platform.y << endl;
						platform.x = Event_Mouse.dwMousePosition.X; ////////////////////////////
						platform.y = Event_Mouse.dwMousePosition.Y; ////////////////////////////
						a = true;
					}
					if (Event_Mouse.dwEventFlags == MOUSE_MOVED) // ПРОВЕРЯЕТ СВЯЗАНО СОБЫТИЕ ЛИ С ДВИЖЕНИЕМ
					{
						if (a == true)
						{
							platform.xw = Event_Mouse.dwMousePosition.X - platform.x + 1;
							platforms.push_back(platform);
						}
					}
					if (Event_Mouse.dwEventFlags == 0 && Event_Mouse.dwButtonState == 0)
					{
						//platform.xw = Event_Mouse.dwMousePosition.X - platform.x + 1;
						//platforms.push_back(platform);
						cout << "x_platforms_width = " << platform.xw << endl;
						cout << "Нажата левая кнопка мыши\n";

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

void draw_platforms(Platform a)
{
	for (int i = 0; i < a.xw; i++)
	{
		COORD position = { short(a.x + i), short(a.y) }; //позиция x и y
		SetConsoleCursorPosition(hConsole, position);
		cout << '%';
		fflush(stdout);
	}
	COORD position = { 0, 21 }; //позиция x и y
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
			draw_platforms(platforms[platforms.size() - 1]);
			p = true;
		}
	}
}