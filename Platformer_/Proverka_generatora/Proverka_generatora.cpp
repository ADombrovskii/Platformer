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

vector<int>x_platforms_width;
vector<int>y_platforms;
vector<int>x_platforms;

int main()
{
	/*uniform_int_distribution<> ot_do(2, 4);
	for (int i = 0; i < 15; i++)
	{
		y_platforms.push_back(ot_do(gen));
		cout << y_platforms[i] << " ";
	}
	*/
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
		x_platforms[o] = x_platforms_width[o] + 3; // 1 создание каординаты на которой будет находится 2 платформа (1 кардината + ширина 1 каординаты + пробел из 2 + 1)
		o = 2;
		while (o < 15)
		{
			x_platforms[o] = x_platforms[o - 1] + x_platforms_width[o - 1] + 2;
			o++;
		}
		o = 0;
		while (o < 15)
		{
			cout << x_platforms[o] << " ";
			o++;
		}
}