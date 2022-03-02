#include <stdio.h>
#include <iostream>
#include <SDL/SDL.h>
#include <stdlib.h>
#include "Library/Vector3.h"
#include "engine.h"
#include "player.h"
#include "game.h"


void SDFCheck()
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
}

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	// Title, x, y, width, height, flags
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	bool running = true;
	Uint64 prevTicks = SDL_GetPerformanceCounter();

	// To keep the program running:
	while (running)
	{
		// Get kernel ticks
		Uint64 ticks = SDL_GetPerformanceCounter();
		Uint64 deltaTicks = ticks - prevTicks;
		prevTicks = ticks;
		deltaTime = (float)deltaTicks / SDL_GetPerformanceFrequency();

		SDL_Event event;
		while (SDL_PollEvent(&event))
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

				keys[scancode] = true;

				break;
			}
			case SDL_KEYUP:
			{
				int scancode = event.key.keysym.scancode;
				keys[scancode] = false;

				break;
			}

			}
		}

		SDL_SetRenderDrawColor(render, 20, 20, 30, 255); // #FF00FFFF
		SDL_RenderClear(render);

		player.update();
		player.draw();

		projectile.update();
		projectile.draw();

		SDL_RenderPresent(render);

		SDL_Delay(16);
	}
}