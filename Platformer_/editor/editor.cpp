/*#include <vector>
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

vector<int>x_platforms;
vector<int>x_platforms_width;
vector<int>y_platforms;

void editor()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD fdvMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin, fdvMode);
	bool a = false;
	int o = 0;
	while (1)
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
						a = true;
						//cout << "Нажата левая кнопка мыши\n";
						x_platforms.push_back(Event_Mouse.dwMousePosition.X);
						y_platforms.push_back(Event_Mouse.dwMousePosition.Y);
						cout << "x_platforms = " << x_platforms[o] << " y_platforms = " << y_platforms[o] << endl;
						//cout << do_x_player;// координаты по пробелам в консоли (координаты определяются так же как и в Платформере)
						//cout << do_y_player;// координаты по пробелам в консоли (координаты определяются так же как и в Платформере)
					}
					if (Event_Mouse.dwEventFlags == 0 && Event_Mouse.dwButtonState == 0 && a == true)////////////////////
					{
						x_platforms_width.push_back(Event_Mouse.dwMousePosition.X - x_platforms[o] + 1);
						cout << "x_platforms_width = " << x_platforms_width[o] << endl;
						cout << "Нажата левая кнопка мыши\n";
						a = false;
						o++;
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
}

int main()
{
	editor();
}*/

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

vector<int>x_platforms;
vector<int>x_platforms_width;
vector<int>y_platforms;

ofstream out;

int b = 0;
int number_of_platforms = 3;

void editor()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD fdvMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin, fdvMode);
	bool a = false;
	int o = 0;
	out.open("C:\\Users\\User\\Desktop\\a.txt");
	while (1)
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
						a = true;
						//cout << "Нажата левая кнопка мыши\n";
						x_platforms.push_back(Event_Mouse.dwMousePosition.X);
						y_platforms.push_back(Event_Mouse.dwMousePosition.Y);
						cout << "x_platforms = " << x_platforms[o] << " y_platforms = " << y_platforms[o] << endl;
						//cout << do_x_player;// координаты по пробелам в консоли (координаты определяются так же как и в Платформере)
						//cout << do_y_player;// координаты по пробелам в консоли (координаты определяются так же как и в Платформере)
					}
					if (Event_Mouse.dwEventFlags == 0 && Event_Mouse.dwButtonState == 0 && a == true)////////////////////
					{
						x_platforms_width.push_back(Event_Mouse.dwMousePosition.X - x_platforms[o] + 1);
						cout << "x_platforms_width = " << x_platforms_width[o] << endl;
						cout << "Нажата левая кнопка мыши\n";

						if (b == 0)
						{
							out << x_platforms[o];
							out << endl << x_platforms_width[o];
							out << endl << y_platforms[o];
							out.flush();
							b = 1;
						}
						else
						{
							out << endl << x_platforms[o];
							out << endl << x_platforms_width[o];
							out << endl << y_platforms[o];
							out.flush();
						}
						number_of_platforms--;
						if (number_of_platforms == 0)
						{
							out.close();
							ExitProcess(0);
						}
						a = false;
						o++;
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
}

int main()
{
	editor();
}