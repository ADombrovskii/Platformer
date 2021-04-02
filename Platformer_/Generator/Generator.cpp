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

vector<int>x_platforms_width;
vector<int>y_platforms;
vector<int>x_platforms;

random_device rd;
mt19937 gen(rd());

const int width = 80;
int height = 20;

int number_of_platforms = 15;

void x_generator()
{
	int a = x_platforms.size();
	uniform_int_distribution<> ot_do(3, 5);

	x_platforms.push_back(1); // 0 создание каординаты на которой будет находится 1 платформа

	for (int i = 0; i < number_of_platforms; i++) // ширина платформ от 3 до 5
	{
		x_platforms_width.push_back(ot_do(gen));
		if (i + 1 < number_of_platforms)
		{
			x_platforms.push_back(x_platforms[i] + x_platforms_width[i] + 2);
			if (x_platforms[i] + x_platforms_width[i] >= width - 2)
			{
				x_platforms_width[i] = width - 2 - x_platforms[i];
			}
		}
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

int main()
{
	x_generator();
	y_generator();

	ofstream out;          // поток для записи
	out.open("C:\\Users\\User\\Desktop\\a.txt"); // окрываем файл для записи
	if (out.is_open())
	{
		for (int i = 0; i < number_of_platforms; i++)
		{
			if (i <= 13)
			{
				out << x_platforms[i] << endl;
				out << x_platforms_width[i] << endl;
				out << y_platforms[i] << endl;
			}
			else
			{
				out << x_platforms[i] << endl;
				out << x_platforms_width[i] << endl;
				out << y_platforms[i];
			}
		}
	}

	cout << "End of program" << endl;
	return 0;
}