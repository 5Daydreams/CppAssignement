#include <stdio.h>
#include <iostream>
#include <SDL/SDL.h>
#include <stdlib.h>
#include "engine.h"
#include "player.h"
#include "game.h"


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