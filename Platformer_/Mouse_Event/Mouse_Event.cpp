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

int x_player;
int y_player;

int do_x_player;
int do_y_player;

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD fdvMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin, fdvMode);
	bool a = false;
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
						do_x_player = Event_Mouse.dwMousePosition.X;
						do_y_player = Event_Mouse.dwMousePosition.Y;
						cout << "do_x_player = " << do_x_player << " do_y_player = " << do_y_player << endl;
						//cout << do_x_player;// координаты по пробелам в консоли (координаты определяются так же как и в Платформере)
						//cout << do_y_player;// координаты по пробелам в консоли (координаты определяются так же как и в Платформере)
					}
					if (Event_Mouse.dwEventFlags == 0 && Event_Mouse.dwButtonState == 0 && a == true)////////////////////
					{
						cout << "Нажата левая кнопка мыши\n";
						x_player = Event_Mouse.dwMousePosition.X;
						y_player = Event_Mouse.dwMousePosition.Y;
						cout << "x_player = " << x_player << " y_player = " << y_player << endl;
						//cout << "Вы отпустили мышь";
					}
					/*if (Event_Mouse.dwEventFlags == DOUBLE_CLICK)
					{
						cout << "Двойное нажатие левой кнопки мыши\n";
					}*/
				}
			}
		}
	}
}