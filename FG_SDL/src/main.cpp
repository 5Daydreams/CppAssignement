#include <stdio.h>
#include <iostream>
#include <SDL/SDL.h>
#include <stdlib.h>
#include "Library/Vector3.h"

int main()
{
	Vector3 thing1;
	thing1.x = 1;
	thing1.y = 0;
	thing1.z = 0;

	Vector3 thing2;
	thing2.x = 1;
	thing2.y = 1;
	thing2.z = 1;

	Vector3 thing3 = (thing1 * 3) - (thing2 * 2);

	std::cout << "Vector result = " << thing3.x << "," << thing3.y << "," << thing3.z << std::endl;
	std::cout << "Dot result = " << VectorDot(thing1, thing2) << std::endl;

	return 0;

	SDL_Init(SDL_INIT_EVERYTHING);

	// Title, x, y, width, height, flags
	SDL_Window* wnd = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
	SDL_Renderer* render = SDL_CreateRenderer(wnd, -1, SDL_RENDERER_ACCELERATED);

	float x = 0;
	float y = 0;

	bool pressing_w = false;
	bool pressing_a = false;
	bool pressing_s = false;
	bool pressing_d = false;

	Uint64 prevTicks = SDL_GetPerformanceCounter();

	// To keep the program running:
	bool running = true;
	while (running)
	{
		// Get kernel ticks
		Uint64 ticks = SDL_GetPerformanceCounter();

		Uint64 deltaTicks = ticks - prevTicks;
		printf("delta ticks= %lld\n", deltaTicks);
		prevTicks = ticks;

		float deltaSeconds = (float)deltaTicks / SDL_GetPerformanceFrequency();
		printf("delta time = %f\n", deltaSeconds);
		printf("FPS = %f\n", 1.0f / deltaSeconds);

		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
			{
				running = false;
				break;
			}
			case SDL_KEYDOWN:
			{
				int scancode = event.key.keysym.scancode;
				if (scancode == SDL_SCANCODE_ESCAPE)
				{
					running = false;
				}

				if (scancode == SDL_SCANCODE_D)
				{
					pressing_d = true;
				}
				if (scancode == SDL_SCANCODE_A)
				{
					pressing_a = true;
				}
				if (scancode == SDL_SCANCODE_W)
				{
					pressing_w = true;
				}
				if (scancode == SDL_SCANCODE_S)
				{
					pressing_s = true;
				}

				break;
			}
			case SDL_KEYUP:
			{
				int scancode = event.key.keysym.scancode;

				if (scancode == SDL_SCANCODE_W)
				{
					pressing_w = false;
				}
				if (scancode == SDL_SCANCODE_A)
				{
					pressing_a = false;
				}
				if (scancode == SDL_SCANCODE_S)
				{
					pressing_s = false;
				}
				if (scancode == SDL_SCANCODE_D)
				{
					pressing_d = false;
				}
			}

			}
		}

		float speed = 32 * deltaSeconds;

		if (pressing_w)
		{
			y -= speed;
		}
		if (pressing_a)
		{
			x -= speed;
		}
		if (pressing_s)
		{
			y += speed;
		}
		if (pressing_d)
		{
			x += speed;
		}

		SDL_SetRenderDrawColor(render, 20, 20, 30, 255); // #FF00FFFF
		SDL_RenderClear(render);

		SDL_SetRenderDrawColor(render, rand() & 0xFF, rand() & 0xFF, rand() & 0xFF, 255);
		// SDL_SetRenderDrawColor(render, 200, 0, 20, 255);

		SDL_RenderPresent(render);

		SDL_Rect rect = { (int)x, (int)y, 32, 32 };

		SDL_RenderFillRect(render, &rect);

		SDL_RenderPresent(render);

		// SDL_Delay(16);
	}
}