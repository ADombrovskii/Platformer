#include <SDL.h>
#include <cstdlib>
#include <iostream>


#include <vector>
#include <Windows.h>
#include <math.h>
#include <iomanip>
#include <conio.h>
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

const int width = 1080;
const int height = 480;
const int delay = 1;
int travel_time = 0;

const int number_of_platforms = 100;

string key_lock; // блокирока клавиш

int camera_offset = 0;

uint64_t time()
{
	return chrono::duration_cast<std::chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
}

void x_generator()
{
	uniform_int_distribution<> ot_do(30, 50);

	x_platforms.push_back(0); // 0 создание каординаты на которой будет находится 1 платформа

	for (int i = 0; i < number_of_platforms; i++) // ширина платформ от 3 до 5
	{
		x_platforms_width.push_back(ot_do(gen));
		x_platforms.push_back(x_platforms[i] + x_platforms_width[i] + 20);
	}
}

void y_generator()
{
	uniform_int_distribution<> ot_do(30, 50);
	for (int i = 0; i < number_of_platforms; i++)
	{
		y_platforms.push_back(ot_do(gen));
		y_platforms[i] = height - y_platforms[i] - 1;
	}
}

int keydown;
vector<int>visible_platforms;

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian");

	x_generator();
	y_generator();

	SDL_Window* window = NULL;
	window = SDL_CreateWindow
	(
		"Sasha", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_SHOWN
	);

	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	SDL_Event e;
	bool quit = false;

	SDL_Rect player = { width / 2, height / 2, 20, 20 };
	SDL_Rect platform = { x_platforms[0], y_platforms[0], x_platforms_width[0], -10 };
	SDL_Rect next_player = { player.x, player.y, player.w, player.h };

	int x_player_direction = 0;
	int y_player_direction = 0;

	bool keyup_or_keydown = false;

	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN)
			{
				if (keyup_or_keydown == false)
				{
					if (e.key.keysym.sym == SDLK_w) { y_player_direction = -1; keydown = time(); }
					else if (e.key.keysym.sym == SDLK_s) { y_player_direction = 1; keydown = time(); }
					else if (e.key.keysym.sym == SDLK_a) { x_player_direction = -1; keydown = time(); }
					else if (e.key.keysym.sym == SDLK_d) { x_player_direction = 1; keydown = time(); }
					cout << "keydown" << endl;
					keyup_or_keydown = true;
				}
			}
			if (e.type == SDL_KEYUP)
			{
				if (keyup_or_keydown == true)
				{
					if (e.key.keysym.sym == SDLK_w) { y_player_direction = 0; }
					else if (e.key.keysym.sym == SDLK_s) { y_player_direction = 0; }
					else if (e.key.keysym.sym == SDLK_a) { x_player_direction = 0; }
					else if (e.key.keysym.sym == SDLK_d) { x_player_direction = 0; }
					keyup_or_keydown = false;
					cout << "keyup" << endl;
				}
			}
			if (e.type == SDL_QUIT) { quit = true; }
		}

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderClear(renderer);
		if (keyup_or_keydown == true) 
		{
			if (time() > travel_time)
			{
				bool first_visible_platform = false;
				for (int i = 0; i < number_of_platforms; i++)
				{
					if ((x_platforms[i] - camera_offset) + x_platforms_width[i] >= 0 && platform.x <= x_platforms[i] - camera_offset)
					{
						if (!first_visible_platform && i > 0)
						{
							visible_platforms.push_back(i - 1);
							first_visible_platform = true;
						}
						visible_platforms.push_back(i); 
						if (x_platforms[i + 1] - camera_offset > width && i + 1 < x_platforms.size())
						{
							visible_platforms.push_back(i + 1);
							break;
						}
					}
					SDL_Rect next_player = { player.x + x_player_direction, player.y + y_player_direction, player.w, player.h };
					if (SDL_HasIntersection(&next_player, &platform))
					{
						x_player_direction = 0;
						y_player_direction = 0;
					}
				}

				camera_offset += x_player_direction;
				player.y += y_player_direction;
				travel_time = time() + 1;
			}
		}

		cout << visible_platforms.size() << endl;
		for (int i = 0; i < visible_platforms.size(); i++)
		{
			int x_pl = x_platforms[visible_platforms[i]] - camera_offset;
			int y_pl = y_platforms[visible_platforms[i]];
			int w_pl = x_platforms_width[visible_platforms[i]];
			int h_pl = 10;
			platform = { x_pl, y_pl, w_pl, h_pl };

			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			SDL_RenderFillRect(renderer, &platform);
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderFillRect(renderer, &player);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}